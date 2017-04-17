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
	~LetNode();

	//Public Methods:
	//Accessors
	ObjectIdentifierNode* getObjectId() const{return e_object_id;};
	TypeIdentifierNode* getObjectType() const{return e_object_type;};
	ExpressionNode* getInitExp() const{return e_init_exp;};
	ExpressionNode* getScopeExp() const{return e_scope_exp;};
	VSOPNode* getCurrentScope() const{return e_current_scope;};

	//Inherited
	std::string getLiteral(bool with_type = false) const;
	TypeIdentifierNode* getDeclarationType(std::string id);
	int accept(Visitor* visitor){return visitor->visitLetNode(this);};
	int updateType();

	//Setters
	void setCurrentScope(VSOPNode* node){e_current_scope = node;};

};

#endif //LetNode_hpp
