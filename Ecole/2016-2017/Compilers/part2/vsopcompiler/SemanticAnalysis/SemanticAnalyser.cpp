#include "SemanticAnalyser.hpp"
#include "../Visitors/CheckUndefinedClassVisitor.hpp"
#include "../Visitors/FillScopeTablesVisitor.hpp"
#include "../Visitors/CheckTypeVisitor.hpp"

using namespace std;

int SemanticAnalyser::semanticAnalysis(ProgramNode* program){
  
  unordered_map<string, ClassNode*> class_table;
  // Adding Object class to the class table
  class_table["Object"] = new ClassNode(new TypeIdentifierNode("Object"), new ClassBodyNode());
  // Adding IO class to the class table (maybe good to replace with include system)
  ClassNode* io_class = createIOClass();
  program->addClass(io_class);

  // Fill the class table with the other class in the program
  if(program->fillClassTable(class_table) < 0){
    cerr << "fill class table n'a pas fonctionne :'(" << endl;
    return -1;
  }

  // Set the parents of each class (Object if no parents specified)
  for(auto it = class_table.begin(); it != class_table.end(); ++it){
    if(it->first != "Object" && (it->second)->setParent(class_table) < 0){
      cerr << "Pas reussi à set le parent" << endl;
      return -2;
    }
  }

  // Check for cycles
  for(auto it = class_table.begin(); it != class_table.end(); ++it)
    if((it->second)->inCycle()){
      cerr << "il y a un cycle et c'est pas cool" << endl;
      return -3;
    }

  // Check if any unkown class is used
  CheckUndefinedClassVisitor *visitor = new CheckUndefinedClassVisitor();
  if (program->accept(visitor) < 0){
    cerr << "problem in CheckUndefinedClassVisitor" << endl;
    return -4;
  }

  // Record all the methods, fields and local variables
  FillScopeTablesVisitor *visitor1 = new FillScopeTablesVisitor();
  if (program->accept(visitor1) < 0){
    cerr << "problem in FillScopeTablesVisitor" << endl;
    return -5;
  }

  // Check all the types
  CheckTypeVisitor *visitor2 = new CheckTypeVisitor();
  if (program->accept(visitor2) < 0){
    cerr << "problem in CheckTypeVisitor" << endl;
    return -6;
  }

  // Remove IO class for the class table
  program->removeClass(io_class);
  return 0;
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
