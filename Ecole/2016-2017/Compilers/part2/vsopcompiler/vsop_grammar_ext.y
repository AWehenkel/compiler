%{

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <utility>
#include <sstream>
#include "all_headers.hpp"
#include "yyerror_init.h"
#include "SemanticAnalysis/SemanticAnalyser.hpp"
#include "SemanticAnalysis/SemanticError.hpp"
#include "PairColLine.hpp"
#include "Visitors/CodeGenVisitor.hpp"
#include "Visitors/CodeGenStringVisitor.hpp"

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" char *file_name;
extern "C" char *yytext;
extern "C" int yychar;
extern "C" int yylineno;

int semantic_error = 0;
int errors;
int start_token;
int syntax_error;
ClassNode* io_node;
ClassNode* obj_node;

void yyerror(const char *s);

%}

%locations

%union{
	int ival;
  char *sval;
	class ProgramNode* program_node;
	class ClassNode* class_node;
	class ClassBodyNode* class_body_node;
	class FieldNode* field_node;
	class MethodNode* method_node;
	class AssignNode* assign_node;
	class FormalsNode* formals_node;
	class FormalNode* formal_node;
	class TypeIdentifierNode* type_identifier_node;
  class ObjectIdentifierNode* object_identifier_node;
	class BlockNode* block_node;
	class ExpressionNode* expression_node;
	class ArgsNode* args_node;
	class LiteralNode* literal_node;
	class PairColLine* col_lin;
};

%token T_AND T_BOOL T_CLASS T_DO T_ELSE T_EXTENDS T_FALSE T_IF T_IN T_INT32
%token T_ISNULL T_LET T_NEW T_NOT T_STRING T_THEN T_TRUE T_UNIT T_WHILE
%token T_OBJ_ID
%token T_INT_LIT
%token T_TYPE_ID
%token T_STRING_LIT
%token T_L_BRACE T_R_BRACE T_R_PAR T_L_PAR T_COLON T_SEMI_COLON T_COMMA
%token T_PLUS T_MINUS T_TIMES T_DIV T_POW T_DOT T_EQUAL T_LOWER T_LEQ T_GREATER T_GEQ
%token T_ASSIGN
%token T_COMMENTS
%token START_SYNTAX START_LEXICAL START_SEMANTIC START_CODE_GEN START_IO START_EX_GEN;
%token T_ERROR

%type <program_node>            program
%type <class_node>              class
%type <class_body_node>         class-body
%type <field_node>              field
%type <method_node>             method
%type <expression_node>         assign
%type <formals_node>            formals
%type <formals_node>            virgul-formals
%type <formal_node>             formal
%type <type_identifier_node>    type t_type_id extend
%type <object_identifier_node>  t_obj_id
%type <block_node>              block
%type <block_node>              sc-expr
%type <expression_node>         expr
%type <args_node>               args
%type <args_node>               comma-arg
%type <literal_node>            literal
%type <literal_node>            boolean-literal
%type <sval>                    T_OBJ_ID T_TYPE_ID T_STRING_LIT
%type <ival>                    T_INT_LIT
%type <sval>										error
%type <col_lin>									t_if
%type <col_lin>									t_while
%type <col_lin>									t_let
%type <col_lin>									t_new

%right T_ASSIGN
%left T_AND
%right T_NOT
%nonassoc T_EQUAL T_LOWER T_LEQ T_GREATER T_GEQ
%left T_PLUS T_MINUS
%left T_TIMES T_DIV
%right T_ISNULL T_UNIT
%right T_POW
%left T_DOT

%start start;

