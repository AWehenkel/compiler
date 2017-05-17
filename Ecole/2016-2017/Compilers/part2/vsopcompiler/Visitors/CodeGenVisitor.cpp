#include <vector>

#include "CodeGenVisitor.hpp"
#include "all_headers.hpp"

using namespace std;
//TODO Storer dans toutes les expressions leur valeur de retour

string CodeGenVisitor::getLLVMAllocationCode(string name, string type){
  return name + " = alloca " + type + "\n";
}

string CodeGenVisitor::getLLVMLoadCode(string load_in, string load_from, string type){
  return load_in + " = load " + type + "* " + load_from + "\n";
}

string CodeGenVisitor::getLLVMStoreCode(string name, string store_address, string type){
  return "store " + type + " " + name + ", " +  type + "* " + store_address + "\n";
}

string CodeGenVisitor::getLLVMBitCastCode(string store_address, string first_type, string init_address, string second_type){
  return store_address + " = bitcast " + first_type + " " + init_address + " to " + second_type + "\n";
}

string CodeGenVisitor::getLLVMCallCode(string function_name, string return_type, vector<string> args_value, vector<string> args_type){

  string to_ret = "call " + return_type + " @" + function_name + "(";
  // Adding all the arguments and their types
  if(args_value.size()){
    for(size_t i = 0; i < args_value.size(); i++)
      to_ret += args_type.at(i) + " " + args_value.at(i) + ", ";
    to_ret.replace(to_ret.size() - 2, 3, ")\n");
  }
  else
    to_ret += ")\n";

  return to_ret;
}

string CodeGenVisitor::getLLVMGetElementPtr(string load_in, string type_struct, string load_from, size_t offset1, size_t offset2){
  return load_in + " = getelementptr inbounds " + type_struct + "* " + load_from + ", i32 " + to_string(offset1) + ", i32 " + to_string(offset2) + "\n";
}

string CodeGenVisitor::getLLVMReturnCode(string to_ret, string type){
  return "ret " + type + " " + to_ret + "\n";
}

string CodeGenVisitor::getLLVMBinaryCode(BinaryOperatorNode* node, string op1, string op2){

  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string code, to_ret = "%" + to_string(counter++);

  switch (node->getOperator()) {
    case b_op_and :
      code = to_ret + " = and i1 " + op1 + ", "  + op2; // TODO : il faut convertir les false/true en 0/1
      break;
    case b_op_minus :
      code = to_ret + " = sub i32 " + op1 + ", "  + op2;
      break;
    case b_op_less :
      code = to_ret + " = slt i32 " + op1 + ", "  + op2;
      break;
    case b_op_leq :
      code = to_ret + " = sle i32 " + op1 + ", "  + op2;
      break;
    case BinaryOperator::b_op_plus :
      code = to_ret + " = add nuw i32 " + op1 + ", "  + op2;
      break;
    case b_op_equal :
      //TODO : Change to handle other type than int32.
      code = to_ret + " = eq i32 " + op1 + ", "  + op2;
      break;
    case b_op_times :
      code = to_ret + " = mul i32 " + op1 + ", "  + op2;
      break;
    case b_op_div :
      code = to_ret + " = sdiv i32 " + op1 + ", "  + op2;
      break;
    case b_op_pow :
      string tmp1 = "%" + to_string(counter++), tmp2 = "%" + to_string(counter++);

      code = tmp1 + " = sitofp i32 " + op1 + " to float\n";
      code += tmp2 + " = call float @llvm.powi.f32(float " + tmp1 + ", i32 " + op2 + ")\n";
      code += to_ret + " = fptosi float " + tmp2 + " to i32";
      break;
  }
  llvm_address_counters.push(counter);

  // Store the value if needed by the parent node
  if(node->getLLVMAddress().size())
    code += "\n" + tab + getLLVMStoreCode(to_ret, node->getLLVMAddress(), "i32"); // TODO : pourquoi est-ce qu'on store forcément un i32 ?

  return code;
}

