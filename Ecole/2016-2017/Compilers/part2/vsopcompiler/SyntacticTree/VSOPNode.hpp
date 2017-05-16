#ifndef vsop_node_hpp
#define vsop_node_hpp

#include "../Visitors/Visitor.hpp"

#include <iostream>
#include <string>
#include <vector>

/*
	Abstract parent class of any node of the syntaxic tree
*/
class VSOPNode {
protected :
	//Fields
	const int n_col;
	const int n_line;
	std::string llvm_address;
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
	virtual std::string getLiteral(bool with_type = false) const = 0;

	/*
	accept
	ROLE: accept the node using a specific visitor.
	IN: visitor: Visitor*, a reference to the visitor.
	OUT: int, a return code.
	*/
	virtual int accept(Visitor* visitor) = 0;

	/*
	getDeclarationType
	ROLE: This function returns a pointer to the TypeIdentifierNode corresponding to the id in the scope.
	IN:		id: std::string, the name of the variable.
	OUT: bool, true if the variable is declared in the VSOPNode or in one of its children.
	*/
	virtual TypeIdentifierNode* getDeclarationType(std::string id){
		return NULL;
	};

	/*
	getDeclarationLLVM
	ROLE: This function returns a string corresponding to the llvm id in the scope of the id.
	IN:		id: std::string, the name of the variable.
	OUT: bool, true if the variable is declared in the VSOPNode or in one of its children.
	*/
	virtual const std::string getDeclarationLLVM(std::string id){
		return "";
	};

	//Accessors
	const int getLine() const{
		return n_line;
	};
	const int getCol() const{
		return n_col;
	};
	const std::string getLLVMAddress(){
		return llvm_address;
	};
	void setLLVMAddress(int i_llvm_address){
		 llvm_address = "%" + std::to_string(i_llvm_address);
	};
	void setLLVMAddressAsString(std::string s_llvm_address){
		 llvm_address = "%" + s_llvm_address;
	};
	void setLLVMAddress(std::string s_llvm_address){
		 llvm_address = s_llvm_address;
	};

};

#endif //vsop_node_hpp
