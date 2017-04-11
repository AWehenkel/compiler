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


void ProgramNode::addClass(ClassNode *new_class) { classes.push_back(new_class);}
