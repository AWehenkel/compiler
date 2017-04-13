#ifndef ConditionalNode_hpp
#define ConditionalNode_hpp

#include <cstring>
#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "../TypeIdentifierNode.hpp"

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
	~ConditionalNode(){delete e_condition; delete e_action; delete e_else_action;};

	//Public Methods:
	//getters
	ExpressionNode* getCondition() const{return e_condition;};
	ExpressionNode* getAction() const{return e_action;};
	ExpressionNode* getElseAction() const{return e_else_action;};

	//Inherited
	std::string getLiteral() const{
		std::string literal = "If(" + e_condition->getLiteral() + "," + e_action->getLiteral();
		std::string end = e_else_action ? "," + e_else_action->getLiteral() : "";
		return literal + end + ")";
	};

	int accept(Visitor* visitor){
		return visitor->visitConditionalNode(this);
	};

	int updateType(){

		// Check if the condition is of type bool
		TypeIdentifierNode *condition_type = e_condition->getType();
		if (!condition_type){
			std::cerr << "Error in the compiler" << std::endl;
			return -1;
		}
		string s_condition_type = condition_type->getLiteral();

		if (strcmp(s_condition_type, "error") != 0 && strcmp(s_condition_type, "bool") != 0){
			std::cerr << "Condition is not bool in conditional" << std::endl;
			node_type = new TypeIdentifierNode("error");
			return -1;
		}

		// Check the types of the two branches
		TypeIdentifierNode *then_type = e_action->getType();
		TypeIdentifierNode *else_type;
		if(e_else_action)
			else_type = e_else_action->getType();
		else
			else_type = new TypeIdentifierNode("unit");

		if(!then_type || !else_type){
			std::cerr << "Error in the compiler" << std::endl;
			return -1;
		}
		std::string s_then_type = then_type->getLiteral();
		std::string s_else_type = else_type->getLiteral();

		// Check if one of the branch is a unit
		if(strcmp(s_then_type,"unit") == 0 || strcmp(s_else_type,"unit") == 0){
			node_type = new TypeIdentifierNode("unit");
			return 0;
		}

		// If one branch is in error, return the type of the other branch
		if(strcmp(s_then_type, "error") == 0){
			node_type = new TypeIdentifierNode(s_else_type);
			return 0;
		}else if (strcmp(s_else_type, "error") == 0){
			node_type = new TypeIdentifierNode(s_then_type);
			return 0;
		}

		// If one of the branch is a basic type, check if the other one is the same
		if (!then_type->getClassType() || !else_type->getClassType()){
			if(*then_type == *else_type){
				node_type = new TypeIdentifierNode(s_then_type);
				return 0;
			}else{
				std::cerr << "Types différents dans conditional" << std::endl;
				node_type = new TypeIdentifierNode("error");
				return -1;
			}
		}

		// If both types are clases, need to check the inheritance
		node_type = then_type->getClassType()->getCommonParent(else_type->getClassType());
		if(!node_type){
			std::cerr << "Pas d'ancêtres en commun dans conditional" << std::endl;
			node_type = new TypeIdentifierNode("error");
			return -1;
		}

		return 0;
	}
};

#endif //ConditionalNode_hpp
