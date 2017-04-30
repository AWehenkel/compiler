#include "WhileNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

WhileNode::~WhileNode(){
  delete e_condition;
  delete e_action;
}

string WhileNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  return "While(" + e_condition->getLiteral(with_type) + "," + e_action->getLiteral(with_type) + ")" + type;
};
