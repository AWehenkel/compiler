#include "NewNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string NewNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  return "New(" + e_type_id->getLiteral(with_type) + ")" + type;
}

vector<SemanticError> NewNode::updateType(Visitor* visitor){

  vector<SemanticError> errors;

  node_type = e_type_id;
  return errors;
}

NewNode::~NewNode(){
  delete e_type_id;
}
