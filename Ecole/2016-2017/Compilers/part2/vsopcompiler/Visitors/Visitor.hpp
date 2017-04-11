#ifndef visitor_hpp
#define visitor_hpp

class Visitor {
  public :
    virtual int visitAssignNode(AssignNode *node) = 0;
    virtual int visitBinaryOperatorNode(BinaryOperatorNode *node) = 0;
    virtual int visitBlockNode(BlockNode *node) = 0;
    virtual int visitBraceNode(BraceNode *node) = 0;
    virtual int visitCallNode(CallNode *node) = 0;
    virtual int visitConditionalNode(ConditionalNode *node) = 0;
    virtual int visitLetNode(LetNode *node) = 0;
    virtual int visitLiteralNode(LiteralNode *node) = 0;
    virtual int visitNewNode(NewNode *node) = 0;
    virtual int visitObjectIdentifierNode(ObjectIdentifierNode *node) = 0;
    virtual int visitUnaryOperatorNode(UnaryOperatorNode *node) = 0;
    virtual int visitWhileNode(WhileNode *node) = 0;
    virtual int visitArgsNode(ArgsNode *node) = 0;
    virtual int visitClassBodyNode(ClassBodyNode *node) = 0;
    virtual int visitClassNode(ClassNode *node) = 0;
    virtual int visitFieldNode(FieldNode *node) = 0;
    virtual int visitFormalNode(FormalNode *node) = 0;
    virtual int visitFormalsNode(FormalsNode *node) = 0;
    virtual int visitMethodNode(MethodNode *node) = 0;
    virtual int visitProgramNode(ProgramNode *node) = 0;
}

#endif //visitor_hpp
