#include "ClassNode.hpp"
#include "ClassBodyNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "MethodNode.hpp"

using namespace std;

string ClassNode::getLiteral() const{

	string literal = "Class(" + e_name->getLiteral() + ", ";
	if(e_extends == NULL)
		literal += "Object, ";
	else
		literal += e_extends->getLiteral() + ", ";
	literal += e_body->getLiteral() + ")";

	return literal;

}

int ClassNode::setParent(unordered_map<std::string, ClassNode*> &table){

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

int ClassNode::fillClassTable(std::unordered_map<std::string, ClassNode*> &table){
	if(table.find(e_name->getLiteral()) != table.end())
		return -1;
	table[e_name->getLiteral()] = this;
	return 0;
}

TypeIdentifierNode* ClassNode::getDeclarationType(std::string id){

	if(fields.find(id) != fields.end())
		return fields.find(id)->second->getType();
	else if(parent)
		return parent->getDeclarationType(id);
	return NULL;
}

int ClassNode::accept(Visitor* visitor){
	return visitor->visitClassNode(this);
}

FieldNode* ClassNode::getField(std::string name){
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
		//Peut etre remplacer le bool de hasField par le field lui meme comme ça on pourra meme dire où il est déjà déclaré.
		std::cerr << "Erreur le champs existe déjà dans la class où dans l'un de ses parents. line: " << old_field->getLine() << " col: " << old_field->getCol() << std::endl;
		return -1;
	}
	std::cerr << "Erreur le champs est null." << std::endl;
	return -1;
}

MethodNode* ClassNode::getMethod(std::string name){
	MethodNode* to_ret;
	if(methods.find(name) == methods.end()){
		if(parent)
			to_ret = parent->getMethod(name);
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
			std::cerr << "Erreur la methode \"" << method->getName()->getLiteral() << "\" est déjà déclarée dans une class parente à la ligne:" << inherit_method->getLine() << " col: " << inherit_method->getCol() << std::endl;
			return -1;
		}
		std::cerr << "Erreur la methode \"" << method->getName()->getLiteral() << "\" existe déjà dans la class à la ligne:" << methods.find(method->getName()->getLiteral())->second->getLine() << " col: " << methods.find(method->getName()->getLiteral())->second->getCol() << std::endl;
		return -1;
	}
	std::cerr << "Erreur la methode est null." << std::endl;
	return -1;
}

bool ClassNode::inCycle(){
	if(!in_cycle){
		in_cycle = true;
		in_cycle = parent == NULL ? false : parent->inCycle();
	}
	return in_cycle;
}

TypeIdentifierNode* getCommonParent(ClassNode *other){

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
