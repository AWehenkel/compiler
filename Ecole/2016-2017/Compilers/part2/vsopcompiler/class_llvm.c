#include <stdlib.h>
#include <assert.h>

struct ChildVTable;
struct Child;
struct Parent;
struct ParentVTable;

// A ChildVTable must be able to masquerade as a ParentVTable
struct ParentVTable {
  // First, parent methods in the same order
  void (*inheritedMethod)(struct Parent *);
  void (*overriddenMethod)(struct Parent *);
};

// A Child must be able to masquerade as a Parent
struct Parent {
  struct ParentVTable *_vtable; // Virtual function table always comes first
  int inheriteField; // Parent fields, in the same order as parent!
};

void Parent_init(struct Parent *self) {
  self->inheriteField = 0;
  self->_vtable = &ParentVTable_inst; // Override vtable
}

void Parent_inheritedMethod (struct Parent* p){}
void Parent_overriddenMethod (struct Parent* p){}

// Child VTable can mix inherited, overridden and new methods
struct ParentVTable ParentVTable_inst = {
  // Necessary (but legit) cast for inherited method
  .inheritedMethod = Parent_inheritedMethod,
  .overriddenMethod = Parent_overriddenMethod,
};

// A ChildVTable must be able to masquerade as a ParentVTable
struct ChildVTable {
  // First, parent methods in the same order
  void (*inheritedMethod)(struct Child *);
  void (*overriddenMethod)(struct Child *);
  // Then child's new methods
  void (*newMethod)(struct Child *, int a);
};

// A Child must be able to masquerade as a Parent
struct Child {
  struct ChildVTable *_vtable; // Virtual function table always comes first
  int inheritedField; // Parent fields, in the same order as parent!
  int newField; // And, finally, child's new fields
};

void Child_overriddenMethod(struct Child *c){}
void Child_newMethod(struct Child *c, int a){}

// Child VTable can mix inherited, overridden and new methods
struct ChildVTable ChildVTable_inst = {
  // Necessary (but legit) cast for inherited method
  .inheritedMethod = (void (*)(struct Child *)) Parent_inheritedMethod,
  .overriddenMethod = Child_overriddenMethod,
  .newMethod = Child_newMethod
};


void Child_init(struct Child *self) {
  Parent_init((struct Parent *) self); // Call parent's initializer
  self->newField = 0;
  self->_vtable = &ChildVTable_inst; // Override vtable
}

struct Child *Child_new() {
  int i = sizeof(struct Parent);
  struct Child *self = malloc(sizeof (struct Child));
  assert(self);
  Child_init(self);
  return self;
};

int main () {
  // let myObject : MyClass <- new MyClass in
  struct Parent *myObject = Child_new();
  // myObject.someOtherMethod(42)
  myObject->_vtable->newMethod(myObject, 42);
}
