#ifndef semantic_error_hpp
#define semantic_error_hpp
#include <vector>
#include <iostream>
#include <string>

class VSOPNode;

class SemanticError{
private:
  std::string m_message;
  VSOPNode* m_context_node;

public:
  SemanticError(std::string message, VSOPNode* context_node = NULL) : m_message(message), m_context_node(context_node){};
  static std::string FILE_NAME;
  /*printError
  *ROLE: Print an error message according to the node where it occured and the
  *      pass when it occured
  */
  void printError() const{
    std::cout << getErrorMessage() << std::endl;
  };
  std::string getErrorMessage() const;
};

#endif
