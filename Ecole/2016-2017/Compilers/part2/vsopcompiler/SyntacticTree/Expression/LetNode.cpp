#include "LetNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

int LetNode::updateType(){

  if (init_expr){
    TypeIdentifierNode *init_expr_type = init_expr->getType();
    if (!init_expr_type){
      cerr << "Error int the compiler" << endl;
      return -1;
    }

    // Compare this type to the type of the let
    if (strcmp(init_expr_type->getLiteral(), "error") != 0 && *init_expr_type != *e_object_type){
      node_type = new TypeIdentifierNode("error");
      cerr << "!! Types différents dans let" << endl;
      return -1;
    }
  }

  TypeIdentifierNode *scope_expr_type = e_scope_exp->getType();
  if (!scope_expr_type){
    cerr << "Error int the compiler" << endl;
    return -1;
  }
  node_type = new TypeIdentifierNode(scope_expr_type->getLiteral());

  return 0;
}

TypeIdentifierNode* LetNode::getDeclarationType(string id){
  if(e_object_id->getLiteral() == id)
    return e_type;
  else if(e_current_scope)
    return e_current_scope->getDeclarationType(id);
  return NULL;
}

string LetNode::getLiteral() const{
  string literal = "Let(" + e_object_id->getLiteral() + ", " + e_type->getLiteral() + ", ";
  string end = e_init_exp ? e_init_exp->getLiteral() + ", " : "";
  return literal + end + e_scope_exp->getLiteral() + ")";
}
