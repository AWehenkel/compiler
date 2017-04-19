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
	virtual ~WhileNode();

	//Public Methods:
	//Accessors:
	ExpressionNode* getCondition() const{return e_condition;};
	ExpressionNode* getAction() const{return e_action;};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitWhileNode(this);};
	std::string getLiteral(bool with_type = false) const;
	int updateType(Visitor* visitor);
};

#endif //ConditionalNode_hpp
