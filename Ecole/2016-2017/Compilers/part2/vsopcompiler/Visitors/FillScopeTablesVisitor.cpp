#include <iostream>

#include "FillScopeTablesVisitor.hpp"
#include "../SyntacticTree/ClassNode.hpp"
#include "../SyntacticTree/MethodNode.hpp"
#include "../SyntacticTree/FieldNode.hpp"

using namespace std;

int FillScopeTablesVisitor::visitClassNode(ClassNode *node){
  current_class = node;
  return Visitor::visitClassNode(node);
}
int FillScopeTablesVisitor::visitMethodNode(MethodNode *node){
  if(!current_class || current_class->addMethod(node) < 0)
    return -5;
  return Visitor::visitMethodNode(node);
}
int FillScopeTablesVisitor::visitFieldNode(FieldNode *node){
  if(!current_class || current_class->addField(node) < 0)
    return -5;
  return Visitor::visitFieldNode(node);
}
