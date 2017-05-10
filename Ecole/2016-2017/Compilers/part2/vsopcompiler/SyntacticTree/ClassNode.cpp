#include "ClassNode.hpp"
#include "ClassBodyNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "FieldNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"
#include "MethodNode.hpp"
#include "../SemanticAnalysis/SemanticError.hpp"

using namespace std;

ClassNode::~ClassNode(){
	delete e_name;
	delete e_extends;
	delete e_body;
}

int ClassNode::setParent(unordered_map<string, ClassNode*> &table){

	// Can have no parents
	if (!e_extends){
		parent = table.find("Object")->second;
		return 0;
	}

	if(table.find(e_extends->getLiteral()) != table.end()){
		parent = table.find(e_extends->getLiteral())->second;
		return 0;
	}
	return -1;
}

bool ClassNode::hasField(FieldNode* field) const{
	return ((fields.find(field->getName()->getLiteral()) != fields.end()) || (parent && parent->hasField(field)));
}

bool ClassNode::hasMethod(MethodNode* method) const{
	return ((methods.find(method->getName()->getLiteral()) != methods.end()) || (parent && parent->hasMethod(method)));
}

bool ClassNode::parentHasMethod(MethodNode* method) const{
	return (parent && parent->hasMethod(method));
}

FieldNode* ClassNode::getField(string name){

	FieldNode* to_ret;
	if(fields.find(name) == fields.end()){
		if(parent)
			to_ret = parent->getField(name);
		else
			to_ret = NULL;
	}
	else
		to_ret = fields.find(name)->second;

	return to_ret;
}

SemanticError ClassNode::addField(FieldNode* field){

	FieldNode* old_field = getField(field->getName()->getLiteral());
	SemanticError error;
	if(!old_field){
		fields[field->getName()->getLiteral()] = field;
	}
	else
		error = SemanticError("Error the field \"" + field->getName()->getLiteral() + "\" has already been declared in a parent class(" + to_string(old_field->getLine()) + ":" + to_string(old_field->getCol()) +").", field);
	return error;
}

MethodNode* ClassNode::getMethod(string name){

	MethodNode* to_ret;
	if(methods.find(name) == methods.end()){
		if(parent){
			to_ret = parent->getMethod(name);
		}
		else
			to_ret = NULL;
	}
	else
		to_ret = methods.find(name)->second;

	return to_ret;
}

SemanticError ClassNode::addMethod(MethodNode* method){

	if(methods.find(method->getName()->getLiteral()) == methods.end()){
		MethodNode* inherit_method = parent ? parent->getMethod(method->getName()->getLiteral()) : NULL;
		if(!inherit_method || *method == *inherit_method){
			methods[method->getName()->getLiteral()] = method;
			return SemanticError();
		}
		SemanticError error("The method \"" + method->getName()->getLiteral() + "\" has already been declared in a parent class(" +
			to_string(inherit_method->getLine()) + ":" + to_string(inherit_method->getCol()) + ") ", method);
		return error;
	}
	SemanticError error("The method \"" + method->getName()->getLiteral() + "\" has already been declared in the class(" +
		to_string((methods.find(method->getName()->getLiteral())->second)->getLine()) + ":" + to_string((methods.find(method->getName()->getLiteral())->second)->getCol()) + ") ", method);
	return error;
}

bool ClassNode::inCycle(){
	if(!in_cycle){
		in_cycle = true;
		in_cycle = !parent ? false : parent->inCycle();
	}
	return in_cycle;
}

TypeIdentifierNode* ClassNode::getCommonParent(ClassNode *other){

	TypeIdentifierNode* common_parent =  NULL;
	if(other == NULL)
		return NULL;

	// Check if there is a direct parent linkage
	TypeIdentifierNode* other_type = other->getName();
	if (*other_type == *e_name)
		common_parent = e_name;

	// If not check if there is a common ancestor
	if (!common_parent && parent)
		common_parent = parent->getCommonParent(other);

	if(!common_parent && other->parent)
		common_parent = other->parent->getCommonParent(this);

	return common_parent;
}

bool ClassNode::hasParent(ClassNode* candidate){
	TypeIdentifierNode* common_parent = getCommonParent(candidate);
	return common_parent && common_parent->getLiteral() == candidate->getName()->getLiteral();
}

