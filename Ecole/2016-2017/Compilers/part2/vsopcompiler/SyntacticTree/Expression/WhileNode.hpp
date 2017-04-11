#ifndef WhileNode_hpp
#define WhileNode_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"
/*
	Class used to represent a while statement.
*/
class WhileNode : public ExpressionNode {
private :
	ExpressionNode* e_condition;
	ExpressionNode* e_action;

public :
	//Constructors:
	/*
	WhileNode
	IN:	condition:	ExpressionNode*, the condition to perform the loop.
			action:			ExpressionNode*, the operation to perform at each iteration.
			col: 				int, the column where the node is present.
			line:				int, the line where the node is present.
	*/
	WhileNode(ExpressionNode* condition, ExpressionNode* action, int col = 0, int line = 0) : ExpressionNode(col, line),
		e_condition(condition), e_action(action){};

	//Destructor:
	~WhileNode(){delete e_condition; delete e_action;};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{return "While(" + e_condition->getLiteral() + "," + e_action->getLiteral() + ")";};

	int accept(Visitor* visitor) const{
		return visitor.visitWhileNode(this);
	};
};

#endif //ConditionalNode_hpp
