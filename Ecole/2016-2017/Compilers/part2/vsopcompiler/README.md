To add new errors to the automatic detection :

1) Copy the content of "vsop_grammar_generation.y" to "vsop_grammar.y"

2) Add errors examples to the file meta.err with the format :
  {example of code with an error} ::: "message to be displayed"

3) Run "make generation"

4) This will have generated a new "yyerror.c".

5) Copy the content of this file from line 3 to the end of function
"yyerror_init".

6) Paste it to replace the old version of that code in "vsop_grammar.y".

7) Comment the lines of "yyerror" in "vsop_grammar.y" starting at the comment
"Lines to comment after generation" until the two last commented lines and
decomment those two lines.
