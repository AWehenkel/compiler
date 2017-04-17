#ifndef check_undefined_class_visitor_hpp
#define check_undefined_class_visitor_hpp

#include <unordered_map>
#include <string>
#include "Visitor.hpp"

/*
* This class is a subclass of the Visitor. Its purpose is to
* create the check that no type in the code corresponds to an unknown class
*/
class CheckUndefinedClassVisitor : public Visitor {
private :
  std::unordered_map<std::string, ClassNode*> table_class;

public :
  int visitProgramNode(ProgramNode *node);
  int visitTypeIdentifierNode(TypeIdentifierNode *node);
};

#endif //check_undefined_class_visitor_hpp
