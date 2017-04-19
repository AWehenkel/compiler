#include "SemanticError.hpp"
#include "../SyntacticTree/VSOPNode.hpp"

std::string SemanticError::FILE_NAME = "";

std::string SemanticError::getErrorMessage() const{
  int line = m_context_node ? m_context_node->getLine() : 0;
  int col = m_context_node ? m_context_node->getCol() : 0;
  return FILE_NAME + ":" + std::to_string(line) + ":" + std::to_string(col) + ": semantic error: " + m_message;
}
