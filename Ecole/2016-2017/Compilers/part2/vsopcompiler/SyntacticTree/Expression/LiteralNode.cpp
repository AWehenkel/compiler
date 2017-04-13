#include "LiteralNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string LiteralNode::getLiteral() const{
  cout << "literal" << endl;
  string type = node_type ? " : " + node_type->getLiteral() : ""; if(node_type) cout << node_type->getLiteral() << endl;
  return e_content + type;
}
