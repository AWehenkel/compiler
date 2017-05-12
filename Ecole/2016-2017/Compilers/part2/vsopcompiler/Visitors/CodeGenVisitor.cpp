#include <vector>

#include "CodeGenVisitor.hpp"
#include "all_headers.hpp"

using namespace std;
//TODO Storer dans toutes les expressions leur valeur de retour

// TODO : attention ça peut changer
string CodeGenVisitor::getLLVMAllocationCode(string name, string type){
  return name + " = alloca " + type + "\n";
}

// TODO : attention au types
string CodeGenVisitor::getLLVMLoadCode(string load_in, string load_from, string type){
  return load_in + " = load " + type + ", " + type + "* " + load_from + "\n";
}

string CodeGenVisitor::getLLVMStoreCode(string name, string store_address, string type){
  return "store " + type + " " + name + ", " +  type + "* " + store_address + "\n";
}

string CodeGenVisitor::getLLVMBitCastCode(string store_address, string first_type, string init_address, string second_type){
  return store_address + " = bitcast " + first_type + " " + init_address + " to " + second_type + "\n";
}

string CodeGenVisitor::getLLVMCallCode(string function_name, string return_type, vector<string> args_value, vector<string> args_type){
  string to_ret = "call " + return_type + " " + function_name + "(";
  if(args_value.size()){
    for(size_t i = 0; i < args_value.size(); i++)
      to_ret += args_type.at(i) + " " + args_value.at(i) + ", ";
    to_ret.replace(to_ret.size() - 2, 3, ")\n");
  }
  else
    to_ret += ")\n";
  return to_ret;
}

int CodeGenVisitor::visitAssignNode(AssignNode *node){

  ExpressionNode* expr = node->getExpression();
  ObjectIdentifierNode* name = node->getName();
  string expr_addr = node->getLLVMAddress();

  // Visit the expression at the right of the assignment TODO pour les literal il faudrait ne pas stocker dans une nouvelle addresse mais utiliser le literal en lui meme.
  if(!expr->alreadyInstanciated()){
    int counter = llvm_address_counters.top();
    llvm_address_counters.pop();
    expr->setLLVMAddress(counter++);
    ir += tab + getLLVMAllocationCode(expr->getLLVMAddress(), expr->getLLVMType());
    llvm_address_counters.push(counter);

    // Visit the init expression
    if (expr->accept(this) < 0)
      return -1;
  }
  else
    expr->setLLVMAddress(current_scope->getDeclarationLLVM(expr->getLiteral()));
  // Store the value of the expression in the left term
  ir += tab + getLLVMStoreCode(expr->getLLVMAddress(), current_scope->getDeclarationLLVM(name->getLiteral()), name->getLLVMType()); // TODO : problème avec name, pas de llvm address

  // Store the value if needed by the parent node
  if(expr_addr != "")
    ir += tab + getLLVMStoreCode(expr->getLLVMAddress(), expr->getLLVMType(), expr_addr);

  return 0;

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
      //TODO Change to handle other type than int32.
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
  code += "\n" + tab + getLLVMStoreCode(to_ret, node->getLLVMAddress(), "i32"); // TODO : pourquoi est-ce qu'on store forcément un i32 ?
  return code;
}

string CodeGenVisitor::getLLVMUnaryCode(UnaryOperatorNode* node, string op){
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string code, to_ret = "%" + to_string(counter++);

  switch (node->getOperator()) {
    case u_op_not :
    // ! pour le not, il y a le intrisics bitreverse ou on peut faire un xor avec un 1
      code = to_ret + " = xor i1 " + op + ", 1";
      break;
    case u_op_minus :
    // ! pour le -, <result> = sub i32 0, %val          ; yields i32:result = -%var
      code = to_ret + " = sub i32 0, "  + op;
      break;
    case u_op_isnull :
    // ! pour le isnull..., faut checker d'une manière ou d'une autre que de la mémoire a déjà été allouée à l'objet (qu'il a été instantié -> new)
      break;
  }
  llvm_address_counters.push(counter);
  code += "\n" + tab +  getLLVMStoreCode(to_ret, node->getLLVMAddress(), "i32"); // TODO : pourquoi est-ce qu'on store forcément un i32 ?
  return code;
}

int CodeGenVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node){

  ExpressionNode* left = node->getLeft();
  ExpressionNode* right = node->getRight();

  // Visit the children nodes
  // TODO : est-ce qu'il faut pas d'abord checker, s'il n'y a pas déjà une address dans les fils ? genre si c'est un objet, la mếmoire est
  // sensé être déjà allouée non ?
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

  // Make the operation
  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string llvm_address_3 = "%" + to_string(counter++);
  string llvm_address_4 = "%" + to_string(counter++);
  llvm_address_counters.push(counter);
  // Load the values of the two child
  ir += tab + getLLVMLoadCode(llvm_address_3, left->getLLVMAddress(), left->getLLVMType());
  ir += tab + getLLVMLoadCode(llvm_address_4, right->getLLVMAddress(), right->getLLVMType());
  // Store the result
  ir += tab + getLLVMBinaryCode(node, llvm_address_3, llvm_address_4);

  return 0;
}

int CodeGenVisitor::visitBlockNode(BlockNode* node){

  vector<ExpressionNode*> expresions = node->getExpressions();
  ExpressionNode* first = *(expresions.begin());
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  //first->setLLVMAddress(counter++);
  //ir += tab + getLLVMAllocationCode(first->getLLVMAddress(), first->getLLVMType()); //TODO Probleme il faut stocker quelque chose dedans pour que ça ait du sens d'allouer
  llvm_address_counters.push(counter);
  Visitor::visitBlockNode(node);
  return 0;
}

int CodeGenVisitor::visitUnaryOperatorNode(UnaryOperatorNode* node){

  ExpressionNode* operand = node->getOperand();

  // Visit the child
  // TODO : est-ce qu'il faut pas d'abord checker, s'il n'y a pas déjà une address dans les fils ? genre si c'est un objet, la mếmoire est
  // sensé être déjà allouée non ?
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  operand->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(operand->getLLVMAddress(), operand->getLLVMType());
  llvm_address_counters.push(counter);
  if (operand->accept(this) < 0)
    return -1;

  // Make the operation
  counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  string llvm_address = "%" + to_string(counter++);
  llvm_address_counters.push(counter);
  ir += tab + getLLVMLoadCode(llvm_address, operand->getLLVMAddress(), operand->getLLVMType());
  ir += tab + getLLVMUnaryCode(node, llvm_address);

  return 0;
}

// TODO : Checker si ça a vraiment un interet
/*int CodeGenVisitor::visitFieldNode(FieldNode *node){

  ObjectIdentifierNode* name = node->getName();
  ExpressionNode* init_expr = node->getInitExpr();
  TypeIdentifierNode* type = node->getType();

  // Allocate space for the field // TODO : je suis pas sur que c'est le mieux de le faire là ou dans le classbody (différence entre le name et le filednode en lui-même)
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  name->setLLVMAddress(counter++);
  // TODO : comment se fait-il que le nom du field n'aie pas de type ?
  ir += tab + getLLVMAllocationCode(name->getLLVMAddress(), type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
  llvm_address_counters.push(counter);
  // If there is an init expression, store its value in the field
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
    ir += tab + getLLVMStoreCode(init_expr->getLLVMAddress(), name->getLLVMAddress(), type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
  }
  return 0;
}*/

//TODO Changer les constructeur de LiteralNode et faire en sorte de prendre en charge correctement les literaux.
int CodeGenVisitor::visitLiteralNode(LiteralNode *node){
  //ir += tab +  "caca" + getLLVMStoreCode(node->getLiteral(), node->getLLVMAddress(), node->getLLVMType());
  return 0;
}

int CodeGenVisitor::visitProgramNode(ProgramNode* node){

  // Add the malloc function
  ir += tab + "declare noalias i8* @malloc(i32)\n\n";
  Visitor::visitProgramNode(node);
  cout << "IR: \n" << ir << endl;
  return 0;
}


//TODO
int CodeGenVisitor::visitMethodNode(MethodNode *node){

  VSOPNode* prev_scope = current_scope;
  current_scope = node;

  TypeIdentifierNode* ret_type = node->getRetType();
  FormalsNode* formals = node->getFormals();

  // Start a new count from the number of fields
  llvm_address_counters.push(llvm_address_counters.top());
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();

  ClassNode* cur_class = (ClassNode*) prev_scope;
  ir += tab + "define " + ret_type->getLLVMType() + " @" + node->getName()->getLiteral();
  ir += " (%struct." + cur_class->getName()->getLiteral() + "* %self, ";
	for(auto formal : formals->getFormals()){
    formal->setLLVMAddress(counter++);
		ir += formal->getType()->getLLVMType() + " " + formal->getLLVMAddress() + ", ";
  }
	ir.replace(ir.size() - 2, 2, ")");
  ir += "{\n";

  tab += "\t";
  // Allocate space for the arguments
  string address = "%" + to_string(counter++);
  ir += tab + address + " alloca " + "%struct." + cur_class->getName()->getLiteral() + "*\n";
  ir += tab + "store %struct." + cur_class->getName()->getLiteral() + "* %self, %struct." + cur_class->getName()->getLiteral() + "* " + address + "\n";
  for(auto formal : formals->getFormals()){
    address = "%" + to_string(counter++);
    ir += tab + address + " alloca " + formal->getType()->getLLVMType() + "\n";
    ir += tab + "store " + formal->getType()->getLLVMType() + " " + formal->getLLVMAddress() + ", " + formal->getType()->getLLVMType() + "* " + address + "\n";
  }
  llvm_address_counters.push(counter);
  // Visit the method instructions
  Visitor::visitMethodNode(node);
  tab.pop_back();

  ir += tab + "}\n\n";

  llvm_address_counters.pop();
  current_scope = prev_scope;
  return 0;
}

