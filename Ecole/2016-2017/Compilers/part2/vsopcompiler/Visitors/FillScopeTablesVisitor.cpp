#include <iostream>

#include "FillScopeTablesVisitor.hpp"
#include "../SyntacticTree/ClassNode.hpp"
#include "../SyntacticTree/MethodNode.hpp"
#include "../SyntacticTree/FieldNode.hpp"
#include "../SyntacticTree/Expression/LetNode.hpp"
#include "../SyntacticTree/Expression/ObjectIdentifierNode.hpp"
#include "../SyntacticTree/Expression/BlockNode.hpp"
#include "../SyntacticTree/Expression/CallNode.hpp"

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
  return 0;
}

int FillScopeTablesVisitor::visitLetNode(LetNode *node){
  node->setCurrentScope(current_scope);
  current_scope = (VSOPNode*) node;
  return Visitor::visitLetNode(node);
}

int FillScopeTablesVisitor::visitFormalNode(FormalNode *node){
  return 0;
}

int FillScopeTablesVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){
  TypeIdentifierNode* obj_type = current_scope->getDeclarationType(node->getLiteral());
  if(!obj_type && node->getLiteral() != "self"){
    cerr << "erreur variable \"" << node->getLiteral() << "\" utilisée avant déclaration(line:" << node->getLine() << " col:" << node->getCol() << ")" << endl;
    return -6;
  }
  node->setType(obj_type);
  return 0;
}

int FillScopeTablesVisitor::visitCallNode(CallNode *node){
  node->setCurrentClass(current_class);
  if(node->getObject())
    return node->getObject()->accept(this);
  return 0;
}