%%
start :
	START_LEXICAL Input
	| START_SYNTAX program													{	if(!syntax_error){
																											cout << *$2;
																											delete $2;
																										}
																									 }
  | START_SEMANTIC program                        {
																										if(!syntax_error){
																											$2->addClass(io_node);
																											$2->addClass(obj_node);
																											semantic_error = SemanticAnalyser::semanticAnalysis($2);
																											// Remove IO class for the class table
																											std::unordered_map<std::string, ClassNode*> c_table = $2->getTableClasses();
																										  $2->removeClass(c_table["IO"]);
																										  $2->removeClass(c_table["Object"]);
																											if(!semantic_error)
																												cout << $2->getLiteral(true);
																										}
																										delete $2;
																									}
	| START_CODE_GEN program												{
																									if(!syntax_error){
																										$2->addClass(io_node);
																										$2->addClass(obj_node);
																										semantic_error = SemanticAnalyser::semanticAnalysis($2);
																										if(!semantic_error){
																											CodeGenStringVisitor* s_gen = new CodeGenStringVisitor();
																											$2->accept(s_gen);
																											string ir = s_gen->getIr();
																											delete s_gen;
																											CodeGenVisitor* generator = new CodeGenVisitor();
																											$2->accept(generator);
																											ir += generator->getIR();
																											cout << ir << endl;
																											delete generator;
																										}

																										delete $2;
																									}
																								}
	| START_EX_GEN program												{
																										if(!syntax_error){
																											$2->addClass(io_node);
																											$2->addClass(obj_node);
																											semantic_error = SemanticAnalyser::semanticAnalysis($2);
																											if(!semantic_error){
																												CodeGenStringVisitor* s_gen = new CodeGenStringVisitor();
																												$2->accept(s_gen);
																												string ir = s_gen->getIr();
																												delete s_gen;
																												CodeGenVisitor* generator = new CodeGenVisitor();
																												$2->accept(generator);
																												ir += generator->getIR();
																												string filename_no_ext;
																												filename_no_ext = filename_no_ext.append(file_name);
																												filename_no_ext = filename_no_ext.substr(0, filename_no_ext.size()-4);
																												ofstream myfile;
																											  myfile.open (filename_no_ext + "llvm");
																												ifstream io_declaration;
																												io_declaration.open("Libraries/IO_declarations.ll");
																											  myfile << io_declaration.rdbuf() << ir;
																											  myfile.close();
																												string command = "llc-3.5 -filetype=obj -o " + filename_no_ext + "o " + filename_no_ext + "llvm";
																												system(command.c_str());
																												command = "gcc " + filename_no_ext + "o" + " Libraries/io.o -o " + filename_no_ext.substr(0, filename_no_ext.size() - 1);
																												system(command.c_str());
																												//cout << ir << endl;
																												delete generator;
																											}
																										}
																										delete $2;
																									}
	| START_IO class class													{
																										io_node = $2;
																										obj_node = $3;
																									}
;

