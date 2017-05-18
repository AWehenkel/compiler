#include "CheckUndefinedClassVisitor.hpp"
#include "../SyntacticTree/TypeIdentifierNode.hpp"
#include "../SyntacticTree/ProgramNode.hpp"

using namespace std;

int CheckUndefinedClassVisitor::visitProgramNode(ProgramNode *node){

  // Get the class tables
  table_class = node->getTableClasses();

  // Visit the classes and check if the Main class is indeed defined
  std::vector<ClassNode*> classes = node->getClasses();
  bool as_main_class = false;
  int to_ret = 0, current_result;
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it){
    as_main_class = (*it)->getName()->getLiteral() == "Main" ? true : as_main_class;
    current_result = (*it)->accept(this);
    if(current_result < 0 )
      return -1;
    to_ret += current_result;
  }
  if(!as_main_class){
    SemanticError error("No Main class defined.");
    errors.push_back(error);
  }

  return errors.size();
}

int CheckUndefinedClassVisitor::visitTypeIdentifierNode(TypeIdentifierNode *node){

  std::string type_id = node->getLiteral();

  // Check if the node is one of the basic types
  if (type_id == "int32" || type_id == "bool"  || type_id == "string"  || type_id == "unit")
    return errors.size();

  // Check if the node is the name of class
  if (table_class.find(type_id) == table_class.end()){
    SemanticError error("Unknown type: " + type_id, node);
    errors.push_back(error);

    node->setContent("error");
    return errors.size();
  }
  node->setClassType(table_class.find(type_id)->second);

  return errors.size();
}
