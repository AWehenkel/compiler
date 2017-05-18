#include <string>

#include "CheckTypeVisitor.hpp"
#include "all_headers.hpp"

using namespace std;

int CheckTypeVisitor::visitAssignNode(AssignNode *node){

  if(Visitor::visitAssignNode(node) < 0)
     return -1;

  // Get types
  TypeIdentifierNode *name_type = node->getName()->getType();
  TypeIdentifierNode *expr_type = node->getExpression()->getType();
  if(!name_type){
    SemanticError error("Error in the compiler in AssignNode : name_type is null", node);
    errors.push_back(error);
    return -1;
  }
  if(!expr_type){
    SemanticError error("Error in the compiler in AssignNode : expr_type is null", node);
    errors.push_back(error);
    return -1;
  }

  /* It there was a type error in the son e_expr or if the two types are the
  * same, assign the type of e_name to node_type and stop the propagation of
  * errors */
  if (expr_type->getLiteral() == "error" || *name_type == *expr_type || (expr_type->getClassType() && expr_type->getClassType()->hasParent(name_type->getClassType()))){
    node->setType(name_type);
    return errors.size();
  }

  // If the two types were different, assign "error" to e_name and create an error
  node->setType(new TypeIdentifierNode("error"));
  SemanticError error("Assignement of different types : '" + node->getName()->getLiteral() + "' of type '" + name_type->getLiteral() + "' has not the same type as assigned expression of type '" + expr_type->getLiteral() + "'", node);
  errors.push_back(error);
  return errors.size();
}


