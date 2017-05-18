#include "MethodNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "Expression/BlockNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"
#include "ClassNode.hpp"
#include "FormalsNode.hpp"
#include "FormalNode.hpp"

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

const string MethodNode::getDeclarationLLVM(string id){
	string to_ret = e_formals->getDeclarationLLVM(id);
	if(!to_ret.size())
		to_ret = e_class_scope->getDeclarationLLVM(id);

	return to_ret;
}

FieldNode* MethodNode::getFieldFromId(string id){
		return e_class_scope->getFieldFromId(id);
}

string MethodNode::getLiteral(bool with_type) const {
	return "Method(" + e_name->getLiteral(with_type) + ", " + e_formals->getLiteral(with_type) + ", "
									 + e_ret_type->getLiteral(with_type) + "," + e_block->getLiteral(with_type) + ")";
}

string MethodNode::getLLVMStructure(string struct_class) const{
	string code_struct = getRetType()->getLLVMType() + " (" + struct_class + "*, ";
	for(auto formal : e_formals->getFormals())
		code_struct += formal->getType()->getLLVMType() + ", ";

	code_struct.replace(code_struct.size() - 2, 2, ")*");
	return code_struct;
}

string MethodNode::getLLVMInstance(string class_name, string parent_name) const{
	string code_inst = getLLVMStructure("%struct." + class_name);
	if(!parent_name.empty()){
		code_inst += " bitcast (" + getLLVMStructure("%struct." + parent_name) + " @" + parent_name + "_" + getName()->getLiteral() + "";
		code_inst += " to " + getLLVMStructure("%struct." + class_name) + ")";
	}
	else if(class_name == "Main" && e_name->getLiteral() == "main" && 0)
		code_inst += " @main";
	else
		code_inst += " @" + class_name + "_" + getName()->getLiteral();

	return code_inst;
}
