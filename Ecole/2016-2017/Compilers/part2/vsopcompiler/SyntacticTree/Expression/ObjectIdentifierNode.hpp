#ifndef ObjectIdentifierNode_hpp
#define ObjectIdentifierNode_hpp

#include <string>
#include "ExpressionNode.hpp"
/*
	Class used to represent a syntaxic node containing an object identifier
*/
class ObjectIdentifierNode : public ExpressionNode {
private :
	std::string e_content;

	//Overload operator
	friend inline bool operator==(ObjectIdentifierNode const &id1, ObjectIdentifierNode const &id2){
		return id1.equals(id2);
	};
public :
	//Constructors:
	/*
	ObjectIdentifierNode
	IN:	content:	std::string, the identifier.
			col: 			int, the column where the node is present.
			line:			int, the line where the node is present.
	*/
	ObjectIdentifierNode(std::string content, int col = 0, int line = 0) : ExpressionNode(col, line), e_content(content){};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{
		return e_content;
	};

	int accept(Visitor* visitor){
		return visitor->visitObjectIdentifierNode(this);
	};

	/*
	equals
	ROLE: Compare a id to determine whether or not it is equal to this id.
	IN:		id: ObjectIdentifierNode const &, the id with which compare the current id.
	OUT: bool, true if the contents are equal.
	*/
	bool equals(ObjectIdentifierNode const &id) const{
		return e_content == id.e_content;
	}
};

#endif //ObjectIdentifierNode_hpp
