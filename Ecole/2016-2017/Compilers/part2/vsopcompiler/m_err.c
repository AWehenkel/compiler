
class B extends A{
  factorial() : int32 {
    let xs : int32 in {
      printInt32(xs);
      factorial2()
    }
  }
  fac() : int32{
    1
  }
  test : unit;
}
class A extends IO{
  factorial( var : B) : int32 {
    var.fac();
    1
  }
  factorial2() : int32 { 2 }
  factorial : int32;
}

class IO {
  print(s : string) : IO {
  (* print s on stdout, then return self *)
  new IO
  }

  printBool(b : bool) : IO {
    (* print b on stdout, then return self *)
    new IO
  }

  printInt32(i : int32) : IO {
    (* print i on stdout, then return self *)
    new IO
  }

  inputLine() : string {
    (* read one line from stdin, return "" in case of error *)
    "connard"
  }

  inputBool() : bool {
    (* read one boolean value from stdin, exit with error message in case of
    error *)
    false
  }

  inputInt32() : int32 {
    (* read one integer from stdin, exit with error message in case of
    error *)
    0
  }
}
