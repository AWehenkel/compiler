#include "ArgsNode.hpp"
#include "Expression/ExpressionNode.hpp"

using namespace std;

string ArgsNode::getLiteral() const {

	string literal;
	literal += "[";
	for (vector<ExpressionNode*>::const_iterator it = expressions.begin(); it != expressions.end(); ++it) {
		literal += (*it)->getLiteral();
		if (it+1 != expressions.end())
			literal += ", ";
	}
	literal += "]";

	return literal;
}

void ArgsNode::addExpression(ExpressionNode *expression) { expressions.push_back(expression);}

void ArgsNode::insertExpr(ExpressionNode *expression) { expressions.insert(expressions.begin(), expression);}

ArgsNode::~ArgsNode(){
	for (std::vector<ExpressionNode*>::const_iterator it = expressions.begin(); it < expressions.end(); ++it) {
		delete (*it);
	}
}
