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
  if (!e_object)
    object_type = current_class->getName();
  else
    object_type = e_object->getType();

  if (!object_type){
    cerr << "Error in the compiler" << endl;
    return -1;
  }

  ClassNode* object_class = object_type->getClassType();
  if (!object_class){
    cerr << "L'objet du call n'est pas une classe" << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }

  MethodNode *method = object_class->getMethod(e_method_name->getLiteral());
  if (!method){
    cerr << "La méthode du call n'est pas définie pour cet objet" << endl;
    node_type = new TypeIdentifierNode("error");
    return -1;
  }

  FormalsNode *formals = method->getFormals();
  vector<FormalNode*> ls_formals = formals->getFormals();
  vector<ExpressionNode*> ls_args = e_args->getExpressions();
  if (ls_formals.size() != ls_formals.size()){
    cerr << "La méthode du call ne contient pas le bon nombre d'argument" << endl;
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
      cerr << "Error in the compiler" << endl;
      return -1;
    }
    if(arg_type->getLiteral() == "error" != 0 && *arg_type != *formal_type){
      cerr << "La méthode du call contient des arguments qui ne sont pas du même type" << endl;
      node_type = new TypeIdentifierNode("error");
      return -1;
    }
    ++it;
  }

  node_type = method->getRetType();

  return 0;

}

string CallNode::getLiteral() const{
  string type = node_type ? " : " + node_type->getLiteral() : ""; if(node_type) cout << node_type->getLiteral() << endl;
  string obj = e_object ? e_object->getLiteral() : "self";
  return "Call(" + obj + ", "  + e_method_name->getLiteral() + ", " + e_args->getLiteral() + ")" + type;
}

CallNode::~CallNode(){delete e_args; delete e_object;}
