#ifndef program_node_hpp
#define program_node_hpp

#include <string>
#include <vector>
#include <unordered_map>

#include "ClassNode.hpp"
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing a program
*/
class ProgramNode : public VSOPNode {
private :
	std::vector<ClassNode*> classes;
	std::unordered_map<std::string, ClassNode*> table_classes;

public :
	//Constructors
	/*
	new_class : ClassNode *, The last class of the program.
	col: 				int, the column where the node is present.
	line:				int, the line where the node is present.
	*/
	ProgramNode(ClassNode *new_class, int col = 0, int line = 0) : VSOPNode(col, line){addClass(new_class);};

	//Destructors
	~ProgramNode(){
		for (std::vector<ClassNode*>::const_iterator it = classes.begin(); it < classes.end(); ++it)
			delete (*it);
	};

	//Public methods
	/*
	addClass
	IN:	new_class:	ClassNode *, A class
	OUT: void
	ROLE: Add a class at the end of the program.
	*/
	void addClass(ClassNode *new_class);
	/*
	fillClassTable
	IN: std::unordered_maptable, a reference to the table to fill with the class contained in the subnode of the current node.
	Out: -
	*/
	int fillClassTable(std::unordered_map<std::string, ClassNode*> &table);

	//Accessor
	std::vector<ClassNode*> getClasses() const {return classes;};
	std::unordered_map<std::string, ClassNode*> getTableClasses() const {return table_classes;};

	//Inherited
	std::string getLiteral() const;
	int accept(Visitor* visitor);

};

#endif //program_node_hpp
