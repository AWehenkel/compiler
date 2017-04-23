#include "BinaryOperatorNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

BinaryOperatorNode::~BinaryOperatorNode(){delete e_left_operand; delete e_right_operand;}

string BinaryOperatorNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  return "BinOp(" + (literal_op_table.find(e_op))->second + ", "  + e_left_operand->getLiteral(with_type) +  ", " + e_right_operand->getLiteral(with_type) + ")" + type;
}

vector<SemanticError> BinaryOperatorNode::updateType(Visitor* visitor){

  vector<SemanticError> errors;

  // Get the types of the two operands
  TypeIdentifierNode* left_type = e_left_operand->getType();
  TypeIdentifierNode* right_type = e_right_operand->getType();
  if(!left_type){
    SemanticError error("Error in the compiler in BinaryOperatorNode : left_type is null", this);
    errors.push_back(error);
    return errors;
  }
  if(!right_type){
    SemanticError error("Error in the compiler in BinaryOperatorNode : right_type is null", this);
    errors.push_back(error);
    return errors;
  }
  string s_left_type = left_type->getLiteral();
  string s_right_type = right_type->getLiteral();

  switch (e_op){
    case BinaryOperator::b_op_and :
      // Check both operands are bools or errors and return a bool if ok
      if ((s_left_type != "bool" && s_left_type != "error") || (s_right_type != "bool" && s_right_type != "error")){
        SemanticError error("The two members of an and-expression must be boolean, got '" + s_left_type +"' and '" + s_right_type + "'", this);
        errors.push_back(error);
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return errors;
      }
      node_type = left_type;
      break;
    case BinaryOperator::b_op_equal :
      // TODO : est-ce qu'on doit pas checker pour l'héritage ?
      // Check if the two types are the same (or errors) and return bool if ok
      if(s_left_type != "error" && s_right_type != "error" && s_left_type != s_right_type){
        SemanticError error("The two members of an equal-expression must have the same type, got '" + s_left_type +"' and '" + s_right_type + "'", this);
        errors.push_back(error);
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return errors;
      }
      node_type = new TypeIdentifierNode("bool");
      self_type = true;
      break;
    case BinaryOperator::b_op_leq :
    case BinaryOperator::b_op_less :
      // Check both operands are int32 or errors and return a bool if ok
      if ((s_left_type != "int32" && s_left_type != "error" != 0) || (s_right_type != "int32" && s_right_type != "error")){
        SemanticError error("The two members of a comparison must be int32, got '" + s_left_type +"' and '" + s_right_type + "'", this);
        errors.push_back(error);
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return errors;
      }
      node_type = new TypeIdentifierNode("bool");
      self_type = true;
      break;
    default :
      // Check both operands are int32 and return a int32 if ok
      if ((s_left_type != "int32" && s_left_type != "error") || (s_right_type != "int32" && s_right_type != "error")){
        SemanticError error("The two members of a math expression must be int32, got '" + s_left_type +"' and '" + s_right_type + "'", this);
        errors.push_back(error);
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return errors;
      }
      node_type = left_type;
  }

  return errors;
}