Input :

	| Input T_AND        		{ cout << yylloc.first_line << "," << yylloc.first_column << ",and" << endl; }
	| Input T_BOOL     			{ cout << yylloc.first_line << "," << yylloc.first_column << ",bool" << endl; }
	| Input T_CLASS    			{ cout << yylloc.first_line << "," << yylloc.first_column << ",class" << endl; }
	| Input T_DO       			{ cout << yylloc.first_line << "," << yylloc.first_column << ",do" << endl; }
	| Input T_ELSE     			{ cout << yylloc.first_line << "," << yylloc.first_column << ",else" << endl; }
	| Input T_EXTENDS  			{ cout << yylloc.first_line << "," << yylloc.first_column << ",extends" << endl; }
	| Input T_FALSE    			{ cout << yylloc.first_line << "," << yylloc.first_column << ",false" << endl; }
	| Input T_IF       			{ cout << yylloc.first_line << "," << yylloc.first_column << ",if" << endl; }
	| Input T_IN       			{ cout << yylloc.first_line << "," << yylloc.first_column << ",in" << endl; }
	| Input T_INT32    			{ cout << yylloc.first_line << "," << yylloc.first_column << ",int32" << endl; }
	| Input T_ISNULL   			{ cout << yylloc.first_line << "," << yylloc.first_column << ",isnull" << endl; }
	| Input T_LET      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",let" << endl; }
	| Input T_NEW      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",new" << endl; }
	| Input T_NOT      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",not" << endl; }
	| Input T_STRING   			{ cout << yylloc.first_line << "," << yylloc.first_column << ",string" << endl; }
	| Input T_THEN     			{ cout << yylloc.first_line << "," << yylloc.first_column << ",then" << endl; }
	| Input T_TRUE     			{ cout << yylloc.first_line << "," << yylloc.first_column << ",true" << endl; }
	| Input T_UNIT     			{ cout << yylloc.first_line << "," << yylloc.first_column << ",unit" << endl; }
	| Input T_WHILE    			{ cout << yylloc.first_line << "," << yylloc.first_column << ",while" << endl; }
	| Input T_OBJ_ID   			{ cout << yylloc.first_line << "," << yylloc.first_column << ",object-identifier," << yylval.sval << endl; free(yylval.sval);}
	| Input T_INT_LIT     	{ cout << yylloc.first_line << "," << yylloc.first_column << ",integer-literal," << yylval.ival << endl; }
	| Input T_TYPE_ID     	{ cout << yylloc.first_line << "," << yylloc.first_column << ",type-identifier," << yylval.sval << endl; free(yylval.sval);}
	| Input T_STRING_LIT    { cout << yylloc.first_line << "," << yylloc.first_column << ",string-literal," << yylval.sval << endl; free(yylval.sval);}
	| Input T_L_BRACE     	{ cout << yylloc.first_line << "," << yylloc.first_column << ",lbrace" << endl; }
	| Input T_R_BRACE     	{ cout << yylloc.first_line << "," << yylloc.first_column << ",rbrace" << endl; }
	| Input T_R_PAR      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",rpar" << endl; }
	| Input T_L_PAR      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",lpar" << endl; }
	| Input T_COLON      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",colon" << endl; }
	| Input T_SEMI_COLON    { cout << yylloc.first_line << "," << yylloc.first_column << ",semicolon" << endl; }
	| Input T_COMMA      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",comma" << endl; }
	| Input T_PLUS      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",plus" << endl; }
	| Input T_MINUS      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",minus" << endl; }
	| Input T_TIMES      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",times" << endl; }
	| Input T_DIV      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",div" << endl; }
	| Input T_POW      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",pow" << endl; }
	| Input T_DOT      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",dot" << endl; }
	| Input T_EQUAL      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",equal" << endl; }
	| Input T_LOWER      		{ cout << yylloc.first_line << "," << yylloc.first_column << ",lower" << endl; }
	| Input T_LEQ      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",lower-equal" << endl; }
	| Input T_GREATER      	{ cout << yylloc.first_line << "," << yylloc.first_column << ",greater" << endl; }
	| Input T_GEQ      			{ cout << yylloc.first_line << "," << yylloc.first_column << ",greater-equal" << endl; }
	| Input T_ASSIGN      	{ cout << yylloc.first_line << "," << yylloc.first_column << ",assign" << endl; }
	| Input T_COMMENTS
;

program :
	class            				{$$ = new ProgramNode($1);}
	| program class  				{$1->addClass($2); $$ = $1;}
;

t_type_id :
  T_TYPE_ID               {string tmp = $1; free($1); $$ = new TypeIdentifierNode(tmp, yylloc.first_column, yylloc.first_line);}
;

t_obj_id :
  T_OBJ_ID                {string tmp = $1; free($1); $$ = new ObjectIdentifierNode(tmp, yylloc.first_column, yylloc.first_line);}
;

t_if :
	T_IF 									{$$ = new PairColLine(yylloc.first_column, yylloc.first_line);}
;

t_while :
	T_WHILE 									{$$ = new PairColLine(yylloc.first_column, yylloc.first_line);}
;

t_let :
	T_LET 									{$$ = new PairColLine(yylloc.first_column, yylloc.first_line);}
;

