#include <string>

#include "CheckTypeVisitor.hpp"
#include "all_headers.hpp"

using namespace std;

int CheckTypeVisitor::visitAssignNode(AssignNode *node){

  int error = 0;
  if(Visitor::visitAssignNode(node) < 0)
    error = -1;

  vector<SemanticError> errors;

  // Get types
  TypeIdentifierNode *name_type = node->getName()->getType();
  TypeIdentifierNode *expr_type = node->getExpression()->getType();
  if(!name_type){
    cerr << "Error in the compiler in AssignNode : name_type is null" << endl;
    return -1;
  }
  if(!expr_type){
    cerr << "Error in the compiler in AssignNode : expr_type is null" << endl;
    return -1;
  }

  /* It there was a type error in the son e_expr or if the two types are the
  * same, assign the type of e_name to node_type and stop the propagation of
  * errors */
  if (expr_type->getLiteral() == "error" || *name_type == *expr_type || (expr_type->getClassType() && expr_type->getClassType()->hasParent(name_type->getClassType()))){
    node_type = name_type;
    return 0;
  }

  // If the two types were different, assign "error" to e_name and create an error
  node_type = new TypeIdentifierNode("error");
  SemanticError error("Assignement of different types : '" + e_name->getLiteral() + "' of type '" + name_type->getLiteral() + "' has not the same type as assigned expression of type '" + expr_type->getLiteral() + "'", this);
  errors.push_back(error);
  return 1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitBinaryOperatorNode(BinaryOperatorNode *node){

  int error = 0;
  if(Visitor::visitBinaryOperatorNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitBlockNode(BlockNode *node){

  int error = 0;
  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;

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

  // TODO : check if it cannot be done in Visitor
  int error = 0;
  std::vector<FieldNode*> fields = node->getFields();
  for(std::vector<FieldNode*>::iterator it = fields.begin(); it != fields.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
  }

  std::vector<MethodNode*> methods = node->getMethods();
  for(std::vector<MethodNode*>::iterator it = methods.begin(); it != methods.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
  }

  return error;
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

  int error = 0;

  current_scope = (VSOPNode*) node;
  if(Visitor::visitMethodNode(node) < 0)
    error = -1;

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;
}



int CheckTypeVisitor::visitProgramNode(ProgramNode *node){

  int error = 0;
  std::vector<ClassNode*> classes = node->getClasses();
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
    }

  return error;
}
