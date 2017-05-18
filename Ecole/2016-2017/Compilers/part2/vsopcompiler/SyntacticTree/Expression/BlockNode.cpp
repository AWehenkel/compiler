#include "BlockNode.hpp"

using namespace std;

BlockNode::~BlockNode(){
	for(vector<ExpressionNode*>::iterator it = expressions.begin(); it != expressions.end(); ++it)
		delete *it;
}

string BlockNode::getLiteral(bool with_type) const {

	string literal;
	string type = "";
	if(with_type){
	 type = node_type ? " : " + node_type->getLiteral(with_type) : "";
 	}

	size_t expr_size = expressions.size();
	if (expr_size == 0)
		//No empty expression should be generated
		return "";
	else if(expr_size == 1)
		literal += (*(expressions.begin()))->getLiteral(with_type);
	else {
		literal += "[";
		for (vector<ExpressionNode*>::const_iterator it = expressions.begin(); it < expressions.end(); ++it) {
			literal += (*it)->getLiteral(with_type);
			if (it+1 != expressions.end())
				literal += ", ";
		}
		literal += "]" + type;
	}

	return  literal;
}

void BlockNode::addExpression(ExpressionNode *expression){
	expressions.push_back(expression);
}

void BlockNode::insertExpr(ExpressionNode *expression){
	expressions.insert(expressions.begin(), expression);
}
