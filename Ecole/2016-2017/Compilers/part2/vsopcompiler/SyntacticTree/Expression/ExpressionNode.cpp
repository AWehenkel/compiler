#include "ExpressionNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

ExpressionNode::ExpressionNode(std::string type, int col, int line) : VSOPNode(col, line){
  node_type = new TypeIdentifierNode(type);
  self_type = true;
}

string ExpressionNode::getLLVMType(){
  return node_type ? node_type->getLLVMType() : "ERROR";
}

ExpressionNode::~ExpressionNode(){
  if(self_type && node_type)
    delete node_type;
}
