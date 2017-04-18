#include "ExpressionNode.hpp"
#include "../TypeIdentifierNode.hpp"

ExpressionNode::ExpressionNode(std::string type, int col, int line) : VSOPNode(col, line){
  node_type = new TypeIdentifierNode(type);
  self_type = true;
}

ExpressionNode::~ExpressionNode(){
  if(self_type && node_type)
    delete node_type;
}
