#ifndef code_gen_visitor
#define code_gen_visitor

#include <stack>
#include "Visitor.hpp"

/*
* This class is used to visit the nodes in order to generate LLVM code.
*/
class CodeGenVisitor : public Visitor{
private :
    int addr_counter;
    std::string ir;
    std::string tab;
    VSOPNode* current_scope = NULL;
    ClassNode* current_class = NULL;
    bool external_call = false;

public :

    // Accesor
    std::string getIR(){return ir;}

    // Automatic LLVM code generators
    std::string getLLVMAllocationCode(std::string type, std::string name);
    std::string getLLVMLoadCode(std::string load_in, std::string load_from, std::string type);
    std::string getLLVMStoreCode(std::string name, std::string store_address, std::string type);
    std::string getLLVMBitCastCode(std::string store_address, std::string first_type, std::string init_address, std::string second_type);
    std::string getLLVMCallCode(std::string function_name, std::string return_type, std::vector<std::string> args_value, std::vector<std::string> args_type);
    std::string getLLVMBinaryCode(BinaryOperatorNode* node, std::string op1, std::string op2);
    std::string getLLVMUnaryCode(UnaryOperatorNode* node, std::string op);
    std::string getLLVMGetElementPtr(std::string load_in, std::string type_struct, std::string load_from, size_t offset1, size_t offset2);
    std::string getLLVMReturnCode(std::string address, std::string type);

    /*
    genExternalCallCode
    ROLE : generate LLVM code for calls on functions defined in external classes
    IN : a CallNode object representing a call
    OUT : int, error code
    */
    int genExternalCallCode(CallNode* node);

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
    int visitClassBodyNode(ClassBodyNode *node);
    int visitClassNode(ClassNode *node);
    int visitMethodNode(MethodNode *node);
    int visitProgramNode(ProgramNode *node);
};

#endif //code_gen_visitor_hpp
