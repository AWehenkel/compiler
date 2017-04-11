#ifndef semantic_analyser_hpp
#define semantic_analyser_hpp

#include "../all_headers.hpp"

class SemanticAnalyser{
private:
  static int classPass(ProgramNode* program);
public:
  static ProgramNode* semanticAnalysis(ProgramNode* program);
};

#endif
