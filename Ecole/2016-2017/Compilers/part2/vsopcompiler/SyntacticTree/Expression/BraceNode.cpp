#include "BraceNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

BraceNode::~BraceNode(){
  delete e_expr;
}

string BraceNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  string literal = "(";
  string s_expr = e_expr ? e_expr->getLiteral(with_type) : "";

  return literal + s_expr + ")" + type;
}