t_new :
	T_NEW 									{$$ = new PairColLine(yylloc.first_column, yylloc.first_line);}
;

class :
	T_CLASS t_type_id extend T_L_BRACE class-body T_R_BRACE	{if($3){
																														$$ = new ClassNode($2, $5, $3, $2->getCol(), $2->getLine());
																													 }else
																														$$ = new ClassNode($2, $5, NULL, $2->getCol(), $2->getLine());
																													}
;

extend :
														{$$ = NULL;}
	| T_EXTENDS t_type_id			{$$ = $2;}
;

class-body :
														{$$ = new ClassBodyNode();}
	| class-body field				{$1->addField($2); $$ = $1;}
	| class-body method				{$1->addMethod($2); $$ = $1;}
;

field :
	t_obj_id T_COLON type assign T_SEMI_COLON		{if($4)
																								$$ = new FieldNode($1, $3, $4, $1->getCol(), $1->getLine());
																							 else
																								$$ = new FieldNode($1, $3, $1->getCol(), $1->getLine());
																							}
  | t_obj_id T_COLON error T_SEMI_COLON					{delete $1;$$ = NULL;syntax_error++;}
  | error T_COLON type assign T_SEMI_COLON			{delete $3; delete $4;$$ = NULL;syntax_error++;}
;

assign :
														{$$ = NULL;}
	| T_ASSIGN expr						{$$ = $2;}
;

method :
	t_obj_id T_L_PAR formals T_R_PAR T_COLON type block	{$$ = new MethodNode($1, $3, $6, $7, $1->getCol(), $1->getLine());}
;

type :
	t_type_id									{$$ = $1;}
	| T_INT32									{$$ = new TypeIdentifierNode("int32", yylloc.first_column, yylloc.first_line);}
	| T_BOOL									{$$ = new TypeIdentifierNode("bool", yylloc.first_column, yylloc.first_line);}
	| T_STRING								{$$ = new TypeIdentifierNode("string", yylloc.first_column, yylloc.first_line);}
	| T_UNIT									{$$ = new TypeIdentifierNode("unit", yylloc.first_column, yylloc.first_line);}
;

formals :
														{$$ = new FormalsNode();}
	| formal virgul-formals		{$2->insertFormal($1); $$ = $2;}
;

virgul-formals :
																				{$$ = new FormalsNode();}
	| T_COMMA formal virgul-formals				{$3->insertFormal($2); $$ = $3;}
;

formal :
	t_obj_id T_COLON type									{$$ = new FormalNode($1, $3, $1->getCol(), $1->getLine());}
;

block :
	T_L_BRACE expr sc-expr T_R_BRACE			{$3->insertExpr($2); $$ = $3;}
;

sc-expr :
																				{$$ = new BlockNode();}
	| T_SEMI_COLON expr sc-expr						{$3->insertExpr($2); $$ = $3;}
;

