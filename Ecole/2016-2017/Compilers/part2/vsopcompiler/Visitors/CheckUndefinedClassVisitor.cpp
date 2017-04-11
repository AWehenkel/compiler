#include "CheckUndefinedClassVisitor.hpp"

int CheckUndefinedClassVisitor::visitAssignNode(AssignNode *node);
int CheckUndefinedClassVisitor::visitBinaryOperatorNode(BinaryOperatorNode *node);
int CheckUndefinedClassVisitor::visitBlockNode(BlockNode *node);
int CheckUndefinedClassVisitor::visitBraceNode(BraceNode *node);
int CheckUndefinedClassVisitor::visitCallNode(CallNode *node);
int CheckUndefinedClassVisitor::visitConditionalNode(ConditionalNode *node);
int CheckUndefinedClassVisitor::visitLetNode(LetNode *node);
int CheckUndefinedClassVisitor::visitLiteralNode(LiteralNode *node);
int CheckUndefinedClassVisitor::visitNewNode(NewNode *node);
int CheckUndefinedClassVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node);
int CheckUndefinedClassVisitor::visitUnaryOperatorNode(UnaryOperatorNode *node);
int CheckUndefinedClassVisitor::visitWhileNode(WhileNode *node);
int CheckUndefinedClassVisitor::visitArgsNode(ArgsNode *node);

int CheckUndefinedClassVisitor::visitClassBodyNode(ClassBodyNode *node){

    int result = 0;

    // Check fields
    std::vector<FieldNode*> fields = getFields();
    for (vector<ClassNode*>::const_iterator it = fields.begin(); it < fields.end(); ++it){
      result = (*it)->accept(this);
      if (result != 0)
        break;
    }

    // Check methods
  	std::vector<MethodNode*> methods = getMethods();
    for (vector<ClassNode*>::const_iterator it = methods.begin(); it < methods.end(); ++it){
      result = (*it)->accept(this);
      if (result != 0)
        break;
    }

    return result;
}

int CheckUndefinedClassVisitor::visitClassNode(ClassNode *node){

  // Get body
  ClassBodyNode *body = node->getBody();

  return body->accept(this);

}

int CheckUndefinedClassVisitor::visitFieldNode(FieldNode *node){

  int result = 0;

  // Check type
  TypeIdentifierNode* type = getType();
  result = type->accept(this);
  if (result != 0)
    return result;

  // Check expressions
	ExpressionNode* expr = getInitExpr();
  result = expr->accept(this);
  if (result != 0)
    return result;

  return result;

}

int CheckUndefinedClassVisitor::visitFormalNode(FormalNode *node);
int CheckUndefinedClassVisitor::visitFormalsNode(FormalsNode *node);

int CheckUndefinedClassVisitor::visitMethodNode(MethodNode *node){

  int result = 0;

  // Check formals
  FormalsNode* formals = getFormals();
  result = formals->accept(this);
  if (result != 0)
    return result;

  // Check type identifier
  TypeIdentifierNode* id = getRetType();
  result = id->accept(this);
  if (result != 0)
    return result;

  // Check block
  BlockNode* block = getBlock();
  result = block->accept(this);
  if (result != 0)
    return result;

  return result;

}

int CheckUndefinedClassVisitor::visitProgramNode(ProgramNode *node){

  int result = 0;

  // Get the class tables
  table_class = node->getTableClass();

  // Get the classes
  std::vector<ClassNode*> classes = node->getClasses();

  for (vector<ClassNode*>::const_iterator it = classes.begin(); it < classes.end(); ++it){
    result = (*it)->accept(this);
    if (result != 0)
      break;
  }

  return result;

}
