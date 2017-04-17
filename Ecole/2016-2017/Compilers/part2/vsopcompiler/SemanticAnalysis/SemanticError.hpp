#include "../SyntacticTree/VSOPNode.hpp"

class SemanticError{
private:
  std::string m_message;
  VSOPNode* m_context_node;

public:

  SemanticError(std::string message, VSOPNode* context_node) : m_message(message), m_context_node(context_node){};

  /*printError
  *ROLE: Print an error message according to the node where it occured and the
  *      pass when it occured
  */
  void printError(){
    std::cerr << m_message << "(" << m_context_node->getMessageNode() << ")" << std::endl;
  };
};