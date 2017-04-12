#include <string>

#include "CheckTypeVisitor.hpp"
#include "all_headers.hpp"

int CheckTypeVisitor::visitAssignNode(AssignNode *node){

  if(Visitor::visitAssignNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de assign " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de assign " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitBinaryOperatorNode(BinaryOperatorNode *node){

  if(Visitor::visitBinaryOperatorNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de binary " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de binary " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitBlockNode(BlockNode *node){

  if(Visitor::visitBlockNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de block " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de block " << std::endl;
    return -1;
  }

  return 0;

}

int CheckTypeVisitor::visitBraceNode(BraceNode *node){

  if(Visitor::visitBraceNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de brace " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de brace " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitCallNode(CallNode *node){

  if(Visitor::visitCallNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de call " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de call " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitConditionalNode(ConditionalNode *node){

  if(Visitor::visitConditionalNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de conditional " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de conditional " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitLetNode(LetNode *node){

  if(Visitor::visitLetNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de let " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de let " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitLiteralNode(LiteralNode *node){

  if(Visitor::visitLiteralNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de literal " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de literal " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){

  if(Visitor::visitObjectIdentifierNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de object " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de object " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitUnaryOperatorNode(UnaryOperatorNode *node){

  if(Visitor::visitUnaryOperatorNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de unary " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de unary " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitWhileNode(WhileNode *node){

  if(Visitor::visitWhileNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de while " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de while " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitFieldNode(FieldNode *node){

  if(Visitor::visitFieldNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de field " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de field " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitFormalNode(FormalNode *node){

  if(Visitor::visitFormalNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de formal " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de formal " << std::endl;
    return -1;
  }

  return 0;

}

int CheckTypeVisitor::visitMethodNode(MethodNode *node){

  if(Visitor::visitMethodNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de method " << std::endl;
    return -1;
  }

  if (node->updateType() < 0){
    std::cerr << "Erreur dans le type de method " << std::endl;
    return -1;
  }

  return 0;
}
