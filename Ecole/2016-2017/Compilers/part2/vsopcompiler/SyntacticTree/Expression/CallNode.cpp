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
    cerr << "Error in the compiler in CallNode : object_type is null" << endl;
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
      cerr << "Error in the compiler in CallNode : formal_type or arg_type is null" << endl;
      return -1;
    }
    if(arg_type->getLiteral() == "error" != 0 && *arg_type != *formal_type){
      cerr << "La méthode du call contient des arguments qui ne sont pas du même type" << endl;
      node_type = new TypeIdentifierNode("error");
      return -1;
    }
    ++it;
  }

  cout << "return type" << endl;
  cout << method->getRetType()->getLiteral() << endl;
  node_type = new TypeIdentifierNode(method->getRetType()->getLiteral());


  return 0;

}

string CallNode::getLiteral() const{
<<<<<<< HEAD
  cout << "call" << " " << e_method_name->getLiteral() << " nom de la var " << e_object->getLiteral() << " type var " << e_object->getType()->getLiteral() <<  endl;
  if(e_object->getType()->getClassType()){
    cout << "ok class type"  << endl;
    if(e_object->getType()->getClassType()->getExtends())
      cout << "extends aussi" << endl;
    if(node_type && node_type->getClassType() && e_method_name->getLiteral() == "print"){
      cout << "ici ok" << endl;
      cout << node_type->getLiteral() << endl;
    }
    cout << "ok2" << endl;
  }

  string type = node_type ? " : " + node_type->getClassType()->getLiteral() : "";
  cout << "ok1" << endl;
  string obj = e_object ? e_object->getLiteral() : "self";
  cout << "ok2" << endl;
  if(e_method_name)
    cout << "e_method ok : " << e_method_name->getLiteral() << endl;
  if(e_args)
    cout << "e_args ok" << e_args->getLiteral() << endl;
  return "Call(" + obj + ", "  + e_method_name->getLiteral() + ", " + e_args->getLiteral() + ")" + type;
=======
  cout << "Object name" << endl;
  cout << e_object->getLiteral() << endl;

  string type = node_type ? " : " + node_type->getLiteral() : "";
  cout << "Call type" << endl;
  cout << type << endl;
  //string obj = e_object ? e_object->getLiteral() : "self";
  return "Call(" + e_object->getLiteral() + ", "  + e_method_name->getLiteral() + ", " + e_args->getLiteral() + ")" + type;
>>>>>>> be04c390746c409aa65f9774d6deec67a02fc9ab
}

CallNode::~CallNode(){delete e_args; delete e_object;}
