#ifndef expression_node_hpp
#define expression_node_hpp

#include <string>
#include "../VSOPNode.hpp"
#include "../TypeIdentifierNode"
/*
	Parent class of any node representing an expression.
*/
class ExpressionNode : public VSOPNode {
protected :
	TypeIdentifierNode* node_type;
public :
	//Constructors
	/*
	ExpressionNode
	IN:	col: 					int, the column where the node is present.
			line:					int, the line where the node is present.
	*/
	ExpressionNode(int col = 0, int line = 0) : VSOPNode(col, line){};

	//Public method
	//Inherited
	virtual std::string getLiteral() const = 0;

	virtual int accept(Visitor* visitor) = 0;

	virtual int getType(){return node_type;}
};

#endif //expression_node_hpp
