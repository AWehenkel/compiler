#ifndef visitor_hpp
#define visitor_hpp

class ArgsNode;
class ClassBodyNode;
class ClassNode;
class FieldNode;
class FormalNode;
class FormalsNode;
class MethodNode;
class ProgramNode;
class TypeIdentifierNode;
class VSOPNode;
class AssignNode;
class BinaryOperatorNode;
class BlockNode;
class BraceNode;
class CallNode;
class ConditionalNode;
class ExpressionNode;
class LetNode;
class LiteralNode;
class NewNode;
class ObjectIdentifierNode;
class UnaryOperatorNode;
class WhileNode;

class Visitor {
  public :
    virtual int visitAssignNode(AssignNode *node);

    virtual int visitBinaryOperatorNode(BinaryOperatorNode *node);

    virtual int visitBlockNode(BlockNode *node);

    virtual int visitBraceNode(BraceNode *node);

    virtual int visitCallNode(CallNode *node);

    virtual int visitConditionalNode(ConditionalNode *node);

    virtual int visitLetNode(LetNode *node);

    virtual int visitLiteralNode(LiteralNode *node);

    virtual int visitNewNode(NewNode *node);

    virtual int visitObjectIdentifierNode(ObjectIdentifierNode *node);

    virtual int visitUnaryOperatorNode(UnaryOperatorNode *node);

    virtual int visitWhileNode(WhileNode *node);

    virtual int visitArgsNode(ArgsNode *node);

    virtual int visitClassBodyNode(ClassBodyNode *node);

    virtual int visitClassNode(ClassNode *node);

    virtual int visitFieldNode(FieldNode *node);

    virtual int visitFormalNode(FormalNode *node);

    virtual int visitFormalsNode(FormalsNode *node);

    virtual int visitMethodNode(MethodNode *node);

    virtual int visitProgramNode(ProgramNode *node);

    virtual int visitTypeIdentifierNode(TypeIdentifierNode *node);
};

#endif //visitor_hpp
