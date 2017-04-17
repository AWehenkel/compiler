#include "FormalNode.hpp"
#include "Expression/ObjectIdentifierNode.hpp"

using namespace std;

FormalNode::~FormalNode(){
	delete e_name;
	delete e_type;
}

string FormalNode::getLiteral(bool with_type) const {
	return e_name->getLiteral(with_type) + " : " + e_type->getLiteral(with_type);
}
