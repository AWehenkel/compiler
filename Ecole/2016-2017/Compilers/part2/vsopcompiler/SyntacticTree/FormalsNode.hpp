#ifndef formals_node_hpp
#define formals_node_hpp

#include <string>
#include <vector>
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
	//Constructor:
	FormalsNode(int col = 0, int line = 0) : VSOPNode(col, line){};

	//Destructor:
	virtual ~FormalsNode();

	//Accessor:
	std::vector<FormalNode*> getFormals() const {return formals;};

	//Inherited:
	int accept(Visitor* visitor){return visitor->visitFormalsNode(this);};
	TypeIdentifierNode* getDeclarationType (const std::string& id) const;
	const std::string getDeclarationLLVM(const std::string& id) const;
	std::string getLiteral(bool with_type = false) const;

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
	bool equals(const FormalsNode &formals) const;
};

#endif //formals_node_hpp
