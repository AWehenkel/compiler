#ifndef semantic_analyser_hpp
#define semantic_analyser_hpp

#include <unordered_map>
#include <string>

#include "../all_headers.hpp"

class SemanticAnalyser{
private:
  static int classPass(ProgramNode* program);
  static ClassNode* createIOClass();
public:
  static int semanticAnalysis(ProgramNode* program);
};

#endif
