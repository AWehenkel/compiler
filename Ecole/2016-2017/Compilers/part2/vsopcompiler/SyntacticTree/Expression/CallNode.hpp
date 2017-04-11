#ifndef CallNode_hpp
#define CallNode_hpp

#include <string>
#include "../ArgsNode.hpp"
#include "ExpressionNode.hpp"
#include "ObjectIdentifierNode.hpp"
/*
	Class used to represent a syntaxic node containing a call to a method
*/
class CallNode : public ExpressionNode {
private :
	ObjectIdentifierNode* e_method_name;
	ArgsNode* e_args;
	ExpressionNode* e_object;
public :
	//Constructors:
	/*
	CallNode
	IN:	method_name:	ObjectIdentifierNode*, the name of the method.
			args:					ArgsNode*, the arguments of the call.
			object:				ExpressionNode*, the object on which the call is made(self by default).
			col: 					int, the column where the node is present.
			line:					int, the line where the node is present.
	*/
	CallNode(ObjectIdentifierNode* method_name, ArgsNode* args, ExpressionNode* object = NULL, int col = 0, int line = 0) : ExpressionNode(col, line), e_object(object), e_args(args), e_method_name(method_name){};

	//Destructor:
	~CallNode(){delete e_args; delete e_object;};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{
		std::string obj = e_object ? e_object->getLiteral() : "self";
		return "Call(" + obj + ", "  + e_method_name->getLiteral() + ", " + e_args->getLiteral() + ")";
	};

	int accept(Visitor* visitor) const{
		return visitor.visitCallNode(this);
	};
};

#endif //CallNode_hpp
