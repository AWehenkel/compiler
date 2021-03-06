#include <algorithm>

#include "ProgramNode.hpp"
#include "ClassNode.hpp"
#include "TypeIdentifierNode.hpp"
#include "../SemanticAnalysis/SemanticError.hpp"

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

void ProgramNode::removeClass(ClassNode* node){
	classes.erase(std::remove(classes.begin(), classes.end(), node), classes.end());
	to_delete.push_back(node);
}

void ProgramNode::addClass(ClassNode *new_class) {
	classes.push_back(new_class);
}

SemanticError ProgramNode::fillClassTable(std::unordered_map<std::string, ClassNode*> &table){

	for(std::vector<ClassNode*>::iterator class_it = classes.begin(); class_it != classes.end(); ++class_it)
		if((*class_it)->fillClassTable(table) < 0)
			return SemanticError("Redefinition of class: " + (*class_it)->getName()->getLiteral(), *class_it);
			
	table_classes = table;

	return SemanticError();
}
