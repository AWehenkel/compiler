#ifndef AssignNode_hpp
#define AssignNode_hpp

#include <string>
#include "ExpressionNode.hpp"
/*
	Class used to represent a syntaxic node containing an assignment
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
	~AssignNode(){delete e_name; delete e_expr;};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{return "Assign(" + e_name->getLiteral() + ", " + e_expr->getLiteral() + ")";};
};

#endif //AssignNode_hpp
