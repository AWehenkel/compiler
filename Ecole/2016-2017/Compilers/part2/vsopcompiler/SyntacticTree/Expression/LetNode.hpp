#ifndef LetNode_hpp
#define LetNode_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"
/*
	Class used to represent a syntaxic node containing a let statement
*/
class LetNode : public ExpressionNode {
private :
	ObjectIdentifierNode* e_object_id;
	TypeIdentifierNode* e_type;
	ExpressionNode* e_init_exp;
	ExpressionNode* e_scope_exp;

public :
	//Constructors:
	/*
	LetNode
	IN:	object_id:	ObjectIdentifierNode*, the object identifier.
			type:				TypeIdentifierNode*, the type.
			scope_exp:	ExpressionNode*, the scope exp.
			init_exp:		ExpressionNode*, the init exp.
			col: 				int, the column where the node is present.
			line:				int, the line where the node is present.
	*/
	LetNode(ObjectIdentifierNode* object_id, TypeIdentifierNode* type, ExpressionNode* scope_exp, ExpressionNode* init_exp = NULL, int col = 0, int line = 0) : ExpressionNode(col, line), e_object_id(object_id), e_type(type), e_scope_exp(scope_exp), e_init_exp(init_exp) {};

	//Destructor:
	~LetNode(){delete e_init_exp; delete e_scope_exp;};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{
		std::string literal = "Let(" + e_object_id->getLiteral() + ", " + e_type->getLiteral() + ", ";
		std::string end = e_init_exp ? e_init_exp->getLiteral() + ", " : "";
		return literal + end + e_scope_exp->getLiteral() + ")";
	};

	int accept(Visitor* visitor) const{
		return visitor.visitLetNode(this);
	};
};

#endif //LetNode_hpp
