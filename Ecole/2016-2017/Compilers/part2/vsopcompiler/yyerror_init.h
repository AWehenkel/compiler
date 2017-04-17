int yyerror_isinitialized, yymaxstate = 163;
struct errtable {
   int i;
   union {
      const char *msg;
      struct errtable *p;
      } u;
   } errtab[164];
int yyerror_init()
{
   errtab[5].i = 2;
   errtab[5].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[5].u.p[0].u.msg = "Missing class name";
   errtab[5].u.p[1].i = 277;
   errtab[5].u.p[1].u.msg = "First letter of class is not uppercase";
   errtab[5].u.p[2].i = 281;
   errtab[5].u.p[2].u.msg = "Missing class name";
   errtab[68].i = 5;
   errtab[68].u.p = (errtable*) calloc(1,6 * sizeof(struct errtable));
   errtab[68].u.p[0].u.msg = "Missing closing brackets in method declaration";
   errtab[68].u.p[1].i = 277;
   errtab[68].u.p[1].u.msg = "Missing ',' to separate formals in method declaration";
   errtab[68].u.p[2].i = 285;
   errtab[68].u.p[2].u.msg = "Missing name in formal in method declaration";
   errtab[68].u.p[3].i = 279;
   errtab[68].u.p[3].u.msg = "Formal name cannot start with a capital letter";
   errtab[68].u.p[4].i = 284;
   errtab[68].u.p[4].u.msg = "Too many opening brackets in method declaration";
   errtab[68].u.p[5].i = 286;
   errtab[68].u.p[5].u.msg = "Wrong separator of formals in method declaration";
   errtab[89].i = 1;
   errtab[89].u.msg = "Missing expression after 'new'";
   errtab[136].i = 2;
   errtab[136].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[136].u.p[0].u.msg = "Missing closing brackets at the end of call";
   errtab[136].u.p[1].i = 282;
   errtab[136].u.p[1].u.msg = "Missing closing brackets at the end of call";
   errtab[136].u.p[2].i = 287;
   errtab[136].u.p[2].u.msg = "Unexpected ',' in function call";
   errtab[157].i = 1;
   errtab[157].u.msg = "Missing expression after 'then'";
   errtab[78].i = 1;
   errtab[78].u.msg = "Unexpected ',' after formal in method declaration";
   errtab[120].i = 1;
   errtab[120].u.msg = "Missing right member in '-' expression";
   errtab[62].i = 1;
   errtab[62].u.msg = "Missing ':' in field declaration";
   errtab[83].i = 2;
   errtab[83].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[83].u.p[0].u.msg = "Missing type in method declaration";
   errtab[83].u.p[1].i = 277;
   errtab[83].u.p[1].u.msg = "Wrong type in method declaration";
   errtab[83].u.p[2].i = 281;
   errtab[83].u.p[2].u.msg = "Missing type in method declaration";
   errtab[104].i = 1;
   errtab[104].u.msg = "Missing opening curly braces in method declaration";
   errtab[125].i = 1;
   errtab[125].u.msg = "Missing right member in '=' expression";
   errtab[130].i = 2;
   errtab[130].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[130].u.p[0].u.msg = "Missing type in let declaration";
   errtab[130].u.p[1].i = 277;
   errtab[130].u.p[1].u.msg = "Invalid type in let declaration";
   errtab[130].u.p[2].i = 266;
   errtab[130].u.p[2].u.msg = "Missing type in let declaration";
   errtab[4].i = 1;
   errtab[4].u.msg = "Too much closing curly braces at the closing of class";
   errtab[67].i = 1;
   errtab[67].u.msg = "Missing ':' in formal in method declaration";
   errtab[88].i = 2;
   errtab[88].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[88].u.p[0].u.msg = "Missing variable name in let declaration";
   errtab[88].u.p[1].i = 285;
   errtab[88].u.p[1].u.msg = "Missing variable name in let declaration";
   errtab[88].u.p[2].i = 279;
   errtab[88].u.p[2].u.msg = "Variable name can not start with a capital letter in let declaration";
   errtab[114].i = 1;
   errtab[114].u.msg = "Missing closing brackets";
   errtab[56].i = 3;
   errtab[56].u.p = (errtable*) calloc(1,4 * sizeof(struct errtable));
   errtab[56].u.p[0].u.msg = "Missing opening curly brace at the beginning of class";
   errtab[56].u.p[1].i = 277;
   errtab[56].u.p[1].u.msg = "Wrong extension keyword, use 'extends'";
   errtab[56].u.p[2].i = 282;
   errtab[56].u.p[2].u.msg = "Missing opening curly brace at the beginning of class";
   errtab[56].u.p[3].i = 279;
   errtab[56].u.p[3].u.msg = "Missing extension keyword";
   errtab[77].i = 3;
   errtab[77].u.p = (errtable*) calloc(1,4 * sizeof(struct errtable));
   errtab[77].u.p[0].u.msg = "Missing ':' in method declaration";
   errtab[77].u.p[1].i = 267;
   errtab[77].u.p[1].u.msg = "Missing ':' in method declaration";
   errtab[77].u.p[2].i = 286;
   errtab[77].u.p[2].u.msg = "Wrong separator in method declaration";
   errtab[77].u.p[3].i = 283;
   errtab[77].u.p[3].u.msg = "Too many closing brackets in method declaration";
   errtab[119].i = 1;
   errtab[119].u.msg = "Missing right member in '+' expression";
   errtab[108].i = 2;
   errtab[108].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[108].u.p[0].u.msg = "Missing ':' in let declaration";
   errtab[108].u.p[1].i = 267;
   errtab[108].u.p[1].u.msg = "Missing ':' in let declaration";
   errtab[108].u.p[2].i = 286;
   errtab[108].u.p[2].u.msg = "Wrong separator in let declaration";
   errtab[129].i = 1;
   errtab[129].u.msg = "Missing expression after 'else'";
   errtab[66].i = 2;
   errtab[66].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[66].u.p[0].u.msg = "Missing type in field declaration";
   errtab[66].u.p[1].i = 277;
   errtab[66].u.p[1].u.msg = "Wrong type in field declaration";
   errtab[66].u.p[2].i = 286;
   errtab[66].u.p[2].u.msg = "Missing type in field declaration";
   errtab[87].i = 1;
   errtab[87].u.msg = "Missing expression after 'isnull'";
   errtab[92].i = 1;
   errtab[92].u.msg = "Missing expression after 'while'";
   errtab[55].i = 1;
   errtab[55].u.msg = "Extension can only be applied on objects";
   errtab[76].i = 2;
   errtab[76].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[76].u.p[0].u.msg = "Missing type in formal in method declaration";
   errtab[76].u.p[1].i = 277;
   errtab[76].u.p[1].u.msg = "Wrong type in formal in method declaration";
   errtab[76].u.p[2].i = 283;
   errtab[76].u.p[2].u.msg = "Missing type in formal in method declaration";
   errtab[118].i = 1;
   errtab[118].u.msg = "Missing right member in 'and' expression";
   errtab[81].i = 2;
   errtab[81].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[81].u.p[0].u.msg = "Missing ';' at the end of field declaration";
   errtab[81].u.p[1].i = 282;
   errtab[81].u.p[1].u.msg = "Missing ';' at the end of field declaration";
   errtab[81].u.p[2].i = 278;
   errtab[81].u.p[2].u.msg = "Missing '<-' in assignment";
   errtab[123].i = 1;
   errtab[123].u.msg = "Missing right member in '^' expression";
   errtab[86].i = 1;
   errtab[86].u.msg = "Missing expression after 'if'";
   errtab[133].i = 4;
   errtab[133].u.p = (errtable*) calloc(1,5 * sizeof(struct errtable));
   errtab[133].u.p[0].u.msg = "Missing ';' at the end of expression";
   errtab[133].u.p[1].i = 285;
   errtab[133].u.p[1].u.msg = "Wrong separator in function call";
   errtab[133].u.p[2].i = 287;
   errtab[133].u.p[2].u.msg = "Wrong expression separator in block";
   errtab[133].u.p[3].i = 278;
   errtab[133].u.p[3].u.msg = "Missing ';' at the end of expression";
   errtab[133].u.p[4].i = 283;
   errtab[133].u.p[4].u.msg = "Too many closing brackets";
   errtab[117].i = 1;
   errtab[117].u.msg = "Missing value to assign in assignment";
   errtab[59].i = 5;
   errtab[59].u.p = (errtable*) calloc(1,6 * sizeof(struct errtable));
   errtab[59].u.p[0].u.msg = "Missing closing curly brace at the end of class";
   errtab[59].u.p[1].i = 0;
   errtab[59].u.p[1].u.msg = "Missing closing curly brace at the end of class";
   errtab[59].u.p[2].i = 285;
   errtab[59].u.p[2].u.msg = "Missing name in field declaration";
   errtab[59].u.p[3].i = 279;
   errtab[59].u.p[3].u.msg = "Method cannot start with a capital letter";
   errtab[59].u.p[4].i = 284;
   errtab[59].u.p[4].u.msg = "Missing method name in method declaration";
   errtab[59].u.p[5].i = 281;
   errtab[59].u.p[5].u.msg = "Too much opening curly braces at the beginning of class";
   errtab[80].i = 2;
   errtab[80].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[80].u.p[0].u.msg = "Mising assignemen value";
   errtab[80].u.p[1].i = 266;
   errtab[80].u.p[1].u.msg = "Missing expression after '<-' in let declaration";
   errtab[80].u.p[2].i = 286;
   errtab[80].u.p[2].u.msg = "Mising assignemen value";
   errtab[122].i = 1;
   errtab[122].u.msg = "Missing right member in '/' expression";
   errtab[127].i = 1;
   errtab[127].u.msg = "Missing right member in '<=' expression";
   errtab[1].i = 2;
   errtab[1].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[1].u.p[0].u.msg = "The program should contain at least one class";
   errtab[1].u.p[1].i = 0;
   errtab[1].u.p[1].u.msg = "The program should contain at least one class";
   errtab[1].u.p[2].i = 279;
   errtab[1].u.p[2].u.msg = "Wrong class definition keyword, should be 'class'";
   errtab[90].i = 1;
   errtab[90].u.msg = "Missing expression after 'not'";
   errtab[106].i = 2;
   errtab[106].u.p = (errtable*) calloc(1,3 * sizeof(struct errtable));
   errtab[106].u.p[0].u.msg = "Missing 'then' after 'if'";
   errtab[106].u.p[1].i = 282;
   errtab[106].u.p[1].u.msg = "Missing 'then' after 'if'";
   errtab[106].u.p[2].i = 278;
   errtab[106].u.p[2].u.msg = "Missing 'then' after 'if'";
   errtab[111].i = 1;
   errtab[111].u.msg = "Missing 'do' after 'while'";
   errtab[132].i = 1;
   errtab[132].u.msg = "Unexpected ';' at the end fof block";
   errtab[153].i = 1;
   errtab[153].u.msg = "Unexpected ',' in function call";
   errtab[95].i = 13;
   errtab[95].u.p = (errtable*) calloc(1,14 * sizeof(struct errtable));
   errtab[95].u.p[0].u.msg = "Mising opening brackets in method declaration";
   errtab[95].u.p[1].i = 290;
   errtab[95].u.p[1].u.msg = "Missing left member in '*' expression";
   errtab[95].u.p[2].i = 261;
   errtab[95].u.p[2].u.msg = "Missing 'while' before 'do'";
   errtab[95].u.p[3].i = 282;
   errtab[95].u.p[3].u.msg = "Block must contain at least one expression";
   errtab[95].u.p[4].i = 295;
   errtab[95].u.p[4].u.msg = "Missing left member in '<' expression";
   errtab[95].u.p[5].i = 258;
   errtab[95].u.p[5].u.msg = "Missing left member in 'and' expression";
   errtab[95].u.p[6].i = 279;
   errtab[95].u.p[6].u.msg = "Function call cannot start with a capital letter";
   errtab[95].u.p[7].i = 292;
   errtab[95].u.p[7].u.msg = "Missing left member in '^' expression";
   errtab[95].u.p[8].i = 297;
   errtab[95].u.p[8].u.msg = "Missing assignee in assignment";
   errtab[95].u.p[9].i = 273;
   errtab[95].u.p[9].u.msg = "Missing 'if' before 'then'";
   errtab[95].u.p[10].i = 294;
   errtab[95].u.p[10].u.msg = "Missing left member in '=' expression";
   errtab[95].u.p[11].i = 291;
   errtab[95].u.p[11].u.msg = "Missing left member in '/' expression";
   errtab[95].u.p[12].i = 288;
   errtab[95].u.p[12].u.msg = "Missing left member in '+' expression";
   errtab[95].u.p[13].i = 296;
   errtab[95].u.p[13].u.msg = "Missing left member in '<=' expression";
   errtab[158].i = 1;
   errtab[158].u.msg = "Missing 'in' in let declaration";
   errtab[163].i = 1;
   errtab[163].u.msg = "Missing expression after 'in' in let declaration";
   errtab[121].i = 1;
   errtab[121].u.msg = "Missing right member in '*' expression";
   errtab[126].i = 1;
   errtab[126].u.msg = "Missing right member in '<' expression";
   errtab[131].i = 1;
   errtab[131].u.msg = "Missing expression after 'do'";
}