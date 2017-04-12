#ifndef fill_scope_tables_visitor
#define fill_scope_tables_visitor

#include <unordered_map>
#include <string>
#include "Visitor.hpp"
/*
This class is a subclass of the Visitor. Its purpose is to
create the scope table(methods and fields) of the declared
classes and to check there is no double declared method or field.
*/

class FillScopeTablesVisitor : public Visitor {
  private :
    ClassNode* current_class;
  public :
    int visitClassNode(ClassNode *node);
    int visitMethodNode(MethodNode *node);
    int visitFieldNode(FieldNode *node);
};

#endif //fill_scope_tables_visitor
