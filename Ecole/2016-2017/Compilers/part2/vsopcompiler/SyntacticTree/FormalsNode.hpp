#ifndef formals_node_hpp
#define formals_node_hpp

#include <string>
#include <vector>
#include "FormalNode.hpp"
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing formals(arguments)
*/
class FormalsNode : public VSOPNode {
private :
	std::vector<FormalNode*> formals;

public :
	//Constructors
	FormalsNode(int col = 0, int line = 0) : VSOPNode(col, line){};

	//Destructor
	~FormalsNode(){
		for (std::vector<FormalNode*>::const_iterator it = formals.begin(); it < formals.end(); ++it) {
			delete (*it);
		}
	};

	//Public methods
	//Inherited
	std::string getLiteral() const;

	/*
	addFormal
	IN: formal: FormalNode*, the formal to add.
	OUT: void
	ROLE: Add a formal at the end of the list of argument
	*/
	void addFormal(FormalNode *formal);

	/*
	insertExpr
	IN: formal: FormalNode*, the formal to add.
	OUT: void
	ROLE: Add a formal at the front of the list of argument
	*/
	void insertFormal(FormalNode *formal);

	//Accessors
	std::vector<FormalNode*> getFormals() const {return formals;};
};

#endif //formals_node_hpp
