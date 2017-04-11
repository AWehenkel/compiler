#ifndef class_body_node_hpp
#define class_body_node_hpp

#include <string>
#include <vector>
#include "FieldNode.hpp"
#include "MethodNode.hpp"
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
	~ClassBodyNode(){
		for (std::vector<FieldNode*>::const_iterator it = fields.begin(); it < fields.end(); ++it) {
			delete (*it);
		}
		for (std::vector<MethodNode*>::const_iterator it = methods.begin(); it < methods.end(); ++it) {
			delete (*it);
		}
	}

	//Public methods
	//Inherited
	std::string getLiteral() const;

	int accept(Visitor* visitor){
		return visitor->visitClassBodyNode(this);
	};
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
};

#endif //class_body_node_hpp
