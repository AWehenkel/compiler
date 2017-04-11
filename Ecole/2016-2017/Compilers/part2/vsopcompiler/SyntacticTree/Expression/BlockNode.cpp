#include "BlockNode.hpp"

using namespace std;

string BlockNode::getLiteral() const {
	
	string literal;
	size_t expr_size = expressions.size();
	if (expr_size == 0) 
		//Not empty expression should be generated
		return "";		
	else if(expr_size == 1)
		literal += (*(expressions.begin()))->getLiteral();
	else {
		literal += "[";
		for (vector<ExpressionNode*>::const_iterator it = expressions.begin(); it < expressions.end(); ++it) {
			literal += (*it)->getLiteral();
			if (it+1 != expressions.end())		
				literal += ", ";
		}
		literal += "]";
	}

	return literal;
}

void BlockNode::addExpression(ExpressionNode *expression) { expressions.push_back(expression);}

void BlockNode::insertExpr(ExpressionNode *expression) { expressions.insert(expressions.begin(), expression);}
