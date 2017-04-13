#include "FieldNode.hpp"
#include  "TypeIdentifierNode.hpp"

using namespace std;

std::string FieldNode::getLiteral() const {

	string literal = "Field(" + e_name->getLiteral() + ", " + e_type->getLiteral();
	if(e_init_expr)
		literal += ", " + e_init_expr->getLiteral();
	literal += ")";

	return literal;
}

int FieldNode::update(){

	if (e_init_expr){
		TypeIdentifierNode *init_expr_type = init_expr->getType();
		if (!init_expr_type){
			std::cerr << "Error in the compiler" << std::endl;
			return -1;
		}
		string s_init_expr_type = init_expr_type->getLiteral();

		if (strcmp(s_init_expr_type, "error") != 0 || *init_expr_type != *e_type){
			std::cerr << "Pas le même type dans field" << std::endl;
			return -1;
		}
	}

	return 0;
}
