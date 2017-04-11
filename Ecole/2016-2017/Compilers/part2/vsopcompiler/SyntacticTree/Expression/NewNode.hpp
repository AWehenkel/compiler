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
	//Constructors:
	/*
	NewNode
	IN:	type_id:	TypeIdentifierNode*, the type of the new object.
			col: 			int, the column where the node is present.
			line:			int, the line where the node is present.
	*/
	NewNode(TypeIdentifierNode* type_id, int col = 0, int line = 0) : ExpressionNode(col, line), e_type_id(type_id){};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{
		return "New(" + e_type_id->getLiteral() + ")";
	};
};

#endif //NewNode_hpp
