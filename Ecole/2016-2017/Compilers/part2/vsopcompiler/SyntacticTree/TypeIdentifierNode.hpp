#ifndef TypeIdentifierNode_hpp
#define TypeIdentifierNode_hpp

#include <string>
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing a type identifier
*/
class TypeIdentifierNode : public VSOPNode {
private :
	std::string t_content;
	ClassNode* t_class_type;
	//Overloaded operator
	friend inline bool operator==(TypeIdentifierNode &id1, TypeIdentifierNode &id2){
		return id1.equals(id2);
	};
	friend inline bool operator!=(TypeIdentifierNode &id1, TypeIdentifierNode &id2){
		return !(id1 == id2);
	};

public :

	//Constructors:
	TypeIdentifierNode(std::string content, int col = 0, int line = 0) : VSOPNode(col, line), t_content(content), t_class_type(NULL){};
	TypeIdentifierNode(std::string content, ClassNode* class_type, int col = 0, int line = 0) : VSOPNode(col, line), t_content(content), t_class_type(class_type){};

	//Public Methods:
	//Setter
	void setClassType(ClassNode* class_type){
		t_class_type = class_type;
	};

	// getters
	ClassNode* getClassType(){return t_class_type;};

	/*
	equals
	ROLE: Compare an id to determine whether or not it is equal to this id.
	IN:		id: TypeIdentifierNode const &, the id with which compare the current id.
	OUT: bool, true if the contents are equal.
	*/
	bool equals(TypeIdentifierNode &id){
		return id.t_content == t_content;
	};

	//Inherited
	int accept(Visitor* visitor){return visitor->visitTypeIdentifierNode(this);};
	std::string getLiteral(bool with_type = false) const{return t_content;};

};

#endif //TypeIdentifierNode_hpp
