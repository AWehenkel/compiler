#include "BlockNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

string BlockNode::getLiteral() const {

	string literal;
	string type = node_type ? " : " + node_type->getLiteral() : "";
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

	return literal + type;
}

void BlockNode::addExpression(ExpressionNode *expression) { expressions.push_back(expression);}

void BlockNode::insertExpr(ExpressionNode *expression) { expressions.insert(expressions.begin(), expression);}

int BlockNode::updateType(){

	string type;

	cout << "number of expressions in block" << endl;
	cout << expressions.size() << endl;
	for (vector<ExpressionNode*>::iterator it = expressions.begin(); it != expressions.end(); ++it){
		ExpressionNode *expr = *it;
		cout << "expression type is " << endl;
		if (!expr->getType()){
			cout << "bizarre" << endl;
		}
		cout << expr->getType()->getLiteral() << endl;
	}
	ExpressionNode *last_expr = *(expressions.end()-1);
	TypeIdentifierNode *expr_type = last_expr->getType();
	if (!expr_type){
		cerr << "Error in the compiler in BlockNode : expr_type is null" << endl;
		return -1;
	}else{
		type = expr_type->getLiteral();
	}
	// Put the type of the last instruction, even if it was an error.
	node_type = new TypeIdentifierNode(type);

	/* Even if there is an error in the last instruction, it wasn't in the block
	* directly, so we don't return an error code
	*/
	return 0;
}
