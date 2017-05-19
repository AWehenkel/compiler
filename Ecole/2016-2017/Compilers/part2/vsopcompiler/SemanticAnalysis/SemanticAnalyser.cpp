#include "SemanticAnalyser.hpp"
#include "../Visitors/CheckUndefinedClassVisitor.hpp"
#include "../Visitors/FillScopeTablesVisitor.hpp"
#include "../Visitors/CheckTypeVisitor.hpp"
#include "../SyntacticTree/Expression/CallNode.hpp"

using namespace std;

std::ostream& operator << (std::ostream& out, const std::vector<SemanticError>& errors){
  for(std::vector<SemanticError>::const_iterator it = errors.begin(); it < errors.end(); ++it)
    out << it->getErrorMessage() << std::endl;
  return out;
};

int SemanticAnalyser::semanticAnalysis(ProgramNode* program){

  vector<SemanticError> errors;
  unordered_map<string, ClassNode*> class_table;

  // Fill the class table with the other class in the program
  SemanticError result_fill = program->fillClassTable(class_table);
  if(result_fill.isValid()){
    errors.push_back(result_fill);
    cerr << errors;
    // Directly exit because a doublon in the class name would lead to incoherent error detection
    return 1;
  }

  // Set the parents of each class (Object if no parents specified)
  for(auto it = class_table.begin(); it != class_table.end(); ++it){
    if(it->first != "Object" && (it->second)->setParent(class_table) < 0){
      SemanticError error("Unable to find parent class(" + it->second->getExtends()->getLiteral() + ") of class: " + it->first, it->second);
      errors.push_back(error);
      //Recovery by setting the parent at Object by default.
      delete it->second->getExtends();
      it->second->setExtends(new TypeIdentifierNode("Object"));
    }
  }

  // Check for cycles
  for(auto it = class_table.begin(); it != class_table.end(); ++it){
    if((it->second)->inCycle()){
      SemanticError error("Inheritance cycle detetected between class: " + it->first + " and class: " + it->second->getExtends()->getLiteral(), it->second);
      errors.push_back(error);
      //Recovery by setting the parent at Object by default.
      delete it->second->getExtends();
      it->second->setExtends(new TypeIdentifierNode("Object"));
    }
  }

  // Check if any unkown class is used
  CheckUndefinedClassVisitor *visitor = new CheckUndefinedClassVisitor();
  int result = program->accept(visitor);
  if(result){
    vector<SemanticError> errors_generated = visitor->getErrors();
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    //If negative then it is an unrecoverable error.
    if(result < 0){
      delete visitor;
      cerr << errors;
      return errors.size();
    }
  }
  delete visitor;

  // Record all the methods, fields and local variables
  FillScopeTablesVisitor *visitor1 = new FillScopeTablesVisitor();
  result = program->accept(visitor1);
  if(result){
    vector<SemanticError> errors_generated = visitor1->getErrors();
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    //Always consider it is an unrecoverable error.
    delete visitor1;
    cerr << errors;
    return errors.size();
  }
  delete visitor1;


  // Check all the types
  CheckTypeVisitor *visitor2 = new CheckTypeVisitor();
  result = program->accept(visitor2);
  if (result){
    vector<SemanticError> errors_generated = visitor2->getErrors();
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
  }
  delete visitor2;

  cerr << errors;
  return errors.size();
}
