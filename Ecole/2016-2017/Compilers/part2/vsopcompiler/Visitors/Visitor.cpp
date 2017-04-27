#include "Visitor.hpp"
#include "all_headers.hpp"

using namespace std;

std::vector<SemanticError>& Visitor::getErrors(){
  return errors;
}

void Visitor::addError(SemanticError& error){
  errors.push_back(error);
}

int Visitor::visitAssignNode(AssignNode *node){

  int nb_errors = 0;
  int error;
  ExpressionNode* expr = node->getExpression();
  ObjectIdentifierNode* id = node->getName();
  if(expr){
    error = expr->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if(id){
    error = id->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int Visitor::visitBinaryOperatorNode(BinaryOperatorNode *node){

  int nb_errors = 0;
  int error = 0;
  ExpressionNode* left = node->getLeft();
  ExpressionNode* right = node->getRight();
  if(left){
    error = left->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (right){
    error = right->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int Visitor::visitBlockNode(BlockNode *node){

  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }

  return 0;
}

int Visitor::visitBraceNode(BraceNode *node){

  ExpressionNode* expr = node->getExpression();
  if(expr && expr->accept(this) < 0)
    return -1;

  return 0;
}

int Visitor::visitCallNode(CallNode *node){

  int nb_errors = 0;
  int error;
  ObjectIdentifierNode* method_name = node->getMethodName();
  ArgsNode* args = node->getArgs();
  ExpressionNode* object = node->getObject();
  if(method_name){
    error = method_name->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (args){
    error = args->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if(object){
    error = object->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int Visitor::visitConditionalNode(ConditionalNode *node){

  ExpressionNode* condition = node->getCondition();
  ExpressionNode* action = node->getAction();
  ExpressionNode* else_action = node->getElseAction();
  if((condition && condition->accept(this) < 0) || (action && action->accept(this) < 0) || (else_action && else_action->accept(this) < 0))
    return -1;

  return 0;
}

int Visitor::visitLetNode(LetNode *node){

  ObjectIdentifierNode* object_id = node->getObjectId();
  TypeIdentifierNode* type = node->getObjectType();
  ExpressionNode* init_exp = node->getInitExp();
  ExpressionNode* scope_exp = node->getScopeExp();
  if((object_id && object_id->accept(this) < 0) || (type && type->accept(this) < 0) || (init_exp && init_exp->accept(this) < 0) || (scope_exp && scope_exp->accept(this) < 0))
    return -1;

  return 0;
}

int Visitor::visitLiteralNode(LiteralNode *node){
  return 0;
}

int Visitor::visitNewNode(NewNode *node){

  TypeIdentifierNode* type_id = node->getTypeId();
  if(type_id && type_id->accept(this) < 0)
    return -1;

  return 0;
}

int Visitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){
  return 0;
}

int Visitor::visitUnaryOperatorNode(UnaryOperatorNode *node){

  int nb_errors = 0;
  int error;
  ExpressionNode* operand = node->getOperand();
  if(operand){
    error = operand->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int Visitor::visitWhileNode(WhileNode *node){

  int nb_errors = 0;
  int error;
  ExpressionNode* condition = node->getCondition();
  ExpressionNode* action = node->getAction();
  if(condition){
    error = condition->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (action){
    error = action->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int Visitor::visitArgsNode(ArgsNode *node){

  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }

  return 0;
}

int Visitor::visitClassBodyNode(ClassBodyNode *node){

  std::vector<FieldNode*> fields = node->getFields();
  for(std::vector<FieldNode*>::iterator it = fields.begin(); it != fields.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }

  std::vector<MethodNode*> methods = node->getMethods();
  for(std::vector<MethodNode*>::iterator it = methods.begin(); it != methods.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }

  return 0;
}

int Visitor::visitClassNode(ClassNode *node){

  int nb_errors = 0;
  int error;
  TypeIdentifierNode* name = node->getName();
  TypeIdentifierNode* extends = node->getExtends();
  ClassBodyNode *body = node->getBody();

  if (name){
    error = name->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (extends){
    error = extends->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (body){
    error = body->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int Visitor::visitFieldNode(FieldNode *node){

  ObjectIdentifierNode* name = node->getName();
  TypeIdentifierNode* type = node->getType();
  ExpressionNode* init_expr = node->getInitExpr();
  if((name && name->accept(this) < 0) || (type && type->accept(this) < 0) || (init_expr && init_expr->accept(this) < 0))
    return -1;

  return 0;
}

int Visitor::visitFormalNode(FormalNode *node){

  ObjectIdentifierNode* name = node->getName();
  TypeIdentifierNode* type = node->getType();
  if((name && name->accept(this)) || (type && type->accept(this)))
    return -1;

  return 0;
}

int Visitor::visitFormalsNode(FormalsNode *node){

  std::vector<FormalNode*> formals = node->getFormals();
  for(std::vector<FormalNode*>::iterator it = formals.begin(); it != formals.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
    }

  return 0;
}

int Visitor::visitMethodNode(MethodNode *node){

  int nb_errors = 0;
  int error = 0;
  ObjectIdentifierNode* name = node->getName();
  FormalsNode* formals = node->getFormals();
  TypeIdentifierNode* ret_type = node->getRetType();
  BlockNode* block = node->getBlock();
  if (name){
    error = name->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (formals){
    error = formals->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (ret_type){
    error = ret_type->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }
  if (block){
    error = block->accept(this);
    if(error < 0)
      return -1;
    nb_errors += error;
  }

  return nb_errors;
}

int Visitor::visitProgramNode(ProgramNode *node){

  std::vector<ClassNode*> classes = node->getClasses();
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
    }

  return 0;
}

int Visitor::visitTypeIdentifierNode(TypeIdentifierNode *node){
  return 0;
}
