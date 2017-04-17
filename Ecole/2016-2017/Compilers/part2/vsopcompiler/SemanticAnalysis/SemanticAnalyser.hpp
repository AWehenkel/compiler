#ifndef semantic_analyser_hpp
#define semantic_analyser_hpp

#include <unordered_map>
#include <string>

#include "../all_headers.hpp"

class SemanticAnalyser{
private:
  static int classPass(ProgramNode* program);
  static void addStandardClass(std::unordered_map<std::string, ClassNode*> &class_table);
public:
  static ProgramNode* semanticAnalysis(ProgramNode* program);
};

#endif
