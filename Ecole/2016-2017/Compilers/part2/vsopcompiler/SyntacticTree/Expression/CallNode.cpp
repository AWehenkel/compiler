#include "CallNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "../ClassNode.hpp"
#include "../MethodNode.hpp"
#include "../FormalsNode.hpp"
#include "../FormalNode.hpp"

using namespace std;

CallNode::~CallNode(){
  delete e_args;
  delete e_object;
  delete e_method_name;
}

string CallNode::getLiteral(bool with_type) const{

  string type = "";
  if(with_type)
    type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  string obj_name = e_object ? e_object->getLiteral(with_type) : "self";

  return "Call(" + obj_name + ", "  + e_method_name->getLiteral(with_type) + ", " + e_args->getLiteral(with_type) + ")" + type;
}
