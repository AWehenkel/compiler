#ifndef block_node_hpp
#define block_node_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"

/*
	Class used to represent a syntaxic node containing a block
*/
class BlockNode : public ExpressionNode {
private :
	std::vector<ExpressionNode*> expressions;

public :
	//Constructors
	/*
	BlockNode
	IN:	col: 				int, the column where the node is present.
			line:				int, the line where the node is present.
	*/
	BlockNode(int col = 0, int line = 0) : ExpressionNode(col, line){};

	//Public methods
	/*
	addExpression
	IN: expression: ExpressionNode*, the expression to add.
	OUT: void
	ROLE: Add an expression at the end of the list expression of the block.
	*/
	void addExpression(ExpressionNode *expression);

	/*
	insertExpr
	IN: expression: ExpressionNode*, the expression to add.
	OUT: void
	ROLE: Add an expression at the frond of the list expression of the block.
	*/
	void insertExpr(ExpressionNode *expression);

	//Accessors
	std::vector<ExpressionNode*> getExpressions() const {return expressions;};

	//Inherited
	std::string getLiteral() const;

	int accept(Visitor* visitor){
		return visitor->visitBlockNode(this);
	};

	int updateType(){

		string type;

		ExpressionNode *last_expr = *(expressions.end()-1):
		TypeIdentifierNode *expr_type = expr->getType();
		if (!expr_type)
			type = expr_type->getLiteral();
		else{
			std::cerr << "Error in the compiler" << std::endl;
			return -1;
		}
		// Put the type of the last instruction, even if it was an error.
		node_type = new TypeIdentifierNode(type);

		/* Even if there is an error in the last instruction, it wasn't in the block
		* directly, so we don't return an error code
		*/
		return 0;
	};
};

#endif //block_node_hpp
