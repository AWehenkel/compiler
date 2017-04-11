#include "ClassNode.hpp"

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
	if(table.find(e_extends->getLiteral()) != table.end()){
		parent = table.find(e_extends->getLiteral())->second;
		return 0;
	}
	return -1;
}
