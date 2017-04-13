#include "ExpressionNode.hpp"
#include "../TypeIdentifierNode.hpp"

ExpressionNode::ExpressionNode(std::string type, int col, int line) : VSOPNode(col, line){
  node_type = new TypeIdentifierNode(type);
}
