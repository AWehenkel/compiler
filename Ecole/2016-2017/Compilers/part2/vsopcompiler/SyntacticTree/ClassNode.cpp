#include "ClassNode.hpp"
#include "ClassBodyNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "FieldNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"
#include "MethodNode.hpp"

using namespace std;

string ClassNode::getLiteral(bool with_type) const{
	string literal = "Class(" + e_name->getLiteral(with_type) + ", ";
	if(e_extends == NULL)
		literal += "Object, ";
	else
		literal += e_extends->getLiteral(with_type) + ", ";
	literal += e_body->getLiteral(with_type) + ")";

	return literal;

}

int ClassNode::setParent(unordered_map<string, ClassNode*> &table){

	// Can have no parents
	if (!e_extends)
		return 0;

	if(table.find(e_extends->getLiteral()) != table.end()){
		parent = table.find(e_extends->getLiteral())->second;
		return 0;
	}
	return -1;
}
bool ClassNode::hasField(FieldNode* field) const{
	return ((fields.find(field->getName()->getLiteral()) != fields.end()) || (parent && parent->hasField(field)));
};;

bool ClassNode::hasMethod(MethodNode* method) const{
	return ((methods.find(method->getName()->getLiteral()) != methods.end()) || (parent && parent->hasMethod(method)));
}

bool ClassNode::parentHasMethod(MethodNode* method) const{
	return (parent && parent->hasMethod(method));
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

int ClassNode::accept(Visitor* visitor){
	return visitor->visitClassNode(this);
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

int ClassNode::addField(FieldNode* field){
	if(field){
		FieldNode* old_field = getField(field->getName()->getLiteral());
		if(!old_field){
			fields[field->getName()->getLiteral()] = field;
			return 0;
		}
		//Peut etre remplacer le bool de hasField par le field lui meme comme ça on pourra meme dire où il est dejà declare.
		cerr << "Erreur le champs existe dejà dans la class où dans l'un de ses parents. line: " << old_field->getLine() << " col: " << old_field->getCol() << endl;
		return -1;
	}
	cerr << "Erreur le champs est null." << endl;
	return -1;
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

int ClassNode::addMethod(MethodNode* method){
	if(method){
		if(methods.find(method->getName()->getLiteral()) == methods.end()){
			MethodNode* inherit_method = parent ? parent->getMethod(method->getName()->getLiteral()) : NULL;
			if(!inherit_method || *method == *inherit_method){
				methods[method->getName()->getLiteral()] = method;
				return 0;
			}
			cerr << "Erreur la methode \"" << method->getName()->getLiteral() << "\" est dejà declaree dans une class parente à la ligne:" << inherit_method->getLine() << " col: " << inherit_method->getCol() << endl;
			return -1;
		}
		cerr << "Erreur la methode \"" << method->getName()->getLiteral() << "\" existe dejà dans la class à la ligne:" << methods.find(method->getName()->getLiteral())->second->getLine() << " col: " << methods.find(method->getName()->getLiteral())->second->getCol() << endl;
		return -1;
	}
	cerr << "Erreur la methode est null." << endl;
	return -1;
}

bool ClassNode::inCycle(){
	if(!in_cycle){
		in_cycle = true;
		in_cycle = parent == NULL ? false : parent->inCycle();
	}
	return in_cycle;
}

TypeIdentifierNode* ClassNode::getCommonParent(ClassNode *other){

	TypeIdentifierNode* common_parent =  NULL;

	// Check if there is a direct parent linkage
	TypeIdentifierNode* other_type = other->getName();
	if (*other_type == *e_name)
		common_parent = e_name;

	if (!common_parent && parent)
		common_parent = parent->getCommonParent(other);

	if(!common_parent && other->parent)
		common_parent = other->parent->getCommonParent(this);

	return common_parent;
}

ClassNode::~ClassNode(){
	delete e_name;
	delete e_extends;
	delete e_body;
}

bool ClassNode::hasParent(ClassNode* candidate){
	TypeIdentifierNode* common_parent = getCommonParent(candidate);
	return common_parent && common_parent->getLiteral() == candidate->getName()->getLiteral();
}
