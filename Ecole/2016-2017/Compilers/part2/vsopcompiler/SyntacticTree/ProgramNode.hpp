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
class SemanticError;

class ProgramNode : public VSOPNode {
private :
	std::vector<ClassNode*> classes;
	std::unordered_map<std::string, ClassNode*> table_classes;
	std::vector<ClassNode*> to_delete;

public :
	//Overloaded operator
	ProgramNode& operator+=(const ProgramNode &p1);

	//Constructor:
	/*
	new_class : ClassNode *, The last class of the program.
	col: 				int, the column where the node is present.
	line:				int, the line where the node is present.
	*/
	ProgramNode(ClassNode *new_class = NULL, int col = 0, int line = 0) : VSOPNode(col, line){if(new_class)addClass(new_class);};

	//Destructor:
	virtual ~ProgramNode();

	//Accessors:
	std::vector<ClassNode*> getClasses() const {return classes;};
	std::unordered_map<std::string, ClassNode*> getTableClasses() const {return table_classes;};
	void removeClass(ClassNode* node);

	//Inherited:
	int accept(Visitor* visitor);
	std::string getLiteral(bool with_type = false) const;

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
	SemanticError fillClassTable(std::unordered_map<std::string, ClassNode*> &table);
};

#endif //program_node_hpp
