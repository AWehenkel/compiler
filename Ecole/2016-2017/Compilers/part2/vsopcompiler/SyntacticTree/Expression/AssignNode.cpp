#include <cstring>

#include "AssignNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "ObjectIdentifierNode.hpp"

using namespace std;

int AssignNode::updateType(){

  // Get types
  TypeIdentifierNode *name_type = e_name->getType();
  TypeIdentifierNode *expr_type = e_expr->getType();
  if(!name_type || !expr_type)
    cerr << "Error in the compiler in AssignNode : name_type or expr_type is null" << endl;

  /* It there was a type error in the son e_expr or if the two types are the
  * same, assign the type of e_name to node_type and stop the propagation of
  * errors */
  if (!strcmp(expr_type->getLiteral().c_str(), "error") || *name_type == *expr_type){
    node_type = new TypeIdentifierNode(name_type->getLiteral());
    return 0;
  }

  // If the two types were different, assign "error" to e_name and return -1
  node_type = new TypeIdentifierNode("error");
  cerr << "!! Les deux types sont différents dans assign" << endl;
  return -1;
}

string AssignNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : "";
  return "Assign(" + e_name->getLiteralWithoutType() + ", " + e_expr->getLiteral() + ")" + type;
}

AssignNode::~AssignNode(){delete e_name; delete e_expr;};
