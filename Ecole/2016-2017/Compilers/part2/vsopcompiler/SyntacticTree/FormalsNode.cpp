#include "FormalsNode.hpp"

using namespace std;

string FormalsNode::getLiteral() const {
	
	string literal = "[";
	for (vector<FormalNode*>::const_iterator it = formals.begin(); it < formals.end(); ++it) {
		literal += (*it)->getLiteral();
		if (it+1 != formals.end())		
			literal += ", ";
	}
	literal += "]";

	return literal;
}

void FormalsNode::addFormal(FormalNode *formal) { formals.push_back(formal);}

void FormalsNode::insertFormal(FormalNode *formal) { formals.insert(formals.begin(), formal);}
