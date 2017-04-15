To add new errors to the automatic detection :

1) In file "vsop_grammar.y", change the include:
 #include "yyerror_init.h
 to
 #include "yyerror_generation.h"

2) Comment the two last lines of the file

3) Decomment the lines going from
  "// Lines to comment after error generation"
  to
  "// Lines to comment when doing error generation"

4) Add errors examples to the file meta.err with the format :
  {example of code with an error} ::: "message to be displayed"

3) Run "make generation"

4) This will have generated a new "yyerror.c".

5) Copy the content of this file from line 3 to the end of function
"yyerror_init" to "yyerror_init.h"

6) In "yyerror_init.h", change
  char *msg;
  to
  const char *msg;

7) Add a conversion to *errtable before every calloc 

8) Finally, undo all you did at point 1, 2 and 3
