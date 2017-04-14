#include <cstring>

#include "UnaryOperatorNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

int UnaryOperatorNode::updateType(){
  // Get the types of the two operands
  TypeIdentifierNode* op_type = e_operand->getType();
  if(!op_type){
    cerr << "Error in the compiler in UnaryOperatorNode : op_type is null" << endl;
    return -1;
  }
  string s_op_type = op_type->getLiteral();

  switch (e_op){
    case UnaryOperator::u_op_not :
      // Check if operand is bools and return a bool if ok
      if (strcmp(s_op_type.c_str(), "error") != 0 && strcmp(s_op_type.c_str(), "bool") != 0){
        cerr << "Le membre du not n'est pas un booléan dans unary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      node_type = new TypeIdentifierNode("bool");
      break;
    case UnaryOperator::u_op_isnull :
      // Check if it not a basic type
      if (strcmp(s_op_type.c_str(), "bool") == 0 || strcmp(s_op_type.c_str(), "int32") == 0 || strcmp(s_op_type.c_str(), "string") == 0){
        cerr << "Le membre du isnull n'est pas une classe dans unary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      node_type = new TypeIdentifierNode(s_op_type);
      break;
    case UnaryOperator::u_op_minus :
    // Check if operand is int32 and return a bool if ok
    if (strcmp(s_op_type.c_str(), "error") != 0 && strcmp(s_op_type.c_str(), "int32") != 0){
      cerr << "Le membre du minus n'est pas un int dans unary" << endl;
      node_type = new TypeIdentifierNode("error");
      return -1;
    }
    node_type = new TypeIdentifierNode("int32");
    break;
      break;
  }

  return 0;
}

UnaryOperatorNode::~UnaryOperatorNode(){delete e_operand;}

string UnaryOperatorNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : "";
  return "UnOp(" + (literal_op_table.find(e_op))->second + ","  + e_operand->getLiteral() + ")" + type;
}
