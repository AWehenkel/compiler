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

  // Check for forbidden assignment on self
  if(node->getName()->getLiteral() == "self"){

    SemanticError error("Self assignment is forbiden.", node);

    //Error recovery consists in setting a type for self which is linked to the current class.
    TypeIdentifierNode* self_type = new TypeIdentifierNode(current_class->getName()->getLiteral(), current_class);
    node->getName()->setType(self_type, true);
    errors.push_back(error);

    if(node->getExpression()->accept(this) < 0)
      return -1;

    return errors.size();
  }

  return Visitor::visitAssignNode(node);
}

int FillScopeTablesVisitor::visitCallNode(CallNode *node){

  // Set which class the call is part of
  node->setCurrentClass(current_class);

  if(!node->getObject()){
    if(!current_scope){
      //In this case we are in a field so call is not authorized.
      SemanticError error("Field assignment with call to self function is forbiden.", node);
      errors.push_back(error);
    }
    node->setObject(new ObjectIdentifierNode("self"));
  }

  // Visit the object
  if(node->getObject()->accept(this) < 0)
    return -1;

  // Visit the args
  if(node->getArgs()->accept(this) < 0)
    return -1;

  return errors.size();
}

int FillScopeTablesVisitor::visitLetNode(LetNode *node){

  node->setCurrentScope(current_scope);
  current_scope = (VSOPNode*) node;
  if(node->getObjectId()->getLiteral() == "self"){
    SemanticError error("Let declaration variable name cannot be \"self\".", node);
    errors.push_back(error);
  }

  if (Visitor::visitLetNode(node) < 0)
    return -1;

  current_scope = node->getCurrentScope();

  return errors.size();
}

int FillScopeTablesVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){

  // In an objectidentifier, we set the type of the node directly during this pass
  // because we have the necessary information to do so
  if(node->getLiteral() == "self"){
    node->setType(current_class->getName());
    return errors.size();
  }

  TypeIdentifierNode* obj_type = current_scope ? current_scope->getDeclarationType(node->getLiteral()) : NULL;
  if(!obj_type){
    SemanticError error("Variable \"" + node->getLiteral() +"\" used before declaration.", node);
    errors.push_back(error);
    TypeIdentifierNode* var_type = new TypeIdentifierNode("error");
    node->setType(var_type, true);
    return errors.size();
  }
  node->setType(obj_type);

  return errors.size();
}

int FillScopeTablesVisitor::visitClassNode(ClassNode *node){

  current_class = node;
  current_scope = NULL;

  if(Visitor::visitClassNode(node) < 0)
    return -1;

  // If we are in the Main class, check that it contains the right method
  if(node->getName()->getLiteral() == "Main"){
    MethodNode* main = node->getMethod("main");
    if(!main){
      SemanticError error("Function main not defined in main class.", node);
      errors.push_back(error);
      return errors.size();
    }
    if(main->getRetType()->getLiteral() != "int32"){
      SemanticError error("Function main must return an int32.", main);
      errors.push_back(error);
    }
    if(main->getFormals()->getFormals().size()){
      SemanticError error("Function main must not take argument.", main);
      errors.push_back(error);
    }
  }

  return errors.size();
}

int FillScopeTablesVisitor::visitFieldNode(FieldNode *node){

  SemanticError error = current_class->addField(node);
  if(error.isValid()){
    errors.push_back(error);
    return -1;
  }
  if(node->getName()->getLiteral() == "self"){
    error = SemanticError("Cannot redeclare the field 'self'.", node);
    errors.push_back(error);
  }
  node->setClassScope(current_class);
  node->getName()->setType(node->getType());

  // Visit the init expression if there is one
  ExpressionNode* init_expr = node->getInitExpr();
  if(init_expr && init_expr->accept(this) < 0)
    return -1;

  return errors.size();
}

int FillScopeTablesVisitor::visitFormalNode(FormalNode *node){
  //The sub-nodes won't be visited.
  return errors.size();
}

int FillScopeTablesVisitor::visitFormalsNode(FormalsNode *node){

  vector<FormalNode*> formals = node->getFormals();
  //Ok for an inneficient search of doublons because we don't expect too much formals
  for(vector<FormalNode*>::iterator formal_it = formals.begin(); formal_it != formals.end(); ++formal_it){
    for(vector<FormalNode*>::iterator formal_it2 = formal_it + 1; formal_it2 != formals.end(); ++formal_it2){
      if(*((*formal_it)->getName()) == *((*formal_it2)->getName())){
        SemanticError error("Arguments of the function must have unique names.", *formal_it);
        errors.push_back(error);
        return errors.size();
      }
    }
  }

  return errors.size();
}

int FillScopeTablesVisitor::visitMethodNode(MethodNode *node){

  current_scope = (VSOPNode*) node;

  // TODO : ça sert à quoi le !current_class ?
  if(node->getFormals()->accept(this) < 0 || !current_class)
    return -1;

  SemanticError error = current_class->addMethod(node);
  if(error.isValid())
    errors.push_back(error);
  node->setClassScope(current_class);
  current_method = node;

  if(node->getBlock()->accept(this) < 0)
    return -1;

  return errors.size();
}
