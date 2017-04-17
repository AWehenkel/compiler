#include "CallNode.hpp"
#include "../TypeIdentifierNode.hpp"
#include "../ClassNode.hpp"
#include "../MethodNode.hpp"
#include "../FormalsNode.hpp"
#include "../FormalNode.hpp"

using namespace std;

int CallNode::updateType(){

  // Get the type of the object
  TypeIdentifierNode* object_type;
  if (!e_object){
    cerr << "pas d'objet defini sur " << e_method_name->getLiteral() << endl;
    object_type = current_class->getName();
  }
  else
    object_type = e_object->getType();

  if (!object_type){
    cerr << "Error in the compiler in CallNode : object_type is null" << endl;
    return -1;
  }

  ClassNode* object_class = object_type->getClassType();
  if (!object_class){
    cerr << "L'objet (" << object_type->getLiteral(true) << ") du call (" << e_method_name->getLiteral() << ") n'est pas une classe" << endl;
    cerr << object_type->getLiteral() << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }

  MethodNode *method = object_class->getMethod(e_method_name->getLiteral());
  if (!method){
    cerr << "La methode du call n'est pas definie pour cet objet" << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }

  FormalsNode *formals = method->getFormals();
  vector<FormalNode*> ls_formals = formals->getFormals();
  vector<ExpressionNode*> ls_args = e_args->getExpressions();
  if (ls_formals.size() != ls_args.size()){
    cerr << "La methode du call ne contient pas le bon nombre d'argument" << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }

  vector<ExpressionNode*>::const_iterator it = ls_args.begin();
  for(vector<FormalNode*>::const_iterator it2 = ls_formals.begin(); it2 != ls_formals.end(); ++it2){
    FormalNode* formal = *it2;
    ExpressionNode* arg = *it;
    TypeIdentifierNode* formal_type = formal->getType();
    TypeIdentifierNode* arg_type = arg->getType();
    if (!formal_type || !arg_type){
      cerr << formal->getLiteral(true) << endl;
      cerr << arg->getLiteral(true) << endl;
      cerr << "Error in the compiler in CallNode : formal_type or arg_type is null(l: " << e_method_name->getLine() << ", c: " << e_method_name->getCol() << ")" << endl;
      return -1;
    }

    if(arg_type->getLiteral() != "error" && *arg_type != *formal_type && (!arg_type->getClassType() || !arg_type->getClassType()->hasParent(formal_type->getClassType()))){
      cerr << "La methode du call contient des arguments qui ne sont pas du même type" << endl;
      node_type = new TypeIdentifierNode("error");
      return -1;
    }
    ++it;
  }
  node_type = method->getRetType();

  return 0;

}

string CallNode::getLiteral(bool with_type) const{
  string type = "";
  if(with_type)
    type = node_type ? " : " + node_type->getLiteral(with_type) : "";

  string obj_name = e_object ? e_object->getLiteral(with_type) : "self";

  return "Call(" + obj_name + ", "  + e_method_name->getLiteral(with_type) + ", " + e_args->getLiteral(with_type) + ")" + type;
}

CallNode::~CallNode(){delete e_args; delete e_object;}
