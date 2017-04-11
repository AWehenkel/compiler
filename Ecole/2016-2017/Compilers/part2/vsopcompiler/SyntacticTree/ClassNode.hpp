#ifndef class_node_hpp
#define class_node_hpp

#include <string>
#include <unordered_map>
#include "ClassBodyNode.hpp"
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing a class
*/
class ClassNode : public VSOPNode {
private :
	TypeIdentifierNode* e_name;
	TypeIdentifierNode* e_extends;
	ClassBodyNode *e_body;
	ClassNode *parent;
	bool in_cycle;
public :
	//Constructors

	/*
	IN:	name:			TypeIdentifierNode*, The name of the class.
			extends: 	TypeIdentifierNode, The name of the parent class.
			body:			ClassBodyNode *, The body of the class.
			col: 			int, the column where the node is present.
			line:			int, the line where the node is present.
	*/
	ClassNode(TypeIdentifierNode* name, ClassBodyNode *body, TypeIdentifierNode* extends = NULL, int col = 0, int line = 0) : VSOPNode(col, line),
	 	e_name(name), e_extends(extends), e_body(body), in_cycle(false) {};

	//Destructor
	~ClassNode(){delete e_name; delete e_extends; delete e_body;}

	//Public methods
	//Inherited
	std::string getLiteral() const;
	int fillClassTable(std::unordered_map<std::string, ClassNode*> &table){
		if(table.find(e_name->getLiteral()) != table.end())
			return -1;
		table[e_name->getLiteral()] = this;
		return 0;
	};
	//Accesors
	TypeIdentifierNode* getName() const {return e_name;};
	TypeIdentifierNode* getExtends() const {return e_extends;};
	ClassBodyNode* getBody() const {return e_body;};
	/*
	setParent
	ROLE: This function is aimed at setting the parent ClassNode of the class.
	IN:		unordered_map<std:string, ClassNode*> class_table, the table containing the class of the program.
	OUT: -
	*/
	int setParent(std::unordered_map<std::string, ClassNode*> &table);
	/*
	inCycle
	ROLE: This function is used to know if there are cyclic inheritance.
	IN: -
	OUT: bool, true if the class is in a inheritance cycle
	*/
	bool inCycle(){
		if(!in_cycle){
			in_cycle = true;
			in_cycle = parent == NULL ? false : parent->inCycle();
		}
		return in_cycle;
	}
};

#endif //class_node_hpp
