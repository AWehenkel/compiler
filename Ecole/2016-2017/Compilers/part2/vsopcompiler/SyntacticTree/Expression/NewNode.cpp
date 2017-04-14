#include "NewNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string NewNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : "";
  return "New(" + e_type_id->getLiteral() + ")" + type;
}
