#ifndef AssignNode_hpp
#define AssignNode_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"
/*
*	Class used to represent a syntaxic node containing an assignment.
*/
class AssignNode : public ExpressionNode {
private :
	ObjectIdentifierNode* e_name;
	ExpressionNode* e_expr;

public :
	//Constructors:
	/*
	AssignNode
	IN:	name:	ObjectIdentifierNode*, The name of the variable.
			expr:	ExpressionNode*, The expression to assign.
			col: 	int, the column where the node is present.
			line:	int, the line where the node is present.
	*/
	AssignNode(ObjectIdentifierNode* name, ExpressionNode* expr, int col = 0, int line = 0) : ExpressionNode(col, line),
		e_name(name), e_expr(expr){};

	//Destructor:
	virtual ~AssignNode();

	//Public Methods:
	//Getter
	ObjectIdentifierNode* getName() const{return e_name;};
	ExpressionNode* getExpression() const{return e_expr;};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitAssignNode(this);};
	std::string getLiteral(bool with_type = false) const;
};

#endif //AssignNode_hpp
