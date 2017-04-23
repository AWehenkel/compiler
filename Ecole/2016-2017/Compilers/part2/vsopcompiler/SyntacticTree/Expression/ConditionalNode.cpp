#include "ConditionalNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "../ClassNode.hpp"

using namespace std;

ConditionalNode::~ConditionalNode(){
  delete e_condition;
  delete e_action;
  delete e_else_action;
}

string ConditionalNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  string literal = "If(" + e_condition->getLiteral(with_type) + "," + e_action->getLiteral(with_type);
  string end = e_else_action ? "," + e_else_action->getLiteral(with_type) : "";

  return literal + end + ")" + type;
}

vector<SemanticError> ConditionalNode::updateType(Visitor* visitor){

  vector<SemanticError> errors;

  TypeIdentifierNode *condition_type = e_condition->getType();
  if (!condition_type){
    SemanticError error("Error in the compiler in ConditionalNode : conditon_type is null", this);
		errors.push_back(error);
    return errors;
  }
  string s_condition_type = condition_type->getLiteral();

    // Check if the condition is of type bool
  if (s_condition_type != "error" && s_condition_type != "bool"){
    SemanticError error("Condition of if-expression must be bool in conditional : got '" + s_condition_type + "'", this);
		errors.push_back(error);
    cerr << "Condition is not bool in conditional" << endl;
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return errors;
  }

  // Check the types of the two branches
  TypeIdentifierNode *then_type = e_action->getType();
  TypeIdentifierNode *else_type;
  bool is_else_new_type = false;
  if(e_else_action)
    else_type = e_else_action->getType();
  else{
    // If there is no else branch, consider that its type is unit
    else_type = new TypeIdentifierNode("unit");
    is_else_new_type = true;
  }

  if(!then_type){
    SemanticError error("Error in the compiler in ConditionalNode : then_type is null", this);
		errors.push_back(error);
    return errors;
  }
  if(!else_type){
    SemanticError error("Error in the compiler in ConditionalNode : else_type is null", this);
		errors.push_back(error);
    return errors;
  }
  string s_then_type = then_type->getLiteral();
  string s_else_type = else_type->getLiteral();

  // Check if one of the branch is a unit
  if(s_then_type == "unit" ){
    node_type = then_type;
    if(is_else_new_type)
      delete else_type;
    return errors;
  }
  if(s_else_type == "unit" ){
    node_type = else_type;
    self_type = is_else_new_type;
    return errors;
  }
  // If one branch is in error, return the type of the other branch
  if(s_then_type == "error"){
    node_type = else_type;
    return errors;
  }else if (s_else_type == "error"){
    node_type = then_type;
    return errors;
  }

  // If one of the branch is a basic type, check if the other one is the same
  if (!then_type->getClassType() || !else_type->getClassType()){
    if(*then_type == *else_type){
      node_type = then_type;
      return errors;
    }else{
      SemanticError error("If they are basic types, the types of then and else branch must be the same : got '" + then_type->getLiteral() + "' and '" + else_type->getLiteral() + "'", this);
  		errors.push_back(error);
      node_type = new TypeIdentifierNode("error");
      self_type = true;
      return errors;
    }
  }

  // If both types are clases, need to check the inheritance
  node_type = then_type->getClassType()->getCommonParent(else_type->getClassType());
  // TODO : reflexion, en fait il peut jamais y avoir d'erreur ici, il y a au moins object comme parent...
  if(!node_type){
    SemanticError error("If they are class types, the types of then and else branch must be the same or be linked by inheritance : got '" + then_type->getLiteral() + "' and '" + else_type->getLiteral() + "'", this);
    errors.push_back(error);
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return errors;
  }

  return errors;
}