string CodeGenVisitor::getLLVMUnaryCode(UnaryOperatorNode* node, string op){

  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string code, to_ret = "%" + to_string(counter++);
  string type;

  switch (node->getOperator()) {
    case u_op_not :
      code = to_ret + " = add i1 " + op + ", 1";
      type = "i1";
      break;
    case u_op_minus :
      code = to_ret + " = sub i32 0, "  + op;
      type = "i32";
      break;
    case u_op_isnull :
      // TODO : ! pour le isnull..., faut checker d'une manière ou d'une autre que de la mémoire a déjà été allouée à l'objet (qu'il a été instantié -> new)
      type = "i1";
      break;
  }
  llvm_address_counters.push(counter);

  code += "\n" + tab +  getLLVMStoreCode(to_ret, node->getLLVMAddress(), type);

  return code;
}

int CodeGenVisitor::visitAssignNode(AssignNode *node){

  ExpressionNode* expr = node->getExpression();
  ObjectIdentifierNode* name = node->getName();
  string expr_addr = node->getLLVMAddress();
  int counter;

  ir += tab + "; assignement\n";

  // Visit the expression at the right of the assignment
  /*if(!expr->alreadyInstanciated()){
    counter = llvm_address_counters.top();
    llvm_address_counters.pop();
    expr->setLLVMAddress(counter++);
    ir += tab + getLLVMAllocationCode(expr->getLLVMAddress(), expr->getLLVMType());
    llvm_address_counters.push(counter);

    // Visit the init expression
    if (expr->accept(this) < 0)
      return -1;

  }else{
    expr->setLLVMAddress(current_scope->getDeclarationLLVM(expr->getLiteral()));
  }*/

  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  expr->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(expr->getLLVMAddress(), expr->getLLVMType());
  llvm_address_counters.push(counter);
  // Visit the init expression
  if (expr->accept(this) < 0)
    return -1;

  // Store the value of the expression in the left term
  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string load = "%" + to_string(counter++);
  ir += tab + getLLVMLoadCode(load, expr->getLLVMAddress(), expr->getLLVMType());
  // Have to particularize if it is a field
  FieldNode* field = current_scope->getFieldFromId(name->getLiteral());
  if (field){
    MethodNode* cur_method = (MethodNode*) current_scope;
    ClassNode* cur_class = cur_method->getClassScope();
    ir += tab + getLLVMLoadCode("%" + to_string(counter++), "%1", "%struct." + cur_class->getName()->getLiteral() + "*"); // TODO : attention incohérence avec call
    ir += tab + getLLVMGetElementPtr("%" + to_string(counter++), "%struct." + cur_class->getName()->getLiteral(), "%" + to_string(counter-1), 0, field->getPosition());
    ir += tab + getLLVMStoreCode(load, "%" + to_string(counter-1), name->getLLVMType());
  }else
    ir += tab + getLLVMStoreCode(load, current_scope->getDeclarationLLVM(name->getLiteral()), name->getLLVMType());

  if(expr_addr != "")
    ir += tab + getLLVMStoreCode(load, expr_addr, expr->getLLVMType());

    llvm_address_counters.push(counter);

  return 0;
}

int CodeGenVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node){

  ExpressionNode* left = node->getLeft();
  ExpressionNode* right = node->getRight();

  ir += tab + "; binary operation\n";

  // Visit the children nodes
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  left->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(left->getLLVMAddress(), left->getLLVMType());
  llvm_address_counters.push(counter);
  if (left->accept(this) < 0)
    return -1;

  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  right->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(right->getLLVMAddress(), right->getLLVMType());
  llvm_address_counters.push(counter);
  if (right->accept(this) < 0)
    return -1;

  // Load the two operands
  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string left_op_address = "%" + to_string(counter++);
  string right_op_address = "%" + to_string(counter++);
  llvm_address_counters.push(counter);
  // Load the values of the two child
  ir += tab + getLLVMLoadCode(left_op_address, left->getLLVMAddress(), left->getLLVMType());
  ir += tab + getLLVMLoadCode(right_op_address, right->getLLVMAddress(), right->getLLVMType());
  // Make the operation and store the result
  ir += tab + getLLVMBinaryCode(node, left_op_address, right_op_address);

  return 0;
}

