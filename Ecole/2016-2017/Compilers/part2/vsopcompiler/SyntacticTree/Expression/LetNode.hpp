#ifndef LetNode_hpp
#define LetNode_hpp

#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "ObjectIdentifierNode"
#include "../TypeIdentifierNode"
/*
	Class used to represent a syntaxic node containing a let statement
*/
class LetNode : public ExpressionNode {
private :
	ObjectIdentifierNode* e_object_id;
	TypeIdentifierNode* e_object_type;
	ExpressionNode* e_init_exp;
	ExpressionNode* e_scope_exp;
	VSOPNode* e_current_scope;
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
	LetNode(ObjectIdentifierNode* object_id, TypeIdentifierNode* type, ExpressionNode* scope_exp, ExpressionNode* init_exp = NULL, int col = 0, int line = 0) : ExpressionNode(col, line), e_object_id(object_id), e_object_type(type), e_scope_exp(scope_exp), e_init_exp(init_exp) {};

	//Destructor:
	~LetNode(){delete e_init_exp; delete e_scope_exp;};

	//Public Methods:
	//Accessors
	ObjectIdentifierNode* getObjectId() const{return e_object_id;};
	TypeIdentifierNode* getObjectType() const{return e_object_type;};
	ExpressionNode* getInitExp() const{return e_init_exp;};
	ExpressionNode* getScopeExp() const{return e_scope_exp;};

	//Inherited
	std::string getLiteral() const{
		std::string literal = "Let(" + e_object_id->getLiteral() + ", " + e_type->getLiteral() + ", ";
		std::string end = e_init_exp ? e_init_exp->getLiteral() + ", " : "";
		return literal + end + e_scope_exp->getLiteral() + ")";
	};

	TypeIdentifierNode* getDeclarationType(std::string id){
		if(e_object_id->getLiteral() == id)
			return e_type;
		else if(e_current_scope)
			return e_current_scope->getDeclarationType(id);
		return NULL;
	};

	int accept(Visitor* visitor){
		return visitor->visitLetNode(this);
	};

	int updateType(){

		if (init_expr){
			TypeIdentifierNode *init_expr_type = init_expr->getType();
			if (!init_expr_type){
				std::cerr << "Error int the compiler" << std::endl;
				return -1;
			}

			// Compare this type to the type of the let
			if (strcmp(init_expr_type->getLiteral(), "error") != 0 && *init_expr_type != *e_object_type){
				node_type = new TypeIdentifierNode("error");
				std::cerr << "!! Types différents dans let" << std::endl;
				return -1;
			}
		}

		TypeIdentifierNode *scope_expr_type = e_scope_exp->getType();
		if (!scope_expr_type){
			std::cerr << "Error int the compiler" << std::endl;
			return -1;
		}
		node_type = new TypeIdentifierNode(scope_expr_type->getLiteral());

		return 0;
	};

	//Setters
	void setCurrentScope(VSOPNode* node){
		e_current_scope = node;
	}

};

#endif //LetNode_hpp
