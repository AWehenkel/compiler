class A {
  factorial() : int32 { 1 }
  factorial : int32;
}
class B extends A{
  factorial() : int32 { factorial }
  test : unit;
}
