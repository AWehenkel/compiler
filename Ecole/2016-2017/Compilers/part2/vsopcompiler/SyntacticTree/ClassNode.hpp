#ifndef class_node_hpp
#define class_node_hpp

#include <string>
#include <unordered_map>
#include "ClassBodyNode.hpp"
#include "VSOPNode.hpp"
/*
	Class used to represent a syntaxic node containing a class
*/
class ClassNode : public VSOPNode {
private :
	TypeIdentifierNode* e_name;
	TypeIdentifierNode* e_extends;
	ClassBodyNode *e_body;
	ClassNode *parent;
	std::unordered_map<std::string, FieldNode*> fields;
	std::unordered_map<std::string, MethodNode*> methods;
	bool in_cycle;

	/*
	hasField
	ROLE: This function is used to know wether or not the field is already declared in the class or in one of its parent.
	IN: field:	FieldNode*, the field to check.
	OUT: bool, true if the field is already declared.
	*/
	bool hasField(FieldNode* field) const{
		return ((fields.find(field->getName()->getLiteral()) != fields.end()) || (parent && parent->hasField(field)));
	};

	/*
	hasMethod
	ROLE: This function is used to know wether or not the field is already declared in the class or in one of its parent.
	IN: method:	MethodNode*, the method to check.
	OUT: bool, true if the method is already declared.
	*/
	bool hasMethod(MethodNode* method) const{
		return ((methods.find(method->getName()->getLiteral()) != methods.end()) || (parent && parent->hasMethod(method)));
	};


	/*
	parentHasMethod
	ROLE: This function is used to know wether or not the method is already declared in one of the parent of the class.
	IN: method:	MethodNode*, the method to check.
	OUT: bool, true if the method is already declared.
	*/
	bool parentHasMethod(MethodNode* method) const{
		return (parent && parent->hasMethod(method));
	};
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
	~ClassNode(){delete e_name; delete e_extends; delete e_body;}

	//Public methods
	//Inherited
	std::string getLiteral() const;
	int fillClassTable(std::unordered_map<std::string, ClassNode*> &table){
		if(table.find(e_name->getLiteral()) != table.end())
			return -1;
		table[e_name->getLiteral()] = this;
		return 0;
	};

	int accept(Visitor* visitor){
		return visitor->visitClassNode(this);
	};
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
	FieldNode* getField(std::string name){
		FieldNode* to_ret;
		if(fields.find(name) == fields.end()){
			if(parent)
				to_ret = parent->getField(name);
			else
				to_ret = NULL;
		}
		else
			to_ret = fields.find(name)->second;
		return to_ret;
	}

	/*
	addField
	ROLE: This function adds a field to the table of fields of the class.
	IN:		field, FieldNode*, a pointer toward the field to add.
	OUT: -
	*/
	int addField(FieldNode* field){
		if(field){
			FieldNode* old_field = getField(field->getName()->getLiteral());
			if(!old_field){
				fields[field->getName()->getLiteral()] = field;
				return 0;
			}
			//Peut etre remplacer le bool de hasField par le field lui meme comme ça on pourra meme dire où il est déjà déclaré.
			std::cerr << "Erreur le champs existe déjà dans la class où dans l'un de ses parents. line: " << old_field->getLine() << " col: " << old_field->getCol() << std::endl;
			return -1;
		}
		std::cerr << "Erreur le champs est null." << std::endl;
		return -1;
	};

	/*
	getMethod
	ROLE: this function returns a pointer to the method declared in the class or in one of its parents.
	IN: 	method, std::string, the literal of the the name of the method.
	OUT:	A pointer to the method if it is declared else NULL.
	*/
	MethodNode* getMethod(std::string name){
		MethodNode* to_ret;
		if(methods.find(name) == methods.end()){
			if(parent)
				to_ret = parent->getMethod(name);
			else
				to_ret = NULL;
		}
		else
			to_ret = methods.find(name)->second;
		return to_ret;
	}

	/*
	addMethod
	ROLE: This function adds a method to the table of methods of the class.
	IN:		method, MethodNode*, a pointer toward the method to add.
	OUT: -
	*/
	int addMethod(MethodNode* method){
		if(method){
			if(methods.find(method->getName()->getLiteral()) == methods.end()){
				MethodNode* inherit_method = parent ? parent->getMethod(method->getName()->getLiteral()) : NULL;
				if(!inherit_method || *method == *inherit_method){
					methods[method->getName()->getLiteral()] = method;
					return 0;
				}
				std::cerr << "Erreur la methode \"" << method->getName()->getLiteral() << "\" est déjà déclarée dans une class parente à la ligne:" << inherit_method->getLine() << " col: " << inherit_method->getCol() << std::endl;
				return -1;
			}
			std::cerr << "Erreur la methode \"" << method->getName()->getLiteral() << "\" existe déjà dans la class à la ligne:" << methods.find(method->getName()->getLiteral())->second->getLine() << " col: " << methods.find(method->getName()->getLiteral())->second->getCol() << std::endl;
			return -1;
		}
		std::cerr << "Erreur la methode est null." << std::endl;
		return -1;
	};

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
	bool inCycle(){
		if(!in_cycle){
			in_cycle = true;
			in_cycle = parent == NULL ? false : parent->inCycle();
		}
		return in_cycle;
	}
};

#endif //class_node_hpp
