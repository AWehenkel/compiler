class MyClass extends IO {
    myMethod(n : int32) : unit {
        while not (n <= 0) do {
            printInt32(n);
            print("\n");
            n = n - 1
        }
    }
}
class Main { main() : int32 { 0 } }
