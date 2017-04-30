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
  int counter = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  string code, to_ret = "%" + to_string(counter++);

  switch (node->getOperator()) {
    case b_op_and :
      code = to_ret + " = and i1 " + op1 + ", "  + op2;
      break;
    case b_op_minus :
      code = to_ret + " = sub i32 " + op1 + ", "  + op2;
      break;
    case b_op_less :
      code = to_ret + " = slt i32 " + op1 + ", "  + op2;
      break;
    case b_op_leq :
      code = to_ret + " = sle i32 " + op1 + ", "  + op2;
      break;
    case BinaryOperator::b_op_plus :
      code = to_ret + " = add nuw i32 " + op1 + ", "  + op2;
      break;
    case b_op_equal :
      //TODO Change to handle other type than int32.
      code = to_ret + " = eq i32 " + op1 + ", "  + op2;
      break;
    case b_op_times :
      code = to_ret + " = mul i32 " + op1 + ", "  + op2;
      break;
    case b_op_div :
      code = to_ret + " = sdiv i32 " + op1 + ", "  + op2;
      break;
    case b_op_pow :
      string tmp1 = "%" + to_string(counter++), tmp2 = "%" + to_string(counter++);

      code = tmp1 + " = sitofp i32 " + op1 + " to float\n";
      code += tmp2 + " = call float @llvm.powi.f32(float " + tmp1 + ", i32 " + op2 + ")\n";
      code += to_ret + " = fptosi float " + tmp2 + " to i32";
      break;
  }
  llvm_address_counteurs.push(counter);
  code += "\n" + getLLVMStoreCode(to_ret, node->getLLVMAddress(), "i32");
  return code;
}



int CodeGenVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node){

  ExpressionNode* left = node->getLeft();
  ExpressionNode* right = node->getRight();

  // VIsit the children nodes
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  left->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(left->getLLVMAddress(), left->getLLVMType());
  llvm_address_counteurs.push(counteur);
  if (left->accept(this) < 0)
    return -1;

  counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  right->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(right->getLLVMAddress(), right->getLLVMType());
  llvm_address_counteurs.push(counteur);
  if (right->accept(this) < 0)
    return -1;

  counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  string llvm_address_3 = "%" + to_string(counteur++);
  string llvm_address_4 = "%" + to_string(counteur++);
  llvm_address_counteurs.push(counteur);
  ir += getLLVMLoadCode(llvm_address_3, left->getLLVMAddress(), left->getLLVMType());
  ir += getLLVMLoadCode(llvm_address_4, right->getLLVMAddress(), right->getLLVMType());
  ir += getLLVMBinaryCode(node, llvm_address_3, llvm_address_4);

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

//TODO Changer les constructeur de LiteralNode et faire en sorte de prendre en charge correctement les literaux.
int CodeGenVisitor::visitLiteralNode(LiteralNode *node){
  ir += getLLVMStoreCode(node->getLiteral(), node->getLLVMAddress(), node->getLLVMType());
  return 0;
}

int CodeGenVisitor::visitProgramNode(ProgramNode* node){
  llvm_address_counteurs.push(0);
  Visitor::visitProgramNode(node);
  cout << "IR: " << ir << endl;
  return 0;
}
