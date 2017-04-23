#ifndef method_node_hpp
#define method_node_hpp

#include <string>
#include <vector>
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing a method
*/
class MethodNode : public VSOPNode {
private :
	ObjectIdentifierNode* e_name;
	FormalsNode* e_formals;
	TypeIdentifierNode* e_ret_type;
	BlockNode* e_block;
	ClassNode* e_class_scope;
	//Overloaded operator
	friend inline bool operator==(MethodNode &method1, MethodNode &method2){
		return method1.equals(method2);
	};

public :
	//Constructors
	MethodNode(ObjectIdentifierNode* name, FormalsNode *formals, TypeIdentifierNode *ret_type, BlockNode *block,int col = 0, int line = 0) :
		VSOPNode(col, line), e_name(name), e_formals(formals), e_ret_type(ret_type), e_block(block) {};

	//Destructor
	virtual ~MethodNode();

	//Public methods
	//Accesors
	ObjectIdentifierNode* getName() const {return e_name;};
	FormalsNode* getFormals() const {return e_formals;};
	TypeIdentifierNode* getRetType() const {return e_ret_type;};
	BlockNode* getBlock() const {return e_block;};

	//Setter
	void setClassScope(ClassNode* class_scope){e_class_scope = class_scope;};

	/*
	equals
	ROLE: Compare a method to determine whether or not it is equal to this method.
	IN:		method: MethodNode const &, the method with which compare the current method.
	OUT: bool, true if the name, the type and the arguments are equal.
	*/
	bool equals(MethodNode &method);

	//Inherited
	int accept(Visitor* visitor){return visitor->visitMethodNode(this);}
	TypeIdentifierNode* getDeclarationType(std::string id);
	std::string getLiteral(bool with_type = false) const;
	std::vector<SemanticError> updateType(Visitor* visitor);
};

#endif //method_node_hpp
