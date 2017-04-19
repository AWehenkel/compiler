#include "MethodNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "Expression/BlockNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"
#include "ClassNode.hpp"
#include "FormalsNode.hpp"

using namespace std;


MethodNode::~MethodNode(){
	delete e_name;
	delete e_ret_type;
	delete e_formals;
	delete e_block;
}

bool MethodNode::equals(MethodNode &method){
	return *(method.getName()) == *(getName()) && *(method.getFormals()) == *(getFormals()) && *(method.getRetType()) == *(getRetType());
}

TypeIdentifierNode* MethodNode::getDeclarationType(string id){

	TypeIdentifierNode* to_ret = e_formals->getDeclarationType(id);
	if(!to_ret)
		to_ret = e_class_scope->getDeclarationType(id);

	return to_ret;
}

string MethodNode::getLiteral(bool with_type) const {
	return "Method(" + e_name->getLiteral(with_type) + ", " + e_formals->getLiteral(with_type) + ", "
									 + e_ret_type->getLiteral(with_type) + "," + e_block->getLiteral(with_type) + ")";
}

int MethodNode::updateType(Visitor* visitor){

	// Get block type
	TypeIdentifierNode *block_type = e_block->getType();
	if (!block_type){
		cerr << "Error in the compiler" << endl;
		return -1;
	}

	// Check if the types are the same or the block type class inherits from the return type class.
	if (e_ret_type->getLiteral() != "error" && block_type->getLiteral() != "error" && *block_type != *e_ret_type &&
			(!block_type->getClassType() || !block_type->getClassType()->hasParent(e_ret_type->getClassType()))){
		cerr << "Pas le même type dans methode" << endl;
		return -1;
	}

	return 0;
}
