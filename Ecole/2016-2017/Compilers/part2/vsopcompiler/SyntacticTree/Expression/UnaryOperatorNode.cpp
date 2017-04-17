#include "UnaryOperatorNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

UnaryOperatorNode::~UnaryOperatorNode(){delete e_operand;}

string UnaryOperatorNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  return "UnOp(" + (literal_op_table.find(e_op))->second + ","  + e_operand->getLiteral(with_type) + ")" + type;
}

int UnaryOperatorNode::updateType(){

  // Get the type of the operand
  TypeIdentifierNode* op_type = e_operand->getType();
  if(!op_type){
    cerr << "Error in the compiler in UnaryOperatorNode : op_type is null" << endl;
    return -1;
  }
  string s_op_type = op_type->getLiteral();

  switch (e_op){
    case UnaryOperator::u_op_not :
      // Check if operand is bools and return operand type if ok
      if (s_op_type != "error" && s_op_type != "bool"){
        cerr << "Le membre du not n'est pas un boolean dans unary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      node_type = op_type;
      break;
    case UnaryOperator::u_op_isnull :
      // Check if it not a basic type and return bool if ok
      if (s_op_type == "bool" || s_op_type == "int32" || s_op_type == "string"){
        cerr << "Le membre du isnull n'est pas une classe dans unary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      node_type = new TypeIdentifierNode("bool");
      break;
    case UnaryOperator::u_op_minus :
      // Check if operand is int32 and return operand type if ok
      if (s_op_type != "error" && s_op_type != "int32"){
        cerr << "Le membre du minus n'est pas un int dans unary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      node_type = op_type;
      break;
  }

  return 0;
}
