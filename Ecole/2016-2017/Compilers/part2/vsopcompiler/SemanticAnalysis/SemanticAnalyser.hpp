#ifndef semantic_analyser_hpp
#define semantic_analyser_hpp

#include "../all_headers.hpp"

/*
* This class is used to do the semantic analysis of the parse tree generated
* after parsing.
*/
class SemanticAnalyser{
private:
  /* createIOClass
  *ROLE: Create a ClassNode corresponding to the class IO
  *IN: -
  *OUT: pointer to the ClassNode
  */
  static ClassNode* createIOClass();

public:
  /* semanticAnalysis
  *ROLE: Do the necessary passes to do the semantic analysis
  *IN: pointer to the ProgramNode at the root of the parse tree
  *OUT : error number
  */
  static int semanticAnalysis(ProgramNode* program);
};

#endif
