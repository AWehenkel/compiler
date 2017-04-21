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

string LetNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  string literal = "Let(" + e_object_id->getLiteral(false) + ", " + e_object_type->getLiteral(with_type) + ", ";
  string end = e_init_exp ? e_init_exp->getLiteral(with_type) + ", " : "";

  return literal + end + e_scope_exp->getLiteral(with_type) + ")" + type;
}

int LetNode::updateType(Visitor* visitor){
  // Check the type of the initialization expression, if any
  if (e_init_exp){
    TypeIdentifierNode *init_expr_type = e_init_exp->getType();
    if (!init_expr_type){
      cerr << "Error int the compiler in LetNode : init_expr_type is null" << endl;
      return -1;
    }

    // Compare this type to the type of the let
    if (init_expr_type->getLiteral() != "error" && *init_expr_type != *e_object_type
        && (!init_expr_type->getClassType() || !init_expr_type->getClassType()->hasParent(e_object_type->getClassType()))){
      node_type = new TypeIdentifierNode("error");
      self_type = true;
      cerr << "Types differents dans let" << endl;
      return -1;
    }
  }

  // The return type of the let is the type of the scope
  TypeIdentifierNode *scope_expr_type = e_scope_exp->getType();
  if (!scope_expr_type){
    cerr << "Error int the compiler in LetNode : scope_expr_type null" << endl;
    return -1;
  }
  node_type = scope_expr_type;
  return 0;
}
