#ifndef LiteralNode_hpp
#define LiteralNode_hpp

#include <string>
#include "ExpressionNode.hpp"
/*
	Class used to represent a syntaxic node containing a literal
*/
class LiteralNode : public ExpressionNode {
private :
	std::string e_content;

public :
	//Constructors:
	/*
	LiteralNode
	IN:	content:	int|std::string, the content of the literal.
			col: 			int, the column where the node is present.
			line:			int, the line where the node is present.
	*/
	LiteralNode(std::string content, std::string type, int col = 0, int line = 0) : ExpressionNode(type, col, line), e_content(content){};
	LiteralNode(int content, std::string type, int col = 0, int line = 0) : ExpressionNode(type, col, line), e_content(std::to_string(content)){};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{return e_content;};
	int accept(Visitor* visitor){return visitor->visitLiteralNode(this);};
};

#endif //LiteralNode_hpp
