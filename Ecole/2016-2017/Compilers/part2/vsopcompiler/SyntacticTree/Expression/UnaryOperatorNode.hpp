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
	//Inherited
	std::string getLiteral() const{
		return "UnOp(" + (literal_op_table.find(e_op))->second + ","  + e_operand->getLiteral() + ")";
	};

	int accept(Visitor* visitor) const{
		return visitor.visitUnaryOperatorNode(this);
	};
};

#endif //UnaryOperatorNode_hpp
