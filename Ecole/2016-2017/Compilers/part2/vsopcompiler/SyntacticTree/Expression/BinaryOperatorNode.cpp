#include "BinaryOperatorNode.hpp"

using namespace std;

BinaryOperatorNode::~BinaryOperatorNode(){delete e_left_operand; delete e_right_operand;}

string BinaryOperatorNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  return "BinOp(" + (literal_op_table.find(e_op))->second + ", "  + e_left_operand->getLiteral(with_type) +  ", " + e_right_operand->getLiteral(with_type) + ")" + type;
}
