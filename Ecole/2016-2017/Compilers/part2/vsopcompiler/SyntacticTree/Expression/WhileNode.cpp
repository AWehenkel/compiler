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

int WhileNode::updateType(Visitor* visitor){

  // Check if the condition is a bool
  TypeIdentifierNode *condition_type = e_condition->getType();
  if (!condition_type){
    cerr << "Error in the compiler in WhileNode : condition_type is null" << endl;
    return -1;
  }
  string s_condition_type = condition_type->getLiteral();

  if (s_condition_type != "error" && s_condition_type != "bool"){
    cerr << "Condition n'est pas un bool dans while" << endl;
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return -1;
  }
  node_type = new TypeIdentifierNode("unit");
  self_type = true;
  return 0;
}
