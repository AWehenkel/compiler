#include "ConditionalNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "../ClassNode.hpp"

using namespace std;

ConditionalNode::~ConditionalNode(){
  delete e_condition;
  delete e_action;
  delete e_else_action;
}

string ConditionalNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  string literal = "If(" + e_condition->getLiteral(with_type) + "," + e_action->getLiteral(with_type);
  string end = e_else_action ? "," + e_else_action->getLiteral(with_type) : "";

  return literal + end + ")" + type;
}
