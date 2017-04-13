#ifndef vsop_node_hpp
#define vsop_node_hpp

#include "../Visitors/Visitor.hpp"

#include <iostream>
#include <string>

/*
	Abstract parent class of any node of the syntaxic tree
*/
class VSOPNode {
protected :
	//Fields
	int n_col;
	int n_line;
	//Overloaded operator
	friend std::ostream &operator<<(std::ostream &out, VSOPNode const &node);

public :
	//Constructor
	VSOPNode(int col, int line) : n_col(col), n_line(line){};

	//Destructor
	virtual ~VSOPNode(){};

	//Public method
	/*
	getLiteral
	IN: -
	OUT: std::string, the literal version of the node.
	*/
	virtual std::string getLiteral() const = 0;

	/*
	accept
	ROLE: accept the node using a specific visitor.
	IN: visitor: Visitor*, a reference to the visitor.
	OUT: int, a return code.
	*/
	virtual int accept(Visitor* visitor) = 0;

	/*
	updateType
	ROLE : update the type of the node according to the type of its children
	IN : -
	OUT : int, a return code
	*/
	virtual int updateType(){return 0;};

	/*
	getDeclarationType
	ROLE: This function returns a pointer to the TypeIdentifierNode corresponding to the id in the scope.
	IN:		id: std::string, the name of the variable.
	OUT: bool, true if the variable is declared in the VSOPNode or in one of its children.
	*/
	virtual TypeIdentifierNode* getDeclarationType(std::string id){
		return NULL;
	};
	//Accessors
	int getLine() const{
		return n_line;
	};
	int getCol() const{
		return n_col;
	};

};

#endif //vsop_node_hpp
