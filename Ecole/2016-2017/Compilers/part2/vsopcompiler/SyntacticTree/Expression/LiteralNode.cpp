#include "LiteralNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string LiteralNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  return e_content + type;
}
