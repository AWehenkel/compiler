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
  if(program->fillClassTable(class_table)){
    SemanticError error("Internal failure of the compiler during the first pass."); // TODO : change error
    errors.push_back(error);
    cerr << errors;
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
  for(auto it = class_table.begin(); it != class_table.end(); ++it)
    if((it->second)->inCycle()){
      SemanticError error("Inheritance cycle detetected between class: " + it->first + " and class: " + it->second->getExtends()->getLiteral(), it->second);
      errors.push_back(error);
      //Recovery by setting the parent at Object by default. TODO changer pour que ça laisse tel quel et que toutes les fonctions qui peuvent dépendre d'un cycle soient robuste.
      delete it->second->getExtends();
      it->second->setExtends(new TypeIdentifierNode("Object"));
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
      return result;
    }
  }
  delete visitor;

  // Record all the methods, fields and local variables
  FillScopeTablesVisitor *visitor1 = new FillScopeTablesVisitor();
  int current_result = program->accept(visitor1);
  result += current_result;
  if(current_result){
    vector<SemanticError> errors_generated = visitor1->getErrors();
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    //If negative then it is an unrecoverable error.
    delete visitor1;
    cerr << errors;
    return current_result;
  }
  delete visitor1;


// Check all the types
  CheckTypeVisitor *visitor2 = new CheckTypeVisitor();
  result = program->accept(visitor2);
  if (result != 0){
    vector<SemanticError> errors_generated = visitor2->getErrors();
    errors.insert(errors.end(), errors_generated.begin(), errors_generated.end());
    delete visitor2;
    cerr << errors;
    return -6;
  }
  delete visitor2;

  cerr << errors;
  return errors.size();
}

ClassNode* SemanticAnalyser::createIOClass(){

  ClassBodyNode* body = new ClassBodyNode();
  ClassNode* io_class = new ClassNode(new TypeIdentifierNode("IO"), body);

  FormalsNode* formals = new FormalsNode();
  BlockNode* content = new BlockNode();
  content->addExpression(new NewNode(new TypeIdentifierNode("IO")));
  formals->addFormal(new FormalNode(new ObjectIdentifierNode("s"), new TypeIdentifierNode("string")));
  body->addMethod(new MethodNode(new ObjectIdentifierNode("print"), formals, new TypeIdentifierNode("IO"), content));

  formals = new FormalsNode();
  content = new BlockNode();
  content->addExpression(new NewNode(new TypeIdentifierNode("IO")));
  formals->addFormal(new FormalNode(new ObjectIdentifierNode("b"), new TypeIdentifierNode("bool")));
  body->addMethod(new MethodNode(new ObjectIdentifierNode("printBool"), formals, new TypeIdentifierNode("IO"), content));

  formals = new FormalsNode();
  content = new BlockNode();
  //ArgsNode args = new ArgsNode();
  //args->
  //content->addExpression(new CallNode(new ObjectIdentifierNode("printInt32"), ));
  content->addExpression(new NewNode(new TypeIdentifierNode("IO")));
  formals->addFormal(new FormalNode(new ObjectIdentifierNode("i"), new TypeIdentifierNode("int32")));
  body->addMethod(new MethodNode(new ObjectIdentifierNode("printInt32"), formals, new TypeIdentifierNode("IO"), content));

  formals = new FormalsNode();
  content = new BlockNode();
  content->addExpression(new LiteralNode("to_ret", "string"));
  body->addMethod(new MethodNode(new ObjectIdentifierNode("inputLine"), formals, new TypeIdentifierNode("string"), content));

  formals = new FormalsNode();
  content = new BlockNode();
  content->addExpression(new LiteralNode("true", "bool"));
  body->addMethod(new MethodNode(new ObjectIdentifierNode("inputBool"), formals, new TypeIdentifierNode("bool"), content));

  formals = new FormalsNode();
  content = new BlockNode();
  content->addExpression(new LiteralNode("42", "int32"));
  body->addMethod(new MethodNode(new ObjectIdentifierNode("inputInt32"), formals, new TypeIdentifierNode("int32"), content));

  return io_class;
}
