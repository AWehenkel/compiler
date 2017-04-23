#include "UnaryOperatorNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

UnaryOperatorNode::~UnaryOperatorNode(){delete e_operand;}

string UnaryOperatorNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  return "UnOp(" + (literal_op_table.find(e_op))->second + ","  + e_operand->getLiteral(with_type) + ")" + type;
}

vector<SemanticError> UnaryOperatorNode::updateType(Visitor* visitor){

  vector<SemanticError> errors;

  // Get the type of the operand
  TypeIdentifierNode* op_type = e_operand->getType();
  if(!op_type){
    SemanticError error("Error in the compiler in UnaryOperatorNode : op_type is null", this);
    errors.push_back(error);
    return errors;
  }
  string s_op_type = op_type->getLiteral();

  switch (e_op){
    case UnaryOperator::u_op_not :
      // Check if operand is bools and return operand type if ok
      if (s_op_type != "error" && s_op_type != "bool"){
        SemanticError error("not-expression must be followed by a bool : got '" + s_op_type + "'", this);
        errors.push_back(error);
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return errors;
      }
      node_type = op_type;
      break;
    case UnaryOperator::u_op_isnull :
      // Check if it not a basic type and return bool if ok
      // TODO : pourquoi il n'y a pas de comparaison à unit ?
      if (s_op_type == "bool" || s_op_type == "int32" || s_op_type == "string"){
        SemanticError error("isnull-expression must be followed by a class : got '" + s_op_type + "'", this);
        errors.push_back(error);
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return errors;
      }
      node_type = new TypeIdentifierNode("bool");
      self_type = true;
      break;
    case UnaryOperator::u_op_minus :
      // Check if operand is int32 and return operand type if ok
      if (s_op_type != "error" && s_op_type != "int32"){
        SemanticError error("minus-expression must be followed by a int32 : got '" + s_op_type + "'", this);
        errors.push_back(error);
        node_type = new TypeIdentifierNode("error");
        self_type = true;
        return errors;
      }
      node_type = op_type;
      break;
  }

  return errors;
}
