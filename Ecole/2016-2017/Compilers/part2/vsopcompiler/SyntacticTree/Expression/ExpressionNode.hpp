#ifndef expression_node_hpp
#define expression_node_hpp

#include <string>
#include "../VSOPNode.hpp"
#include "../TypeIdentifierNode.hpp" // TODO : check que ça fout pas la merde
/*
	Parent class of any node representing an expression.
*/
class ExpressionNode : public VSOPNode {
protected :
	TypeIdentifierNode* node_type;
	bool self_type = false;
	std::string llvm_type; // TODO : check qu'il faut bien le mettre là
public :
	//Constructors
	/*
	ExpressionNode
	IN:	col: 					int, the column where the node is present.
			line:					int, the line where the node is present.
	*/
	ExpressionNode(int col = 0, int line = 0) : VSOPNode(col, line), node_type(NULL){};
	ExpressionNode(std::string type, int col = 0, int line = 0);
	ExpressionNode(TypeIdentifierNode* type, int col = 0, int line = 0) : VSOPNode(col, line), node_type(type){};

	//Destructor
	virtual ~ExpressionNode();

	//Public method
	// TODO : check qu'il faut bien le mettre là
	void setLLVMType(std::string content){
		if(content == "int32")
			llvm_type = "i32";
		else if(content == "bool")
			llvm_type = "i1";
		else if(content == "string")
			llvm_type = "c";
		else
			llvm_type = content;
	};

	//Inherited
	virtual int accept(Visitor* visitor) = 0;
	virtual std::string getLiteral(bool with_type = false) const = 0;
	virtual TypeIdentifierNode* getType(){return node_type;};
	virtual std::string getLLVMType();
	virtual void setType(TypeIdentifierNode* new_type, bool new_self_type = false){
		node_type = new_type;
		self_type = new_self_type;
		setLLVMType(node_type->getLiteral()); // TODO : check que c'est bien là qu'il faut mettre ça
	};
};

#endif //expression_node_hpp
