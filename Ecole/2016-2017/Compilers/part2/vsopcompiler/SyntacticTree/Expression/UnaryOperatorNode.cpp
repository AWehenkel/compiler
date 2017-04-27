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
