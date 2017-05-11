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
  for(size_t i = 0; i < args_value.size(); i++)
    to_ret += args_type.at(i) + " " + args_value.at(i) + ", ";
  to_ret.replace(to_ret.size() - 2, 3, ")\n");
  return to_ret;
}

int CodeGenVisitor::visitAssignNode(AssignNode *node){
  ir += "AssignNode: \n";

  ExpressionNode* expr = node->getExpression();
  ObjectIdentifierNode* name = node->getName();

  // Visit the expression at the right of the assignment TODO pour les literal il faudrait ne pas stocker dans une nouvelle addresse mais utiliser le literal en lui meme.
  if(!expr->alreadyInstanciated()){
    ir += "!expr->alreadyInstanciated() " + expr->getLiteral() + "\n";
    int counteur = llvm_address_counteurs.top();
    llvm_address_counteurs.pop();
    expr->setLLVMAddress(counteur++);
    ir += getLLVMAllocationCode(expr->getLLVMAddress(), expr->getLLVMType());
    llvm_address_counteurs.push(counteur);

    // Visit the init expression
    if (expr->accept(this) < 0)
      return -1;
  }
  else
    expr->setLLVMAddress(current_scope->getDeclarationLLVM(expr->getLiteral()));
  // Store the value of the expression in the left term
  ir += getLLVMStoreCode(expr->getLLVMAddress(), current_scope->getDeclarationLLVM(name->getLiteral()), name->getLLVMType()); // TODO : problème avec name, pas de llvm address

  return 0;

}


string CodeGenVisitor::getLLVMBinaryCode(BinaryOperatorNode* node, string op1, string op2){
  int counter = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
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
  llvm_address_counteurs.push(counter);
  code += "\n" + getLLVMStoreCode(to_ret, node->getLLVMAddress(), "i32"); // TODO : pourquoi est-ce qu'on store forcément un i32 ?
  return code;
}

string CodeGenVisitor::getLLVMUnaryCode(UnaryOperatorNode* node, string op){
  int counter = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
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
  llvm_address_counteurs.push(counter);
  code += "\n" + getLLVMStoreCode(to_ret, node->getLLVMAddress(), "i32"); // TODO : pourquoi est-ce qu'on store forcément un i32 ?
  return code;
}

int CodeGenVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node){
  ir += "BinaryOperatorNode: \n";

  ExpressionNode* left = node->getLeft();
  ExpressionNode* right = node->getRight();

  // Visit the children nodes
  // TODO : est-ce qu'il faut pas d'abord checker, s'il n'y a pas déjà une address dans les fils ? genre si c'est un objet, la mếmoire est
  // sensé être déjà allouée non ?
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  left->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(left->getLLVMAddress(), left->getLLVMType());
  llvm_address_counteurs.push(counteur);
  if (left->accept(this) < 0)
    return -1;

  counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  right->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(right->getLLVMAddress(), right->getLLVMType());
  llvm_address_counteurs.push(counteur);
  if (right->accept(this) < 0)
    return -1;

  // Make the operation
  counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  string llvm_address_3 = "%" + to_string(counteur++);
  string llvm_address_4 = "%" + to_string(counteur++);
  llvm_address_counteurs.push(counteur);
  // Load the values of the two child
  ir += getLLVMLoadCode(llvm_address_3, left->getLLVMAddress(), left->getLLVMType());
  ir += getLLVMLoadCode(llvm_address_4, right->getLLVMAddress(), right->getLLVMType());
  // Store the result
  ir += getLLVMBinaryCode(node, llvm_address_3, llvm_address_4);

  return 0;
}

int CodeGenVisitor::visitBlockNode(BlockNode* node){

  vector<ExpressionNode*> expresions = node->getExpressions();
  ExpressionNode* first = *(expresions.begin());
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  //first->setLLVMAddress(counteur++);
  //ir += getLLVMAllocationCode(first->getLLVMAddress(), first->getLLVMType()); //TODO Probleme il faut stocker quelque chose dedans pour que ça ait du sens d'allouer
  llvm_address_counteurs.push(counteur);
  Visitor::visitBlockNode(node);
  return 0;
}

int CodeGenVisitor::visitUnaryOperatorNode(UnaryOperatorNode* node){
  ir += "UnaryOperatorNode: \n";

  ExpressionNode* operand = node->getOperand();

  // Visit the child
  // TODO : est-ce qu'il faut pas d'abord checker, s'il n'y a pas déjà une address dans les fils ? genre si c'est un objet, la mếmoire est
  // sensé être déjà allouée non ?
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  operand->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(operand->getLLVMAddress(), operand->getLLVMType());
  llvm_address_counteurs.push(counteur);
  if (operand->accept(this) < 0)
    return -1;

  // Make the operation
  counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  string llvm_address = "%" + to_string(counteur++);
  llvm_address_counteurs.push(counteur);
  ir += getLLVMLoadCode(llvm_address, operand->getLLVMAddress(), operand->getLLVMType());
  ir += getLLVMUnaryCode(node, llvm_address);

  return 0;
}

