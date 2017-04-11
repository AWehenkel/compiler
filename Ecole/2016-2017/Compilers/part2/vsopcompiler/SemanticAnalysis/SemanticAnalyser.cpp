#include <unordered_map>
#include <string>
#include "SemanticAnalyser.hpp"
#include "../Visitors/CheckUndefinedClassVisitor.hpp"
using namespace std;

ProgramNode* SemanticAnalyser::semanticAnalysis(ProgramNode* program){
  cout << classPass(program) << endl;
  return program;
}

int SemanticAnalyser::classPass(ProgramNode* program){
  unordered_map<string, ClassNode*> class_table;
  if(program->fillClassTable(class_table) < 0)
    return -1;
  for(auto it = class_table.begin(); it != class_table.end(); ++it)
    if((it->second)->setParent(class_table) < 0)
      return -2;

  for(auto it = class_table.begin(); it != class_table.end(); ++it)
    if((it->second)->inCycle()){
      cerr << "il y a un cycle et c'est pas cool" << endl;
      return -3;
    }

  CheckUndefinedClassVisitor *visitor;
  if (program->accept(visitor) < 0)
    cerr << "Type inconnu" << endl;

  return 0;
}
