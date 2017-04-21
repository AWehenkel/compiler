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

string ClassNode::getLiteral(bool with_type) const{

	string literal = "Class(" + e_name->getLiteral(with_type) + ", ";
	if(e_extends == NULL)
		literal += "Object, ";
	else
		literal += e_extends->getLiteral(with_type) + ", ";
	literal += e_body->getLiteral(with_type) + ")";

	return literal;
}
