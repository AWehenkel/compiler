#include <string>

#include "CheckTypeVisitor.hpp"
#include "all_headers.hpp"

using namespace std;

int CheckTypeVisitor::visitAssignNode(AssignNode *node){
  //cout"AssignNode" << endl;
  if(Visitor::visitAssignNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de assign " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de assign " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitBinaryOperatorNode(BinaryOperatorNode *node){
  //cout"visitBinaryOperatorNode" << endl;
  if(Visitor::visitBinaryOperatorNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de binary " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
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

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de block " << std::endl;
    return -1;
  }

  return 0;

}

int CheckTypeVisitor::visitBraceNode(BraceNode *node){
//cout"visitBraceNode" << endl;
  if(Visitor::visitBraceNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de brace " << std::endl;
    return -1;
  }
//cout"visitBraceNode update" << endl;
  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de brace " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitCallNode(CallNode *node){
//cout"visitCallNode" << endl;
  if(Visitor::visitCallNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de call " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de call " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitConditionalNode(ConditionalNode *node){
//cout"visitConditionalNode" << endl;
  if(Visitor::visitConditionalNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de conditional " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de conditional " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitLetNode(LetNode *node){
  //cout"visitLetNode" << endl;
  current_scope = (VSOPNode*) node;
  if(Visitor::visitLetNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de let " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de let " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitNewNode(NewNode *node){
  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de method " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitUnaryOperatorNode(UnaryOperatorNode *node){
//cout"visitUnaryOperatorNode" << endl;
  if(Visitor::visitUnaryOperatorNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de unary " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de unary " << std::endl;
    return -1;
  }

  return 0;
}

int CheckTypeVisitor::visitWhileNode(WhileNode *node){
//cout"visitWhileNode" << endl;
  if(Visitor::visitWhileNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de while " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
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

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de field " << std::endl;
    return -1;
  }

  return 0;
}


int CheckTypeVisitor::visitMethodNode(MethodNode *node){
  //cout"visitMethodNode" << endl;
  current_scope = (VSOPNode*) node;
  if(Visitor::visitMethodNode(node) < 0){
    std::cerr << "Erreur dans le type des fils de method " << std::endl;
    return -1;
  }

  if (node->updateType(this) < 0){
    std::cerr << "Erreur dans le type de method " << std::endl;
    return -1;
  }

  return 0;
}
