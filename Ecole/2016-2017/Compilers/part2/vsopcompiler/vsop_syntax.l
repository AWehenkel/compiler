%{
using namespace std;
#include <unordered_map>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>
#define YY_DECL extern "C" int yylex()
#include "vsop_grammar.tab.h"
void yyerror(const char *s);
void lexicalError();
char *file_name;
extern int start_token;
/*
ROLE:   This function is used to replace any occurence of sub string into a string.
IN:     text: string, the text to transform.
        search: ref to the old substring to replace.
        replace: ref to the new string replacing search occurences.
OUT     The string where the occurences of serach have been replaced by replace.
*/
string replaceString(string text, string& search, string& replace);

/*
ROLE:   This function is used to replace the escaped character by the correspondent ascii character.
IN:     text: string, the text to transform.
        min: unsigned int, the min value of the ascii code the function is allowed to change.
        max: unsigned int, the max value of the ascii code the function is allowed to change.
OUT:    The string where the escaped sequence have been replaced.
*/
string replaceASCII(string text, unsigned int min, unsigned int max);

//Action performed each time a regex is matched. Here we update the current column and line.
#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line; \
    yylloc.first_column = yylloc.last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc.last_line++; \
            yylloc.last_column = 1; \
        } \
        else { \
            yylloc.last_column++; \
        } \
    }

//Hash table for keywords.
unordered_map<std::string,int> keywords_map ({
     {"and", T_AND},
     {"bool", T_BOOL},
     {"class", T_CLASS},
     {"do", T_DO},
     {"else", T_ELSE},
     {"extends", T_EXTENDS},
     {"false", T_FALSE},
     {"if", T_IF},
     {"in", T_IN},
     {"int32", T_INT32},
     {"isnull", T_ISNULL},
     {"let", T_LET},
     {"new", T_NEW},
     {"not", T_NOT},
     {"string", T_STRING},
     {"then", T_THEN},
     {"true", T_TRUE},
     {"unit", T_UNIT},
     {"while", T_WHILE}});

      //Stack used to keep track of the nested comments.
      stack<YYLTYPE,vector<YYLTYPE> > comment_stack;
%}

