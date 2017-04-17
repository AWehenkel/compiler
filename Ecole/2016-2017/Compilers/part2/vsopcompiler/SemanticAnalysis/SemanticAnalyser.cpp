#include "SemanticAnalyser.hpp"
#include "../Visitors/CheckUndefinedClassVisitor.hpp"
#include "../Visitors/FillScopeTablesVisitor.hpp"
#include "../Visitors/CheckTypeVisitor.hpp"

using namespace std;

ProgramNode* SemanticAnalyser::semanticAnalysis(ProgramNode* program){
  classPass(program);
  return program;
}
//Attention à faire un destructeur!
int SemanticAnalyser::classPass(ProgramNode* program){
  unordered_map<string, ClassNode*> class_table;
  addStandardClass(class_table);

  if(program->fillClassTable(class_table) < 0)
    return -1;

  for(auto it = class_table.begin(); it != class_table.end(); ++it){
    if((it->second)->setParent(class_table) < 0)
      return -2;
  }

  for(auto it = class_table.begin(); it != class_table.end(); ++it)
    if((it->second)->inCycle()){
      cerr << "il y a un cycle et c'est pas cool" << endl;
      return -3;
    }
  //cout << "CheckUndefinedClassVisitor" << endl;
  CheckUndefinedClassVisitor *visitor = new CheckUndefinedClassVisitor();
  if (program->accept(visitor) < 0)
    return -4;
  //cout << "CheckUndefinedClassVisitor ok. FillScopeTablesVisitor" << endl;
  FillScopeTablesVisitor *visitor1 = new FillScopeTablesVisitor();
  if (program->accept(visitor1) < 0)
    return -5;
  //cout << "FillScopeTablesVisitor ok. CheckTypeVisitor" << endl;
  CheckTypeVisitor *visitor2 = new CheckTypeVisitor();
  if (program->accept(visitor2) < 0)
    return -6;

  return 0;
}

void SemanticAnalyser::addStandardClass(unordered_map<string, ClassNode*> &class_table){
  class_table["Object"] = new ClassNode(new TypeIdentifierNode("Object"), new ClassBodyNode());

  ClassBodyNode* body = new ClassBodyNode();
  class_table["IO"] = new ClassNode(new TypeIdentifierNode("IO"), body);

  FormalsNode* formals = new FormalsNode();
  formals->addFormal(new FormalNode(new ObjectIdentifierNode("s"), new TypeIdentifierNode("string")));
  class_table["IO"]->addMethod(new MethodNode(new ObjectIdentifierNode("print"), formals, new TypeIdentifierNode("IO", class_table["IO"]), new BlockNode()));

  formals = new FormalsNode();
  formals->addFormal(new FormalNode(new ObjectIdentifierNode("b"), new TypeIdentifierNode("bool")));
  class_table["IO"]->addMethod(new MethodNode(new ObjectIdentifierNode("printBool"), formals, new TypeIdentifierNode("IO", class_table["IO"]), new BlockNode()));

  formals = new FormalsNode();
  formals->addFormal(new FormalNode(new ObjectIdentifierNode("i"), new TypeIdentifierNode("int32")));
  class_table["IO"]->addMethod(new MethodNode(new ObjectIdentifierNode("printInt32"), formals, new TypeIdentifierNode("IO", class_table["IO"]), new BlockNode()));

  formals = new FormalsNode();
  class_table["IO"]->addMethod(new MethodNode(new ObjectIdentifierNode("inputLine"), formals, new TypeIdentifierNode("string"), new BlockNode()));

  formals = new FormalsNode();
  class_table["IO"]->addMethod(new MethodNode(new ObjectIdentifierNode("inputBool"), formals, new TypeIdentifierNode("bool"), new BlockNode()));

  formals = new FormalsNode();
  class_table["IO"]->addMethod(new MethodNode(new ObjectIdentifierNode("inputInt32"), formals, new TypeIdentifierNode("int32"), new BlockNode()));

}
