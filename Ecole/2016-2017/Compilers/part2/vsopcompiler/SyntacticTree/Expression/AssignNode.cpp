#include "AssignNode.hpp"
#include "../ClassNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "ObjectIdentifierNode.hpp"

using namespace std;

AssignNode::~AssignNode(){delete e_name; delete e_expr;};

string AssignNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  return "Assign(" + e_name->getLiteral(false) + ", " + e_expr->getLiteral(with_type) + ")" + type;
}
