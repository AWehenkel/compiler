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