int CodeGenVisitor::visitBlockNode(BlockNode* node){

  std::vector<ExpressionNode*> exprs = node->getExpressions();
  int counter;

  // Visit all the expresssions contained in the block
  for(std::vector<ExpressionNode*>::iterator it = exprs.begin(); it != exprs.end(); ++it){
    ExpressionNode* expr = *it;
    counter = llvm_address_counters.top();
    llvm_address_counters.pop();
    expr->setLLVMAddress(counter++);
    llvm_address_counters.push(counter);
    ir += tab + getLLVMAllocationCode(expr->getLLVMAddress(), expr->getLLVMType());
    if(expr->accept(this) < 0)
      return -1;
  }

  // Get the address where we stored the last expression and store it as return value
  if (node->getLLVMAddress().size()){
    ExpressionNode* last = *(exprs.end()-1);
    counter = llvm_address_counters.top();
    llvm_address_counters.pop();
    string load = "%" + to_string(counter++);
    llvm_address_counters.push(counter);
    ir += tab + getLLVMLoadCode(load, last->getLLVMAddress(), last->getLLVMType());
    ir += tab + getLLVMStoreCode(load, node->getLLVMAddress(), node->getLLVMType());
  }

  return 0;
}



int CodeGenVisitor::visitConditionalNode(ConditionalNode *node){

  ExpressionNode* condition = node->getCondition();
  ExpressionNode* action = node->getAction();
  ExpressionNode* else_action = node->getElseAction();
  string expr_addr = node->getLLVMAddress();

  ir += tab + "; condition\n";

  // Generate code for the condition
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  condition->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(condition->getLLVMAddress(), condition->getLLVMType());
  llvm_address_counters.push(counter);
  if (condition->accept(this) < 0)
    return -1;

  // Branch on the result
  string br_id = condition->getLLVMAddress().substr(1, 1);
  if (else_action)
    ir += tab + "br i1 " + condition->getLLVMAddress() + "*, label %then_" + br_id + ", label %else_" + br_id + "\n";
  else
    ir += tab + "br i1 " + condition->getLLVMAddress() + "*, label %then_" + br_id + ", label %end_" + br_id + "\n";

  // First branch
  ir += tab + "\nthen_" + br_id + ":\n";
  tab += "\t";
  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  action->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(action->getLLVMAddress(), action->getLLVMType());
  llvm_address_counters.push(counter);
  if(action->accept(this) < 0)
    return -1;
  // Store the value if needed by the parent node
  if(expr_addr != "")
      ir += tab + getLLVMStoreCode(action->getLLVMAddress(), expr_addr, action->getLLVMType());
  tab.pop_back();

  // Branch 2
  if(else_action){
    ir += tab + "\tbr label %end_" + br_id + "\n";
    ir += tab + "\nelse_" + br_id + ":\n";
    tab += "\t";
    counter = llvm_address_counters.top();
    llvm_address_counters.pop();
    else_action->setLLVMAddress(counter++);
    ir += tab + getLLVMAllocationCode(else_action->getLLVMAddress(), else_action->getLLVMType());
    llvm_address_counters.push(counter);
    if(else_action->accept(this) < 0)
      return -1;
    // Store the value if needed by the parent node
    if(expr_addr != "")
      ir += tab + getLLVMStoreCode(else_action->getLLVMAddress(), expr_addr, else_action->getLLVMType());
    tab.pop_back();
  }
  ir += tab + "\nend_" + node->getLLVMAddress().substr(1,1) + ":\n";

  return 0;
}

int CodeGenVisitor::visitLetNode(LetNode *node){

  VSOPNode* prev_scope = current_scope;
  current_scope = node;

  ir += tab + "; let\n";

  ObjectIdentifierNode* object_id = node->getObjectId();
	TypeIdentifierNode* object_type = node->getObjectType();
	ExpressionNode* init_expr = node->getInitExp();
	ExpressionNode* scope_exp = node->getScopeExp();
  string expr_addr = node->getLLVMAddress();

  // Allocate space for the let
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  object_id->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(object_id->getLLVMAddress(), object_type->getLLVMType());
  llvm_address_counters.push(counter);

  // If there is an init expression, store its value in the let
  if (init_expr != NULL){
    // Allocate memory for the init expression
    counter = llvm_address_counters.top();
    llvm_address_counters.pop();
    init_expr->setLLVMAddress(counter++);
    ir += tab + getLLVMAllocationCode(init_expr->getLLVMAddress(), init_expr->getLLVMType());
    llvm_address_counters.push(counter);
    // Visit the init expression
    if (init_expr->accept(this) < 0)
      return -1;
    // Store the value of the init expression in the field
    ir += tab + getLLVMStoreCode(init_expr->getLLVMAddress(), object_id->getLLVMAddress(), object_type->getLLVMType());
  }

  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  scope_exp->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(scope_exp->getLLVMAddress(), scope_exp->getLLVMType());
  llvm_address_counters.push(counter);
  if(scope_exp->accept(this))
    return 1;

  // Store the value if needed by the parent node
  if (expr_addr != "")
    ir += tab + getLLVMStoreCode(scope_exp->getLLVMAddress(), scope_exp->getLLVMType(), expr_addr);

  current_scope = prev_scope;

  return 0;
}