int CheckTypeVisitor::visitBinaryOperatorNode(BinaryOperatorNode *node){

  if(Visitor::visitBinaryOperatorNode(node) < 0)
     return -1;

  // Get the types of the two operands
  TypeIdentifierNode* left_type = node->getLeft()->getType();
  TypeIdentifierNode* right_type = node->getRight()->getType();
  if(!left_type){
    SemanticError error("Error in the compiler in BinaryOperatorNode : left_type is null", node);
    errors.push_back(error);
    return -1;
  }
  if(!right_type){
    SemanticError error("Error in the compiler in BinaryOperatorNode : right_type is null", node);
    errors.push_back(error);
    return -1;
  }
  string s_left_type = left_type->getLiteral();
  string s_right_type = right_type->getLiteral();

  BinaryOperator op = node->getOperator();
  switch (op){
    case BinaryOperator::b_op_and :
      // Check both operands are bools or errors and return a bool if ok
      if ((s_left_type != "bool" && s_left_type != "error") || (s_right_type != "bool" && s_right_type != "error")){
        SemanticError error("The two members of an and-expression must be boolean, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return errors.size();
      }
      node->setType(left_type);
      break;
    case BinaryOperator::b_op_equal :
      // TODO : est-ce qu'on doit pas checker pour l'héritage ?
      // Check if the two types are the same (or errors) and return bool if ok
      if(s_left_type != "error" && s_right_type != "error" && s_left_type != s_right_type){
        SemanticError error("The two members of an equal-expression must have the same type, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return errors.size();
      }
      node->setType(new TypeIdentifierNode("bool"), true);
      break;
    case BinaryOperator::b_op_leq :
    case BinaryOperator::b_op_less :
      // Check both operands are int32 or errors and return a bool if ok
      if ((s_left_type != "int32" && s_left_type != "error" != 0) || (s_right_type != "int32" && s_right_type != "error")){
        SemanticError error("The two members of a comparison must be int32, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return errors.size();
      }
      node->setType(new TypeIdentifierNode("bool"), true);
      break;
    default :
      // Check both operands are int32 and return a int32 if ok
      if ((s_left_type != "int32" && s_left_type != "error") || (s_right_type != "int32" && s_right_type != "error")){
        SemanticError error("The two members of a math expression must be int32, got '" + s_left_type +"' and '" + s_right_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return errors.size();
      }
      node->setType(left_type);
  }

  return errors.size();
}

int CheckTypeVisitor::visitBlockNode(BlockNode *node){

  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }

  vector<ExpressionNode*> expressions = node->getExpressions();
	ExpressionNode *last_expr = *(expressions.end()-1);
	TypeIdentifierNode *expr_type = last_expr->getType();
	if (!expr_type){
		SemanticError error("Error in the compiler in BlockNode : expr_type is null", node);
		errors.push_back(error);
		return -1;
	}
	// Put the type of the last instruction, even if it was an error.
	node->setType(expr_type);

	/* Even if there is an error in the last instruction, it wasn't in the block
	* directly, so we don't return an error code
	*/
  return errors.size();
}


int CheckTypeVisitor::visitBraceNode(BraceNode *node){

  if(Visitor::visitBraceNode(node) < 0)
     return -1;

  // If the braces are empty, they are of type unit, in the other case get the type of the expression
  ExpressionNode* expr = node->getExpression();
  TypeIdentifierNode *expr_type = expr ? expr->getType() : new TypeIdentifierNode("unit");
  if(!expr)
    node->setType(expr_type, true);
  else
    node->setType(expr_type);

  return errors.size();
}

int CheckTypeVisitor::visitCallNode(CallNode *node){

  if(Visitor::visitCallNode(node) < 0)
     return -1;

  // Get the type of the object
  TypeIdentifierNode* object_type;
  if (!node->getObject()){
    // If no objet identifier, the call is made on the current object
    object_type = node->getCurrentClass()->getName();
  }
  else
    object_type = node->getObject()->getType();

  if (!object_type){
    SemanticError error("Error in the compiler in CallNode : object_type is null", node);
		errors.push_back(error);
    node->setType(new TypeIdentifierNode("error"), true);
    return -1;
  }

  // Check if the call is indeed made on an object
  ClassNode* object_class = object_type->getClassType();
  if (!object_class){
    SemanticError error("Calls must be done on object : '" + object_type->getLiteral() + "' is not a class.", node);
		errors.push_back(error);
    node->setType(new TypeIdentifierNode("error"), true);
    return errors.size();
  }

  // Check if the method called exists for the given object
  MethodNode *method = object_class->getMethod(node->getMethodName()->getLiteral());
  if (!method){
    SemanticError error("Undefined method '" + node->getMethodName()->getLiteral() + " for object of type '" + object_type->getLiteral() + "'", node);
		errors.push_back(error);
    node->setType(new TypeIdentifierNode("error"), true);
    return errors.size();
  }

  // Check if the arguments correspond to the formals of the method
  FormalsNode *formals = method->getFormals();
  vector<FormalNode*> ls_formals = formals->getFormals();
  vector<ExpressionNode*> ls_args = node->getArgs()->getExpressions();
  if (ls_formals.size() != ls_args.size()){
    SemanticError error("Wrong number of argument in call : need " + to_string(ls_formals.size()) + " and got "  +  to_string(ls_args.size()), node);
		errors.push_back(error);
    node->setType(new TypeIdentifierNode("error"), true);
    return errors.size();
  }

  vector<ExpressionNode*>::const_iterator it = ls_args.begin();
  int i = 1;
  for(vector<FormalNode*>::const_iterator it2 = ls_formals.begin(); it2 != ls_formals.end(); ++it2){
    FormalNode* formal = *it2;
    ExpressionNode* arg = *it;
    TypeIdentifierNode* formal_type = formal->getType();
    TypeIdentifierNode* arg_type = arg->getType();
    if (!formal_type){
      SemanticError error("Error in the compiler in CallNode : formal_type is null", node);
  		errors.push_back(error);
      return -1;
    }
    if (!arg_type){
      SemanticError error("Error in the compiler in CallNode : arg_type is null", node);
  		errors.push_back(error);
      return -1;
    }

    if(arg_type->getLiteral() != "error" && *arg_type != *formal_type && (!arg_type->getClassType() || !arg_type->getClassType()->hasParent(formal_type->getClassType()))){
      SemanticError error("Type of argument " + to_string(i) + " in call does not correspond to type in method :  got '" + arg_type->getLiteral() + "' and needed '" + formal_type->getLiteral() + "'" , node);
  		errors.push_back(error);
      node->setType(new TypeIdentifierNode("error"), true);
    }
    ++it;
    ++i;
  }
  node->setType(method->getRetType());

  return errors.size();
}

int CheckTypeVisitor::visitConditionalNode(ConditionalNode *node){

  if(Visitor::visitConditionalNode(node) < 0)
     return -1;

  TypeIdentifierNode *condition_type = node->getCondition()->getType();
  if (!condition_type){
    SemanticError error("Error in the compiler in ConditionalNode : conditon_type is null", node);
		errors.push_back(error);
    return -1;
  }
  string s_condition_type = condition_type->getLiteral();

    // Check if the condition is of type bool
  if (s_condition_type != "error" && s_condition_type != "bool"){
    SemanticError error("Condition of if-expression must be bool in conditional : got '" + s_condition_type + "'", node);
		errors.push_back(error);
    node->setType(new TypeIdentifierNode("error"), true);
    return errors.size();
  }

  // Check the types of the two branches
  TypeIdentifierNode *then_type = node->getAction()->getType();
  TypeIdentifierNode *else_type;
  bool is_else_new_type = false;
  ExpressionNode* else_action = node->getElseAction();
  if(else_action)
    else_type = else_action->getType();
  else{
    // If there is no else branch, consider that its type is unit
    else_type = new TypeIdentifierNode("unit");
    is_else_new_type = true;
  }

  if(!then_type){
    SemanticError error("Error in the compiler in ConditionalNode : then_type is null", node);
		errors.push_back(error);
    return -1;
  }
  if(!else_type){
    SemanticError error("Error in the compiler in ConditionalNode : else_type is null", node);
		errors.push_back(error);
    return -1;
  }
  string s_then_type = then_type->getLiteral();
  string s_else_type = else_type->getLiteral();

  // Check if one of the branch is a unit
  if(s_then_type == "unit"){
    node->setType(then_type);
    if(is_else_new_type)
      delete else_type;
    return errors.size();
  }
  if(s_else_type == "unit"){
    node->setType(else_type, is_else_new_type);
    return errors.size();
  }
  // If one branch is in error, return the type of the other branch
  if(s_then_type == "error"){
    node->setType(else_type);
    return errors.size();
  }else if (s_else_type == "error"){
    node->setType(then_type);
    return errors.size();
  }

  // If one of the branch is a basic type, check if the other one is the same
  if (!then_type->getClassType() || !else_type->getClassType()){
    if(*then_type == *else_type){
      node->setType(then_type);
      return errors.size();
    }else{
      SemanticError error("If they are basic types, the types of then and else branch must be the same : got '" + then_type->getLiteral() + "' and '" + else_type->getLiteral() + "'", node);
  		errors.push_back(error);
      node->setType(new TypeIdentifierNode("error"), true);
      return errors.size();
    }
  }

  // If both types are clases, need to check the inheritance, at least Object in common
  node->setType(then_type->getClassType()->getCommonParent(else_type->getClassType()));

  return errors.size();
}

int CheckTypeVisitor::visitLetNode(LetNode *node){

  current_scope = (VSOPNode*) node;

  if(Visitor::visitLetNode(node) < 0)
     return -1;

  // Check the type of the initialization expression, if any
  ExpressionNode* init_exp = node->getInitExp();
  if (init_exp){
    TypeIdentifierNode *init_expr_type = init_exp->getType();
    if (!init_expr_type){
      SemanticError error("Error in the compiler in LetNode : init_expr_type is null", node);
      errors.push_back(error);
      return -1;
    }

    // Compare this type to the type of the let
    TypeIdentifierNode* object_type = node->getObjectType();
    if (init_expr_type->getLiteral() != "error" && *init_expr_type != *object_type
        && (!init_expr_type->getClassType() || !init_expr_type->getClassType()->hasParent(object_type->getClassType()))){
      if (!object_type->getClassType()){
        SemanticError error("The initialization expression of a let must have the same type as the object: got '" + init_expr_type->getLiteral() + "' and need '" + object_type->getLiteral() + "'", node);
        errors.push_back(error);
      }else{
        SemanticError error("The initialization expression of a let must have a type that inherits from the object type : got '" + init_expr_type->getLiteral() + "' and need a children of '" + object_type->getLiteral() + "'", node);
        errors.push_back(error);
      }
      node->setType(new TypeIdentifierNode("error"), true);
      return errors.size();
    }
  }

  // The return type of the let is the type of the scope
  TypeIdentifierNode *scope_expr_type = node->getScopeExp()->getType();
  if (!scope_expr_type){
    SemanticError error("Error in the compiler in LetNode : scope_expr_type is null", node);
    errors.push_back(error);
    return -1;
  }
  node->setType(scope_expr_type);
  return errors.size();
}

int CheckTypeVisitor::visitNewNode(NewNode *node){

  node->setType(node->getTypeId());
  return errors.size();
}

int CheckTypeVisitor::visitUnaryOperatorNode(UnaryOperatorNode *node){

  if(Visitor::visitUnaryOperatorNode(node) < 0)
     return -1;

  // Get the type of the operand
  ExpressionNode* operand = node->getOperand();
  TypeIdentifierNode* op_type = operand->getType();
  if(!op_type){
    SemanticError error("Error in the compiler in UnaryOperatorNode : op_type is null", node);
    errors.push_back(error);
    return -1;
  }
  string s_op_type = op_type->getLiteral();

  UnaryOperator op = node->getOperator();
  switch (op){
    case UnaryOperator::u_op_not :
      // Check if operand is bools and return operand type if ok
      if (s_op_type != "error" && s_op_type != "bool"){
        SemanticError error("not-expression must be followed by a bool : got '" + s_op_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return errors.size();
      }
      node->setType(op_type);
      break;
    case UnaryOperator::u_op_isnull :
      // Check if it not a basic type and return bool if ok
      // TODO : pourquoi il n'y a pas de comparaison à unit ?
      if (s_op_type == "bool" || s_op_type == "int32" || s_op_type == "string"){
        SemanticError error("isnull-expression must be followed by a class : got '" + s_op_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return errors.size();
      }
      node->setType(new TypeIdentifierNode("bool"), true);
      break;
    case UnaryOperator::u_op_minus :
      // Check if operand is int32 and return operand type if ok
      if (s_op_type != "error" && s_op_type != "int32"){
        SemanticError error("minus-expression must be followed by a int32 : got '" + s_op_type + "'", node);
        errors.push_back(error);
        node->setType(new TypeIdentifierNode("error"), true);
        return errors.size();
      }
      node->setType(op_type);
      break;
  }

  return errors.size();
}

int CheckTypeVisitor::visitWhileNode(WhileNode *node){

  if(Visitor::visitWhileNode(node) < 0)
     return -1;

   // Check if the condition is a bool
   TypeIdentifierNode *condition_type = node->getCondition()->getType();
   if (!condition_type){
     SemanticError error("Error in the compiler in WhileNode : condition_type is null", node);
     errors.push_back(error);
     return -1;
   }
   string s_condition_type = condition_type->getLiteral();

   if (s_condition_type != "error" && s_condition_type != "bool"){
     SemanticError error("Condition of while must be bool : got '" + s_condition_type + "'", node);
     errors.push_back(error);
     node->setType(new TypeIdentifierNode("error"), true);
     return errors.size();
   }
   node->setType(new TypeIdentifierNode("unit"), true);
   return errors.size();
}

int CheckTypeVisitor::visitArgsNode(ArgsNode *node){

  std::vector<ExpressionNode*> exprs = node->getExpressions();
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }

  return errors.size();
}

int CheckTypeVisitor::visitClassBodyNode(ClassBodyNode *node){

  std::vector<FieldNode*> fields = node->getFields();
  for(std::vector<FieldNode*>::iterator it = fields.begin(); it != fields.end(); ++it)
    if((*it)->accept(this) < 0)
      return -1;

  std::vector<MethodNode*> methods = node->getMethods();
  for(std::vector<MethodNode*>::iterator it = methods.begin(); it != methods.end(); ++it)
    if((*it)->accept(this) < 0)
      return -1;

  return errors.size();
}

int CheckTypeVisitor::visitFieldNode(FieldNode *node){

  if(Visitor::visitFieldNode(node) < 0)
     return -1;

  // Check if the type of the initialization expression if any
  ExpressionNode* init_expr = node->getInitExpr();
 	if (init_expr){
 		TypeIdentifierNode *init_expr_type = init_expr->getType();
 		if (!init_expr_type){
 			SemanticError error("Error in the compiler in ExpressionNode : init_expr_type is null", node);
 	    errors.push_back(error);
 			return -1;
 		}

    TypeIdentifierNode* type = node->getType();
 		if (init_expr_type->getLiteral() != "error" && init_expr_type->getLiteral() != type->getLiteral() &&
 		 (!init_expr_type->getClassType() || !init_expr_type->getClassType()->hasParent(type->getClassType()))){
 			 if (!type->getClassType()){
          SemanticError error("The initialization expression of a field must have the same type as the object: got '" + init_expr_type->getLiteral() + "' and need '" + type->getLiteral() + "'", node);
          errors.push_back(error);
        }else{
          SemanticError error("The initialization expression of a field must have a type that inherits from the object type : got '" + init_expr_type->getLiteral() + "' and need a children of '" + type->getLiteral() + "'", node);
          errors.push_back(error);
        }
 			return errors.size();
 		}
 	}

  return errors.size();
}

int CheckTypeVisitor::visitMethodNode(MethodNode *node){

  current_scope = (VSOPNode*) node;

  if(Visitor::visitMethodNode(node) < 0)
     return -1;

   // Get block type
 	TypeIdentifierNode *block_type = node->getBlock()->getType();
 	if (!block_type){
 		SemanticError error("Error in the compiler in MethodNode : block_type is null", node);
 		errors.push_back(error);
 		return -1;
 	}

 	// Check if the types are the same or the block type class inherits from the return type class.
  TypeIdentifierNode* ret_type = node->getRetType();
 	if (ret_type->getLiteral() != "error" && block_type->getLiteral() != "error" && *block_type != *ret_type &&
 			(!block_type->getClassType() || !block_type->getClassType()->hasParent(ret_type->getClassType()))){
 		if (!ret_type->getClassType()){
 			SemanticError error("The type of the block of a method must be the same as the return type of that method: got '" + block_type->getLiteral() + "' and need '" + ret_type->getLiteral() + "'", node);
 			errors.push_back(error);
 		}else{
 			SemanticError error("The type of the block of a method must have a type that inherits from the return type of that method : got '" + block_type->getLiteral() + "' and need a children of '" + ret_type->getLiteral() + "'", node);
 			errors.push_back(error);
 		}
 		return errors.size();
 	}

  return errors.size();
}

int CheckTypeVisitor::visitProgramNode(ProgramNode *node){

  std::vector<ClassNode*> classes = node->getClasses();
  for(std::vector<ClassNode*>::iterator it = classes.begin(); it != classes.end(); ++it)
    if((*it)->accept(this) < 0)
      return -1;

  return errors.size();
}
