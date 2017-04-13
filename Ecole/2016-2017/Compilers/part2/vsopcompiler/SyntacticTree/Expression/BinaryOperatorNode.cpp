#include "BinaryOperatorNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

int BinaryOperatorNode::update(){

  // Get the types of the two operands
  TypeIdentifierNode* left_type = e_left_operand->getType();
  TypeIdentifierNode* right_type = e_right_operand->getType();
  if(!left_type || !right_type){
    cerr << "Error in the compiler" << endl;
    return -1;
  }
  string s_left_type = left_type->getLiteral();
  string s_right_type = right_type->getLiteral();

  switch (e_op){
    case BinaryOperator::b_op_and :
      // Check both operands are bools or errors and return a bool if ok
      if ((strcmp(s_left_type, "bool") != 0 && strcmp(s_left_type, "error") != 0) || (strcmp(s_right_type, "bool") != 0 && strcmp(s_right_type, "error") != 0)){
        cerr << "Les deux membres ne sont pas des booléans dans binary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      node_type = new TypeIdentifierNode("bool");
      break;
    case BinaryOperator::b_op_equal :
      // !!! à compléter
      cerr << "pas encore complété" << endl;





      break;
    case BinaryOperator::b_op_leq :
    case BinaryOperator::b_op_less :
    // Check both operands are int32 or errors and return a bool if ok
    if ((strcmp(s_left_type, "int32") != 0 && strcmp(s_left_type, "error") != 0) || (strcmp(s_right_type, "int32") != 0 && strcmp(s_right_type, "error") != 0)){
      cerr << "Les deux membres ne sont pas des ints dans binary" << endl;
      node_type = new TypeIdentifierNode("error");
      return -1;
    }
    node_type = new TypeIdentifierNode("bool");
      break;
    default :
    // Check both operands are int32 and return a int32 if ok
    if ((strcmp(s_left_type, "int32") != 0 && strcmp(s_left_type, "error") != 0) || (strcmp(s_right_type, "int32") != 0 && strcmp(s_right_type, "error") != 0)){
      cerr << "Les deux membres ne sont pas des ints dans binary" << endl;
      node_type = new TypeIdentifierNode("error");
      return -1;
    }
    node_type = new TypeIdentifierNode("int32");
      break;
  }

  return 0;
}
