#ifndef formal_node_hpp
#define formal_node_hpp

#include <string>
#include "VSOPNode.hpp"
#include "TypeIdentifierNode.hpp"
/*
	Class used to represent a syntaxic node containing a formal argument
*/
class FormalNode : public VSOPNode {
private :
	ObjectIdentifierNode* e_name;
	TypeIdentifierNode* e_type;

public :
	//Constructors
	/*
	IN: name:	ObjectIdentifierNode*, the name of the parameter.
			type:	TypeIdentifierNode*, the type of the parameter.
			col: 	int, the column where the node is present.
			line:	int, the line where the node is present.
	*/
	FormalNode(ObjectIdentifierNode* name, TypeIdentifierNode* type, int col = 0, int line = 0) : VSOPNode(col, line), e_name(name), e_type(type){};

	//Destructor
	virtual ~FormalNode();

	//Public methods
	//Accesors
	ObjectIdentifierNode* getName() const {return e_name;};
	TypeIdentifierNode* getType() const {return e_type;};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitFormalNode(this);};
	std::string getLiteral(bool with_type = false) const;
};

#endif //formals_node_hpp
