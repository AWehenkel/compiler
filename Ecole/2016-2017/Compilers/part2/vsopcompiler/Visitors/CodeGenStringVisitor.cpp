#include "CodeGenStringVisitor.hpp"
#include "all_headers.hpp"
#include <algorithm>

using namespace std;

string CodeGenStringVisitor::transformStringInLLVMFormat(const string& lit) const{

  string new_lit(lit);
  string find = "\\x";

  for(string::size_type i = 0; (i = new_lit.find(find, i)) != string::npos;){
    new_lit.replace(i, find.length(), "\\");
    i += new_lit.length();
  }

  return new_lit.insert(new_lit.size() - 1, "\\00");
}

int CodeGenStringVisitor::visitLiteralNode(LiteralNode *node){

  // If the node is a string, add a declaration of a global variable
  if(node->getLLVMType() == "i8*"){
    string value = transformStringInLLVMFormat(node->getLiteral());
    int id = str_counter++, length = value.size() - 2 - 2*count(value.begin(), value.end(), '\\');
    node->setLength(length);
    node->setConstantAdd("@.str" + to_string(id));
    ir += "@.str" + to_string(id) + " = private unnamed_addr constant [" + to_string(length) + " x i8] c" + value + ", align 1\n";
  }

  return errors.size();
}
