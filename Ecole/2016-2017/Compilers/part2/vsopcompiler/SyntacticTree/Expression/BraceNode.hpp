#ifndef BraceNode_hpp
#define BraceNode_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "../TypeIdentifierNode.hpp"

/*
	Class used to represent a syntaxic node containing an empty brace expression
*/
class BraceNode : public ExpressionNode {
private :
	ExpressionNode* e_expr;
	TypeIdentifierNode* node_type;

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
	ExpressionNode* getExpression() const{return e_expr;};
	TypeIdentifierNode* getType() const{return node_type;};

	//Inherited
	std::string getLiteral() const{
		std::string literal = "(";
		std::string s_expr = e_expr ? e_expr->getLiteral() : "";
		return literal + s_expr + ")";
	};

	int accept(Visitor* visitor){
		return visitor->visitBraceNode(this);
	};

	int updateType(){

		string type;

		TypeIdentifierNode *expr_type = e_expr->getType();
		if (!expr_type)
			type = expr_type->getLiteral();
		else{
			std::cerr << "Error in the compiler" << std::endl;
			return -1;
		}
		e_type = new TypeIdentifierNode(type);

		return 0;
	};

};

#endif //BraceNode_hpp
