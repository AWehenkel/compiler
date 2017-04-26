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

vector<SemanticError> CallNode::updateType(Visitor* visitor){

  vector<SemanticError> errors;

  // Get the type of the object
  TypeIdentifierNode* object_type;
  if (!e_object){
    // If no objet identifier, the call is made on the current object
    object_type = current_class->getName();
  }
  else
    object_type = e_object->getType();

  if (!object_type){
    SemanticError error("Error in the compiler in CallNode : object_type is null", this);
		errors.push_back(error);
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return errors;
  }

  // Check if the call is indeed made on an object
  ClassNode* object_class = object_type->getClassType();
  if (!object_class){
    SemanticError error("Calls must be done on object : '" + object_type->getLiteral() + "' is not a class.", this);
		errors.push_back(error);
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return errors;
  }

  // Check if the method called exists for the given object
  MethodNode *method = object_class->getMethod(e_method_name->getLiteral());
  if (!method){
    SemanticError error("Undefined method '" + e_method_name->getLiteral() + " for object of type '" + object_type->getLiteral() + "'", this);
		errors.push_back(error);
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return errors;
  }

  // Check if the arguments correspond to the formals of the method
  FormalsNode *formals = method->getFormals();
  vector<FormalNode*> ls_formals = formals->getFormals();
  vector<ExpressionNode*> ls_args = e_args->getExpressions();
  if (ls_formals.size() != ls_args.size()){
    SemanticError error("Wrong number of argument in call : need " + to_string(ls_formals.size()) + " and got "  +  to_string(ls_args.size()), this);
		errors.push_back(error);
    node_type = new TypeIdentifierNode("error");
    self_type = true;
    return errors;
  }

  vector<ExpressionNode*>::const_iterator it = ls_args.begin();
  int i = 1;
  for(vector<FormalNode*>::const_iterator it2 = ls_formals.begin(); it2 != ls_formals.end(); ++it2){
    FormalNode* formal = *it2;
    ExpressionNode* arg = *it;
    TypeIdentifierNode* formal_type = formal->getType();
    TypeIdentifierNode* arg_type = arg->getType();
    if (!formal_type){
      SemanticError error("Error in the compiler in CallNode : formal_type is null", this);
  		errors.push_back(error);
      return errors;
    }
    if (!arg_type){
      SemanticError error("Error in the compiler in CallNode : arg_type is null", this);
  		errors.push_back(error);
      return errors;
    }

    if(arg_type->getLiteral() != "error" && *arg_type != *formal_type && (!arg_type->getClassType() || !arg_type->getClassType()->hasParent(formal_type->getClassType()))){
      SemanticError error("Type of argument " + to_string(i) + " in call does not correspond to type in method :  got '" + arg_type->getLiteral() + "' and needed '" + formal_type->getLiteral() + "'" , this);
  		errors.push_back(error);
      cerr << "La methode du call contient des arguments qui ne sont pas du même type" << endl;
      node_type = new TypeIdentifierNode("error");
      self_type = true;
      return errors;
    }
    ++it;
    ++i;
  }
  node_type = method->getRetType();

  return errors;

}
