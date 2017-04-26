#include <string>

#include "CheckTypeVisitor.hpp"
#include "all_headers.hpp"

using namespace std;

int CheckTypeVisitor::visitAssignNode(AssignNode *node){

  int error = 0;
  if(Visitor::visitAssignNode(node) < 0)
    error = -1;

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
