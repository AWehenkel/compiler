#include <string>

#include "CheckTypeVisitor.hpp"
#include "all_headers.hpp"

using namespace std;

int CheckTypeVisitor::visitAssignNode(AssignNode *node){

  int nb_errors = Visitor::visitAssignNode(node);
  if(nb_errors < 0)
     return -1;

  // Get types
  TypeIdentifierNode *name_type = node->getName()->getType();
  TypeIdentifierNode *expr_type = node->getExpression()->getType();
  if(!name_type){
    SemanticError error("Error in the compiler in AssignNode : name_type is null", node);
    errors.push_back(error);
    return -1;
  }
  if(!expr_type){
    SemanticError error("Error in the compiler in AssignNode : expr_type is null", node);
    errors.push_back(error);
    return -1;
  }

  /* It there was a type error in the son e_expr or if the two types are the
  * same, assign the type of e_name to node_type and stop the propagation of
  * errors */
  if (expr_type->getLiteral() == "error" || *name_type == *expr_type || (expr_type->getClassType() && expr_type->getClassType()->hasParent(name_type->getClassType()))){
    node->setType(name_type);
    return nb_errors;
  }

  // If the two types were different, assign "error" to e_name and create an error
  node->setType(new TypeIdentifierNode("error"));
  SemanticError error("Assignement of different types : '" + node->getName()->getLiteral() + "' of type '" + name_type->getLiteral() + "' has not the same type as assigned expression of type '" + expr_type->getLiteral() + "'", node);
  errors.push_back(error);
  return ++nb_errors;
}


int CheckTypeVisitor::visitBinaryOperatorNode(BinaryOperatorNode *node){

  int nb_errors = Visitor::visitBinaryOperatorNode(node);
  if(nb_errors < 0)
     return -1;

  // Get the types of the two operands
  TypeIdentifierNode* left_type = node->getLeft()->getType();
  TypeIdentifierNode* right_type = node->getRight()->getType();
  if(!left_type){
    SemanticError error("Error in the compiler in BinaryOperatorNode : left_type is null", node);
    errors.push_back(error);
    return -1;
  }
  if(!right_type){
    SemanticError error("Error in the compiler in BinaryOperatorNode : right_type is null", node);
    errors.push_back(error);
    return -1;
  }
  string s_left_type = left_type->getLiteral();
  string s_right_type = right_type->getLiteral();

  BinaryOperator op = node->getOperand();
  switch (op){
    case BinaryOperator::b_op_and :
      // Check both operands are bools or errors and return a bool if ok
      if ((s_left_type != "bool" && s_left_type != "error") || (s_right_type != "bool" && s_right_type != "error")){
        SemanticError error("The two members of an and-expression must be boolean, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return ++nb_errors;
      }
      node->setType(left_type);
      break;
    case BinaryOperator::b_op_equal :
      // TODO : est-ce qu'on doit pas checker pour l'héritage ?
      // Check if the two types are the same (or errors) and return bool if ok
      if(s_left_type != "error" && s_right_type != "error" && s_left_type != s_right_type){
        SemanticError error("The two members of an equal-expression must have the same type, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return ++nb_errors;
      }
      node->setType(new TypeIdentifierNode("bool"), true);
      break;
    case BinaryOperator::b_op_leq :
    case BinaryOperator::b_op_less :
      // Check both operands are int32 or errors and return a bool if ok
      if ((s_left_type != "int32" && s_left_type != "error" != 0) || (s_right_type != "int32" && s_right_type != "error")){
        SemanticError error("The two members of a comparison must be int32, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return ++nb_errors;
      }
      node->setType(new TypeIdentifierNode("bool"), true);
      break;
    default :
      // Check both operands are int32 and return a int32 if ok
      if ((s_left_type != "int32" && s_left_type != "error") || (s_right_type != "int32" && s_right_type != "error")){
        SemanticError error("The two members of a math expression must be int32, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return ++nb_errors;
      }
      node->setType(left_type);
  }

  return nb_errors;
}

int CheckTypeVisitor::visitBlockNode(BlockNode *node){

  int nb_errors = 0;
  int error;
  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    error = (*it)->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return nb_errors;

}


int CheckTypeVisitor::visitBraceNode(BraceNode *node){

  int error = 0;
  if(Visitor::visitBraceNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitCallNode(CallNode *node){

  int error = 0;
  if(Visitor::visitCallNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitConditionalNode(ConditionalNode *node){

  int error = 0;
  if(Visitor::visitConditionalNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitLetNode(LetNode *node){

  int error = 0;

  current_scope = (VSOPNode*) node;
  if(Visitor::visitLetNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitNewNode(NewNode *node){

  int error = 0;
  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitUnaryOperatorNode(UnaryOperatorNode *node){

  int error = 0;
  if(Visitor::visitUnaryOperatorNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitWhileNode(WhileNode *node){

  int error = 0;
  if(Visitor::visitWhileNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitArgsNode(ArgsNode *node){

  int error = 0;
  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitClassBodyNode(ClassBodyNode *node){

  int nb_errors = 0;
  int error ;
  std::vector<FieldNode*> fields = node->getFields();
  for(std::vector<FieldNode*>::iterator it = fields.begin(); it != fields.end(); ++it){
    error = (*it)->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  std::vector<MethodNode*> methods = node->getMethods();
  for(std::vector<MethodNode*>::iterator it = methods.begin(); it != methods.end(); ++it){
    error = (*it)->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int CheckTypeVisitor::visitFieldNode(FieldNode *node){

  int error = 0;
  if(Visitor::visitFieldNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}


int CheckTypeVisitor::visitMethodNode(MethodNode *node){

  current_scope = (VSOPNode*) node;

  int nb_errors = Visitor::visitMethodNode(node);
  if(nb_errors < 0)
    return -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    nb_errors += errors_generated.size();
  }

  return nb_errors;
}



int CheckTypeVisitor::visitProgramNode(ProgramNode *node){

  int nb_errors = 0;
  int error;
  std::vector<ClassNode*> classes = node->getClasses();
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it){
    error = (*it)->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}
