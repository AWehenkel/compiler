#include "LetNode.hpp"
#include "../TypeIdentifierNode.hpp"

int LetNode::updateType(){

  if (init_expr){
    TypeIdentifierNode *init_expr_type = init_expr->getType();
    if (!init_expr_type){
      std::cerr << "Error int the compiler" << std::endl;
      return -1;
    }

    // Compare this type to the type of the let
    if (strcmp(init_expr_type->getLiteral(), "error") != 0 && *init_expr_type != *e_object_type){
      node_type = new TypeIdentifierNode("error");
      std::cerr << "!! Types différents dans let" << std::endl;
      return -1;
    }
  }

  TypeIdentifierNode *scope_expr_type = e_scope_exp->getType();
  if (!scope_expr_type){
    std::cerr << "Error int the compiler" << std::endl;
    return -1;
  }
  node_type = new TypeIdentifierNode(scope_expr_type->getLiteral());

  return 0;
}

TypeIdentifierNode* LetNode::getDeclarationType(std::string id){
  if(e_object_id->getLiteral() == id)
    return e_type;
  else if(e_current_scope)
    return e_current_scope->getDeclarationType(id);
  return NULL;
}
