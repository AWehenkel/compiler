#include <algorithm>

#include "ProgramNode.hpp"
#include "ClassNode.hpp"

//To remove:
#include "TypeIdentifierNode.hpp"

using namespace std;

ProgramNode& ProgramNode::operator+=(const ProgramNode &p1) {
	for(std::vector<ClassNode*>::const_iterator class_it = p1.classes.begin(); class_it != p1.classes.end(); ++class_it)
		addClass(*class_it);
	return *this;
}

ProgramNode::~ProgramNode(){
	for (std::vector<ClassNode*>::const_iterator it = classes.begin(); it < classes.end(); ++it)
		delete (*it);
	for (std::vector<ClassNode*>::const_iterator it = to_delete.begin(); it < to_delete.end(); ++it)
		delete (*it);
}

void ProgramNode::addClass(ClassNode *new_class) {
	classes.push_back(new_class);
}

void ProgramNode::addClassToDelete(string new_class) {
	to_delete.push_back(table_classes[new_class]);
}

int ProgramNode::fillClassTable(std::unordered_map<std::string, ClassNode*> &table){

	for(std::vector<ClassNode*>::iterator class_it = classes.begin(); class_it != classes.end(); ++class_it)
		if((*class_it)->fillClassTable(table) < 0)
			return -1;
	table_classes = table;

	return 0;
}

void ProgramNode::removeClass(ClassNode* node){
	classes.erase(std::remove(classes.begin(), classes.end(), node), classes.end());
	to_delete.push_back(node);
}

int ProgramNode::accept(Visitor* visitor){
	return visitor->visitProgramNode(this);
}

string ProgramNode::getLiteral(bool with_type) const{

	string literal = "[";
	for (vector<ClassNode*>::const_iterator it = classes.begin(); it < classes.end(); ++it) {
		literal += (*it)->getLiteral(with_type);
		if (it+1 != classes.end())
			literal += ",\n";
	}
	literal += "]\n";

	return literal;
}
