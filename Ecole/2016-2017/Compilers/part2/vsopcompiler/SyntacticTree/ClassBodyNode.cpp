#include "ClassBodyNode.hpp"
#include "FieldNode.hpp"
#include "MethodNode.hpp"

//To delete
#include "Expression/ObjectIdentifierNode.hpp"
using namespace std;

ClassBodyNode::~ClassBodyNode(){
	for (vector<FieldNode*>::const_iterator it = fields.begin(); it < fields.end(); ++it)
		delete (*it);
	for (vector<MethodNode*>::const_iterator it = methods.begin(); it < methods.end(); ++it)
		delete (*it);
}

string ClassBodyNode::getLiteral(bool with_type) const{

	//Print fields
	string literal = "[";
	for (vector<FieldNode*>::const_iterator it = fields.begin(); it != fields.end(); ++it) {
		literal += (*it)->getLiteral(with_type);
		if (it+1 != fields.end())
			literal += ",\n";
	}
	literal += "],\n";

	//Print methods
	literal += "[";
	for (vector<MethodNode*>::const_iterator it = methods.begin(); it != methods.end(); ++it) {
		literal += (*it)->getLiteral(with_type);
		if (it+1 != methods.end())
			literal += ",\n";
	}
	literal += "]";

	return literal;
}

void ClassBodyNode::addField(FieldNode *field) { fields.push_back(field);}

void ClassBodyNode::addMethod(MethodNode *method) { methods.push_back(method);}
