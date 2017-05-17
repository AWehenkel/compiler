#ifndef TypeIdentifierNode_hpp
#define TypeIdentifierNode_hpp

#include <string>
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing a type identifier
*/
class TypeIdentifierNode : public VSOPNode {
private :
	std::string t_content;
	std::string llvm_type;
	ClassNode* t_class_type;
	//Overloaded operator
	friend inline bool operator==(TypeIdentifierNode &id1, TypeIdentifierNode &id2){
		return id1.equals(id2);
	};
	friend inline bool operator!=(TypeIdentifierNode &id1, TypeIdentifierNode &id2){
		return !(id1 == id2);
	};

	void setLLVMType(std::string vsop_type){
		if(vsop_type == "int32")
			llvm_type = "i32";
		else if(vsop_type == "bool" || vsop_type == "unit")
			llvm_type = "i1";
		else if(vsop_type == "string")
			llvm_type = "i8*";
		else
			llvm_type = "%struct."+ vsop_type + "*";
	};

public :

	//Constructors:
	TypeIdentifierNode(std::string content, int col = 0, int line = 0) : VSOPNode(col, line), t_content(content), t_class_type(NULL){setLLVMType(content);};
	TypeIdentifierNode(std::string content, ClassNode* class_type, int col = 0, int line = 0) : VSOPNode(col, line), t_content(content), t_class_type(class_type){setLLVMType(content);};

	//Public Methods:
	//Setter
	void setClassType(ClassNode* class_type){
		t_class_type = class_type;
	};

	void setContent(std::string content){
		t_content = content;
	};

	// getters
	ClassNode* getClassType() const{return t_class_type;};
	std::string getLLVMType() const{return llvm_type;};

	//TODO changer peut etre
	std::string getInitLLVMValue() const{
		std::string init_val;
		if(llvm_type == "i32")
			init_val = "0";
		else if(llvm_type == "i1")
			init_val = "0";
		else if(llvm_type == "i8*")
			init_val = "null";
		else
			init_val = "null";
		return init_val;
	};

	/*
	equals
	ROLE: Compare an id to determine whether or not it is equal to this id.
	IN:		id: TypeIdentifierNode const &, the id with which compare the current id.
	OUT: bool, true if the contents are equal.
	*/
	bool equals(TypeIdentifierNode &id){
		return id.t_content == t_content;
	};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitTypeIdentifierNode(this);};
	std::string getLiteral(bool with_type = false) const{return t_content;};

};

#endif //TypeIdentifierNode_hpp
