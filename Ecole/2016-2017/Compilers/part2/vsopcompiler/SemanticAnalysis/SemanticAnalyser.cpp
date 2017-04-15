#include <unordered_map>
#include <string>
#include "SemanticAnalyser.hpp"
#include "../Visitors/CheckUndefinedClassVisitor.hpp"
#include "../Visitors/FillScopeTablesVisitor.hpp"
#include "../Visitors/CheckTypeVisitor.hpp"
using namespace std;

ProgramNode* SemanticAnalyser::semanticAnalysis(ProgramNode* program){
  classPass(program);
  return program;
}

int SemanticAnalyser::classPass(ProgramNode* program){
  unordered_map<string, ClassNode*> class_table;
  class_table["Object"] = new ClassNode(new TypeIdentifierNode("Object"), new ClassBodyNode());
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
