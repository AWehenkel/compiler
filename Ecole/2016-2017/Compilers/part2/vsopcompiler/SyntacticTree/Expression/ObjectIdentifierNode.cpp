#include "ObjectIdentifierNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string ObjectIdentifierNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : "";
  return e_content + type;
}

string ObjectIdentifierNode::getLiteralWithoutType() const{
  return e_content;
}
