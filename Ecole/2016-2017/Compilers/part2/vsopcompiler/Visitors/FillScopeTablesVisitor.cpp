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
    SemanticError error("Self assignment is forbiden.", node);
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
  int to_ret = 0;
  if(!node->getObject()){
    if(!current_scope){
      //In this case we are in a field so call is not authorized.
      SemanticError error("Field assignment with call to self function is forbiden.", node);
      errors.push_back(error);
      to_ret = 1;
    }
    node->setObject(new ObjectIdentifierNode("self"));
  }
  int result = node->getObject()->accept(this);
  if(result < 0)
    return -1;
  to_ret += result;
  result = node->getArgs()->accept(this);
  if(result < 0)
    return -1;
  return to_ret + result;
}

int FillScopeTablesVisitor::visitLetNode(LetNode *node){

  node->setCurrentScope(current_scope);
  current_scope = (VSOPNode*) node;
  if(node->getObjectId()->getLiteral() == "self"){
    SemanticError error("Let declaration variable name cannot be \"self\".", node);
    errors.push_back(error);
    //TODO reflechir si c'est bien de retourner -1(erreur non recoverable), -1 pour le moment car c'est difficile d'analyser correctement le let si self est utilisé et donc
    //Beaucoup d'erreurs(et même des seg fautl pour le moment) en découlent.
    return 1;
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
    SemanticError error("Variable \"" + node->getLiteral() +"\" used before declaration.", node);
    errors.push_back(error);
    TypeIdentifierNode* var_type = new TypeIdentifierNode("error");
    node->setType(var_type, true);
    return 1;
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
      SemanticError error("Function main not defined in main class.", node);
      errors.push_back(error);
      return 1;
    }
    if(main->getRetType()->getLiteral() != "int32"){
      SemanticError error("Function main must return an int32.", main);
      errors.push_back(error);
      return 1;
    }
    if(main->getFormals()->getFormals().size()){
      SemanticError error("Function main must not take argument.", main);
      errors.push_back(error);
      return 1;
    }
  }

  return 0;
}

int FillScopeTablesVisitor::visitFieldNode(FieldNode *node){

  SemanticError error = current_class->addField(node);
  if(error.isValid()){
    errors.push_back(error);
    return -1;
  }
  if(node->getName()->getLiteral() == "self"){
    error = SemanticError("Self assignment is forbiden.", node);
    errors.push_back(error);
    //TODO voir si on peut pas continuer à analyser.
    return 1;
  }
  node->setClassScope(current_class);
  node->getName()->setType(node->getType());
  ExpressionNode* init_expr = node->getInitExpr();
  if(init_expr)
    return init_expr->accept(this);

  return 0;
}

int FillScopeTablesVisitor::visitFormalNode(FormalNode *node){
  //The sub-nodes won't be visited.
  return 0;
}

int FillScopeTablesVisitor::visitFormalsNode(FormalsNode *node){

  vector<FormalNode*> formals = node->getFormals();
  //Ok for an inneficient search of doublon because we don't expect too much formals
  for(vector<FormalNode*>::iterator formal_it = formals.begin(); formal_it != formals.end(); ++formal_it){
    for(vector<FormalNode*>::iterator formal_it2 = formal_it + 1; formal_it2 != formals.end(); ++formal_it2){
      if(*((*formal_it)->getName()) == *((*formal_it2)->getName())){
        SemanticError error("Arguments of the function must have unique names.", *formal_it);
        errors.push_back(error);
        //TODO reflechir si c'est bien d'arreter la compilation ou si on peut pas essayer de retirer la fonction des pass suivantes.
        return 1;
      }
    }
  }

  return 0;
}

int FillScopeTablesVisitor::visitMethodNode(MethodNode *node){

  current_scope = (VSOPNode*) node;
  int result_formals_pass = node->getFormals()->accept(this);
  if(result_formals_pass < 0 || !current_class )
    return -1;
  if(result_formals_pass)
    return result_formals_pass;
  SemanticError error = current_class->addMethod(node);
  if(error.isValid()){
    errors.push_back(error);
    //TODO voir si on peut pas continuer à analyser.
    return 1;
  }
  node->setClassScope(current_class);
  current_method = node;

  return node->getBlock()->accept(this);
}