int ClassNode::accept(Visitor* visitor){
	return visitor->visitClassNode(this);
}

int ClassNode::fillClassTable(unordered_map<string, ClassNode*> &table){

	if(table.find(e_name->getLiteral()) != table.end())
		return -1;
	table[e_name->getLiteral()] = this;

	return 0;
}

TypeIdentifierNode* ClassNode::getDeclarationType(string id){

	if(fields.find(id) != fields.end())
		return fields.find(id)->second->getType();
	else if(parent)
		return parent->getDeclarationType(id);

	return NULL;
}

const string ClassNode::getDeclarationLLVM(string id){
	if(fields.find(id) != fields.end())
		return fields.find(id)->second->getName()->getLLVMAddress();//TODO est ce que c'est vraiment mieux de stocker l'adresse de declaration du field dans son nom et non pas direct dans le fiedl.
	else if(parent)
		return parent->getDeclarationLLVM(id);

	return "";
}

string ClassNode::getLiteral(bool with_type) const{

	string literal = "Class(" + e_name->getLiteral(with_type) + ", ";
	if(e_extends == NULL)
		literal += "Object, ";
	else
		literal += e_extends->getLiteral(with_type) + ", ";
	literal += e_body->getLiteral(with_type) + ")";

	return literal;
}

vector<MethodNode*> ClassNode::getInheritedMethods(){
	vector<MethodNode*> inherited_methods;
	if(parent){
		vector<MethodNode*> parents_methods = parent->getAllMethods();
		for(vector<MethodNode*>::iterator it = parents_methods.begin(); it != parents_methods.end(); ++it)
			if(methods.find((*it)->getName()->getLiteral()) == methods.end())
				inherited_methods.push_back(*it);
	}
	return inherited_methods;
}

vector<MethodNode*> ClassNode::getOverridendMethods(){
	vector<MethodNode*> overriden_methods;
	if(parent){
		vector<MethodNode*> parents_methods = parent->getAllMethods();
		for(vector<MethodNode*>::iterator it = parents_methods.begin(); it != parents_methods.end(); ++it)
			if(methods.find((*it)->getName()->getLiteral()) != methods.end())
				overriden_methods.push_back(*it);
	}
	return overriden_methods;
}

vector<MethodNode*> ClassNode::getNewMethods(){
	unordered_map<string, MethodNode*> all_methods(methods);
	vector<MethodNode*> overriden_methods = getOverridendMethods();
	vector<MethodNode*> new_methods;

	for(vector<MethodNode*>::iterator it = overriden_methods.begin(); it != overriden_methods.end(); ++it)
		all_methods.erase((*it)->getName()->getLiteral());

	for(auto method : all_methods)
		new_methods.push_back(method.second);

	return new_methods;
}

vector<MethodNode*> ClassNode::getAllMethods(){
	vector<MethodNode*> all_methods;
	vector<MethodNode*> new_methods = getNewMethods();
	vector<MethodNode*> overriden_methods = getOverridendMethods();
	vector<MethodNode*> inherited_methods = getInheritedMethods();

	all_methods.reserve(new_methods.size() + overriden_methods.size() + inherited_methods.size());
	all_methods.insert(all_methods.end(), new_methods.begin(), new_methods.end());
	all_methods.insert(all_methods.end(), overriden_methods.begin(), overriden_methods.end());
	all_methods.insert(all_methods.end(), inherited_methods.begin(), inherited_methods.end());

	return all_methods;
}

vector<FieldNode*> ClassNode::getInheritedFields(){
	vector<FieldNode*> all_fields;
	vector<FieldNode*> parent_inh_fields;
	vector<FieldNode*> parent_new_fields;
	if(parent){
		parent_inh_fields = parent->getInheritedFields();
		parent_new_fields = parent->getNewFields();
	}
	all_fields.reserve(parent_inh_fields.size() + parent_new_fields.size());

	all_fields.insert(all_fields.end(), parent_inh_fields.begin(), parent_inh_fields.end());
	all_fields.insert(all_fields.end(), parent_new_fields.begin(), parent_new_fields.end());

	return all_fields;
}
vector<FieldNode*> ClassNode::getNewFields(){
	vector<FieldNode*> new_fields;
	for(auto field : fields)
		new_fields.push_back(field.second);
	return new_fields;
}
