#ifndef TypeIdentifierNode_hpp
#define TypeIdentifierNode_hpp

#include <string>
#include "Expression/ExpressionNode.hpp"
/*
	Class used to represent a syntaxic node containing a type identifier
*/
class TypeIdentifierNode : public VSOPNode {
private :
	std::string t_content;
public :

	//Constructors:
	TypeIdentifierNode(std::string content, int col = 0, int line = 0) : VSOPNode(col, line), t_content(content){};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{
		return t_content;
	};

	int accept(Visitor* visitor) const{
		return visitor.visitTypeIdentifierNode(this);
	}
};

#endif //TypeIdentifierNode_hpp
