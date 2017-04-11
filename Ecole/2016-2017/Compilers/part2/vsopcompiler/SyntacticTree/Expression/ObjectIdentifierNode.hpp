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
};

#endif //ObjectIdentifierNode_hpp