//TODO : Changer les constructeur de LiteralNode et faire en sorte de prendre en charge correctement les literaux.
int CodeGenVisitor::visitLiteralNode(LiteralNode *node){
  string value = node->getLiteral();
  cout << node->getLLVMType() << endl;
  if(node->getLLVMType() == "i8*"){
    value = "getelementptr inbounds ([" + to_string(node->getLength()) + " x i8], [" + to_string(node->getLength()) + " x i8]* " + node->getConstantAdd() + ", i32 0, i32 0)";
  }
  ir += tab + getLLVMStoreCode(value, node->getLLVMAddress(), node->getLLVMType());
  return 0;
}

int CodeGenVisitor::visitNewNode(NewNode *node){

  string expr_addr = node->getLLVMAddress();

  ir += tab + "; new\n";

  string new_function = "@"+ node->getTypeId()->getLiteral() + "_new";
  if (expr_addr != "")
    ir += tab + expr_addr + " = " + getLLVMCallCode(new_function, node->getTypeId()->getLLVMType(), vector<string>(), vector<string>());
  else
    ir += tab + getLLVMCallCode(new_function, node->getTypeId()->getLLVMType(), vector<string>(), vector<string>());

  return 0;
}

int CodeGenVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){
  // TODO : il faut particulariser le truc au différents cas , genre pour un field il faut faire un getelementptr sur la structure
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();

  if(current_scope && node->getLLVMAddress().size()){
    FieldNode* field = current_scope->getFieldFromId(node->getLiteral());

    if (field){
      MethodNode* cur_method = (MethodNode*) current_scope;
      ClassNode* cur_class = cur_method->getClassScope();
      ir += tab + getLLVMLoadCode("%" + to_string(counter++), "%1", "%struct." + cur_class->getName()->getLiteral() + "*");
      ir += tab + getLLVMGetElementPtr("%" + to_string(counter++), "%struct." + cur_class->getName()->getLiteral(), "%" + to_string(counter-1), 0, field->getPosition());
    }else
      ir += tab + getLLVMLoadCode("%" + to_string(counter++), current_scope->getDeclarationLLVM(node->getLiteral()), node->getLLVMType());

    ir += tab + getLLVMStoreCode("%" + to_string(counter), node->getLLVMAddress(), node->getLLVMType());
  }
  llvm_address_counters.push(counter);
  return 0;
}

int CodeGenVisitor::visitUnaryOperatorNode(UnaryOperatorNode* node){

  ExpressionNode* operand = node->getOperand();

  ir += tab + "; unary\n";

  // Visit the child
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  operand->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(operand->getLLVMAddress(), operand->getLLVMType());
  llvm_address_counters.push(counter);
  if (operand->accept(this) < 0)
    return -1;

  // Load the value of the operand
  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string llvm_address = "%" + to_string(counter++);
  llvm_address_counters.push(counter);
  ir += tab + getLLVMLoadCode(llvm_address, operand->getLLVMAddress(), operand->getLLVMType());
  // Make the operation and store it
  ir += tab + getLLVMUnaryCode(node, llvm_address);

  return 0;
}

