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
    MethodNode* current_method;
    LetNode* current_let;
    VSOPNode* current_scope;
  public :
    int visitClassNode(ClassNode *node);
    int visitMethodNode(MethodNode *node);
    int visitFieldNode(FieldNode *node);
    int visitObjectIdentifierNode(ObjectIdentifierNode *node);
    int visitLetNode(LetNode *node);
    int visitFormalNode(FormalNode *node);
    int visitCallNode(CallNode *node);
    int visitFormalsNode(FormalsNode *node);
    int visitAssignNode(AssignNode *node);
};

#endif //fill_scope_tables_visitor
