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

public :
	//Constructors
	MethodNode(ObjectIdentifierNode* name, FormalsNode *formals, TypeIdentifierNode *ret_type, BlockNode *block,int col = 0, int line = 0) :
		VSOPNode(col, line), e_name(name), e_formals(formals), e_ret_type(ret_type), e_block(block) {};

	//Destructor
	~MethodNode(){delete e_name; delete e_ret_type; delete e_ret_type; delete e_block;}

	//Public methods
	//Inherited
	std::string getLiteral() const;

	//Accesors
	ObjectIdentifierNode* getName() const {return e_name;};
	FormalsNode* getFormals() const {return e_formals;};
	TypeIdentifierNode* getRetType() const {return e_ret_type;};
	BlockNode* getBlock() const {return e_block;};
};

#endif //method_node_hpp
