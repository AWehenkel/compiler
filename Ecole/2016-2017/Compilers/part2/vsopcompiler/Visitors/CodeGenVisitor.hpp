#ifndef code_gen_visitor
#define code_gen_visitor

#include <stack>
#include "Visitor.hpp"

/*
* This class is used to visit the nodes in order to generate LLVM code.
*/
class CodeGenVisitor : public Visitor{
  private :
    std::stack<std::string> llvm_addresses; // TODO : possibly to remove
    std::stack<int> llvm_address_counters;
    std::string ir;
    std::string tab;
    VSOPNode* current_scope = NULL;
    bool external_call = false;
  public :
    std::string getLLVMAllocationCode(std::string type, std::string name);
    std::string getLLVMLoadCode(std::string load_in, std::string load_from, std::string type);
    std::string getLLVMStoreCode(std::string name, std::string store_address, std::string type);
    std::string getLLVMBitCastCode(std::string store_address, std::string first_type, std::string init_address, std::string second_type);
    std::string getLLVMCallCode(std::string function_name, std::string return_type, std::vector<std::string> args_value, std::vector<std::string> args_type);
    std::string getLLVMBinaryCode(BinaryOperatorNode* node, std::string op1, std::string op2);
    std::string getLLVMUnaryCode(UnaryOperatorNode* node, std::string op);
    std::string getLLVMGetElementPtr(std::string load_in, std::string type_struct, std::string load_from, size_t offset1, size_t offset2);

    int genExternalCallCode(CallNode* node);

    int visitAssignNode(AssignNode *node);
    int visitBinaryOperatorNode(BinaryOperatorNode *node);
    int visitBlockNode(BlockNode *node);
    // TODO : Brace Node à enlever, pas besoin à priori
    // int visitBraceNode(BraceNode *node);
    int visitCallNode(CallNode *node);
    int visitConditionalNode(ConditionalNode *node);
    int visitLetNode(LetNode *node);
    int visitLiteralNode(LiteralNode *node);
    int visitNewNode(NewNode *node);
    int visitObjectIdentifierNode(ObjectIdentifierNode *node);
    int visitUnaryOperatorNode(UnaryOperatorNode *node);
    int visitWhileNode(WhileNode *node);
    // int visitArgsNode(ArgsNode *node);
    // int visitClassBodyNode(ClassBodyNode *node);
    int visitClassNode(ClassNode *node);
    //int visitFieldNode(FieldNode *node);
    // int visitFormalNode(FormalNode *node);
    // int visitFormalsNode(FormalsNode *node);
    int visitMethodNode(MethodNode *node);
    int visitProgramNode(ProgramNode *node);
    //int visitTypeIdentifierNode(TypeIdentifierNode *node);
};

#endif //code_gen_visitor_hpp
