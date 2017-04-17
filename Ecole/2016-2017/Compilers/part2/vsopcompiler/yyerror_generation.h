#ifndef yyerror_generation_h
#define yyerror_generation_h

// Code to use to generate errors using merr
int yyerror_isinitialized, yymaxstate = -1;
struct errtable {
   int i;
   union {
      const char* msg;
      struct errtable *p;
      } u;
   } errtab[0];
int yyerror_init(){}

#endif //yyerror_generation_h
