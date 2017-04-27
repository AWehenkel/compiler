#ifndef code_gen_visitor
#define code_gen_visitor

#include "Visitor.hpp"

/*
* This class is used to visit the nodes in order to generate LLVM code.
*/
class CodeGenVisitor {
  private :
    std::stack<std::string> llvm_addresses;
    std::stack<int> llvm_address_counteurs;
    std::string ir;
  public :
    std::string getLLVMAllocationCode(std::string type);
    std::string getLLVMLoadCode(std::string load_in, std::string load_from, std::string type);
    std::string getLLVMBinaryCode(BinaryOperatorNode* node, std::string op1, std::string op2);
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
    int visitTypeIdentifierNode(TypeIdentifierNode *node);
};

#endif //code_gen_visitor_hpp
