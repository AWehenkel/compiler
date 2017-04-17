#include "Visitor.hpp"
#include "all_headers.hpp"

using namespace std;

int Visitor::visitAssignNode(AssignNode *node){
  ExpressionNode* expr = node->getExpression();
  if(expr && expr->accept(this) < 0)
    return -1;

  ObjectIdentifierNode* id = node->getName();
  if(id && id->accept(this) < 0)
    return -1;

  return 0;
}

int Visitor::visitBinaryOperatorNode(BinaryOperatorNode *node){
  ExpressionNode* left = node->getLeft();
  if(left && left->accept(this) < 0)
    return -1;

  ExpressionNode* right = node->getRight();
  if(right && right->accept(this) < 0)
    return -1;

  return 0;
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
  ObjectIdentifierNode* method_name = node->getMethodName();
  ArgsNode* args = node->getArgs();
  ExpressionNode* object = node->getObject();
  if((method_name && method_name->accept(this) < 0) || (args && args->accept(this) < 0) || (object && object->accept(this) < 0))
    return -1;

  return 0;
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
  //UnaryOperator op = node->getOperator();
  ExpressionNode* operand = node->getOperand();
  if(operand && operand->accept(this) < 0)
    return -1;
  return 0;
}

int Visitor::visitWhileNode(WhileNode *node){
  ExpressionNode* condition = node->getCondition();
  ExpressionNode* action = node->getAction();
  if((condition && condition->accept(this) < 0) || (action && action->accept(this) < 0))
    return -1;
  return 0;
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
  TypeIdentifierNode* name = node->getName();
  TypeIdentifierNode* extends = node->getExtends();
  ClassBodyNode *body = node->getBody();
  if((name && name->accept(this)  < 0) || (extends && extends->accept(this) < 0) || (body && body->accept(this) < 0))
    return -1;
  return 0;
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
  ObjectIdentifierNode* name = node->getName();
  FormalsNode* formals = node->getFormals();
  TypeIdentifierNode* ret_type = node->getRetType();
  BlockNode* block = node->getBlock();
  if((name && name->accept(this) < 0) || (formals && formals->accept(this) < 0) || (ret_type && ret_type->accept(this) < 0) || (block && block->accept(this) < 0))
    return -1;
  return 0;
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
