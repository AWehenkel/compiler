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

TypeIdentifierNode* MethodNode::getDeclarationType(const string& id) const{

	TypeIdentifierNode* to_ret = e_formals->getDeclarationType(id);
	if(!to_ret)
		to_ret = e_class_scope->getDeclarationType(id);

	return to_ret;
}

const string MethodNode::getDeclarationLLVM(const string& id) const{

	string to_ret = e_formals->getDeclarationLLVM(id);
	if(!to_ret.size())
		to_ret = e_class_scope->getDeclarationLLVM(id);

	return to_ret;
}

FieldNode* MethodNode::getFieldFromId(const string& id) const{
	TypeIdentifierNode* to_ret = e_formals->getDeclarationType(id);
	if(to_ret)
		return NULL;

	return e_class_scope->getFieldFromId(id);
}

string MethodNode::getLiteral(bool with_type) const{
	return "Method(" + e_name->getLiteral(with_type) + ", " + e_formals->getLiteral(with_type) + ", "
									 + e_ret_type->getLiteral(with_type) + "," + e_block->getLiteral(with_type) + ")";
}

bool MethodNode::equals(const MethodNode &method) const{
	return *(method.getName()) == *(getName()) && *(method.getFormals()) == *(getFormals()) && *(method.getRetType()) == *(getRetType());
}

string MethodNode::getLLVMStructure(const string& struct_class) const{

	string code_struct = getRetType()->getLLVMType() + " (" + struct_class + "*, ";
	for(auto formal : e_formals->getFormals())
		code_struct += formal->getType()->getLLVMType() + ", ";

	code_struct.replace(code_struct.size() - 2, 2, ")*");

	return code_struct;
}

string MethodNode::getLLVMInstance(const string& class_name, ClassNode* parent) const{

	string code_inst = getLLVMStructure("%struct." + class_name);
	if(parent){
		string parent_name = parent->getInstanciatorOfMethod(getName()->getLiteral());
		code_inst += " bitcast (" + getLLVMStructure("%struct." + parent_name) + " @" + parent_name + "_" + getName()->getLiteral() + "";
		code_inst += " to " + getLLVMStructure("%struct." + class_name) + ")";
	}
	else if(class_name == "Main" && e_name->getLiteral() == "main" && 0)
		code_inst += " @main";
	else
		code_inst += " @" + class_name + "_" + getName()->getLiteral();

	return code_inst;
}