int CodeGenVisitor::visitFieldNode(FieldNode *node){
  ir += "FieldNode: \n";

  ObjectIdentifierNode* name = node->getName();
  ExpressionNode* init_expr = node->getInitExpr();
  TypeIdentifierNode* type = node->getType();

  // Allocate space for the field // TODO : je suis pas sur que c'est le mieux de le faire là ou dans le classbody (différence entre le name et le filednode en lui-même)
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  name->setLLVMAddress(counteur++);
  // TODO : comment se fait-il que le nom du field n'aie pas de type ?
  ir += getLLVMAllocationCode(name->getLLVMAddress(), type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
  llvm_address_counteurs.push(counteur);
  // If there is an init expression, store its value in the field
  if (init_expr != NULL){
    // Allocate memory for the init expression
    counteur = llvm_address_counteurs.top();
    llvm_address_counteurs.pop();
    init_expr->setLLVMAddress(counteur++);
    ir += getLLVMAllocationCode(init_expr->getLLVMAddress(), init_expr->getLLVMType());
    llvm_address_counteurs.push(counteur);
    // Visit the init expression
    if (init_expr->accept(this) < 0)
      return -1;
    // Store the value of the init expression in the field
    ir += getLLVMStoreCode(init_expr->getLLVMAddress(), name->getLLVMAddress(), type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
  }
  ir += "end FieldNode: \n";
  return 0;
}

//TODO Changer les constructeur de LiteralNode et faire en sorte de prendre en charge correctement les literaux.
int CodeGenVisitor::visitLiteralNode(LiteralNode *node){
  ir += getLLVMStoreCode(node->getLiteral(), node->getLLVMAddress(), node->getLLVMType());
  return 0;
}

int CodeGenVisitor::visitProgramNode(ProgramNode* node){
  llvm_address_counteurs.push(0);
  // Add the malloc function
  ir += "declare noalias i8* @malloc(i32)\n\n";
  Visitor::visitProgramNode(node);
  cout << "IR: " << ir << endl;
  return 0;
}


//TODO
int CodeGenVisitor::visitMethodNode(MethodNode *node){
  VSOPNode* prev_scope = current_scope;
  current_scope = node;
  Visitor::visitMethodNode(node);
  current_scope = prev_scope;
  return 0;
}

int CodeGenVisitor::visitLetNode(LetNode *node){
  ir += "LetNode: \n";

  ObjectIdentifierNode* object_id = node->getObjectId();
	TypeIdentifierNode* object_type = node->getObjectType();
	ExpressionNode* init_expr = node->getInitExp();
	ExpressionNode* scope_exp = node->getScopeExp();

  VSOPNode* prev_scope = current_scope;
  current_scope = node;

  // Allocate space for the field // TODO : je suis pas sur que c'est le mieux de le faire là ou dans le classbody (différence entre le name et le filednode en lui-même)
  int counteur = llvm_address_counteurs.top();
  llvm_address_counteurs.pop();
  node->setLLVMAddress(counteur++);
  ir += getLLVMAllocationCode(node->getLLVMAddress(), object_type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
  llvm_address_counteurs.push(counteur);

  // If there is an init expression, store its value in the field
  if (init_expr != NULL){
    // Allocate memory for the init expression
    counteur = llvm_address_counteurs.top();
    llvm_address_counteurs.pop();
    init_expr->setLLVMAddress(counteur++);
    ir += getLLVMAllocationCode(init_expr->getLLVMAddress(), init_expr->getLLVMType());
    llvm_address_counteurs.push(counteur);
    // Visit the init expression
    if (init_expr->accept(this) < 0)
      return -1;
    // Store the value of the init expression in the field
    ir += getLLVMStoreCode(init_expr->getLLVMAddress(), node->getLLVMAddress(), object_type->getLLVMType()); // TODO : faudrait changer type par name ce serait plus propre
  }

  if(scope_exp->accept(this))
    return 1;

  current_scope = prev_scope;

  return 0;
}

int CodeGenVisitor::visitObjectIdentifierNode(ObjectIdentifierNode *node){
  ir += "ObjectIdentifierNode\n";
  if(current_scope && node->getLLVMAddress().size())
    ir += getLLVMStoreCode(current_scope->getDeclarationLLVM(node->getLiteral()), node->getLLVMAddress(), node->getLLVMType());
  return 0;
}

int CodeGenVisitor::visitClassNode(ClassNode *node){
  Visitor::visitClassNode(node);

  string struct_name = "%struct." + node->getName()->getLiteral();
  string struct_vtable = "%struct." + node->getName()->getLiteral() + "VTable";
  string struct_instance = "@" + node->getName()->getLiteral() + "VTable_inst";
  string struct_init = "@" + node->getName()->getLiteral() + "_init";
  string struct_new = "@" + node->getName()->getLiteral() + "_new";

  //Class structure
  vector<FieldNode*> inherited_fields = node->getInheritedFields();
  ir += struct_name + " = type {\n\t" + struct_vtable + "*,";
  for(auto field : inherited_fields)
    ir += "\n\t" + field->getType()->getLLVMType() + ",";

  vector<FieldNode*> new_fields = node->getNewFields();
  for(auto field : new_fields)
    ir += "\n\t" + field->getType()->getLLVMType() + ",";

  ir.pop_back();
  ir += "\n}\n\n";
  //Class structure VTable
  ir += struct_vtable + " = type {";
  vector<MethodNode*> inherited_methods = node->getInheritedMethods();
  for(auto method : inherited_methods)
    ir += "\n\t" + method->getLLVMStructure(struct_name) + ",";

  vector<MethodNode*> overriden_methods = node->getOverridendMethods();
  for(auto method : overriden_methods)
    ir += "\n\t" + method->getLLVMStructure(struct_name) + ",";

  vector<MethodNode*> new_methods = node->getNewMethods();
  for(auto method : new_methods)
    ir += "\n\t" + method->getLLVMStructure(struct_name) + ",";

  ir.pop_back();
  ir += "\n}\n\n";

  //Class structure instanciation
  //TODO peut être que le struct_vtable devrait être le code de la vtable explicitement.
  ir += struct_instance + " = global " + struct_vtable + "{";
  for(auto method : inherited_methods)
    ir += "\n\t" + method->getLLVMInstance(node->getName()->getLiteral(), node->getParent()->getName()->getLiteral())+ ",";
  for(auto method : overriden_methods)
    ir += "\n\t" + method->getLLVMInstance(node->getName()->getLiteral()) + ",";
  for(auto method : new_methods)
    ir += "\n\t" + method->getLLVMInstance(node->getName()->getLiteral()) + ",";

  ir.pop_back();
  ir += "\n}\n\n";

  //Init function
  int var_counter = 1;
  ir += "define void " + struct_init + "(" + struct_name + "* %self){\n";
  if(node->getParent()){
    ir += "\t" + getLLVMBitCastCode("%" + to_string(var_counter), struct_name + "*", "%self", "%struct." + node->getParent()->getName()->getLiteral() + "*");
    vector<string> args_value;
    args_value.push_back("%" + to_string(var_counter));
    vector<string> args_type;
    args_type.push_back("%struct." + node->getParent()->getName()->getLiteral() + "*");
    ir += "\t" + getLLVMCallCode(node->getParent()->getName()->getLiteral() + "_init", "void", args_value, args_type);
  }
  int i = 0;
  for(auto field : new_fields){
    i++;//TODO pas très claire si le field->getType()->getLLVMType() en dessous doit toujours être i32 ou bien dépend du type.
    ir += "\t%" + to_string(++var_counter) + " = getelementptr inbounds " + struct_name + "* %self, i32 0, " + field->getType()->getLLVMType() + " " + to_string(i) + "\n";
    ir += "\t" + getLLVMStoreCode("0", "%" + to_string(var_counter), field->getType()->getLLVMType()); //TODO Peut être changer le zero par une valeur qui dépend du type.
  }
  ir += "\t%" + to_string(++var_counter) + " = getelementptr inbounds " + struct_name + "* %self, i32 0, i32 0\n";
  ir += "\t" + getLLVMStoreCode(struct_instance, "%" + to_string(var_counter), struct_vtable + "*");//TODO j'ai pas cast comme dans le code car je comprends pas à quoi aç sert.
  ir += "\tret void\n}\n\n";

  // New function
  var_counter = 1;
  ir += "define " + struct_name + "* " + struct_new + "(){\n";
  ir += "\t%self = alloca " + struct_name + "*\n";

  // Code to compute the code of a structure and store it in memory
  ir += "\t%" + to_string(var_counter) + " = getelementptr " + struct_name + "* null, i32 1\n";
  ir += "\t%size = ptrtoint " + struct_name + "* %" + to_string(var_counter) + " to i32\n";

  // Malloc
  ir += "\t%" + to_string(++var_counter) + " = call noalias i8* @malloc(i32 %size)\n";
  ir += "\t%" + to_string(++var_counter) + " = bitcast i8* %" + to_string(var_counter) + " to " + struct_name + "*\n";
  ir += "\tstore " + struct_name + "* %" + to_string(var_counter) + ", " + struct_name + "** %self\n";

  // Assert
  string llvm_load = "%" + to_string(++var_counter);
  ir += "\t" + getLLVMLoadCode(llvm_load, "%self", struct_name + "*");
  int llvm_assert = ++var_counter;
  ir += "\t%" + to_string(llvm_assert) + " = icmp ne " + struct_name + "* %" + to_string(var_counter - 1) + ", null\n";
  ir += "\tbr i1 %" + to_string(llvm_assert) + ", label %notnull, label %null\n";
  ir += "\nnotnull:\n";
  ir += "\tcall void " + struct_init + "(" + struct_name + "* " + llvm_load + ")\n";

  ir += "\nnull:\n";
  ir += "\tret " + struct_name + "* " + llvm_load + "\n}\n\n";

  return 0;
}
