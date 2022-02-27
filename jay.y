%{
//**************************************
// pascal.y
//
// Parser definition file. bison uses this file to generate the parser.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <iostream>
#include "lex.h"
#include "astnodes.h"

%}

%locations

 /* union defines the type for lexical values */
%union{
    int             int_val;
    double          real_val;
    cAstNode*       ast_node;
    cSystemNode*    system_node;
    cDeclsNode*     decls_node;
    cCodeNode*      code_node;
    cSymbol*        symbol;
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
%}

%start  system

%token SYSTEM
%token START
%token END
%token UNITS
%token STOCK
%token FLOW
%token VAR
%token FUNCTION
%token SOURCE
%token DESTINATION
%token MIN
%token MAX
%token INFINITE
%token INITIAL_VAL
%token TYPE
%token DISCRETE
%token CONTINUOUS
%token MILLISECONDS
%token SECOND
%token HOURS
%token DAYS
%token YEARS
%token JUNK_TOKEN

%token <symbol>    IDENTIFIER
%token <int_val>   INT_VAL
%token <real_val>  REAL_VAL
%token <code_node> CODE

%type <decls_node> decls
%type <system_node> system
%%

system: SYSTEM IDENTIFIER '{' decls '}'
                                { $$ = new cSystemNode($2, $4);
                                  yyast_root = $$;
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
decls : decls decl
                                {}
    |   decl
                                {}
decl :  stock
                                {}
    |   flow
                                {}
    |   var
                                {}
    |   func
                                {}

stock : STOCK IDENTIFIER '{' settings '}'
                                {}
flow : FLOW IDENTIFIER '{' settings '}'
                                {}
var : VAR IDENTIFIER '{' settings '}'
                                {}
func : FUNCTION IDENTIFIER CODE 
                                {}

settings : settings setting
                                {}
    |      setting
                                {}

setting : MIN '=' value ';'
                                {}
        | MAX '=' value ';'
                                {}
        | START '=' value ';'
                                {}
        | END '=' value ';'
                                {}
        | INITIAL_VAL '=' value ';'
                                {}
        | SOURCE '=' IDENTIFIER ';'
                                {}
        | DESTINATION '=' IDENTIFIER ';'
                                {}
        | FUNCTION '=' IDENTIFIER ';'
                                {}
        | error ';'
                                {}
value : INT_VAL
                                {}
        | REAL_VAL
                                {}
        | INFINITE
                                {}

%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cout << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}