int CodeGenVisitor::visitWhileNode(WhileNode *node){

  ExpressionNode* condition = node->getCondition();
  ExpressionNode* action = node->getAction();

  ir += tab + "; while\n";

  // Branch to the condition
  string br_id = node->getLLVMAddress().substr(1, 1);
  ir += tab + "br label %loop_" + br_id + "\n";
  ir += "\nloop_" + br_id + ":\n";

  // Visit the condition
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  condition->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(condition->getLLVMAddress(), condition->getLLVMType());
  llvm_address_counters.push(counter);
  if (condition->accept(this) < 0)
    return -1;

  // Load the value of the condition
  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string conditon_value = "%" + to_string(counter++);
  ir += tab + getLLVMLoadCode(conditon_value, condition->getLLVMAddress(), condition->getLLVMType());
  llvm_address_counters.push(counter);

  // Branch according to the condition
  ir += tab + "br i1 " + conditon_value + ", label %do_" + br_id + ", label %end_" + br_id + "\n";
  ir += "\ndo_" + br_id + ":\n";
  if (action->accept(this) < 0)
    return -1;
  ir += tab + "br label %loop_" + br_id + "\n";

  ir += "\nend_" + br_id + ":\n";

  return 0;
}

int CodeGenVisitor::visitClassBodyNode(ClassBodyNode *node){

  // Visit only the methods because the fields have already been treated in visitClassNode
  std::vector<MethodNode*> methods = node->getMethods();
  for(std::vector<MethodNode*>::iterator it = methods.begin(); it != methods.end(); ++it){
    if((*it)->accept(this) < 0)
      return -1;
  }
  return 0;
}

