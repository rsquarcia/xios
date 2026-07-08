%{
#include "filter_expr_node.hpp"
#include "scalar_expr_node.hpp" 
#include <string>
#include <iostream>
#include "exception.hpp"

using namespace std;
using namespace xios;

extern "C"
{
  int yyparse(void);
  int yylex(void);
  int yyerror(const char *s);
}

  std::vector<IFilterExprNode*>* parsed;
  std::string globalInputText;
  size_t globalReadOffset = 0;

  int readInputForLexer(char* buffer, size_t* numBytesRead, size_t maxBytesToRead)
  {
    size_t numBytesToRead = maxBytesToRead;
    size_t bytesRemaining = globalInputText.length()-globalReadOffset;
    size_t i;
    if (numBytesToRead > bytesRemaining) numBytesToRead = bytesRemaining;
    for (i = 0; i < numBytesToRead; i++) buffer[i] = globalInputText.c_str()[globalReadOffset + i];
    *numBytesRead = numBytesToRead;
    globalReadOffset += numBytesToRead;
    return 0;
  }
%}

%union
{
  std::string* str;
  xios::IScalarExprNode* scalarNode;
  xios::IFilterExprNode* filterNode;
  std::vector<xios::IExprNode>* filterNodeList;                      
  std::vector<xios::IFilterExprNode*>* exprList;   
  xios::SArg* arg;
};


%token <str> NUMBER
%token <str> INDEX
%token <str> ARGID
%token <str> VAR ID AVERAGE
%token PLUS MINUS TIMES DIVIDE POWER
%token EQ LT GT LE GE NE
%token LEFT_PARENTHESIS RIGHT_PARENTHESIS
%token LEFT_BRACKET RIGHT_BRACKET
%token COMMA
%token QUESTION_MARK COLON
%token <str> END

%nonassoc QUESTION_MARK COLON
%left EQ LT GT LE GE NE
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc NEG
%right POWER

%type <scalarNode> Expression
%type <filterNode> Field_expr
%type <filterNodeList> Field_arg_list
%type <exprList> Line Expr_list
%type <arg> Arg
%start Line
%%


Line:
     END            { /* Nothing to do */ }
   | Expr_list END { parsed = $1; }
  ;

Expression:
            NUMBER { $$ = new CScalarValExprNode(*$1); delete $1; }
          | VAR    { $$ = new CScalarVarExprNode(*$1); delete $1; }
          | Expression PLUS Expression   { $$ = new CScalarOpExprNode("add", {$1, $3}); }
          | Expression MINUS Expression  { $$ = new CScalarOpExprNode("minus", {$1, $3}); }
          | Expression TIMES Expression  { $$ = new CScalarOpExprNode("mult", {$1, $3}); }
          | Expression DIVIDE Expression { $$ = new CScalarOpExprNode("div", {$1, $3}); }
          | MINUS Expression %prec NEG   { $$ = new CScalarOpExprNode("neg", {$2}); }
          | Expression POWER Expression  { $$ = new CScalarOpExprNode("pow", {$1, $3}); }
          | Expression EQ Expression  { $$ = new CScalarOpExprNode("eq", {$1, $3}); }
          | Expression LT Expression  { $$ = new CScalarOpExprNode("lt", {$1, $3}); }
          | Expression GT Expression  { $$ = new CScalarOpExprNode("gt", {$1, $3}); }
          | Expression LE Expression  { $$ = new CScalarOpExprNode("le", {$1, $3}); }
          | Expression GE Expression  { $$ = new CScalarOpExprNode("ge", {$1, $3}); }
          | Expression NE Expression  { $$ = new CScalarOpExprNode("ne", {$1, $3}); }
          | Expression QUESTION_MARK Expression COLON Expression {$$ = new CScalarOpExprNode("cond", {$1, $3, $5});} 
          | LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS    { $$ = $2; }
          ;

