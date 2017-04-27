#ifndef expression_node_hpp
#define expression_node_hpp

#include <string>
#include "../VSOPNode.hpp"
/*
	Parent class of any node representing an expression.
*/
class ExpressionNode : public VSOPNode {
protected :
	TypeIdentifierNode* node_type;
	bool self_type = false;
public :
	//Constructors
	/*
	ExpressionNode
	IN:	col: 					int, the column where the node is present.
			line:					int, the line where the node is present.
	*/
	ExpressionNode(int col = 0, int line = 0) : VSOPNode(col, line), node_type(NULL){};
	ExpressionNode(std::string type, int col = 0, int line = 0);
	ExpressionNode(TypeIdentifierNode* type, int col = 0, int line = 0) : VSOPNode(col, line), node_type(type){};

	//Destructor
	virtual ~ExpressionNode();

	//Public method
	//Inherited
	virtual int accept(Visitor* visitor) = 0;
	virtual std::string getLiteral(bool with_type = false) const = 0;
	virtual TypeIdentifierNode* getType(){return node_type;};
	virtual void setType(TypeIdentifierNode* new_type, bool new_self_type = false){
		node_type = new_type;
		self_type = new_self_type;
	};
};

#endif //expression_node_hpp
