#include "MethodNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "Expression/BlockNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"
#include "ClassNode.hpp"
#include "FormalsNode.hpp"

using namespace std;

string MethodNode::getLiteral() const {

	return "Method(" + e_name->getLiteral() + ", " + e_formals->getLiteral() + ", " + e_ret_type->getLiteral() + "," + e_block->getLiteral() + ")";
}

MethodNode::~MethodNode(){
	delete e_name; delete e_ret_type; delete e_ret_type; delete e_block;
}

bool MethodNode::equals(MethodNode &method){
	return *(method.getName()) == *(getName()) && *(method.getFormals()) == *(getFormals()) && *(method.getRetType()) == *(getRetType());
}

int MethodNode::updateType(){

	// Get block type
	TypeIdentifierNode *block_type = e_block->getType();
	if (!block_type){
		cerr << "Error in the compiler" << endl;
		return -1;
	}

	// Check if the types are the same
	if (strcmp(block_type->getLiteral().c_str(), "error") != 0 && *block_type != *e_ret_type){
		cerr << "Pas le même type dans méthode" << endl;
		return -1;
	}

	return 0;
}

TypeIdentifierNode* MethodNode::getDeclarationType(string id){
	TypeIdentifierNode* to_ret = e_formals->getDeclarationType(id);
	if(!to_ret)
		to_ret = e_class_scope->getDeclarationType(id);
	return to_ret;
}
