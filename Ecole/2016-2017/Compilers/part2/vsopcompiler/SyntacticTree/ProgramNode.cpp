#include "ProgramNode.hpp"

using namespace std;

string ProgramNode::getLiteral() const{

	string literal = "[";
	for (vector<ClassNode*>::const_iterator it = classes.begin(); it < classes.end(); ++it) {
		literal += (*it)->getLiteral();
		if (it+1 != classes.end())
			literal += ",\n";
	}
	literal += "]\n";

	return literal;
}


void ProgramNode::addClass(ClassNode *new_class) {
	classes.push_back(new_class);
}

int ProgramNode::fillClassTable(std::unordered_map<std::string, ClassNode*> &table){
	for(std::vector<ClassNode*>::iterator class_it = classes.begin(); class_it != classes.end(); ++class_it)
		if((*class_it)->fillClassTable(table) < 0)
			return -1;
	table_classes = table;
	return 0;
}

int ProgramNode::accept(Visitor* visitor){
	return visitor->visitProgramNode(this);
}

ProgramNode::~ProgramNode(){
	for (std::vector<ClassNode*>::const_iterator it = classes.begin(); it < classes.end(); ++it)
		delete (*it);
}
