#include <cstring>

#include "CheckUndefinedClassVisitor.hpp"
#include "../SyntacticTree/TypeIdentifierNode.hpp"
#include "../SyntacticTree/ProgramNode.hpp"

using namespace std;
int CheckUndefinedClassVisitor::visitProgramNode(ProgramNode *node){

  std::cerr << "Checking the program" << std::endl;
  // Get the class tables
  table_class = node->getTableClasses();

  // Get the classes
  std::vector<ClassNode*> classes = node->getClasses();
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }

  return 0;
}

int CheckUndefinedClassVisitor::visitTypeIdentifierNode(TypeIdentifierNode *node){

  std::string str = node->getLiteral();
  char * s = new char[str.size() + 1];
  std::copy(str.begin(), str.end(), s);
  s[str.size()] = '\0'; // don't forget the terminating 0

  // Check if it is not one the basic types
  if (!strcmp(s, "int32") || !strcmp(s, "bool")  || !strcmp(s, "string")  || !strcmp(s, "unit"))
    return 0;

  // Check if it is the name of class
  if (table_class.find(s) == table_class.end())
    return -1;

  return 0;

}
