#include <cstring>

#include "LetNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "ObjectIdentifierNode.hpp"

using namespace std;

int LetNode::updateType(){

  if (e_init_exp){
    TypeIdentifierNode *init_expr_type = e_init_exp->getType();
    if (!init_expr_type){
      cerr << "Error int the compiler" << endl;
      return -1;
    }

    // Compare this type to the type of the let
    if (strcmp(init_expr_type->getLiteral().c_str(), "error") != 0 && *init_expr_type != *e_object_type){
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
    return e_object_type;
  else if(e_current_scope)
    return e_current_scope->getDeclarationType(id);
  return NULL;
}

string LetNode::getLiteral() const{
  string literal = "Let(" + e_object_id->getLiteral() + ", " + e_object_type->getLiteral() + ", ";
  string end = e_init_exp ? e_init_exp->getLiteral() + ", " : "";
  return literal + end + e_scope_exp->getLiteral() + ")";
}

LetNode::~LetNode(){delete e_init_exp; delete e_scope_exp;}
