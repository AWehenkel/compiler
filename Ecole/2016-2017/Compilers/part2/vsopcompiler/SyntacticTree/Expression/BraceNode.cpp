#include "BraceNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

int BraceNode::updateType(){

  string type;

  TypeIdentifierNode *expr_type = e_expr->getType();
  if (!expr_type)
    type = expr_type->getLiteral();
  else{
    cerr << "Error in the compiler" << endl;
    return -1;
  }
  node_type = new TypeIdentifierNode(type);

  return 0;
}

string BraceNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : ""; if(node_type) cout << node_type->getLiteral() << endl;
  string literal = "(";
  string s_expr = e_expr ? e_expr->getLiteral() : "";
  return literal + s_expr + ")" + type;
}

BraceNode::~BraceNode(){delete e_expr;}