expr :
	t_if expr T_THEN expr															{$$ = new ConditionalNode($2, $4, NULL, $1->getCol(), $1->getLine()); delete $1;}
	| t_if expr T_THEN expr T_ELSE expr								{$$ = new ConditionalNode($2, $4, $6, $1->getCol(), $1->getLine()); delete $1;}
	| t_while expr T_DO expr													{$$ = new WhileNode($2, $4, $1->getCol(), $1->getLine()); delete $1;}
	| t_let t_obj_id T_COLON type assign T_IN expr		{$$ = new LetNode($2, $4, $7, $5, $1->getCol(), $1->getLine()); delete $1;}
	| t_obj_id T_ASSIGN expr													{$$ = new AssignNode($1, $3, $1->getCol(), $1->getLine());}
	| T_NOT expr																			{$$ = new UnaryOperatorNode(UnaryOperator::u_op_not, $2, @1.first_column, @1.first_line);}
	| T_MINUS expr																		{$$ = new UnaryOperatorNode(UnaryOperator::u_op_minus, $2, @1.first_column, @1.first_line);}
	| T_ISNULL expr																		{$$ = new UnaryOperatorNode(UnaryOperator::u_op_isnull, $2, @1.first_column, @1.first_line);}
	| expr T_PLUS expr																{$$ = new BinaryOperatorNode(BinaryOperator::b_op_plus, $1, $3, @2.first_column, @2.first_line);}
	| expr T_AND expr																	{$$ = new BinaryOperatorNode(BinaryOperator::b_op_and, $1, $3, @2.first_column, @2.first_line);}
	| expr T_EQUAL expr																{$$ = new BinaryOperatorNode(BinaryOperator::b_op_equal, $1, $3, @2.first_column, @2.first_line);}
	| expr T_LEQ expr																	{$$ = new BinaryOperatorNode(BinaryOperator::b_op_leq, $1, $3, @2.first_column, @2.first_line);}
	| expr T_LOWER expr																{$$ = new BinaryOperatorNode(BinaryOperator::b_op_less, $1, $3, @2.first_column, @2.first_line);}
	| expr T_GEQ expr																	{$$ = new BinaryOperatorNode(BinaryOperator::b_op_less, $3, $1, @2.first_column, @2.first_line);}
	| expr T_GREATER expr															{$$ = new BinaryOperatorNode(BinaryOperator::b_op_leq, $3, $1, @2.first_column, @2.first_line);}
	| expr T_MINUS expr																{$$ = new BinaryOperatorNode(BinaryOperator::b_op_minus, $1, $3, @2.first_column, @2.first_line);}
	| expr T_TIMES expr																{$$ = new BinaryOperatorNode(BinaryOperator::b_op_times, $1, $3, @2.first_column, @2.first_line);}
	| expr T_DIV expr																	{$$ = new BinaryOperatorNode(BinaryOperator::b_op_div, $1, $3, @2.first_column, @2.first_line);}
	| expr T_POW expr																	{$$ = new BinaryOperatorNode(BinaryOperator::b_op_pow, $1, $3, @2.first_column, @2.first_line);}
	| t_obj_id T_L_PAR args T_R_PAR										{$$ = new CallNode($1, $3, NULL, $1->getCol(), $1->getLine());}
	| expr T_DOT t_obj_id T_L_PAR args T_R_PAR				{$$ = new CallNode($3, $5, $1, $3->getCol(), $3->getLine());}
	| t_new t_type_id																	{$$ = new NewNode($2, $1->getCol(), $1->getLine()); delete $1;}
	| t_obj_id																				{$$ = $1;}
	| literal																					{$$ = $1;}
	| T_L_PAR T_R_PAR																	{$$ = new BraceNode(NULL, yylloc.first_column, yylloc.first_line);}
	| T_L_PAR expr T_R_PAR														{$$ = $2;}
	| block																						{$$ = $1;}
;

args :
															{$$ = new ArgsNode();}
	| expr comma-arg						{$2->insertExpr($1); $$ = $2;}
;

comma-arg :
															{$$ = new ArgsNode();}
	| T_COMMA expr comma-arg		{$3->insertExpr($2); $$ = $3;}
;

literal :
	T_INT_LIT										{$$ = new LiteralNode($1, "int32", yylloc.first_column, yylloc.first_line);}
	| T_STRING_LIT							{string tmp = $1; free $1; $$ = new LiteralNode(tmp, "string", yylloc.first_column, yylloc.first_line);}
	| boolean-literal						{$$ = $1;}
;

boolean-literal :
	T_TRUE											{$$ = new LiteralNode("true", "bool", yylloc.first_column, yylloc.first_line);}
	| T_FALSE										{$$ = new LiteralNode("false", "bool", yylloc.first_column, yylloc.first_line);}
;



%%