int CodeGenVisitor::visitClassNode(ClassNode *node){

  // TODO : nettoyer le code

  if(node->getName()->getLiteral() == "IO")
    external_call = true;
  else
    external_call = false;
  current_scope = (VSOPNode *) node;

  // Reinitialize the stack
  llvm_address_counters.push(0);

  string struct_name = "%struct." + node->getName()->getLiteral();
  string struct_vtable = "%struct." + node->getName()->getLiteral() + "VTable";
  string struct_instance = "@" + node->getName()->getLiteral() + "VTable_inst";
  string struct_init = "@" + node->getName()->getLiteral() + "Init";
  string struct_new = "@" + node->getName()->getLiteral() + "New";

  //Class structure
  vector<FieldNode*> inherited_fields = node->getInheritedFields();
  ir += tab + struct_name + " = type {\n\t" + struct_vtable + "*,";
  tab += "\t";
  for(auto field : inherited_fields)
    ir += "\n" + tab + field->getType()->getLLVMType() + ",";

  vector<FieldNode*> new_fields = node->getNewFields();
  for(auto field : new_fields)
    ir += "\n" + tab + field->getType()->getLLVMType() + ",";

  ir.pop_back();
  tab.pop_back();
  ir += "\n" + tab + "}\n\n";

  //Class structure VTable
  ir += tab + struct_vtable + " = type {";
  tab += "\t";
  vector<MethodNode*> inherited_methods = node->getInheritedMethods();
  for(auto method : inherited_methods)
    ir += "\n" + tab + method->getLLVMStructure(struct_name) + ",";

  vector<MethodNode*> overriden_methods = node->getOverridendMethods();
  for(auto method : overriden_methods)
    ir += "\n" + tab + method->getLLVMStructure(struct_name) + ",";

  vector<MethodNode*> new_methods = node->getNewMethods();
  for(auto method : new_methods)
    ir += "\n" + tab + method->getLLVMStructure(struct_name) + ",";

  ir.pop_back();
  tab.pop_back();
  ir += "\n" + tab + "}\n\n";

  //Class structure instanciation
  //TODO peut être que le struct_vtable devrait être le code de la vtable explicitement.
  ir += tab + struct_instance + " = global " + struct_vtable + "{";
  tab += "\t";
  for(auto method : inherited_methods)
    ir += "\n" + tab + method->getLLVMInstance(node->getName()->getLiteral(), node->getParent()->getName()->getLiteral())+ ",";
  for(auto method : overriden_methods)
    ir += "\n" + tab + method->getLLVMInstance(node->getName()->getLiteral()) + ",";
  for(auto method : new_methods)
    ir += "\n" + tab + method->getLLVMInstance(node->getName()->getLiteral()) + ",";

  ir.pop_back();
  tab.pop_back();
  ir += "\n" + tab + "}\n\n";

  //Init function
  int var_counter = 1;
  ir += tab + "define void " + struct_init + "(" + struct_name + "* %self){\n";
  tab += "\t";
  if(node->getParent()){
    ir += tab + getLLVMBitCastCode("%" + to_string(var_counter), struct_name + "*", "%self", "%struct." + node->getParent()->getName()->getLiteral() + "*");
    vector<string> args_value;
    args_value.push_back("%" + to_string(var_counter));
    vector<string> args_type;
    args_type.push_back("%struct." + node->getParent()->getName()->getLiteral() + "*");
    ir += tab + getLLVMCallCode(node->getParent()->getName()->getLiteral() + "Init", "void", args_value, args_type);
  }

  int i = 0;
  for(auto field : new_fields){
    i++;//TODO pas très claire si le field->getType()->getLLVMType() en dessous doit toujours être i32 ou bien dépend du type.
    field->setLLVMAddressAsString(field->getName()->getLiteral());
    ir += tab + getLLVMGetElementPtr(field->getLLVMAddress(), struct_name, "%self", 0, i);
    field->setPosition(i);
    string init_value; //TODO Peut être changer le zero par une valeur qui dépend du type.
    ExpressionNode *init_expr = field->getInitExpr();
    if (init_expr){
        // Visit the init expression
        init_expr->setLLVMAddress(++var_counter);
        ir += tab + getLLVMAllocationCode(init_expr->getLLVMAddress(), init_expr->getLLVMType());
        if (init_expr->accept(this) < 0)
          return -1;
        // Load the value
        ir += tab + getLLVMLoadCode("%" + to_string(++var_counter), init_expr->getLLVMAddress(), init_expr->getLLVMType());
        init_value = "%" + to_string(var_counter);
    }
    else
      init_value = field->getType()->getInitLLVMValue();
    ir += tab + getLLVMStoreCode(init_value, field->getLLVMAddress(), field->getType()->getLLVMType());
  }
  ir += tab + getLLVMGetElementPtr("%" + to_string(++var_counter), struct_name, "%self", 0, 0);
  //ir += tab + "%" + to_string(++var_counter) + " = getelementptr inbounds " + struct_name + "* %self, i32 0, i32 0\n";
  ir += tab + getLLVMStoreCode(struct_instance, "%" + to_string(var_counter), struct_vtable + "*");//TODO j'ai pas cast comme dans le code car je comprends pas à quoi aç sert.
  ir += tab + "ret void\n";
  tab.pop_back();
  ir += tab + "}\n\n";

  // New function
  var_counter = 1;
  ir += tab + "define " + struct_name + "* " + struct_new + "(){\n";
  ir += tab + "\t%self = alloca " + struct_name + "*\n";

  // Code to compute the code of a structure and store it in memory, case a bit special so stay like that without call to getLLVMGetElementPtr
  ir += tab + "\t%" + to_string(var_counter) + " = getelementptr " + struct_name + "* null, i32 1\n";
  ir += tab + "\t%size = ptrtoint " + struct_name + "* %" + to_string(var_counter) + " to i32\n";

  // Malloc
  ir += tab + "\t%" + to_string(++var_counter) + " = call noalias i8* @malloc(i32 %size)\n";
  ir += tab + "\t%" + to_string(++var_counter) + " = bitcast i8* %" + to_string(var_counter) + " to " + struct_name + "*\n";
  ir += tab + "\tstore " + struct_name + "* %" + to_string(var_counter) + ", " + struct_name + "** %self\n";

  // Assert
  string llvm_load = "%" + to_string(++var_counter);
  ir += tab + "\t" + getLLVMLoadCode(llvm_load, "%self", struct_name + "*");
  string llvm_assert = to_string(++var_counter);
  ir += tab + "\t%" + llvm_assert + " = icmp ne " + struct_name + "* %" + to_string(var_counter - 1) + ", null\n";
  ir += tab + "\tbr i1 %" + llvm_assert + ", label %notnull, label %null\n";
  ir += tab + "\nnotnull:\t\t\t; preds = %" + llvm_assert + "\n";
  ir += tab + "\tcall void " + struct_init + "(" + struct_name + "* " + llvm_load + ")\n";
  ir += tab + "\tbr label %null\n";

  ir += tab + "\nnull:   \t\t\t; preds = %" + llvm_assert + "\n";
  ir += tab + "\tret " + struct_name + "* " + llvm_load + "\n}\n\n";

  // Visit the methods and classes
  ClassBodyNode* body = node->getBody();
  if(body->accept(this) < 0)
    return -1;

  llvm_address_counters.pop();
  return 0;
}


