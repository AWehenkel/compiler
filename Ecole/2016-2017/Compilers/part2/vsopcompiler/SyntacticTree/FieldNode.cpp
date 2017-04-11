#include "FieldNode.hpp"

using namespace std;

std::string FieldNode::getLiteral() const {

	string literal = "Field(" + e_name->getLiteral() + ", " + e_type->getLiteral();
	if(e_init_expr)
		literal += ", " + e_init_expr->getLiteral();
	literal += ")";

	return literal;
}
