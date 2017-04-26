#include <string>

#include "CheckTypeVisitor.hpp"
#include "all_headers.hpp"

using namespace std;

int CheckTypeVisitor::visitAssignNode(AssignNode *node){
  //cout<<"AssignNode" << endl;

  // TODO : Choose how to organise the error management here!

  if(Visitor::visitAssignNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de assign " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitBinaryOperatorNode(BinaryOperatorNode *node){
  cout << "visitBinaryOperatorNode" << endl;
  if(Visitor::visitBinaryOperatorNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de binary " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitBlockNode(BlockNode *node){

  // TODO : check if it cannot be done in Visitor
  int error = 0;
   std::vector<ExpressionNode*> exprs = node->getExpressions();
   for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
     if((*it)->accept(this) < 0)
       error = -1;
   }
  /*if(Visitor::visitBlockNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de block " << std::endl;
    return -1;
  }*/

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    error = -1;
  }

  return error;

}


int CheckTypeVisitor::visitBraceNode(BraceNode *node){
//cout<<"visitBraceNode" << endl;
  if(Visitor::visitBraceNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de brace " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitCallNode(CallNode *node){
  //cout<<"visitCallNode" << endl;
  if(Visitor::visitCallNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de call " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitConditionalNode(ConditionalNode *node){
  //cout<<"visitConditionalNode" << endl;
  if(Visitor::visitConditionalNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de conditional " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitLetNode(LetNode *node){
  //cout << "visitLetNode" << endl;
  current_scope = (VSOPNode*) node;
  if(Visitor::visitLetNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de let " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitNewNode(NewNode *node){

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitUnaryOperatorNode(UnaryOperatorNode *node){
  //cout<<"visitUnaryOperatorNode" << endl;
  if(Visitor::visitUnaryOperatorNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de unary " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitWhileNode(WhileNode *node){
  //cout<<"visitWhileNode" << endl;
  if(Visitor::visitWhileNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de while " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitArgsNode(ArgsNode *node){

  // TODO : check if it cannot be done in Visitor
  int error = 0;
  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitClassBodyNode(ClassBodyNode *node){

  // TODO : check if it cannot be done in Visitor
  int error = 0;
  std::vector<FieldNode*> fields = node->getFields();
  for(std::vector<FieldNode*>::iterator it = fields.begin(); it != fields.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
  }

  std::vector<MethodNode*> methods = node->getMethods();
  for(std::vector<MethodNode*>::iterator it = methods.begin(); it != methods.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
  }

  return error;
}

int CheckTypeVisitor::visitFieldNode(FieldNode *node){
  if(Visitor::visitFieldNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de field " << std::endl;
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}


int CheckTypeVisitor::visitMethodNode(MethodNode *node){
  //cout<<"visitMethodNode" << endl;
  current_scope = (VSOPNode*) node;
  if(Visitor::visitMethodNode(node) < 0){
    return -1;
  }

  vector<SemanticError> errors_generated = node->updateType(this);
  if (errors_generated.size() > 0){
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    return -1;
  }

  return 0;
}



int CheckTypeVisitor::visitProgramNode(ProgramNode *node){

  // TODO : voir si on ne peut pas faire ça directement dans Visitor
  int error = 0;
  std::vector<ClassNode*> classes = node->getClasses();
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it){
    if((*it)->accept(this) < 0)
      error = -1;
    }

  return error;
}
