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
	//Overloaded operator
	friend inline bool operator==(FormalsNode &formals1, FormalsNode &formals2){
		return formals1.equals(formals2);
	};
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

	int accept(Visitor* visitor){
		return visitor->visitFormalsNode(this);
	};

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

	/*
	equals
	ROLE: Compare a method to determine whether or not it is equal to this method.
	IN:		method: MethodNode const &, the method with which compare the current method.
	OUT: bool, true if the name, the type and the arguments are equal.
	*/
	bool equals(FormalsNode &formals){
		if(formals.formals.size() != this->formals.size())
			return false;
		for(size_t i = 0; i < formals.formals.size(); i++){
			if(formals.formals.at(i)->getType() != this->formals.at(i)->getType())
				return false;
		}
		return true;
	}

	//Accessors
	std::vector<FormalNode*> getFormals() const {return formals;};
};

#endif //formals_node_hpp
