#ifndef semantic_analyser_hpp
#define semantic_analyser_hpp

#include "../all_headers.hpp" // TODO : réappliquer include-what-you-use

/*
* This class is used to do the semantic analysis of the parse tree generated
* after parsing.
*/
class SemanticAnalyser{
public:
  /* semanticAnalysis
  *ROLE: Do the necessary passes to do the semantic analysis
  *IN: pointer to the ProgramNode at the root of the parse tree
  *OUT : error number
  */
  static int semanticAnalysis(ProgramNode* program);
};

#endif // semantic_analyser_hpp
