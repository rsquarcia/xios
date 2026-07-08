%option noyywrap
%{
extern "C"
{
  int yylex(void);
}
#undef YY_INPUT
#define YY_INPUT(b, r, s) \
    { \
        size_t num_bytes_read = r; \
        int result = readInputForLexer(b, &num_bytes_read, s); \
        r = num_bytes_read; \
        result; \
    }
#include <string>
int readInputForLexer(char* buffer, size_t* numBytesRead, size_t maxBytesToRead);
#include "filter_expr_node.hpp"
#include "yacc_parser.hpp"
%}

white    [ \t]+

digit    [0-9]
integer  {digit}+
exponant [eE][+-]?{integer}
real     {integer}("."{integer})?{exponant}?
id       [a-zA-Z][a-zA-Z0-9_]*
average  @{id}
var      \${id}

%x BRACKET

%%

{white}   { /* We ignore white characters */ }


<BRACKET>{integer} {
                      yylval.str = new std::string(yytext);
                      return INDEX;
                    }    


<BRACKET>{id} {
                      yylval.str = new std::string(yytext);
                      return ARGID;
                    }    

<BRACKET>{white}   { /* ignore */ }

{real}    {
            yylval.str = new std::string(yytext);
            return NUMBER;
          }

{average} {
            yylval.str = new std::string(yytext + 1);
            return AVERAGE;
          }

{var}     {
            yylval.str = new std::string(yytext + 1);
            return VAR;
          }

{id}      {
            yylval.str = new std::string(yytext);
            return ID;
          }          

     
                 

"+"  return PLUS;
"-"  return MINUS;

"*"  return TIMES;
"/"  return DIVIDE;

"^"  return POWER;

"==" return EQ;
"<"  return LT;
">"  return GT;
"<=" return LE;
">=" return GE;
"/=" return NE;
"?" return QUESTION_MARK;
":" return COLON;
"("  return LEFT_PARENTHESIS;
")"  return RIGHT_PARENTHESIS;
"," return COMMA;

"[" { BEGIN(BRACKET); return LEFT_BRACKET; }
<BRACKET>"]" { BEGIN(INITIAL); return RIGHT_BRACKET; }


"\0" return END;
