#include "MethodNode.hpp"

using namespace std;

string MethodNode::getLiteral() const {

	return "Method(" + e_name->getLiteral() + ", " + e_formals->getLiteral() + ", " + e_ret_type->getLiteral() + "," + e_block->getLiteral() + ")";
}
