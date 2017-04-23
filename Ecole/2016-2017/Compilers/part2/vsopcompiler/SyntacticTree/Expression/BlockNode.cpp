#include "BlockNode.hpp"
#include "../TypeIdentifierNode.hpp"

using namespace std;

void BlockNode::addExpression(ExpressionNode *expression){
	expressions.push_back(expression);
}

void BlockNode::insertExpr(ExpressionNode *expression){
	expressions.insert(expressions.begin(), expression);
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

vector<SemanticError> BlockNode::updateType(Visitor* visitor){

	 vector<SemanticError> errors;

	string type;
	for (vector<ExpressionNode*>::iterator it = expressions.begin(); it != expressions.end(); ++it)
		ExpressionNode *expr = *it;

	ExpressionNode *last_expr = *(expressions.end()-1);
	TypeIdentifierNode *expr_type = last_expr->getType();
	if (!expr_type){
		SemanticError error("Error in the compiler in BlockNode : expr_type is null", this);
		errors.push_back(error);
		return errors;
	}
	// Put the type of the last instruction, even if it was an error.
	node_type = expr_type;

	/* Even if there is an error in the last instruction, it wasn't in the block
	* directly, so we don't return an error code
	*/
	return errors;
}

BlockNode::~BlockNode(){
	for(vector<ExpressionNode*>::iterator it = expressions.begin(); it != expressions.end(); ++it)
		delete *it;
}
