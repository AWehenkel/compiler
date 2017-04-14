#include "BraceNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

int BraceNode::updateType(){

  string type;

  TypeIdentifierNode *expr_type = e_expr->getType();
  if (!expr_type){
    cerr << "Error in the compiler in BraceNode : expr_type is null" << endl;
    return -1;
  }else{
    type = expr_type->getLiteral();
  }
  node_type = new TypeIdentifierNode(type);

  return 0;
}

string BraceNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  string literal = "(";
  string s_expr = e_expr ? e_expr->getLiteral(with_type) : "";
  return literal + s_expr + ")" + type;
}

BraceNode::~BraceNode(){delete e_expr;}
