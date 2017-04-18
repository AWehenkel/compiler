#include "BinaryOperatorNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

BinaryOperatorNode::~BinaryOperatorNode(){delete e_left_operand; delete e_right_operand;}

string BinaryOperatorNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  return "BinOp(" + (literal_op_table.find(e_op))->second + ", "  + e_left_operand->getLiteral(with_type) +  ", " + e_right_operand->getLiteral(with_type) + ")" + type;
}

int BinaryOperatorNode::updateType(){

  // Get the types of the two operands
  TypeIdentifierNode* left_type = e_left_operand->getType();
  TypeIdentifierNode* right_type = e_right_operand->getType();
  if(!left_type || !right_type){
    cerr << "Error in the compiler in BinaryOperatorNode : left_type or right_type is null" << endl;
    return -1;
  }
  string s_left_type = left_type->getLiteral();
  string s_right_type = right_type->getLiteral();

  switch (e_op){
    case BinaryOperator::b_op_and :
      // Check both operands are bools or errors and return a bool if ok
      if ((s_left_type != "bool" && s_left_type != "error") || (s_right_type != "bool" && s_right_type != "error")){
        cerr << "Les deux membres ne sont pas des booleans dans binary" << endl;
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return -1;
      }
      node_type = left_type;
      break;
    case BinaryOperator::b_op_equal :
      // Check if the two types are the same (or errors) and return bool if ok
      if(s_left_type != "error" && s_right_type != "error" && s_left_type != s_right_type){
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return -1;
      }
      node_type = new TypeIdentifierNode("bool");
      self_type = true;
      break;
    case BinaryOperator::b_op_leq :
    case BinaryOperator::b_op_less :
      // Check both operands are int32 or errors and return a bool if ok
      if ((s_left_type != "int32" && s_left_type != "error" != 0) || (s_right_type != "int32" && s_right_type != "error")){
        cerr << "Les deux membres ne sont pas des ints dans binary" << endl;
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return -1;
      }
      node_type = new TypeIdentifierNode("bool");
      self_type = true;
      break;
    default :
      // Check both operands are int32 and return a int32 if ok
      if ((s_left_type != "int32" && s_left_type != "error") || (s_right_type != "int32" && s_right_type != "error")){
        cerr << "Les deux membres ne sont pas des ints dans binary" << endl;
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return -1;
      }
      node_type = left_type;
  }

  return 0;
}