Field_expr:
            ID      { $$ = new CFilterFieldExprNode(*$1); delete $1; }
          | AVERAGE { $$ = new CFilterTemporalFieldExprNode(*$1); delete $1; }
          | Field_expr PLUS Field_expr   { $$ = new CFilterOpExprNode("add", { IExprNode($1), IExprNode($3) }); }
          | Field_expr MINUS Field_expr  { $$ = new CFilterOpExprNode("minus", { IExprNode($1), IExprNode($3) }); }
          | Field_expr TIMES Field_expr  { $$ = new CFilterOpExprNode("mult", { IExprNode($1), IExprNode($3) }); }
          | Field_expr DIVIDE Field_expr { $$ = new CFilterOpExprNode("div", { IExprNode($1), IExprNode($3) }); }
          | MINUS Field_expr %prec NEG   { $$ = new CFilterOpExprNode("neg", {IExprNode($2)}); }
          | Field_expr POWER Field_expr  { $$ = new CFilterOpExprNode("pow", { IExprNode($1), IExprNode($3) }); }
          | Field_expr EQ Field_expr { $$ = new CFilterOpExprNode("eq", { IExprNode($1), IExprNode($3) }); }
          | Field_expr LT Field_expr { $$ = new CFilterOpExprNode("lt", { IExprNode($1), IExprNode($3) }); }
          | Field_expr GT Field_expr { $$ = new CFilterOpExprNode("gt", { IExprNode($1), IExprNode($3) }); }
          | Field_expr LE Field_expr { $$ = new CFilterOpExprNode("le", { IExprNode($1), IExprNode($3) }); }
          | Field_expr GE Field_expr { $$ = new CFilterOpExprNode("ge", { IExprNode($1), IExprNode($3) }); }
          | Field_expr NE Field_expr { $$ = new CFilterOpExprNode("ne", { IExprNode($1), IExprNode($3) }); }
          | LEFT_PARENTHESIS Field_expr RIGHT_PARENTHESIS	{ $$ = $2; }
          | Expression QUESTION_MARK Expression COLON Field_expr {$$ = new CFilterOpExprNode("cond",{ IExprNode($1), IExprNode($3), IExprNode($5) });}
          | Expression QUESTION_MARK Field_expr COLON Expression {$$ = new CFilterOpExprNode("cond",{ IExprNode($1), IExprNode($3), IExprNode($5) });}
          | Expression QUESTION_MARK Field_expr COLON Field_expr {$$ = new CFilterOpExprNode("cond",{ IExprNode($1), IExprNode($3), IExprNode($5) });}
          | Field_expr QUESTION_MARK Expression COLON Expression {$$ = new CFilterOpExprNode("cond",{ IExprNode($1), IExprNode($3), IExprNode($5) });}
          | Field_expr QUESTION_MARK Expression COLON Field_expr {$$ = new CFilterOpExprNode("cond",{ IExprNode($1), IExprNode($3), IExprNode($5) });}
          | Field_expr QUESTION_MARK Field_expr COLON Expression {$$ = new CFilterOpExprNode("cond",{ IExprNode($1), IExprNode($3), IExprNode($5) });}
          | Field_expr QUESTION_MARK Field_expr COLON Field_expr {$$ = new CFilterOpExprNode("cond",{ IExprNode($1), IExprNode($3), IExprNode($5) });}
          | Field_expr PLUS Expression   { $$ = new CFilterOpExprNode("add", { IExprNode($1), IExprNode($3) }); }
          | Expression PLUS Field_expr   { $$ = new CFilterOpExprNode("add", { IExprNode($1), IExprNode($3) }); }
          | Field_expr MINUS Expression  { $$ = new CFilterOpExprNode("minus", { IExprNode($1), IExprNode($3) }); }
          | Expression MINUS Field_expr  { $$ = new CFilterOpExprNode("minus", { IExprNode($1), IExprNode($3) }); }
          | Field_expr TIMES Expression  { $$ = new CFilterOpExprNode("mult", { IExprNode($1), IExprNode($3) }); }
          | Expression TIMES Field_expr  { $$ = new CFilterOpExprNode("mult", { IExprNode($1), IExprNode($3) }); }
          | Field_expr DIVIDE Expression { $$ = new CFilterOpExprNode("div", { IExprNode($1), IExprNode($3) }); }
          | Expression DIVIDE Field_expr { $$ = new CFilterOpExprNode("div", { IExprNode($1), IExprNode($3) }); }
          | Field_expr POWER Expression  { $$ = new CFilterOpExprNode("pow", { IExprNode($1), IExprNode($3) }); }
          | Field_expr EQ Expression { $$ = new CFilterOpExprNode("eq", { IExprNode($1), IExprNode($3) }); }
          | Expression EQ Field_expr { $$ = new CFilterOpExprNode("eq", { IExprNode($1), IExprNode($3) }); }
          | Field_expr LT Expression { $$ = new CFilterOpExprNode("lt", { IExprNode($1), IExprNode($3) }); }
          | Expression LT Field_expr { $$ = new CFilterOpExprNode("lt", { IExprNode($1), IExprNode($3) }); }
          | Field_expr GT Expression { $$ = new CFilterOpExprNode("gt", { IExprNode($1), IExprNode($3) }); }
          | Expression GT Field_expr { $$ = new CFilterOpExprNode("gt", { IExprNode($1), IExprNode($3) }); }
          | Field_expr LE Expression { $$ = new CFilterOpExprNode("le", { IExprNode($1), IExprNode($3) }); }
          | Expression LE Field_expr { $$ = new CFilterOpExprNode("le", { IExprNode($1), IExprNode($3) }); }
          | Field_expr GE Expression { $$ = new CFilterOpExprNode("ge", { IExprNode($1), IExprNode($3) }); }
          | Expression GE Field_expr { $$ = new CFilterOpExprNode("ge", { IExprNode($1), IExprNode($3) }); }
          | Field_expr NE Expression { $$ = new CFilterOpExprNode("ne", { IExprNode($1), IExprNode($3) }); }
          | Expression NE Field_expr { $$ = new CFilterOpExprNode("ne", { IExprNode($1), IExprNode($3) }); }
          | ID LEFT_PARENTHESIS Field_arg_list RIGHT_PARENTHESIS Arg { $$ = new CFilterOpExprNode(*$1, *$3, *$5); delete $1; delete $3;}
          | ID LEFT_PARENTHESIS RIGHT_PARENTHESIS Arg { $$ = new CFilterOpExprNode(*$1, std::vector<IExprNode>(), *$4); delete $1;}
          ;

  Field_arg_list:
            Field_expr 
            { 
              $$ = new std::vector<IExprNode>{$1};
            }
          | Expression 
            { 
              $$ = new std::vector<IExprNode>{$1};
            }
          | Field_expr COMMA Field_arg_list
            { 
              $3->insert($3->begin(), IExprNode($1));
              $$ = $3;
            }
          | Expression COMMA Field_arg_list
           {
            $3->insert($3->begin(), IExprNode($1));
              $$ = $3;
           }
          ;
  
  Expr_list:
            Field_expr
            {
              $$ = new std::vector<IFilterExprNode*>{$1};
            }
          | Field_expr COMMA Expr_list
            {
              $3->insert($3->begin(), $1);
              $$ = $3;

            }
          ;

Arg:
      LEFT_BRACKET INDEX RIGHT_BRACKET {
          $$ = new SArg(SArg::Type::Positional, atoi($2->c_str()));
          delete $2;
      }
    | LEFT_BRACKET ARGID RIGHT_BRACKET {
          $$ = new SArg(SArg::Type::Named, 0, *$2);
          delete $2;
      }
    | /* empty */ {
          $$ = new SArg();
      }
    ;
      




%%

extern "C"
{
  int yyerror(const char *s)
  {
    ERROR("int yyerror(const char *s)", << "Parsing error: " << s << endl);
  }
}

namespace xios
{
  std::vector<IFilterExprNode*>* parseExpr(const string& strExpr)
  {
    globalInputText = strExpr;
    globalReadOffset = 0;
    yyparse();
    return parsed;
  }
}

