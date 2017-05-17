#ifndef code_gen_string_visitor
#define code_gen_string_visitor
#include <string>

#include "Visitor.hpp"

/*
* This class is used to visit the nodes in order to generate LLVM code.
*/
class CodeGenStringVisitor : public Visitor{
  private :
    int str_counter = 0;
    std::string ir;
    std::string transformStringInLLVMFormat(const std::string& lit) const;
  public :

    // Accesor
    std::string getIr(){return ir;}
    int visitLiteralNode(LiteralNode *node);
};

#endif //code_gen_string_visitor_hpp
