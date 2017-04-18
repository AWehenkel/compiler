#ifndef class_body_node_hpp
#define class_body_node_hpp

#include <string>
#include <vector>
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing the body of a class
*/
class ClassBodyNode : public VSOPNode {
private :
	std::vector<FieldNode*> fields;
	std::vector<MethodNode*> methods;

public :
	//Constructors
	/*
	ArgsNode : -
	IN:	col: 	int, the column where the node is present.
			line:	int, the line where the node is present.
	*/
	ClassBodyNode(int col = 0, int line = 0) : VSOPNode(col, line){};

	//Destructor
	virtual ~ClassBodyNode();

	//Public methods
	/*
	addField
	IN: expression: FieldNode*, the field to add.
	OUT: void
	ROLE: Add a field at the end of the list of fields.
	*/
	void addField(FieldNode *field);

	/*
	addMethod
	IN: expression: MethodNode*, the field to add.
	OUT: void
	ROLE: Add a field at the end of the list of methods.
	*/
	void addMethod(MethodNode *method);

	//Accessors
	std::vector<FieldNode*> getFields() const {return fields;};
	std::vector<MethodNode*> getMethods() const {return methods;};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitClassBodyNode(this);};
	std::string getLiteral(bool with_type = false) const;
};

#endif //class_body_node_hpp
