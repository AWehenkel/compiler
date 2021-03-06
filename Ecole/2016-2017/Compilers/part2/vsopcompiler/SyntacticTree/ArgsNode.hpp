#ifndef args_node_hpp
#define args_node_hpp

#include <string>
#include <vector>
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing arguments
*/
class ArgsNode : public VSOPNode {
private :
	//The list of arguments
	std::vector<ExpressionNode*> expressions;

public :
	//Constructor:
	/*
	ArgsNode
	IN:	col: 	int, the column where the node is present.
			line:	int, the line where the node is present.
	*/
	ArgsNode(int col = 0, int line = 0) : VSOPNode(col, line){};

	//Destructor:
	virtual ~ArgsNode();

	//Accessor:
	std::vector<ExpressionNode*> getExpressions() const {return expressions;};

	//Inherited:
	int accept(Visitor* visitor){return visitor->visitArgsNode(this);};
	std::string getLiteral(bool with_type = false) const;

	/*
	addExpression
	IN: expression: ExpressionNode*, the expression to add.
	OUT: void
	ROLE: Add an expression at the end of the list of argument
	*/
	void addExpression(ExpressionNode* expression);

	/*
	insertExpr
	IN: expression: ExpressionNode*, the expression to add.
	OUT: void
	ROLE: Add an expression at the front of the list of argument
	*/
	void insertExpr(ExpressionNode *expression);
};

#endif //args_node_hpp
