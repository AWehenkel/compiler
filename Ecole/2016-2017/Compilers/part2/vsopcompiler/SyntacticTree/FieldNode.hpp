#ifndef field_node_hpp
#define field_node_hpp

#include <string>
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing a field
*/
class FieldNode : public VSOPNode {
private :
	ObjectIdentifierNode* e_name;
	TypeIdentifierNode* e_type;
	ExpressionNode* e_init_expr = NULL;
	ClassNode* e_class_scope;
	unsigned int position; //Position in the class structure.

public :
	//Constructors:
	/*
	IN: name:	ObjectIdentifierNode*, the name of the field.
			type:	TypeIdentifierNode*, the type of the field.
			col: 	int, the column where the node is present.
			line:	int, the line where the node is present.
	*/
	FieldNode(ObjectIdentifierNode* name, TypeIdentifierNode *type, int col = 0, int line = 0) : VSOPNode(col, line), e_name(name), e_type(type) {};

	/*
	IN: name:				ObjectIdentifierNode*, the name of the field.
			type:				TypeIdentifierNode*, the type of the field.
			init_expr:	ExpressionNode*, the initial value of the field.
			col: 	int, the column where the node is present.
			line:	int, the line where the node is present.
	*/
	FieldNode(ObjectIdentifierNode* name, TypeIdentifierNode *type, ExpressionNode *init_expr, int col = 0, int line = 0) : VSOPNode(col, line),
	 	e_name(name), e_type(type), e_init_expr(init_expr) {};

	//Destructor:
	virtual ~FieldNode();

	//Accesors:
	void setClassScope(ClassNode* class_scope){e_class_scope = class_scope;};
	void setPosition(int pos) {position = pos;};
	ObjectIdentifierNode* getName() const {return e_name;};
	TypeIdentifierNode* getType() const {return e_type;};
	ExpressionNode* getInitExpr() const {return e_init_expr;};
	int getPosition(){return position;};

	//Inherited:
	int accept(Visitor* visitor){return visitor->visitFieldNode(this);};
	std::string getLiteral(bool with_type = false) const;
};

#endif //field_node_hpp
