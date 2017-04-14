#include "ObjectIdentifierNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string ObjectIdentifierNode::getLiteral() const{
<<<<<<< HEAD
  cout <<"obj" << endl;
=======
>>>>>>> be04c390746c409aa65f9774d6deec67a02fc9ab
  string type = node_type ? " : " + node_type->getLiteral() : "";
  return e_content + type;
}
