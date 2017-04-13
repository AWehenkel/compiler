#ifndef CallNode_hpp
#define CallNode_hpp

#include <string>
#include "../ArgsNode.hpp"
#include "ExpressionNode.hpp"
#include "ObjectIdentifierNode.hpp"

/*
	Class used to represent a syntaxic node containing a call to a method
*/
class CallNode : public ExpressionNode {
private :
	ObjectIdentifierNode* e_method_name;
	ArgsNode* e_args;
	ExpressionNode* e_object;
	ClassNode *current_class;
public :
	//Constructors:
	/*
	CallNode
	IN:	method_name:	ObjectIdentifierNode*, the name of the method.
			args:					ArgsNode*, the arguments of the call.
			object:				ExpressionNode*, the object on which the call is made(self by default).
			col: 					int, the column where the node is present.
			line:					int, the line where the node is present.
	*/
	CallNode(ObjectIdentifierNode* method_name, ArgsNode* args, ExpressionNode* object = NULL, int col = 0, int line = 0) : ExpressionNode(col, line), e_object(object), e_args(args), e_method_name(method_name){};

	//Destructor:
	~CallNode(){delete e_args; delete e_object;};

	//Public Methods:
	// Setters
	void setCurrentClass(ClassNode* node){current_class = node;}

	//getters
	ObjectIdentifierNode* getMethodName() const{return e_method_name;};
	ArgsNode* getArgs() const{return e_args;};
	ExpressionNode* getObject() const{return e_object;};

	//Inherited
	std::string getLiteral() const{
		std::string obj = e_object ? e_object->getLiteral() : "self";
		return "Call(" + obj + ", "  + e_method_name->getLiteral() + ", " + e_args->getLiteral() + ")";
	};

	int accept(Visitor* visitor){
		return visitor->visitCallNode(this);
	};

	int updateType(){

		// Get the type of the object
		TypeIdentifierNode* object_type
		if (!e_object)
			object_type = current_class->getType();
		else
			object_type = e_object->getType();

		if (!object_type){
			sdt::cerr << "Error in the compiler" << std::endl;
			return -1;
		}

		ClassNode* object_class = object_type->getClassType();
		if (!object_class){
			std::cerr << "L'objet du call n'est pas une classe" << std::endl;
			node_type = new TypeIdentifierNode("error");
			return -1;
		}

		MethodNode *method = object_class->getMethod(e_method_name->getLiteral());
		if (!method){
			std::cerr << "La méthode du call n'est pas définie pour cet objet" << std::endl;
			node_type = new TypeIdentifierNode("error");
			return -1;
		}

		FormalsNode *formals = method->getFormals();
		std::vector<FormalNode*> ls_formals = formals->getFormals();
		std::vector<ExpressionNode*> ls_args = e_args->getExpressions();
		if (ls_formals.size() != ls_formals.size()){
			std::cerr << "La méthode du call ne contient pas le bon nombre d'argument" << std::endl;
			node_type = new TypeIdentifierNode("error");
			return -1;
		}

		std::vector<ExpressionNode*>::const_iterator it = ls_args.begin();
		for(std::vector<FormalNode*>::const_iterator it2 = ls_formals.begin(); it2 != ls_formals.end(); ++it2){
			FormalNode* formal = *it2;
			ExpressionNode* arg = *it;
			TypeIdentifierNode* formal_type = formal->getType();
			TypeIdentifierNode* arg_type = arg->getType();
			if (!formal_type || !arg_type){
				std::cerr << "Error in the compiler" << std::endl;
				return -1;
			}
			if(strcmp(arg_type->getLiteral(), "error") != 0 && *arg_type != *formal_type){
				std::cerr << "La méthode du call contient des arguments qui ne sont pas du même type" << std::endl;
				node_type = new TypeIdentifierNode("error");
				return -1;
			}
			++it;
		}

		node_type = method->getRetType();

		return 0;

	};
};

#endif //CallNode_hpp
