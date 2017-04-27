#include <vector>

#include "CodeGenVisitor.hpp"
#include "all_headers.hpp"

using namespace std;

// TODO : attention ça peut changer
string CodeGenVisitor::getLLVMAllocationCode(string name, string type){
  return name + " = alloca " + type + "\n";
}

// TODO : attention au types
string CodeGenVisitor::getLLVMLoadCode(string load_in, string load_from, string type){
  return load_in + " = load " + type + ", " + type + "* " + load_from + "\n";
}

string CodeGenVisitor::getLLVMStoreCode(string name, string store_address, string type){
  return "store " + type + " " + name + ", " +  type + "* " + store_address + "\n";
}


string CodeGenVisitor::getLLVMBinaryCode(BinaryOperatorNode* node, string op1, string op2){
  string code;
  switch (node->getOperand()) {
    case BinaryOperator::b_op_plus :
      // TODO : checker nsw ou nuw
      code = node->getLLVMAddress() + " = add " + node->getType()->getLiteral() + " " + op1 + ", "  + op2 + "\n";
  }
  return code;
}



int CodeGenVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node){

  ExpressionNode* left = node->getLeft();
  ExpressionNode* right = node->getRight();

  // VIsit the children nodes
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  left->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(left->getLLVMAddress(), left->getType()->getLiteral());
  llvm_address_counteurs.push(counteur);
  if (left->accept(this) < 0)
    return -1;

  counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  right->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(right->getLLVMAddress(), right->getType()->getLiteral());
  llvm_address_counteurs.push(counteur);
  if (right->accept(this) < 0)
    return -1;

  counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  string llvm_address_3 = "%" + to_string(counteur++);
  string llvm_address_4 = "%" + to_string(counteur++);
  ir += getLLVMLoadCode(llvm_address_3, left->getLLVMAddress(), left->getType()->getLiteral());
  ir += getLLVMLoadCode(llvm_address_4, right->getLLVMAddress(), right->getType()->getLiteral());
  ir += getLLVMBinaryCode(node, llvm_address_3, llvm_address_4);
  llvm_address_counteurs.push(counteur);

  return 0;
}

int CodeGenVisitor::visitBlockNode(BlockNode* node){

  vector<ExpressionNode*> expresions = node->getExpressions();
  ExpressionNode* first = *(expresions.begin());
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  first->setLLVMAddress(counteur++);
  llvm_address_counteurs.push(counteur);
  Visitor::visitBlockNode(node);
  return 0;
}

int CodeGenVisitor::visitLiteralNode(LiteralNode *node){
  ir += getLLVMStoreCode(node->getLiteral(), node->getLLVMAddress(), node->getType()->getLiteral());
  return 0;
}

int CodeGenVisitor::visitProgramNode(ProgramNode* node){
  llvm_address_counteurs.push(0);
  Visitor::visitProgramNode(node);
  cout << "IR: " << ir << endl;
  return 0;
}
