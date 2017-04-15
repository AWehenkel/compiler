int yyerror_isinitialized, yymaxstate = -1;
struct errtable {
   int i;
   union {
      const char* msg;
      struct errtable *p;
      } u;
   } errtab[0];
int yyerror_init(){}
