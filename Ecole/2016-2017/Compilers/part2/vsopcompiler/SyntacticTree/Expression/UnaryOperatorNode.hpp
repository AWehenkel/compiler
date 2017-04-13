#ifndef UnaryOperatorNode_hpp
#define UnaryOperatorNode_hpp

#include <string>
#include <map>
#include "ExpressionNode.hpp"
/*
	Enumeration listing the unary operator
*/
enum UnaryOperator {u_op_not = 0, u_op_minus = 1, u_op_isnull = 2};
/*
	Class used to represent an unary operation
*/
class UnaryOperatorNode : public ExpressionNode {
private :
	UnaryOperator e_op;
	ExpressionNode* e_operand;
	std::map<UnaryOperator, std::string> literal_op_table;
public :
	//Constructors:
	/*
	UnaryOperatorNode
	IN:	op:				int, the integer corresponding to the unary operator.
			operand:	ExpressionNode*, the operand
			col: 			int, the column where the node is present.
			line:			int, the line where the node is present.
	*/
	UnaryOperatorNode(int op, ExpressionNode* operand, int col = 0, int line = 0) : ExpressionNode(col, line), e_op(static_cast<UnaryOperator>(op)), e_operand(operand){
		literal_op_table[u_op_not] = "not";
		literal_op_table[u_op_isnull] = "isnull";
		literal_op_table[u_op_minus] = "-";
	};

	//Destructor:
	~UnaryOperatorNode(){delete e_operand;};

	//Public Methods:
	//Accessors:
	UnaryOperator getOperator() const{return e_op;};
	ExpressionNode* getOperand() const{return e_operand;};

	//Inherited
	std::string getLiteral() const{
		return "UnOp(" + (literal_op_table.find(e_op))->second + ","  + e_operand->getLiteral() + ")";
	};

	int accept(Visitor* visitor){
		return visitor->visitUnaryOperatorNode(this);
	};

	int update(){
		// Get the types of the two operands
		TypeIdentifierNode* op_type = e_operand->getType();
		if(!op_type){
			std::cerr << "Error in the compiler" << std::endl;
			return -1;
		}
		string s_op_type = op_type->getLiteral();

		switch (e_op){
			case UnaryOperator::u_op_not :
				// Check if operand is bools and return a bool if ok
				if (strcmp(s_op_type, "error") != 0 && strcmp(s_op_type, "bool") != 0){
					std::cerr << "Le membre du not n'est pas un booléan dans unary" << std::endl;
					node_type = new TypeIdentifierNode("error");
					return -1;
				}
				node_type = new TypeIdentifierNode("bool");
				break;
			case BinaryOperator::u_op_isnull :
				// Check if it not a basic type
				if (strcmp(s_op_type, "bool") == 0 || strcmp(s_op_type, "int32") == 0 || strcmp(s_op_type, "string") == 0){
					std::cerr << "Le membre du isnull n'est pas une classe dans unary" << std::endl;
					node_type = new TypeIdentifierNode("error");
					return -1;
				}
				node_type = new TypeIdentifierNode(s_op_type);
				break;
			case BinaryOperator::u_op_minus :
			// Check if operand is int32 and return a bool if ok
			if (strcmp(s_op_type, "error") != 0 && strcmp(s_op_type, "int32") != 0){
				std::cerr << "Le membre du minus n'est pas un int dans unary" << std::endl;
				node_type = new TypeIdentifierNode("error");
				return -1;
			}
			node_type = new TypeIdentifierNode("int32");
			break;
				break;
		}

		return 0;
	};
};

#endif //UnaryOperatorNode_hpp
