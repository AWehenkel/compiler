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
	std::string last_expr_LLVM_addr;

public :
	//Constructors
	/*
	BlockNode
	IN:	col: 				int, the column where the node is present.
			line:				int, the line where the node is present.
	*/
	BlockNode(int col = 0, int line = 0) : ExpressionNode(col, line){};

	//Destructor
	virtual ~BlockNode();

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
	std::string getLastExprLLVMAddr() const {return last_expr_LLVM_addr;};
	void setLastExprLLVMAddr(std::string address){last_expr_LLVM_addr = address;};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitBlockNode(this);};
	std::string getLiteral(bool with_type = false) const;
};

#endif //block_node_hpp
