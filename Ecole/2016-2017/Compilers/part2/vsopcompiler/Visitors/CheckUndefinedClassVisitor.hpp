#ifndef check_undefined_class_visitor_hpp
#define check_undefined_class_visitor_hpp

#include "Visitor.hpp"

class CheckUndefinedClassVisitor : public Visitor {
  private :
    std::unordered_map<std::string, ClassNode*> table_class;
  public :
    int visitAssignNode(AssignNode *node);
    int visitBinaryOperatorNode(BinaryOperatorNode *node);
    int visitBlockNode(BlockNode *node);
    int visitBraceNode(BraceNode *node);
    int visitCallNode(CallNode *node);
    int visitConditionalNode(ConditionalNode *node);
    int visitLetNode(LetNode *node);
    int visitLiteralNode(LiteralNode *node);
    int visitNewNode(NewNode *node);
    int visitObjectIdentifierNode(ObjectIdentifierNode *node);
    int visitUnaryOperatorNode(UnaryOperatorNode *node);
    int visitWhileNode(WhileNode *node);
    int visitArgsNode(ArgsNode *node);
    int visitClassBodyNode(ClassBodyNode *node);
    int visitClassNode(ClassNode *node);
    int visitFieldNode(FieldNode *node);
    int visitFormalNode(FormalNode *node);
    int visitFormalsNode(FormalsNode *node);
    int visitMethodNode(MethodNode *node);
    int visitProgramNode(ProgramNode *node);
}

#endif //check_undefined_class_visitor_hpp
