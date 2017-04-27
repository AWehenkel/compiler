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


string CodeGenVisitor::getLLVMBinaryCode(BinaryOperatorNode* node, string op1, string op2){
  string code;
  switch (node) {
    case BinaryOperatorNode::b_op_plus :
      // TODO : checker nsw ou nuw
      code = node->getLLVMAddress() + " = and " + node->getType() + " " + op1 + ", " op2;
  }
  return code;
}



int CodeGenVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node){

  ExpressionNode* left = node->getLeft();
  ExpressionNode* right = node->getRight();

  // VIsit the children nodes
  int counteur = llvm_address_counteurs.pop();
  left->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(left->getLLVMAddress(), left->getType()->getLiteral())
  if (left->accept(this) < 0)
    return -1;

  right->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(right->getLLVMAddress(), right->getType()->getLiteral())
  if (right->accept(this) < 0)
    return -1;

  string llvm_address_3 = "%" + counteur++;
  string llvm_address_4 = "%" + counteur++;
  ir += getLLVMLoadCode(llvm_address_3, left->getLLVMAddress(), left->getType()->getLiteral());
  ir += getLLVMLoadCode(llvm_address_4, right->getLLVMAddress(), right->getType()->getLiteral());
  ir += getLLVMBinaryCode(node, llvm_address_3, llvm_address_4);

  llvm_address_counteurs.push(counteur);

  return 0;
}

int CodeGenVisitor::visitBlockNode(BlockNode* node){

  vector<ExpressionNode*> expresions = node->getExpressions();

}
