#include "ObjectIdentifierNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string ObjectIdentifierNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : ""; if(node_type) cout << node_type->getLiteral() << endl;
  return e_content + type;
}