int CodeGenVisitor::visitMethodNode(MethodNode *node){

  VSOPNode* prev_scope = current_scope;
  ClassNode* current_class = (ClassNode*) prev_scope;
  current_scope = node;

  TypeIdentifierNode* ret_type = node->getRetType();
  FormalsNode* formals = node->getFormals();

  // TODO : gros doute sur la manière dont on doit gérer les fields..., ça n'a pas vraiment de sens de leur donner une address
  // comme on le fait pour le moment non? --> il faut appeler sur le self pour obtenir le bon élément
  int counter = 1;

  ClassNode* cur_class = (ClassNode*) prev_scope;
  ir += tab + "define " + ret_type->getLLVMType() + " @" + current_class->getName()->getLiteral() + "_" + node->getName()->getLiteral();
  ir += "(%struct." + cur_class->getName()->getLiteral() + "* %self, ";
	for(auto formal : formals->getFormals()){
    formal->setLLVMAddressAsString(formal->getName()->getLiteral());
		ir += formal->getType()->getLLVMType() + " " + formal->getLLVMAddress() + ", ";
  }
	ir.replace(ir.size() - 2, 2, ")");
  ir += " #0 {\n";

  // Allocate space for the arguments
  tab += "\t";
  string address = "%" + to_string(counter++);
  ir += tab + getLLVMAllocationCode(address, "%struct." + cur_class->getName()->getLiteral() + "*");
  ir += tab + getLLVMStoreCode("%self", address, "%struct." + cur_class->getName()->getLiteral() + "*");
  for(auto formal : formals->getFormals()){
    address = "%" + to_string(counter++);
    ir += tab + getLLVMAllocationCode(address, formal->getType()->getLLVMType());
    ir += tab + getLLVMStoreCode(formal->getLLVMAddress(), address, formal->getType()->getLLVMType());
    // Change the address of the formal to the local address
    formal->setLLVMAddress(address);
  }

  // Visit the block of instructions
  BlockNode* block = node->getBlock();
  block->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(block->getLLVMAddress(), block->getLLVMType());
  llvm_address_counters.push(counter);
  if (block->accept(this) < 0)
    return -1;

  // Make a return statement by returning the value of the block
  counter = llvm_address_counters.top();
  string to_ret = "%" + to_string(counter++);
  ir += tab + getLLVMLoadCode(to_ret, block->getLLVMAddress(), node->getRetType()->getLLVMType());
  ir += tab + getLLVMReturnCode(to_ret, node->getRetType()->getLLVMType());

  tab.pop_back();
  ir += tab + "}\n\n";

  // Save back the scope so that the following methods know to which class they belong
  current_scope = prev_scope;

  return 0;
}

