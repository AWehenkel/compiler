#include "ObjectIdentifierNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string ObjectIdentifierNode::getLiteral() const{
  cout <<"obj" << endl;
  string type = node_type ? " : " + node_type->getLiteral() : "";
  return e_content + type;
}
