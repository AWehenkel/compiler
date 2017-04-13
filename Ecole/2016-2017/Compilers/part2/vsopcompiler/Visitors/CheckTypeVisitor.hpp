#ifndef check_type_visitor
#define check_type_visitor

#include "Visitor.hpp"

/*
This class is a subclass of the Visitor.
Its purpose is to find any type errors.
*/
class CheckTypeVisitor : public Visitor {
  private :
    VSOPNode* current_scope;
  public :
    int visitAssignNode(AssignNode *node);
    int visitBinaryOperatorNode(BinaryOperatorNode *node);
    int visitBlockNode(BlockNode *node);
    int visitBraceNode(BraceNode *node);
    int visitCallNode(CallNode *node);
    int visitConditionalNode(ConditionalNode *node);
    int visitLetNode(LetNode *node);
    int visitUnaryOperatorNode(UnaryOperatorNode *node);
    int visitWhileNode(WhileNode *node);
    int visitFieldNode(FieldNode *node);
    int visitMethodNode(MethodNode *node);
};

#endif //check_type_visitor
