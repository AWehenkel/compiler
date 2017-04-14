#include <cstring>

#include "ConditionalNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "../ClassNode.hpp"

using namespace std;

string ConditionalNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  string literal = "If(" + e_condition->getLiteral(with_type) + "," + e_action->getLiteral(with_type);
  string end = e_else_action ? "," + e_else_action->getLiteral(with_type) : "";
  return literal + end + ")" + type;
}

int ConditionalNode::updateType(){

  // Check if the condition is of type bool
  TypeIdentifierNode *condition_type = e_condition->getType();
  if (!condition_type){
    cerr << "Error in the compiler in ConditionalNode : condition_type is null" << endl;
    return -1;
  }
  string s_condition_type = condition_type->getLiteral();

  if (strcmp(s_condition_type.c_str(), "error") != 0 && strcmp(s_condition_type.c_str(), "bool") != 0){
    cerr << "Condition is not bool in conditional" << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }

  // Check the types of the two branches
  TypeIdentifierNode *then_type = e_action->getType();
  TypeIdentifierNode *else_type;
  if(e_else_action)
    else_type = e_else_action->getType();
  else
    else_type = new TypeIdentifierNode("unit");

  if(!then_type || !else_type){
    cerr << "Error in the compiler in ConditionalNode : then_type or else_type null" << endl;
    return -1;
  }
  string s_then_type = then_type->getLiteral();
  string s_else_type = else_type->getLiteral();

  // Check if one of the branch is a unit
  if(strcmp(s_then_type.c_str(), "unit") == 0 || strcmp(s_else_type.c_str(), "unit") == 0){
    node_type = new TypeIdentifierNode("unit");
    return 0;
  }

  // If one branch is in error, return the type of the other branch
  if(strcmp(s_then_type.c_str(), "error") == 0){
    node_type = new TypeIdentifierNode(s_else_type);
    return 0;
  }else if (strcmp(s_else_type.c_str(), "error") == 0){
    node_type = new TypeIdentifierNode(s_then_type);
    return 0;
  }

  // If one of the branch is a basic type, check if the other one is the same
  if (!then_type->getClassType() || !else_type->getClassType()){
    if(*then_type == *else_type){
      node_type = new TypeIdentifierNode(s_then_type);
      return 0;
    }else{
      cerr << "Types différents dans conditional" << endl;
      node_type = new TypeIdentifierNode("error");
      return -1;
    }
  }

  // If both types are clases, need to check the inheritance
  node_type = then_type->getClassType()->getCommonParent(else_type->getClassType());
  if(!node_type){
    cerr << "Pas d'ancêtres en commun dans conditional" << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }

  return 0;
}

ConditionalNode::~ConditionalNode(){
  delete e_condition;
  delete e_action;
  delete e_else_action;
}
