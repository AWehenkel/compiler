
class B extends A{
  factorial() : int32 {
    let xs : int32 in {
      printInt32(xs);
      factorial2()
    }
  }
  test : unit;
}
class A extends IO{
  factorial() : int32 { 1 }
  factorial2() : int32 { 2 }
  factorial : int32;
}

class IO {
  print(s : string) : IO {
  (* print s on stdout, then return self *)
  0
  }

  printBool(b : bool) : IO {
    (* print b on stdout, then return self *)
    0
  }

  printInt32(i : int32) : IO {
    (* print i on stdout, then return self *)
    0
  }

  inputLine() : string {
    (* read one line from stdin, return "" in case of error *)
    0
  }

  inputBool() : bool {
    (* read one boolean value from stdin, exit with error message in case of
    error *)
    0
  }

  inputInt32() : int32 {
    (* read one integer from stdin, exit with error message in case of
    error *)
    0
  }
}
