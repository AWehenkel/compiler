#include <stdio.h>

int yyerror_isinitialized, yymaxstate = 56;
struct errtable {
   int i;
   union {
      char *msg;
      struct errtable *p;
      } u;
   } errtab[57];
int yyerror_init()
{
   errtab[4].i = 1;
   errtab[4].u.msg = "Missing class name";
   errtab[56].i = 1;
   errtab[56].u.msg = "Missing closing brace at the end of class";
   errtab[53].i = 1;
   errtab[53].u.msg = "Missing opening brace at the beginning of class";
}

extern int errors;
extern char *yyfilename, yytext[];
extern int yychar, yylineno;

extern short *yyssp;

int yyerror(char *s)
{
   int state = *yyssp;
   int i;
   char sbuf[128];
   if (! yyerror_isinitialized++) yyerror_init();
   if (strstr(s, "stack")) return 0;
   if (errors++ > 10) {
      fprintf(stderr, "too many errors, aborting");
      exit(errors); }
   if(yyfilename) fprintf(stderr, "%s:", yyfilename);
   if ((!strcmp(s, "syntax error") || !strcmp(s,"parse error"))&&
         (state>=0 && state<=yymaxstate))
       if (errtab[state].i==1)
         s = errtab[state].u.msg;
       else {
          for(i=1;i<=errtab[state].i;i++)
             if(yychar == errtab[state].u.p[i].i) {
                s=errtab[state].u.p[i].u.msg;break;}
          if(i>errtab[state].i)s=errtab[state].u.p[0].u.msg;
          }
   if (!strcmp(s, "syntax error") || !strcmp(s,"parse error")){
      sprintf(sbuf,"%s (%d;%d)", s, state, yychar);
      s=sbuf;
      }
   fprintf(stderr, "%d: # \"%s\": %s\n", yylineno, yytext, s);
   return 0;
}
