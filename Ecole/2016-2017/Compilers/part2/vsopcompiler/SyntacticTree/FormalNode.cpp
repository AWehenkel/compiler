#include "FormalNode.hpp"

using namespace std;

string FormalNode::getLiteral() const {
	return e_name->getLiteral() + " : " + e_type->getLiteral();
}