hex       [0-9a-fA-F]
esc-seq   b|t|n|r|\"|\\|x{hex}{hex}|\n(" "|\t)*
esc-char  \\{esc-seq}
reg-char  [^\\\"]

ws        	(" "|\t|\n|\r|\f)+
int-lit   	[0-9]+|"0x"{hex}+|"0b"[0-1]+
wrong-int-lit 	"0x"[0-9a-zA-Z]*|"0b"[0-9a-zA-Z]*
type-id   	[A-Z][a-zA-Z0-9_]*
obj-id    	[a-z][a-zA-Z0-9_]*
str-lit   	\"({reg-char}|{esc-char})+\"
str-lit-escape  \"([^\"]|\n|{esc-char})+\"
unterm-str-lit  \"({reg-char}|{esc-char})+
comments  	\/\/.*

%x MULTI_COMMENTS

%%

%{
    if(start_token){
      int to_ret = start_token;
      start_token = 0;
      return to_ret;
    }
%}

\(\* 			{BEGIN MULTI_COMMENTS; comment_stack.push(yylloc);}
<MULTI_COMMENTS>\(\*	{comment_stack.push(yylloc);}
<MULTI_COMMENTS>\*\)	{comment_stack.pop();
			if(comment_stack.empty())
				BEGIN 0;}
<MULTI_COMMENTS><<EOF>>	{yylloc.first_line = comment_stack.top().first_line; yylloc.first_column = comment_stack.top().first_column; comment_stack.pop(); lexicalError();}
<MULTI_COMMENTS>.|\n	{}


{ws}     {}
{obj-id} {
            //Check for keyword.
            unordered_map<std::string,int>::iterator it = keywords_map.find(yytext);
            if(it != keywords_map.end()){
              return it->second;
            }
            yylval.sval = strdup(yytext);
            return T_OBJ_ID;
          }

{str-lit} {

            //Check for invalid characters
            size_t pos = 0;
            int cur = 0;
            int first_line = yylloc.first_line;
            int first_column = yylloc.first_column;
            while(pos < yyleng){
              cur = (int) yytext[pos];
              if((yytext[pos] == '\n' && pos==0) || (pos > 0 && yytext[pos-1] != '\\' && yytext[pos] == '\n') || (cur > 126 || cur < 32 && cur!=8 && cur != 9 && cur != 10 & cur != 13))
                lexicalError();
              else if (pos > 0 && yytext[pos-1] == '\\' && yytext[pos] == '\n'){
                yylloc.first_line++;
                yylloc.first_column = 0;
              }
              yylloc.first_column++;
              pos++;
            }
            yylloc.first_line = first_line;
            yylloc.first_column = first_column;

            string text (yytext);
            text = replaceASCII(text, 32, 126);
            vector<string> to_replace = {"\\b", "\\t", "\\n", "\\r"};
            vector<string> replacor = {"\\x08", "\\x09", "\\x0a", "\\x0d"};
            vector<string>::iterator it_replacor = replacor.begin();
            for(vector<string>::iterator it = to_replace.begin(); it != to_replace.end(); it++)
              text = replaceString(text, *it, *it_replacor++);

            //Multi-line strings
            pos = 0;
            size_t begin = 0;
            string search("\\\n");
            string copy;
            while((pos = text.find(search, pos)) != string::npos){
              pos++;
              copy.append(text, begin, pos-begin-1);
              while(text[++pos] == '\t' || text[pos] == ' ');
              begin = pos;
            }
            copy.append(text, begin, pos-begin);
            text = copy;

            char *to_rtn = (char*) malloc(sizeof(char)*(text.length()+1));
            if(to_rtn == NULL){
              cerr << "Allocation error" << endl;
              return -1;
            }
            strcpy(to_rtn, text.c_str());
            yylval.sval = to_rtn;
            return T_STRING_LIT;
          }

{str-lit-escape} {
                  size_t pos = 0;
                  while(yytext[pos] != '\0'){
                    if(yytext[pos] == '\\' && yytext[pos+1] != 'n' && yytext[pos+1] != 't' && yytext[pos+1] != 'r' && yytext[pos+1] != 'b')
                      lexicalError();
                    else if(yytext[pos] == '\n'){
                      yylloc.first_line++;
                      yylloc.first_column = 0;
                    }
                    yylloc.first_column++;
                    pos++;
                  }
                }

{unterm-str-lit}  {
                    lexicalError();
                  }

{int-lit} {
            int base = 10;
            if(yytext[1] != '\0' && yytext[0] == '0'){
              if(yytext[1] == 'x')
                base = 16;
              else if(yytext[1] == 'b'){
                base = 2;
                yytext = yytext+2;
              }
            }
            yylval.ival = strtol(yytext, NULL, base);
            return T_INT_LIT;
          }


{wrong-int-lit} lexicalError();


{type-id} {
            yylval.sval = strdup(yytext);
            return T_TYPE_ID;
          }

{comments}  {  }

"{"            return T_L_BRACE;
"}"            return T_R_BRACE;
")"            return T_R_PAR;
"("            return T_L_PAR;
":"            return T_COLON;
";"            return T_SEMI_COLON;
","            return T_COMMA;
"+"            return T_PLUS;
"-"            return T_MINUS;
"*"            return T_TIMES;
"/"            return T_DIV;
"^"            return T_POW;
"."            return T_DOT;
"="            return T_EQUAL;
"<"            return T_LOWER;
"<="           return T_LEQ;
"<-"           return T_ASSIGN;
.              {lexicalError();};
%%


string replaceString(string text, string& search, string& replace){
	size_t pos = 0;
	while((pos = text.find(search, pos)) != string::npos) {
         text.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return text;
}

string replaceASCII(string text, unsigned int min, unsigned int max){
  size_t pos = 0;
  int replacement;
  char number[2];
  stringstream ss;
  while((pos = text.find("\\x", pos)) != string::npos){
    number[0] = text[pos+2];
    number[1] = text[pos+3];
    replacement = strtol(number, NULL, 16);
    if(replacement >= min && replacement <= max){
      string to_replace;
      ss << (char) replacement;
      ss >> to_replace;
      text.replace(pos, 4, to_replace);
      pos += 1;
    }
    else
      pos += 4;
  }
  return text;
}

void lexicalError(){
  cerr << file_name << ":" << yylloc.first_line << ":" << yylloc.first_column << ": lexical error" << endl;
  exit(1);
}