int CodeGenVisitor::visitLetNode(LetNode *node){
  ir += tab + "LetNode: \n";

  ObjectIdentifierNode* object_id = node->getObjectId();
	TypeIdentifierNode* object_type = node->getObjectType();
	ExpressionNode* init_expr = node->getInitExp();
	ExpressionNode* scope_exp = node->getScopeExp();
  string expr_addr = node->getLLVMAddress();

  VSOPNode* prev_scope = current_scope;
  current_scope = node;

  // Allocate space for the field // TODO : je suis pas sur que c'est le mieux de le faire là ou dans le classbody (différence entre le name et le filednode en lui-même)
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  node->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(node->getLLVMAddress(), object_type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
  llvm_address_counters.push(counter);

  // If there is an init expression, store its value in the field
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
    ir += tab + getLLVMStoreCode(init_expr->getLLVMAddress(), node->getLLVMAddress(), object_type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
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

int CodeGenVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){
  if(current_scope && node->getLLVMAddress().size())
    ir += tab + getLLVMStoreCode(current_scope->getDeclarationLLVM(node->getLiteral()), node->getLLVMAddress(), node->getLLVMType());
  return 0;
}

int CodeGenVisitor::visitClassNode(ClassNode *node){

  current_scope = (VSOPNode *) node;

  // Reinitialize the stack
  llvm_address_counters.push(0);

  string struct_name = "%struct." + node->getName()->getLiteral();
  string struct_vtable = "%struct." + node->getName()->getLiteral() + "VTable";
  string struct_instance = "@" + node->getName()->getLiteral() + "VTable_inst";
  string struct_init = "@" + node->getName()->getLiteral() + "_init";
  string struct_new = "@" + node->getName()->getLiteral() + "_new";

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
    ir += tab + getLLVMCallCode(node->getParent()->getName()->getLiteral() + "_init", "void", args_value, args_type);
  }
  int i = 0;
  for(auto field : new_fields){
    i++;//TODO pas très claire si le field->getType()->getLLVMType() en dessous doit toujours être i32 ou bien dépend du type.
    field->setLLVMAddress(++var_counter);
    ir += tab + field->getLLVMAddress() + " = getelementptr inbounds " + struct_name + "* %self, i32 0, i32 " + to_string(i) + "\n";
    string init_value = "0"; //TODO Peut être changer le zero par une valeur qui dépend du type.
    ExpressionNode *init_expr = field->getInitExpr();
    if (init_expr){
        // Visit the init expression
        init_expr->setLLVMAddress(++var_counter);
        if (init_expr->accept(this) < 0)
          return -1;
        init_value = "*" + init_expr->getLLVMAddress(); // TODO : peut-etre bouger le pointeur
    }
    ir += tab + getLLVMStoreCode(init_value, field->getLLVMAddress(), field->getType()->getLLVMType());
  }
  ir += tab + "%" + to_string(++var_counter) + " = getelementptr inbounds " + struct_name + "* %self, i32 0, i32 0\n";
  ir += tab + getLLVMStoreCode(struct_instance, "%" + to_string(var_counter), struct_vtable + "*");//TODO j'ai pas cast comme dans le code car je comprends pas à quoi aç sert.
  ir += tab + "ret void\n";
  tab.pop_back();
  ir += tab + "}\n\n";

  // New function
  var_counter = 1;
  ir += tab + "define " + struct_name + "* " + struct_new + "(){\n";
  ir += tab + "\t%self = alloca " + struct_name + "*\n";

  // Code to compute the code of a structure and store it in memory
  ir += tab + "\t%" + to_string(var_counter) + " = getelementptr " + struct_name + "* null, i32 1\n";
  ir += tab + "\t%size = ptrtoint " + struct_name + "* %" + to_string(var_counter) + " to i32\n";

  // Malloc
  ir += tab + "\t%" + to_string(++var_counter) + " = call noalias i8* @malloc(i32 %size)\n";
  ir += tab + "\t%" + to_string(++var_counter) + " = bitcast i8* %" + to_string(var_counter) + " to " + struct_name + "*\n";
  ir += tab + "\tstore " + struct_name + "* %" + to_string(var_counter) + ", " + struct_name + "** %self\n";

  // Assert
  string llvm_load = "%" + to_string(++var_counter);
  ir += tab + "\t" + getLLVMLoadCode(llvm_load, "%self", struct_name + "*");
  int llvm_assert = ++var_counter;
  ir += tab + "\t%" + to_string(llvm_assert) + " = icmp ne " + struct_name + "* %" + to_string(var_counter - 1) + ", null\n";
  ir += tab + "\tbr i1 %" + to_string(llvm_assert) + ", label %notnull, label %null\n";
  ir += tab + "\nnotnull:\n";
  ir += tab + "\tcall void " + struct_init + "(" + struct_name + "* " + llvm_load + ")\n";

  ir += tab + "\nnull:\n";
  ir += tab + "\tret " + struct_name + "* " + llvm_load + "\n}\n\n";

  Visitor::visitClassNode(node);

  llvm_address_counters.pop();
  return 0;
}

int CodeGenVisitor::visitNewNode(NewNode *node){
  string expr_addr = node->getLLVMAddress();

  string new_function = "@"+ node->getTypeId()->getLiteral() + "_new";
  if (expr_addr != "")
    ir += tab + expr_addr + " = " + getLLVMCallCode(new_function, node->getTypeId()->getLLVMType(), vector<string>(), vector<string>());
  else
    ir += tab + getLLVMCallCode(new_function, node->getTypeId()->getLLVMType(), vector<string>(), vector<string>());

  return 0;
}

int CodeGenVisitor::visitConditionalNode(ConditionalNode *node){

  ExpressionNode* condition = node->getCondition();
  ExpressionNode* action = node->getAction();
  ExpressionNode* else_action = node->getElseAction();
  string expr_addr = node->getLLVMAddress();

  // Generate code for the condition
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  condition->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(condition->getLLVMAddress(), condition->getLLVMType());
  llvm_address_counters.push(counter);
  if (condition->accept(this) < 0)
    return -1;

  // Branch on the result
  if (else_action)
    ir += tab + "br i1 " + condition->getLLVMAddress() + "*, label then_" + condition->getLLVMAddress() + ", label else_" + condition->getLLVMAddress() + "\n";
  else
    ir += tab + "br i1 " + condition->getLLVMAddress() + "*, label then_" + condition->getLLVMAddress() + ", label end_" + condition->getLLVMAddress() + "\n";

  // First branch1
  ir += tab + "then_" + condition->getLLVMAddress() + ":\n";
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
      ir += tab + getLLVMStoreCode(action->getLLVMAddress(), action->getLLVMType(), expr_addr);
  tab.pop_back();

  if(else_action){
    ir += tab + "\tbr label end_" + condition->getLLVMAddress() + "\n";
    ir += tab + "else_" + condition->getLLVMAddress() + ":\n";
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
      ir += tab + getLLVMStoreCode(else_action->getLLVMAddress(), else_action->getLLVMType(), expr_addr);
    tab.pop_back();
  }
  ir += tab + "end_" + condition->getLLVMAddress() + ":\n";

  return 0;
}

int CodeGenVisitor::visitWhileNode(WhileNode *node){

  ExpressionNode* condition = node->getCondition();

  // Branch to the condition
  ir += tab + "br label loop_" + node->getLLVMAddress() + "\n";
  ir += "loop_" + node->getLLVMAddress() + ":\n";

  // Visit the condtion
  int counter = llvm_address_counters.top();
  llvm_address_counters.pop();
  condition->setLLVMAddress(counter++);
  ir += tab + getLLVMAllocationCode(condition->getLLVMAddress(), condition->getLLVMType());
  llvm_address_counters.push(counter);
  if (condition->accept(this) < 0)
    return -1;

  // Branch according to the condition
  ir += tab + "br i1 " + condition->getLLVMAddress() + "*, label do_" + node->getLLVMAddress() + ", label end_" + node->getLLVMAddress() + "\n";

  ir += "do_" + node->getLLVMAddress() + ":\n";
  if (condition->accept(this) < 0)
    return -1;
  ir += tab + "br label loop_" + node->getLLVMAddress() + "\n";

  ir += "end_" + node->getLLVMAddress() + ":\n";

  return 0;
}

int CodeGenVisitor::visitCallNode(CallNode* node){



  return 0;
}

//int CodeGenVisitor::visitBraceNode()
