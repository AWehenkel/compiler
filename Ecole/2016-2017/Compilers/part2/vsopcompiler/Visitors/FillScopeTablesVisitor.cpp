#include <iostream>

#include "FillScopeTablesVisitor.hpp"
#include "../SyntacticTree/ClassNode.hpp"
#include "../SyntacticTree/MethodNode.hpp"
#include "../SyntacticTree/FieldNode.hpp"
#include "../SyntacticTree/Expression/LetNode.hpp"
#include "../SyntacticTree/Expression/ObjectIdentifierNode.hpp"
#include "../SyntacticTree/Expression/BlockNode.hpp"
#include "../SyntacticTree/Expression/CallNode.hpp"
#include "../SyntacticTree/Expression/BlockNode.hpp"
#include "../SyntacticTree/TypeIdentifierNode.hpp"

using namespace std;

int FillScopeTablesVisitor::visitClassNode(ClassNode *node){
  current_class = node;
  return Visitor::visitClassNode(node);
}

int FillScopeTablesVisitor::visitMethodNode(MethodNode *node){
  current_scope = (VSOPNode*) node;
  if(!current_class || current_class->addMethod(node) < 0)
    return -5;
  node->setClassScope(current_class);
  current_method = node;
  return node->getBlock()->accept(this);
}

int FillScopeTablesVisitor::visitFieldNode(FieldNode *node){
  if(!current_class || current_class->addField(node) < 0)
    return -5;
  node->setClassScope(current_class);
  ExpressionNode* init_expr = node->getInitExpr();
  if(init_expr)
    return init_expr->accept(this);
  return 0;
}

int FillScopeTablesVisitor::visitLetNode(LetNode *node){
  node->setCurrentScope(current_scope);
  current_scope = (VSOPNode*) node;
  int result = Visitor::visitLetNode(node);
  current_scope = node->getCurrentScope();
  return result;
}

int FillScopeTablesVisitor::visitFormalNode(FormalNode *node){
  return 0;
}

int FillScopeTablesVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){
  if(node->getLiteral() == "self"){
    node->setType(current_class->getName());
    return 0;
  }
  TypeIdentifierNode* obj_type = current_scope->getDeclarationType(node->getLiteral());
  if(!obj_type){
    cerr << "erreur variable \"" << node->getLiteral() << "\" utilisee avant declaration(line:" << node->getLine() << " col:" << node->getCol() << ")" << endl;
    return -6;
  }
  node->setType(obj_type);
  return 0;
}

int FillScopeTablesVisitor::visitCallNode(CallNode *node){
  node->setCurrentClass(current_class);
  if(!node->getObject())
    node->setObject(new ObjectIdentifierNode("self"));

  if(node->getObject()->accept(this) < 0)
    return -1;
  return node->getArgs()->accept(this);
}
