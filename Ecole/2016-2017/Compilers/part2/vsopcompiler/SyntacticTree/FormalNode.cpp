#include "FormalNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"

using namespace std;

string FormalNode::getLiteral() const {
	return e_name->getLiteral() + " : " + e_type->getLiteral();
}

FormalNode::~FormalNode(){
	delete e_name;
	delete e_type;
}
