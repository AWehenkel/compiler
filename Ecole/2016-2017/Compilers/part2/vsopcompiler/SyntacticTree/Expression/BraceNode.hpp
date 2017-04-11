#ifndef BraceNode_hpp
#define BraceNode_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"
/*
	Class used to represent a syntaxic node containing an empty brace expression
*/
class BraceNode : public ExpressionNode {
private :
	ExpressionNode* e_expr;

public :
	//Constructors:
	/*
	BraceNode
	IN:	expr:	ExpressionNode*, the expression in the parenthesis.
			col: 	int, the column where the node is present.
			line:	int, the line where the node is present.
	*/
	BraceNode(ExpressionNode* expr = NULL, int col = 0, int line = 0) : ExpressionNode(col, line), e_expr(expr){};

	//Destructor:
	~BraceNode(){delete e_expr;};

	//Public Methods:
	//getters
	ExpressionNode* getExpression() const{
		return e_expr;
	};

	//Inherited
	std::string getLiteral() const{
		std::string literal = "(";
		std::string s_expr = e_expr ? e_expr->getLiteral() : "";
		return literal + s_expr + ")";
	};

	int accept(Visitor* visitor){
		return visitor->visitBraceNode(this);
	};
};

#endif //BraceNode_hpp
