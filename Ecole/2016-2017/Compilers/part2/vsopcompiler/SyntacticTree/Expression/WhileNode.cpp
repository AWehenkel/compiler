#include "WhileNode.hpp"

int WhileNode::update(){

  // Check if the condition is a bool
  TypeIdentifierNode *condition_type = e_condition->getType();
  if (!condition_type || !action_type){
    std::cerr << "Error in the compiler" << std::endl;
    return -1;
  }
  string s_condition_type = condition_type->getLiteral();

  if (strcmp(s_op_type, "error") != 0  && strcmp(s_condition_type, "bool") != 0){
    std::cerr << "Condition n'est pas un bool dans while" << std::endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }
  node_type = new TypeIdentifierNode("unit");

  return 0;
}
