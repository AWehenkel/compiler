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

string FieldNode::getLiteral(bool with_type) const{

	string literal = "Field(" + e_name->getLiteral() + ", " + e_type->getLiteral(with_type);
	if(e_init_expr)
		literal += ", " + e_init_expr->getLiteral(with_type);
	literal += ")";

	return literal;
}
