#include "CheckUndefinedClassVisitor.hpp"
#include "../SyntacticTree/TypeIdentifierNode.hpp"
#include "../SyntacticTree/ProgramNode.hpp"

using namespace std;

int CheckUndefinedClassVisitor::visitProgramNode(ProgramNode *node){

  // Get the class tables
  table_class = node->getTableClasses();

  // Get the classes
  std::vector<ClassNode*> classes = node->getClasses();
  bool as_main_class = false;
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it){
    as_main_class = (*it)->getName()->getLiteral() == "Main" ? true : as_main_class;
    if((*it)->accept(this) < 0 )
      return -1;
  }
  if(!as_main_class){
    cerr << "No Main class defined." << endl;
    return -1;
  }

  return 0;
}

int CheckUndefinedClassVisitor::visitTypeIdentifierNode(TypeIdentifierNode *node){

  std::string type_id = node->getLiteral();

  // Check if it is one the basic types
  if (type_id == "int32" || type_id == "bool"  || type_id == "string"  || type_id == "unit")
    return 0;

  // Check if it is the name of class
  if (table_class.find(type_id) == table_class.end())
    return -1;
  node->setClassType(table_class.find(type_id)->second);

  return 0;
}
