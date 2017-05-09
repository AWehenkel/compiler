#ifndef class_node_hpp
#define class_node_hpp

#include <string>
#include <unordered_map>
#include "VSOPNode.hpp"

class SemanticError;

/*
	Class used to represent a syntaxic node containing a class
*/
class ClassNode : public VSOPNode {
private :
	TypeIdentifierNode* e_name;
	TypeIdentifierNode* e_extends;
	ClassBodyNode *e_body;
	ClassNode *parent = NULL;
	std::unordered_map<std::string, FieldNode*> fields;
	std::unordered_map<std::string, MethodNode*> methods;
	bool in_cycle;

	/*
	hasField
	ROLE: This function is used to know wether or not the field is already declared in the class or in one of its parent.
	IN: field:	FieldNode*, the field to check.
	OUT: bool, true if the field is already declared.
	*/
	bool hasField(FieldNode* field) const;

	/*
	hasMethod
	ROLE: This function is used to know wether or not the field is already declared in the class or in one of its parent.
	IN: method:	MethodNode*, the method to check.
	OUT: bool, true if the method is already declared.
	*/
	bool hasMethod(MethodNode* method) const;


	/*
	parentHasMethod
	ROLE: This function is used to know wether or not the method is already declared in one of the parent of the class.
	IN: method:	MethodNode*, the method to check.
	OUT: bool, true if the method is already declared.
	*/
	bool parentHasMethod(MethodNode* method) const;

public :
	//Constructors

	/*
	IN:	name:			TypeIdentifierNode*, The name of the class.
			extends: 	TypeIdentifierNode, The name of the parent class.
			body:			ClassBodyNode *, The body of the class.
			col: 			int, the column where the node is present.
			line:			int, the line where the node is present.
	*/
	ClassNode(TypeIdentifierNode* name, ClassBodyNode *body, TypeIdentifierNode* extends = NULL, int col = 0, int line = 0) : VSOPNode(col, line),
	 	e_name(name), e_extends(extends), e_body(body), in_cycle(false), fields(), methods() {};

	//Destructor
	virtual ~ClassNode();

	//Public methods
	//Accesors
	TypeIdentifierNode* getName() const {return e_name;};
	TypeIdentifierNode* getExtends() const {return e_extends;};
	ClassBodyNode* getBody() const {return e_body;};

	/*
	getMethod
	ROLE: this function returns a pointer to the method declared in the class or in one of its parents.
	IN: 	method, std::string, the literal of the the name of the method.
	OUT:	A pointer to the method if it is declared else NULL.
	*/
	FieldNode* getField(std::string name);

	/*
	addField
	ROLE: This function adds a field to the table of fields of the class.
	IN:		field, FieldNode*, a pointer toward the field to add.
	OUT: -
	*/
	SemanticError addField(FieldNode* field);

	/*
	getMethod
	ROLE: this function returns a pointer to the method declared in the class or in one of its parents.
	IN: 	method, std::string, the literal of the the name of the method.
	OUT:	A pointer to the method if it is declared else NULL.
	*/
	MethodNode* getMethod(std::string name);

	/*
	addMethod
	ROLE: This function adds a method to the table of methods of the class.
	IN:		method, MethodNode*, a pointer toward the method to add.
	OUT: -
	*/
	SemanticError addMethod(MethodNode* method);

	/*
	setParent
	ROLE: This function is aimed at setting the parent ClassNode of the class.
	IN:		unordered_map<std:string, ClassNode*> class_table, the table containing the class of the program.
	OUT: -
	*/
	int setParent(std::unordered_map<std::string, ClassNode*> &table);

	/*
	inCycle
	ROLE: This function is used to know if there are cyclic inheritance.
	IN: -
	OUT: bool, true if the class is in a inheritance cycle
	*/
	bool inCycle();

	/*
	getCommonParent
	ROLE : This function finds the common ancestor to two classes
	IN : other, pointers to classes
  OUT : A pointer to the common ancestor type, null if no common ancestor
	*/
	TypeIdentifierNode* getCommonParent(ClassNode *other);

	/*
	hasParent
	ROLE: Determine if the argument is a parent of the current class.
	IN : candidate: ClassNode*, the candidate parent.
	OUT : bool, true if the candidate is a parent of the current class.
	*/
	bool hasParent(ClassNode* candidate);

	/*
	getInheritedMethods()
	ROLE: Return the methods inherited by the class.
	OUT: std::vector<MethodNode*>, the inherited methods.
	*/
	std::vector<MethodNode*> getInheritedMethods();

	/*
	getOverridendMethods()
	ROLE: Return the methods overriden by the class.
	OUT: std::vector<MethodNode*>, the overriden methods.
	*/
	std::vector<MethodNode*> getOverridendMethods();

	/*
	getNewMethods()
	ROLE: Return the methods newly declared by the class.
	OUT: std::vector<MethodNode*>, the new methods.
	*/
	std::vector<MethodNode*> getNewMethods();

	/*
	getAllMethods()
	ROLE: Return all the methods of the class.
	OUT: std::vector<MethodNode*>, the methods.
	*/
	std::vector<MethodNode*> getAllMethods();

	//setters
	void setExtends(TypeIdentifierNode* node){
		e_extends = node;
		in_cycle = false;
		parent = NULL;
	};
	//Inherited
	int accept(Visitor* visitor);
	int fillClassTable(std::unordered_map<std::string, ClassNode*> &table);
	TypeIdentifierNode* getDeclarationType(std::string id);
	const std::string getDeclarationLLVM(std::string id);
	std::string getLiteral(bool with_type = false) const;
};

#endif //class_node_hpp
