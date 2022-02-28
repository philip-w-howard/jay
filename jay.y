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
#include <limits.h>
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
    cSettingsNode*  settings_node;
    cSettingNode*   setting_node;
    cDeclsNode*     decls_node;
    cDeclNode*      decl_node;
    cCodeNode*      code_node;
    cSymbol*        symbol;
    cValueNode*     value;
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
%}

%start  system

%token SYSTEM
%token HEADER
%token TRAILER
%token START
%token END
%token UNITS
%token SETUP
%token STOCK
%token FLOW
%token VAR
%token FUNCTION
%token UPDATE
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
%token SECONDS
%token MINUTES
%token HOURS
%token DAYS
%token YEARS
%token JUNK_TOKEN

%token <symbol>    IDENTIFIER
%token <int_val>   INT_VAL
%token <real_val>  REAL_VAL
%token <code_node> CODE

%type <system_node> system
%type <decls_node> decls
%type <decl_node> decl
%type <decl_node> stock
%type <decl_node> flow
%type <decl_node> setup
%type <decl_node> var
%type <decl_node> func
%type <decl_node> header
%type <decl_node> trailer
%type <settings_node> settings
%type <setting_node> setting
%type <value> value
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
                                { $$ = $1; $$->AddDecl($2); }
    |   decl
                                { $$ = new cDeclsNode($1); }
decl :  stock
                                { $$ = $1; }
    |   flow
                                { $$ = $1; }
    |   setup
                                { $$ = $1; }
    |   var
                                { $$ = $1; }
    |   func
                                { $$ = $1; }
    |   header
                                { $$ = $1; }
    |   trailer
                                { $$ = $1; }

setup : SETUP '{' settings '}'
                                { $$ = new cSetupNode($3); }
stock : STOCK IDENTIFIER '{' settings '}'
                                { $$ = new cStockNode($2, $4); }
flow : FLOW IDENTIFIER '{' settings '}'
                                { $$ = new cFlowNode($2, $4); }
var : VAR IDENTIFIER '{' settings '}'
                                { $$ = new cVarNode($2, $4); }
func : FUNCTION IDENTIFIER CODE 
                                { $$ = new cFuncNode($2, $3); }
header : HEADER CODE 
                                { $$ = new cHeaderNode($2); }
trailer : TRAILER CODE 
                                { $$ = new cTrailerNode($2); }

settings : settings setting
                                { $$ = $1; $$->AddSetting($2); }
    |      setting
                                { $$ = new cSettingsNode($1); }

setting : MIN '=' value ';'
                                { $$ = new cValueSettingNode("min", $3); }
        | MAX '=' value ';'
                                { $$ = new cValueSettingNode("max", $3); }
        | START '=' value ';'
                                { $$ = new cValueSettingNode("start", $3); }
        | END '=' value ';'
                                { $$ = new cValueSettingNode("end", $3); }
        | INITIAL_VAL '=' value ';'
                                { $$ = new cValueSettingNode("initial", $3); }
        | SOURCE '=' IDENTIFIER ';'
                                { $$ = new cIdSettingNode("source", $3); }
        | DESTINATION '=' IDENTIFIER ';'
                                { $$ = new cIdSettingNode("destination", $3); }
        | UPDATE '=' IDENTIFIER ';'
                                { $$ = new cIdSettingNode("update", $3); }
        | UNITS '=' units ';'
                                { } //$$ = new cUnitsNode($3); }
        | error ';'
                                {}
value : INT_VAL
                                { } //$$ = new cIntNode($1); }
        | REAL_VAL
                                { } //$$ = new cRealNode($1); }
        | INFINITE
                                { } //$$ = new cRealNode(DBL_MAX); }
units : MILLISECONDS
                                {}
        | SECONDS
                                {}
        | MINUTES
                                {}
        | HOURS
                                {}
        | DAYS
                                {}
        | YEARS
                                {}
%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cout << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}
