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
  cout << "ça marche comme il faut method " << endl;
  if(!current_class)
    return -5;
  return current_class->addMethod(node);
}
int FillScopeTablesVisitor::visitFieldNode(FieldNode *node){
  cout << "ça marche comme il faut field" << endl;
  if(!current_class)
    return -5;
  return current_class->addField(node);
}
