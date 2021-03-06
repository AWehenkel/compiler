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
	size_t length = 0;
	std::string constant_add;
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

	//Accessors:
	void setLength(size_t len){length = len;};
	void setConstantAdd(std::string add){constant_add = add;};

	//Inherited:
	int accept(Visitor* visitor){return visitor->visitLiteralNode(this);};
	std::string getLiteral(bool with_type = false) const;
	size_t getLength() const{return length;};
	std::string getConstantAdd() const{return constant_add;};

};

#endif //LiteralNode_hpp
