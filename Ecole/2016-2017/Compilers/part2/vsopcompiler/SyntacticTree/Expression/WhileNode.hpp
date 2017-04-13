#ifndef WhileNode_hpp
#define WhileNode_hpp

#include <string>
#include <cstring>
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
	//Accessors:
	ExpressionNode* getCondition() const{return e_condition;};
	ExpressionNode* getAction() const{return e_action;};

	//Inherited
	std::string getLiteral() const{return "While(" + e_condition->getLiteral() + "," + e_action->getLiteral() + ")";};

	int accept(Visitor* visitor){
		return visitor->visitWhileNode(this);
	};

	int update(){

		// Check if the condition is a bool
		TypeIdentifierNode *condition_type = e_condition->getType();
		if (!condition_type || !action_type){
			std::cerr << "Error in the compiler" << std::endl;
			return -1;
		}
		string s_condition_type = condition_type->getLiteral();

		if (strcmp(s_op_type, "error") != 0  && strcmp(s_condition_type, "bool") != 0){
			std::cerr << "Condition n'est pas un bool dans while" << std::endl;
			node_type = new TypeIdentifierNode("error");
			return -1;
		}
		node_type = new TypeIdentifierNode("unit");

		return 0;
	}
};

#endif //ConditionalNode_hpp
