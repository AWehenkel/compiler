#include <cstring>

#include "WhileNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

int WhileNode::update(){

  // Check if the condition is a bool
  TypeIdentifierNode *condition_type = e_condition->getType();
  if (!condition_type){
    cerr << "Error in the compiler" << endl;
    return -1;
  }
  string s_condition_type = condition_type->getLiteral();

  if (strcmp(s_condition_type.c_str(), "error") != 0  && strcmp(s_condition_type.c_str(), "bool") != 0){
    cerr << "Condition n'est pas un bool dans while" << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }
  node_type = new TypeIdentifierNode("unit");

  return 0;
}

WhileNode::~WhileNode(){
  delete e_condition;
  delete e_action;
}

string WhileNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : ""; if(node_type) cout << node_type->getLiteral() << endl;
  return "While(" + e_condition->getLiteral() + "," + e_action->getLiteral() + ")" + type;
};
