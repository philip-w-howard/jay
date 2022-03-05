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
#include <limits>
#include "lex.h"
#include "astnodes.h"

bool g_semanticErrorHappened = false;

%}

%locations

 /* union defines the type for lexical values */
%union{
    int                 int_val;
    double              real_val;
    cAstNode*           ast_node;
    cSystemsNode*       systems_node;
    cSystemNode*        system_node;
    cSettingsNode*      settings_node;
    cSettingNode*       setting_node;
    cDeclsNode*         decls_node;
    cDeclNode*          decl_node;
    cCodeNode*          code_node;
    cProgramNode*       program_node;
    cSimulationNode*    sim_node;
    cSystemsListNode*   syslist_node;
    cSysVarNode*        sysvar_node;
    cSysVarsNode*       sysvars_node;
    cSymbol*            symbol;
    cValueNode*         value;
    cTypeNode*          type;
    cUnitsNode*         units;
    std::string*        string;
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
%}

%start  program

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
%token DELTA
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
%token SIMULATION
%token SYSTEMS
%token LOG
%token CSV

%token JUNK_TOKEN

%token <symbol>    IDENTIFIER
%token <int_val>   INT_VAL
%token <real_val>  REAL_VAL
%token <code_node> CODE
%token <string>    STR_CONST

%type <program_node> program
%type <systems_node> systems
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
%type <type> type
%type <units> units

%type <sim_node> simulation
%type <decls_node> simdecls
%type <decl_node> simdecl
%type <decl_node> log
%type <decl_node> csv
%type <sysvars_node> sysvars
%type <sysvar_node> sysvar
%type <syslist_node> systemlist

%%

program: systems simulation
                                { 
                                  $$ = new cProgramNode($1, $2);
                                  yyast_root = $$;
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
systems: systems system
                                { $$ = $1; $$->AddSystem($2); }
    |   system
                                { $$ = new cSystemsNode($1); }

system: SYSTEM IDENTIFIER '{' decls '}'
                                { $$ = new cSystemNode($2, $4); }
simulation: SIMULATION '{' simdecls '}'
                                { $$ = new cSimulationNode($3); }
    |   /* empty */
                                { $$ = nullptr; }
decls : decls decl
                                { $$ = $1; $$->AddDecl($2); }
    |   decl
                                { $$ = new cDeclsNode($1); }
simdecls : simdecls simdecl
                                { $$ = $1; $$->AddDecl($2); }
    |   simdecl
                                { $$ = new cDeclsNode($1); }
decl :  stock
                                { $$ = $1; }
    |   flow
                                { $$ = $1; }
    |   var
                                { $$ = $1; }
    |   func
                                { $$ = $1; }
    |   header
                                { $$ = $1; }
    |   trailer
                                { $$ = $1; }

simdecl :  systemlist
                                { $$ = $1; }
    |   setup
                                { $$ = $1; }
    |   log
                                { $$ = $1; }
    |   csv
                                { $$ = $1; }
    |   trailer
                                { $$ = $1; }

setup : SETUP '{' settings '}'
                                { $$ = new cSetupNode($3); }
stock : STOCK IDENTIFIER ':' type '{' settings '}'
                                { $$ = new cStockNode($2, $4, $6); }
flow : FLOW IDENTIFIER ':' type '{' settings '}'
                                { $$ = new cFlowNode($2, $4, $6); }
var : VAR IDENTIFIER ':' type '{' settings '}'
                                { $$ = new cVarNode($2, $4, $6); }
func : FUNCTION IDENTIFIER ':' type CODE 
                                { $$ = new cFuncNode($2, $4, $5); }
header : HEADER CODE 
                                { $$ = new cHeaderNode($2); }
trailer : TRAILER CODE 
                                { $$ = new cTrailerNode($2); }
log : LOG IDENTIFIER ':' INT_VAL '{' settings '}'
                                { $$ = new cOutputListNode($2, $4, $6, "log"); }
csv : CSV IDENTIFIER ':' INT_VAL '{' settings '}'
                                { $$ = new cOutputListNode($2, $4, $6, "ast"); }
systemlist : SYSTEMS '{' sysvars '}'
                                { $$ = new cSystemsListNode($3); }
sysvars : sysvars sysvar
                                { $$ = $1; $$->AddSystem($2); }
        | sysvar
                                { $$ = new cSysVarsNode($1); }
sysvar : IDENTIFIER IDENTIFIER ';'
                                { $$ = new cSysVarNode($1, $2); }
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
        | DELTA '=' IDENTIFIER ';'
                                { $$ = new cIdSettingNode("delta", $3); }
        | UNITS '=' units ';'
                                {  $$ = $3; }
        | IDENTIFIER '.' IDENTIFIER STR_CONST ';'
                                { $$ = new cOutputNode($1, $3, $4); }
        | error ';'
                                { $$ = nullptr; }
value : INT_VAL
                                { $$ = new cIntValNode($1); }
        | REAL_VAL
                                { $$ = new cRealValNode($1); }
        | INFINITE
                                { $$ = new cRealValNode(std::numeric_limits<double>::infinity()); }
units : MILLISECONDS
                                { $$ = new cUnitsNode("milliseconds"); }
        | SECONDS
                                { $$ = new cUnitsNode("seconds"); }
        | MINUTES
                                { $$ = new cUnitsNode("minutes"); }
        | HOURS
                                { $$ = new cUnitsNode("hours"); }
        | DAYS
                                { $$ = new cUnitsNode("days"); }
        | YEARS
                                { $$ = new cUnitsNode("years"); }
type : CONTINUOUS
                                { $$ = new cTypeNode("continuous"); }
        | DISCRETE
                                { $$ = new cTypeNode("discrete"); }
%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cout << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}

// Function that gets called when a semantic error happens
void SemanticParseError(std::string error)
{
    std::cout << "ERROR: " << error << " on line "
        << yylineno << "\n";
    g_semanticErrorHappened = true;
    yynerrs++;
}

