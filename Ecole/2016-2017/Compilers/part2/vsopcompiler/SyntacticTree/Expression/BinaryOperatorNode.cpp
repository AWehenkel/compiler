#include <cstring>

#include "BinaryOperatorNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

int BinaryOperatorNode::updateType(){

  cout << "BinaryOperatorNode" << endl;
  // Get the types of the two operands
  TypeIdentifierNode* left_type = e_left_operand->getType();
  TypeIdentifierNode* right_type = e_right_operand->getType();
  if(!left_type || !right_type){
    cerr << "Error in the compiler in BinaryOperatorNode : left_type or right_type is null" << endl;
    return -1;
  }
  string s_left_type = left_type->getLiteral();
  string s_right_type = right_type->getLiteral();

  switch (e_op){
    case BinaryOperator::b_op_and :
      // Check both operands are bools or errors and return a bool if ok
      if ((strcmp(s_left_type.c_str(), "bool") != 0 && strcmp(s_left_type.c_str(), "error") != 0) || (strcmp(s_right_type.c_str(), "bool") != 0 && strcmp(s_right_type.c_str(), "error") != 0)){
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
      if ((strcmp(s_left_type.c_str(), "int32") != 0 && strcmp(s_left_type.c_str(), "error") != 0) || (strcmp(s_right_type.c_str(), "int32") != 0 && strcmp(s_right_type.c_str(), "error") != 0)){
        cerr << "Les deux membres ne sont pas des ints dans binary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      node_type = new TypeIdentifierNode("bool");
      break;
    default :
      cout << "addition" << endl;
      // Check both operands are int32 and return a int32 if ok
      if ((strcmp(s_left_type.c_str(), "int32") != 0 && strcmp(s_left_type.c_str(), "error") != 0) || (strcmp(s_right_type.c_str(), "int32") != 0 && strcmp(s_right_type.c_str(), "error") != 0)){
        cerr << "Les deux membres ne sont pas des ints dans binary" << endl;
        node_type = new TypeIdentifierNode("error");
        return -1;
      }
      cout << "addition ok" << endl;
      node_type = new TypeIdentifierNode("int32");
  }

  return 0;
}

BinaryOperatorNode::~BinaryOperatorNode(){delete e_left_operand; delete e_right_operand;}

string BinaryOperatorNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  return "BinOp(" + (literal_op_table.find(e_op))->second + ", "  + e_left_operand->getLiteral(with_type) +  ", " + e_right_operand->getLiteral(with_type) + ")" + type;
}
