#include <cstring>

#include "FieldNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"

using namespace std;

string FieldNode::getLiteral() const {

	string literal = "Field(" + e_name->getLiteral() + ", " + e_type->getLiteral();
	if(e_init_expr)
		literal += ", " + e_init_expr->getLiteral();
	literal += ")";

	return literal;
}

int FieldNode::update(){

	if (e_init_expr){
		TypeIdentifierNode *init_expr_type = e_init_expr->getType();
		if (!init_expr_type){
			cerr << "Error in the compiler" << endl;
			return -1;
		}
		string s_init_expr_type = init_expr_type->getLiteral();

		if (strcmp(s_init_expr_type.c_str(), "error") != 0 || *init_expr_type != *e_type){
			cerr << "Pas le même type dans field" << endl;
			return -1;
		}
	}

	return 0;
}

FieldNode::~FieldNode(){
	delete e_name;
	delete e_type;
	delete e_init_expr;
}
