int speak_impl(int a){
  return 0;
}

struct test {
  int (*speak) (int a);
    int (*speak2) (int a);
};

struct test test_impl = {
  .speak = speak_impl,
  .speak2 = speak_impl
};

int main(){
  struct test t;
  return 0;

}
