#ifndef BinaryOperatorNode_hpp
#define BinaryOperatorNode_hpp

#include <string>
#include <map>
#include "ExpressionNode.hpp"
/*
	Enumeration listing the possible binary operator.
*/
enum BinaryOperator {b_op_and = 0, b_op_minus = 1, b_op_less = 2, b_op_leq = 3, b_op_plus = 4, b_op_equal = 5,
											b_op_times = 6, b_op_div = 7, b_op_pow = 8};
/*
	Class used to represent a syntaxic node containing a binary operation
*/
class BinaryOperatorNode : public ExpressionNode {
private :
	BinaryOperator e_op;
	ExpressionNode* e_left_operand;
	ExpressionNode* e_right_operand;
	std::map<BinaryOperator, std::string> literal_op_table;


public :
	//Constructors:
	/*
	BinaryOperatorNode
	IN:	op:					int, the integer corresponding to the binary symbol.
			l_operand:	ExpressionNode*, the left expression
			r_operand:	ExpressionNode*, the right expression
			col: 				int, the column where the node is present.
			line:				int, the line where the node is present.
	*/
	BinaryOperatorNode(int op, ExpressionNode* l_operand, ExpressionNode* r_operand, int col = 0, int line = 0) : ExpressionNode(col, line), e_op(static_cast<BinaryOperator>(op)),
	e_left_operand(l_operand), e_right_operand(r_operand){
		literal_op_table[b_op_and] = "and";
		literal_op_table[b_op_minus] = "-";
		literal_op_table[b_op_less] = "<";
		literal_op_table[b_op_leq] = "<=";
		literal_op_table[b_op_plus] = "+";
		literal_op_table[b_op_equal] = "=";
		literal_op_table[b_op_times] = "*";
		literal_op_table[b_op_div] = "/";
		literal_op_table[b_op_pow] = "^";
	};

	//Destructor:
	~BinaryOperatorNode(){delete e_left_operand; delete e_right_operand;};

	//Public Methods:
	//Inherited
	std::string getLiteral() const{
		return "BinOp(" + (literal_op_table.find(e_op))->second + ", "  + e_left_operand->getLiteral() +  ", " + e_right_operand->getLiteral() + ")";
	};

	int accept(Visitor* visitor) const{
		return visitor.visitBinaryOperatorNode(this);
	};
};

#endif //BinaryOperatorNode_hpp
