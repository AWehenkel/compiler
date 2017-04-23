#include "AssignNode.hpp"
#include "../ClassNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "ObjectIdentifierNode.hpp"

using namespace std;

AssignNode::~AssignNode(){delete e_name; delete e_expr;};

string AssignNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  return "Assign(" + e_name->getLiteral(false) + ", " + e_expr->getLiteral(with_type) + ")" + type;
}

vector<SemanticError> AssignNode::updateType(Visitor* visitor){

  vector<SemanticError> errors;

  // Get types
  TypeIdentifierNode *name_type = e_name->getType();
  TypeIdentifierNode *expr_type = e_expr->getType();
  if(!name_type){
    SemanticError error("Error in the compiler in AssignNode : name_type is null", this);
    errors.push_back(error);
    return errors;
  }
  if(!expr_type){
    SemanticError error("Error in the compiler in AssignNode : expr_type is null", this);
    errors.push_back(error);
    return errors;
  }

  /* It there was a type error in the son e_expr or if the two types are the
  * same, assign the type of e_name to node_type and stop the propagation of
  * errors */
  if (expr_type->getLiteral() == "error" || *name_type == *expr_type || (expr_type->getClassType() && expr_type->getClassType()->hasParent(name_type->getClassType()))){
    node_type = name_type;
    return errors;
  }

  // If the two types were different, assign "error" to e_name and create an error
  node_type = new TypeIdentifierNode("error");
  SemanticError error("Assignement of different types : '" + e_name->getLiteral() + "' of type '" + name_type->getLiteral() + "' has not the same type as assigned expression of type '" + expr_type->getLiteral() + "'", this);
  errors.push_back(error);
  return errors;
}