int main (int argc, char *argv[]){

	if(argc != 2 && argc != 3 && argc != 4){
		cerr << "Usage for only lexer: ./" << argv[0] << " -lex <Source_File>" << endl;
		cerr << "Usage for both lexer and parse: ./" << argv[0] << " -parse <Source_File>" << endl;
		cerr << "Usage for lexer, parse and semantic: ./" << argv[0] << " -check <Source_File>" << endl;
		cerr << "Usage for code generation: ./" << argv[0] << " -llvm <Source_File>" << endl;
		cerr << "Usage for executable generation : ./" << argv[0] << " <Source_File>" << endl;
		cerr << "You can also add -lex to activate the extensions" << endl;
		return -1;
	}

	start_token = START_EX_GEN;
	for(int i = 1; i < argc; ++i){
		if(!strcmp(argv[i], "-lex"))
			start_token = START_LEXICAL;
		else if(!strcmp(argv[i], "-check"))
			start_token = START_SEMANTIC;
		else if(!strcmp(argv[i], "-parse"))
			start_token = START_SYNTAX;
		else if(!strcmp(argv[i], "-llvm"))
			start_token = START_CODE_GEN;
		else if(!strcmp(argv[i], "-ext")){
			// Do nothing for now
		}else if(argv[i][0] == '-'){
			cerr << "Undefined argument" << endl;
			return -1;
		}
	}

	//Insert IO class if needed.
	if(start_token == START_EX_GEN || start_token == START_CODE_GEN || start_token == START_SEMANTIC){
		FILE *io_class = fopen("Libraries/IO.vsop", "r");
		int t = start_token;
		start_token = START_IO;
		if (!io_class) {
		 	cerr << "Could not open IO class" << endl;
			return -1;
		}
		yyin = io_class;
		// parse through the input until there is no more:
		syntax_error = 0;
		do {
			if(yyparse() == 1){
				syntax_error++;
			}
		} while (!feof(yyin));
		yylloc.first_line = 1;
		yylloc.first_column = 0;
		yylloc.last_line = 1;
		yylloc.last_column = 0;
		start_token = t;
		fclose(yyin);
	}

	FILE *myfile = fopen(argv[argc-1], "r");
	file_name = argv[argc-1];
	if (!myfile) {
	 	cerr << "Could not open " << file_name << endl;
		return -1;
	}
	SemanticError::FILE_NAME = file_name;
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	syntax_error = 0;
	do {
		if(yyparse() == 1){
			syntax_error++;
		}
	} while (!feof(yyin));

	fclose(yyin);
	if(syntax_error)
		return -1;

	return semantic_error;
}

void yyerror(const char *s)
{

  int i;
  char sbuf[128];

  if (! yyerror_isinitialized++) yyerror_init();

  if (!strcmp(s, "stack")) return;

  if (errors++ > 10) {
    fprintf(stderr, "Too many errors, aborting");
    exit(errors);
	}

  if ((!strcmp(s, "syntax error") || !strcmp(s, "parse error")) && (yystate>=0 && yystate<=yymaxstate && errtab[yystate].i != 0)){
      if (errtab[yystate].i == 1)
        s = errtab[yystate].u.msg;
      else {
        for(i=1; i <= errtab[yystate].i; i++)
            if(yychar == errtab[yystate].u.p[i].i){
              s = errtab[yystate].u.p[i].u.msg;
              break;
            }

        if(i > errtab[yystate].i)
          s = errtab[yystate].u.p[0].u.msg;
       }
    }

   // Lines to comment after error generation
	 /*if(file_name) fprintf(stderr, "%s:", file_name);
   if (!strcmp(s, "syntax error") || !strcmp(s,"parse error")){
      sprintf(sbuf,"%s (%d;%d)", s, yystate, yychar);
      s = sbuf;
   }
   fprintf(stderr, "%d: # \"%s\": %s\n", yylineno, yytext, s);
   */

   // Lines to comment when doing error generation
	 cerr << file_name << ":" << yylloc.first_line << ":" << yylloc.first_column << ": syntax error" << endl;
	 cerr << s << endl;
}
