#include "FieldNode.hpp"
#include "ClassNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"

using namespace std;

FieldNode::~FieldNode(){
	delete e_name;
	delete e_type;
	delete e_init_expr;
}

string FieldNode::getLiteral(bool with_type) const {

	string literal = "Field(" + e_name->getLiteral(with_type) + ", " + e_type->getLiteral(with_type);
	if(e_init_expr)
		literal += ", " + e_init_expr->getLiteral(with_type);
	literal += ")";

	return literal;
}

vector<SemanticError> FieldNode::updateType(Visitor* visitor){

	  vector<SemanticError> errors;

	// Check if the type of the initialization expression if any
	if (e_init_expr){
		TypeIdentifierNode *init_expr_type = e_init_expr->getType();
		if (!init_expr_type){
			SemanticError error("Error in the compiler in ExpressionNode : init_expr_type is null", this);
	    errors.push_back(error);
			return errors;
		}

		if (init_expr_type->getLiteral() != "error" && init_expr_type->getLiteral() != e_type->getLiteral() &&
		 (!init_expr_type->getClassType() || !init_expr_type->getClassType()->hasParent(e_type->getClassType()))){
			 if (!e_type->getClassType()){
         SemanticError error("The initialization expression of a field must have the same type as the object: got '" + init_expr_type->getLiteral() + "' and need '" + e_type->getLiteral() + "'", this);
         errors.push_back(error);
       }else{
         SemanticError error("The initialization expression of a field must have a type that inherits from the object type : got '" + init_expr_type->getLiteral() + "' and need a children of '" + e_type->getLiteral() + "'", this);
         errors.push_back(error);
       }
			return errors;
		}
	}

	return errors;
}
