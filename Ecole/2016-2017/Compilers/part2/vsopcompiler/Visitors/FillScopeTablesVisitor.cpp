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
#include "../SyntacticTree/Expression/AssignNode.hpp"
#include "../SyntacticTree/TypeIdentifierNode.hpp"
#include "../SyntacticTree/FormalNode.hpp"
#include "../SyntacticTree/FormalsNode.hpp"

using namespace std;

int FillScopeTablesVisitor::visitAssignNode(AssignNode *node){

  if(node->getName()->getLiteral() == "self"){
    cerr << "bizarre" << endl;
    SemanticError error("self assignment is forbiden.", node);
    //Error recovery consists in setting a type for self which is linked to the current class.
    TypeIdentifierNode* self_type = new TypeIdentifierNode(current_class->getName()->getLiteral(), current_class);
    node->getName()->setType(self_type, true);
    errors.push_back(error);
    int result = node->getExpression()->accept(this);
    if(result < 0)
      return -1;
    return 1 + result;
  }

  return Visitor::visitAssignNode(node);
}

int FillScopeTablesVisitor::visitCallNode(CallNode *node){

  node->setCurrentClass(current_class);
  if(!node->getObject()){
    if(!current_scope)//In this case we are in a field.
      return -1;
    node->setObject(new ObjectIdentifierNode("self"));
  }

  if(node->getObject()->accept(this) < 0)
    return -1;

  return node->getArgs()->accept(this);
}

int FillScopeTablesVisitor::visitLetNode(LetNode *node){

  node->setCurrentScope(current_scope);
  current_scope = (VSOPNode*) node;
  if(node->getObjectId()->getLiteral() == "self"){
    cerr << "in let: objct id cannot be self" << endl;
    return -1;
  }
  int result = Visitor::visitLetNode(node);
  current_scope = node->getCurrentScope();

  return result;
}

int FillScopeTablesVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){

  if(node->getLiteral() == "self"){
    node->setType(current_class->getName());
    return 0;
  }

  TypeIdentifierNode* obj_type = current_scope ? current_scope->getDeclarationType(node->getLiteral()) : NULL;
  if(!obj_type){
    cerr << "erreur variable \"" << node->getLiteral() << "\" utilisee avant declaration(line:" << node->getLine() << " col:" << node->getCol() << ")" << endl;
    return -6;
  }
  node->setType(obj_type);

  return 0;
}

int FillScopeTablesVisitor::visitClassNode(ClassNode *node){

  current_class = node;
  current_scope = NULL;

  if(Visitor::visitClassNode(node) < 0)
    return -1;

  if(node->getName()->getLiteral() == "Main"){
    MethodNode* main = node->getMethod("main");
    if(!main){
      cerr << "main pas défini dans la class Main" << endl;
      return -1;
    }
    if(main->getRetType()->getLiteral() != "int32"){
      cerr << "main pas défini en int32 dans la class Main" << endl;
      return -1;
    }
    if(main->getFormals()->getFormals().size()){
      cerr << "main ne prend pas d'arguments dans la class Main" << endl;
      return -1;
    }
  }

  return 0;
}

int FillScopeTablesVisitor::visitFieldNode(FieldNode *node){

  if(!current_class || current_class->addField(node) < 0 || node->getName()->getLiteral() == "self")
    return -5;
  node->setClassScope(current_class);
  ExpressionNode* init_expr = node->getInitExpr();
  if(init_expr)
    return init_expr->accept(this);

  return 0;
}

int FillScopeTablesVisitor::visitFormalNode(FormalNode *node){
  return 0;
}

int FillScopeTablesVisitor::visitFormalsNode(FormalsNode *node){

  vector<FormalNode*> formals = node->getFormals();
  //Ok for an inneficient search of doublon because we don't expect too much formals
  for(vector<FormalNode*>::iterator formal_it = formals.begin(); formal_it != formals.end(); ++formal_it)
    for(vector<FormalNode*>::iterator formal_it2 = formal_it + 1; formal_it2 != formals.end(); ++formal_it2)
      if(*((*formal_it)->getName()) == *((*formal_it2)->getName()))
        return -1;

  return 0;
}

int FillScopeTablesVisitor::visitMethodNode(MethodNode *node){

  current_scope = (VSOPNode*) node;

  if(node->getFormals()->accept(this) < 0 || !current_class || current_class->addMethod(node) < 0)
    return -5;
  node->setClassScope(current_class);
  current_method = node;

  return node->getBlock()->accept(this);
}
