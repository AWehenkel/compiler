#include "FormalsNode.hpp"
#include "FormalNode.hpp"

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

void FormalsNode::addFormal(FormalNode *formal) {
	formals.push_back(formal);
}

void FormalsNode::insertFormal(FormalNode *formal) {
	formals.insert(formals.begin(), formal);
}

TypeIdentifierNode* FormalsNode::getDeclarationType(std::string id){
	for(std::vector<FormalNode*>::iterator formal_it = formals.begin(); formal_it != formals.end(); ++formal_it)
		if((*formal_it)->getName()->getLiteral() == id)
			return (*formal_it)->getType();
	return NULL;
}

bool FormalsNode::equals(FormalsNode &formals){
	if(formals.formals.size() != this->formals.size())
		return false;
	for(size_t i = 0; i < formals.formals.size(); i++){
		if(formals.formals.at(i)->getType() != this->formals.at(i)->getType())
			return false;
	}
	return true;
}
