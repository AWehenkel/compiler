#ifndef semantic_error_hpp
#define semantic_error_hpp

#include <iostream>
#include <string>

class VSOPNode;

class SemanticError{
private:
  std::string m_message;
  VSOPNode* m_context_node;
  bool is_valid = true;

public:

  static std::string FILE_NAME;

  //Construtors:
  SemanticError(std::string message, VSOPNode* context_node = NULL) : m_message(message), m_context_node(context_node){};
  SemanticError() : is_valid(false){};

  /*printError
  *ROLE: Print an error message according to the node where it occured and the
  *      pass when it occured
  */
  void printError() const{
    std::cout << getErrorMessage() << std::endl;
  };

  /*
  getErrorMessage
  ROLE : generate an error message from the content of the object
  OUT : string, the error message
  */
  std::string getErrorMessage() const;

  // TODO : ça sert à quoi ça ?
  bool isValid() const{
    return is_valid;
  };
};

#endif
