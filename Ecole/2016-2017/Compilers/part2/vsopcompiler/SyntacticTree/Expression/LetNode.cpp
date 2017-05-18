#include "LetNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "ObjectIdentifierNode.hpp"
#include "../ClassNode.hpp"

using namespace std;

LetNode::~LetNode(){
  delete e_init_exp;
  delete e_scope_exp;
  delete e_object_id;
  delete e_object_type;
}

TypeIdentifierNode* LetNode::getDeclarationType(string id){

  if(e_object_id->getLiteral() == id)
    return e_object_type;
  else if(e_current_scope)
    return e_current_scope->getDeclarationType(id);

  return NULL;
}

const string LetNode::getDeclarationLLVM(string id){

  if(e_object_id->getLiteral() == id)
    return e_object_id->getLLVMAddress();
  else if(e_current_scope)
    return e_current_scope->getDeclarationLLVM(id);

  return "";
}

string LetNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  string literal = "Let(" + e_object_id->getLiteral(false) + ", " + e_object_type->getLiteral(with_type) + ", ";
  string end = e_init_exp ? e_init_exp->getLiteral(with_type) + ", " : "";

  return literal + end + e_scope_exp->getLiteral(with_type) + ")" + type;
}
