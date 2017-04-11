#ifndef vsop_node_hpp
#define vsop_node_hpp

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
	virtual int accept(Visitor* visitor) const = 0;

};

#endif //vsop_node_hpp
