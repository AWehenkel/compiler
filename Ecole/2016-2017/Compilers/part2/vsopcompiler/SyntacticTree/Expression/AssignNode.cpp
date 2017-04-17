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
  if (expr_type->getLiteral() == "error" || *name_type == *expr_type){
    node_type = name_type;
    return 0;
  }

  // If the two types were different, assign "error" to e_name and return -1
  node_type = new TypeIdentifierNode("error");
  cerr << "!! Les deux types(" << name_type->getLiteral() <<" et " <<  expr_type->getLiteral() <<") sont differents dans assign" << endl;
  return -1;
}

string AssignNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
   type = node_type ? " : " + node_type->getLiteral(with_type) : "";
  return "Assign(" + e_name->getLiteral(false) + ", " + e_expr->getLiteral(with_type) + ")" + type;
}

AssignNode::~AssignNode(){delete e_name; delete e_expr;};
