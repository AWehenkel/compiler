#include <stdlib.h>
#include <assert.h>

struct ChildVTable;
struct Child;

struct Parent {char i;};
void Parent_init(struct Parent *self) {}

void Parent_inheritedMethod (struct Parent* p){}

// A ChildVTable must be able to masquerade as a ParentVTable
struct ChildVTable {
  // First, parent methods in the same order
  void (*inheritedMethod)(struct Child *);
  void (*overriddenMethod)(struct Child *);
  // Then child's new methods
  void (*newMethod)(struct Child *);
};

// A Child must be able to masquerade as a Parent
struct Child {
  struct ChildVTable *_vtable; // Virtual function table always comes first
  int inheritedField; // Parent fields, in the same order as parent!
  int newField; // And, finally, child's new fields
  int newField2;
};

void Child_overriddenMethod(struct Child *c){}
void Child_newMethod(struct Child *c){}

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
  struct Child c;
}
