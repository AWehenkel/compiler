#ifndef method_node_hpp
#define method_node_hpp

#include <string>
#include "Expression/BlockNode.hpp"
#include "FormalsNode.hpp"
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
	~MethodNode(){delete e_name; delete e_ret_type; delete e_ret_type; delete e_block;}

	//Public methods
	//Inherited
	std::string getLiteral() const;

	int accept(Visitor* visitor){
		return visitor->visitMethodNode(this);
	}

	//Accesors
	ObjectIdentifierNode* getName() const {return e_name;};
	FormalsNode* getFormals() const {return e_formals;};
	TypeIdentifierNode* getRetType() const {return e_ret_type;};
	BlockNode* getBlock() const {return e_block;};

	//Setter
	void setClassScope(ClassNode* class_scope){
		e_class_scope = class_scope;
	};

	/*
	equals
	ROLE: Compare a method to determine whether or not it is equal to this method.
	IN:		method: MethodNode const &, the method with which compare the current method.
	OUT: bool, true if the name, the type and the arguments are equal.
	*/
	bool equals(MethodNode &method){
		return *(method.getName()) == *(getName()) && *(method.getFormals()) == *(getFormals()) && *(method.getRetType()) == *(getRetType());
	}
};

#endif //method_node_hpp
