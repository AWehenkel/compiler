#ifndef ConditionalNode_hpp
#define ConditionalNode_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"

/*
	Class used to represent a syntaxic node containing an if statements
*/
class ConditionalNode : public ExpressionNode {
private :
	ExpressionNode* e_condition;
	ExpressionNode* e_action;
	ExpressionNode* e_else_action;

public :
	//Constructors:
	/*
	ConditionalNode
	IN:	condition:		ExpressionNode*, the condition on the action.
			action:				ExpressionNode*, the action to do if the condition is true.
			else_action:	ExpressionNode*, the condition to do else.
			col: 					int, the column where the node is present.
			line:					int, the line where the node is present.
	*/
	ConditionalNode(ExpressionNode* condition, ExpressionNode* action, ExpressionNode* else_action = NULL, int col = 0, int line = 0) : ExpressionNode(col, line),
		e_condition(condition), e_action(action), e_else_action(else_action){};

	//Destructor:
	~ConditionalNode();

	//Public Methods:
	//getters
	ExpressionNode* getCondition() const{return e_condition;};
	ExpressionNode* getAction() const{return e_action;};
	ExpressionNode* getElseAction() const{return e_else_action;};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitConditionalNode(this);};
	std::string getLiteral(bool with_type = false) const;
	int updateType();
};

#endif //ConditionalNode_hpp