int CodeGenVisitor::visitCallNode(CallNode* node){
  //Visitor::visitCallNode(node);//TODO Je sais pas pourquoi ça y était pas mais j'ai rajouté...
  int counter;
  string var_name;

  //Allocating space for the arguments and setting their value.
  for(auto arg : node->getArgs()->getExpressions()){
    counter = llvm_address_counters.top();
    var_name = "%" + to_string(counter);
    ir += tab + getLLVMAllocationCode(var_name, arg->getLLVMType());
    arg->setLLVMAddress(counter++);
    llvm_address_counters.pop();
    llvm_address_counters.push(counter);
    arg->accept(this);
  }

  //Allocating space for the object of the call.
  ExpressionNode* object = node->getObject();
  string obj_addr = "%self";
  if(object && object->getLiteral() != "self"){
    counter = llvm_address_counters.top();
    var_name = "%" + to_string(counter);
    ir += tab + getLLVMAllocationCode(var_name, object->getLLVMType());
    obj_addr = var_name;
    object->setLLVMAddress(counter++);
    llvm_address_counters.pop();
    llvm_address_counters.push(counter);
    object->accept(this);
  }

  if(external_call)
    return genExternalCallCode(node);//A changer ici on devra juste faire que ça call directement la fonction sans se poser la question

  string method_name = node->getMethodName()->getLiteral();
  ClassNode* obj_class = object->getType()->getClassType();
  MethodNode* method = obj_class->getMethod(method_name);
  obj_class->assignPositionToMethod();
  size_t position_method = method->getPosition();

  //Load of the vtable
  counter = llvm_address_counters.top();
  string ll_object = "%" + to_string(counter++), ll_vtable_pointer = "%" + to_string(counter++),
  ll_vtable = "%" + to_string(counter++),ll_method_pointer = "%" + to_string(counter++), obj_struct = object->getType()->getLLVMType(), ll_method = "%" + to_string(counter++),
  struct_vtable = "%struct." + obj_class->getName()->getLiteral() + "VTable*";

  ir += "; call\n";

  string llvm_obj_type = object->getType()->getLLVMType();
  llvm_obj_type.pop_back();

  ir += getLLVMLoadCode(ll_object, obj_addr, llvm_obj_type + "*");
  ir += tab + getLLVMGetElementPtr(ll_vtable_pointer, llvm_obj_type, ll_object, 0, 0);
  ir += tab + getLLVMLoadCode(ll_vtable, ll_vtable_pointer, struct_vtable);
  ir += tab + getLLVMGetElementPtr(ll_method_pointer, struct_vtable, ll_vtable, 0, position_method);
  ir += tab + getLLVMLoadCode(ll_method, ll_method_pointer, method->getLLVMStructure(object->getType()->getLiteral()));

  vector<string> args_value, args_type;
  args_type.push_back(llvm_obj_type + "*");
  args_value.push_back(obj_addr);

  for(auto arg : method->getFormals()->getFormals())//TODO faire plus propre(implementer dans une class methode ou call et utiliser .reserve)
    args_type.push_back(arg->getType()->getLLVMType());
  for(auto arg : node->getArgs()->getExpressions())//TODO la copie des arg doit etre faite ici ou dans l'implementation de la méthode.
    args_value.push_back(arg->getLLVMAddress());

  ir += tab + getLLVMCallCode(ll_method, method->getRetType()->getLLVMType(), args_value, args_type);

  llvm_address_counters.pop();
  llvm_address_counters.push(counter);

  return 0;
}

int CodeGenVisitor::genExternalCallCode(CallNode* node){
  string method_name = node->getMethodName()->getLiteral();
  ExpressionNode* object = node->getObject();
  string obj_addr = object->getLLVMAddress();
  ClassNode* obj_class = object->getType()->getClassType();
  MethodNode* method = obj_class->getMethod(method_name);
  obj_class->assignPositionToMethod();
  size_t position_method = method->getPosition();
  //Load of the vtable
  int counter = llvm_address_counters.top();
  string ll_vtable_pointer = "%" + to_string(counter++),
  ll_vtable = "%" + to_string(counter++), obj_struct = object->getType()->getLLVMType(), ll_method = method_name,
  struct_vtable = "%struct." + obj_class->getName()->getLiteral() + "VTable*";
  ir += "call\n";
  string llvm_obj_type = object->getType()->getLLVMType();
  llvm_obj_type.pop_back();
  //ir += getLLVMLoadCode(ll_object, obj_addr, llvm_obj_type);
  vector<string> args_value, args_type;
  for(auto arg : method->getFormals()->getFormals())//TODO faire plus propre(implementer dans une class methode ou call et utiliser .reserve)
    args_type.push_back(arg->getType()->getLLVMType());
  for(auto arg : node->getArgs()->getExpressions())//TODO la copie des arg doit etre faite ici ou dans l'implementation de la méthode.
    args_value.push_back(arg->getLLVMAddress());
  ir += tab + getLLVMCallCode(ll_method, method->getRetType()->getLLVMType(), args_value, args_type);
  llvm_address_counters.pop();
  llvm_address_counters.push(counter);
  return 0;
}
//int CodeGenVisitor::visitBraceNode()
int CodeGenVisitor::visitProgramNode(ProgramNode* node){

  // Add the malloc function
  ir += tab + "declare noalias i8* @malloc(i32)\n\n";
  Visitor::visitProgramNode(node);
  ir += "attributes #0 = { nounwind \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"pentium4\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }";
  return 0;
}

//int CodeGenVisitor::visitBraceNode() : TODO return result
