#ifndef NewNode_hpp
#define NewNode_hpp

#include <string>
#include "ExpressionNode.hpp"
/*
	Class used to represent a syntaxic node containing a new statement
*/
class NewNode : public ExpressionNode {
private :
	TypeIdentifierNode* e_type_id;

public :
	//Constructor:
	/*
	NewNode
	IN:	type_id:	TypeIdentifierNode*, the type of the new object.
			col: 			int, the column where the node is present.
			line:			int, the line where the node is present.
	*/
	NewNode(TypeIdentifierNode* type_id, int col = 0, int line = 0) : ExpressionNode(type_id, col, line), e_type_id(type_id){};

	//Destructor
	virtual ~NewNode();

	//Accessors:
	TypeIdentifierNode* getTypeId() const{return e_type_id;};

	//Inherited:
	int accept(Visitor* visitor){return visitor->visitNewNode(this);};
	std::string getLiteral(bool with_type = false) const;
};

#endif //NewNode_hpp
