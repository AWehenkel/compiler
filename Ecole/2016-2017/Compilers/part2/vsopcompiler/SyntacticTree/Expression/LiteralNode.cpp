#include "LiteralNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string LiteralNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : "";
  return e_content + type;
}
