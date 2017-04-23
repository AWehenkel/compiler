#include "WhileNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

WhileNode::~WhileNode(){
  delete e_condition;
  delete e_action;
}

string WhileNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  return "While(" + e_condition->getLiteral(with_type) + "," + e_action->getLiteral(with_type) + ")" + type;
};

vector<SemanticError> WhileNode::updateType(Visitor* visitor){

  vector<SemanticError> errors;

  // Check if the condition is a bool
  TypeIdentifierNode *condition_type = e_condition->getType();
  if (!condition_type){
    SemanticError error("Error in the compiler in WhileNode : condition_type is null", this);
    errors.push_back(error);
    return errors;
  }
  string s_condition_type = condition_type->getLiteral();

  if (s_condition_type != "error" && s_condition_type != "bool"){
    SemanticError error("Condition of while must be bool : got '" + s_condition_type + "'", this);
    errors.push_back(error);
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return errors;
  }
  node_type = new TypeIdentifierNode("unit");
  self_type = true;
  return errors;
}
