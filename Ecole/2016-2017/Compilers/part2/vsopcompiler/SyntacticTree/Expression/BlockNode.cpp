#include "BlockNode.hpp"
#include "../TypeIdentifierNode.hpp"

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

int BlockNode::updateType(){

	string type;

	ExpressionNode *last_expr = *(expressions.end()-1);
	TypeIdentifierNode *expr_type = last_expr->getType();
	if (!expr_type)
		type = expr_type->getLiteral();
	else{
		cerr << "Error in the compiler" << endl;
		return -1;
	}
	// Put the type of the last instruction, even if it was an error.
	node_type = new TypeIdentifierNode(type);

	/* Even if there is an error in the last instruction, it wasn't in the block
	* directly, so we don't return an error code
	*/
	return 0;
}
