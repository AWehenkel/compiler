class A {
  factorial() : B { true }
  factorial : int32;
}
class B extends A{
  factorial2(i : int32) : A { factorial + i }
  test : unit;
}
