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
    cProgramNode*   program_node;
    cBlockNode*     block_node;
    cStmtsNode*     stmts_node;
    cStmtNode*      stmt_node;
    cExprNode*      expr_node;
    cFuncDeclNode*  func_node;
    cProcDeclNode*  proc_node;
    cFuncExprNode*  funccall_node;
    cSymbol*        symbol;
    cSymbolTable::symbolTable_t*  sym_table;
    cDeclsNode*     decls_node;
    cDeclNode*      decl_node;
    cVarExprNode*   varref_node;
    cExprListNode*  exprList_node;
    cIdListNode*    idList_node;
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
%}

%start  program

%token PROGRAM PROCEDURE FUNCTION FORWARD
%token DECLARE OPEN CLOSE
%token WRITE
%token WHILE IF THEN ELSE REPEAT UNTIL
%token FOR DO TO DOWNTO
%token CONST TYPE VAR
%token RECORD ARRAY OF
%token NIL
%token JUNK_TOKEN

%token <symbol>    IDENTIFIER
%token <symbol>    TYPE_ID
%token <int_val>   INT_VAL
%token <real_val>  REAL_VAL
%token <int_val>   AND
%token <int_val>   OR
%token <int_val>   NOT
%token <int_val>   DIV
%token <int_val>   MOD
%token <int_val>   NOT_EQUAL
%token <int_val>   LE
%token <int_val>   GE
%token <int_val>   ASSIGN

%type <program_node> program
%type <symbol> header
%type <block_node> block
%type <symbol> type
%type <decls_node> decls
%type <decls_node> constdecls
%type <decls_node> constdecl
%type <expr_node> constant
%type <decls_node> typedecls
%type <decls_node> typedecl
%type <decl_node>  singleType
/* %type <decls_node> rangeList */
/* %type <decl_node>  range */
%type <decls_node>  goodvar
%type <decls_node>  onevar
/* %type <decls_node> recorddef */
%type <decls_node> vardecls
%type <decls_node> vardecl;
%type <decls_node> procdecls
%type <decl_node> procdecl
%type <decls_node> paramSpec
%type <decls_node> parlist
%type <idList_node> idlist
%type <funccall_node> func_call
%type <func_node>  funcProto
%type <func_node>  funcHeader
%type <proc_node>  procHeader
%type <stmts_node> statements
%type <stmt_node> statement
%type <expr_node> expr
%type <expr_node> oneExpr
%type <expr_node> addit
%type <expr_node> term
%type <expr_node> fact
%type <varref_node> variable
%type <symbol> varpart
%type <exprList_node> exprList
/* %type <sym_table> recHeader */
%type <sym_table> declHeader
%%

program: header block '.'
                                { $$ = new cProgramNode($1, $2);
                                  yyast_root = $$;
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
header: PROGRAM IDENTIFIER ';'
                                {  g_symbolTable.IncreaseScope();
                                   $$ = $2; 
                                }
declHeader: DECLARE
                                { $$ = g_symbolTable.IncreaseScope(); }
block:  declHeader decls OPEN statements CLOSE
                                { $$ = new cBlockNode($2, $4); 
                                       g_symbolTable.DecreaseScope();
                                }

    | OPEN statements CLOSE
                                { $$ = new cBlockNode(nullptr, $2); }

decls: constdecls typedecls vardecls procdecls
                                { 
                                  if ($1 != nullptr || $2 != nullptr ||
                                      $3 != nullptr || $4 != nullptr)
                                  {
                                    $$ = new cDeclsNode();
                                    $$->AddDecls($1);
                                    $$->AddDecls($2);
                                    $$->AddDecls($3);
                                    $$->AddDecls($4);
                                  } else {
                                    $$ = nullptr;
                                  }
                                }
constdecls: CONST constdecl ';'
                                { $$ = $2; }
        | /*empty */
                                { $$ = nullptr; }
constdecl: constdecl ';' IDENTIFIER '=' constant
                                { $$ = $1;
                                  $$->AddDecl(new cConstDeclNode($3, $5)); 
                                }
        |  IDENTIFIER '=' constant 
                                { $$ = new cDeclsNode(new cConstDeclNode($1, $3)); }
        | constdecl error ';'
                                {}
typedecls: TYPE typedecl
                                { $$ = $2; }
        | /*empty */
                                { $$ = nullptr; }
typedecl: typedecl singleType
                                { $$ = $1; 
                                  $$->AddDecl( $2 );
                                }
        |  singleType
                                { $$ = new cDeclsNode( $1 ); }
        |  error ';'
                                {}
singleType:  IDENTIFIER '=' TYPE_ID INT_VAL ';'
                                { $$ = new cBaseTypeNode($1, $3, $4); }
/*
        |    IDENTIFIER '=' recHeader recorddef ';'
                                { $$ = new cRecordDeclNode($3, $4, $1); }
        |    IDENTIFIER '=' ARRAY '[' rangeList ']' OF type ';'
                                { $$ = new cArrayDeclNode($1, $5, $8); }

rangeList: rangeList ',' range
                                { $$ = $1;
                                  $$->AddDecl( $3 );
                                }
        |  range
                                { $$ = new cDeclsNode( $1 ); }
range: INT_VAL '.' '.' INT_VAL
                                { $$ = new cRangeDeclNode($1, $4); }

*/
vardecls: VAR vardecl
                                { $$ = $2; } 
        | /* empty */
                                { $$ = nullptr; }
vardecl: vardecl onevar
                                { $$ = $1;
                                  $$->AddDecls($2);
                                }
        | onevar
                                { $$ = $1; }
onevar: goodvar ';'
                                { $$ = $1; }
        | error ';'
                                { $$ = nullptr; }
goodvar: idlist ':' type
                                { $$ = new cVarDeclsNode($1, $3); }
procdecls: procdecls procdecl
                                { if ($1 == nullptr)
                                    $$ = new cDeclsNode($2);
                                  else {
                                    $$ = $1;
                                    $$->AddDecl($2);
                                  }
                                }
        | /* empty */
                                { $$ = nullptr; }

procdecl: procHeader paramSpec ';' block ';'
                                {
                                    $1->AddParams($2);
                                    $1->AddBlock($4);
                                    $$ = $1;
                                    g_symbolTable.DecreaseScope();
                                }
        |  procHeader paramSpec ';' FORWARD ';'
                                {
                                    $1->AddParams($2);
                                    $1->AddBlock(nullptr);
                                    $$ = $1;
                                    g_symbolTable.DecreaseScope();
                                }
        |  funcProto ';' block ';'
                                {
                                    $1->AddBlock($3);
                                    $$ = $1;
                                    g_symbolTable.DecreaseScope();
                                }
        |  funcProto ';' FORWARD ';'
                                {
                                    $1->AddBlock(nullptr);
                                    $$ = $1;
                                    g_symbolTable.DecreaseScope();
                                }
        |  error ';' block ';'
                                { $$ = nullptr; }
        |  error ';' FORWARD ';'
                                { 
                                    $$ = nullptr; 
                                    g_symbolTable.DecreaseScope();
                                }
procHeader: PROCEDURE IDENTIFIER 
                                { $$ = new cProcDeclNode($2);
                                  g_symbolTable.IncreaseScope();
                                }
funcHeader: FUNCTION IDENTIFIER
                                { $$ = new cFuncDeclNode($2);
                                  g_symbolTable.IncreaseScope();
                                }
funcProto: funcHeader paramSpec ':' type
                                { $$ = $1;
                                    $1->AddParams($2);
                                    $$->AddType($4);
                                }
paramSpec: '(' parlist ')'
                                { $$ = $2; }
        | /* empty */
                                { $$ = nullptr; }

idlist: idlist ',' IDENTIFIER
                                { $$ = $1; $$->AddId($3); }
    |    IDENTIFIER
                                { $$ = new cIdListNode($1); }

parlist: parlist ';' VAR idlist ':' type 
                                { $$ = $1; 
                                  $$->AddDecls(new cVarDeclsNode($4, $6));
                                }
    |    parlist ';' idlist ':' type 
                                { $$ = $1; 
                                  $$->AddDecls(new cVarDeclsNode($3, $5));
                                }
    |    VAR idlist ':' type
                                { $$ = new cVarDeclsNode($2, $4); }
    |    idlist ':' type
                                { $$ = new cVarDeclsNode($1, $3); }
type: TYPE_ID
                                { $$ = $1; }
 /*
recHeader: RECORD
                                { $$ = g_symbolTable.IncreaseScope(); }
recorddef: vardecl CLOSE
                                { $$ = $1; g_symbolTable.DecreaseScope();  }
 */
constant: INT_VAL
                                { $$ = new cIntExprNode($1); }
    |   '-' INT_VAL
                                { $$ = new cUnaryExprNode('-', 
                                        new cIntExprNode($2)); }
    |   REAL_VAL
                                { $$ = new cRealExprNode($1); }
    |   '-' REAL_VAL
                                { $$ = new cUnaryExprNode('-', 
                                        new cRealExprNode($2));
                                }

statements: statements statement
                                { $$ = $1; $$->AddStmt($2); }
    |   statement
                                { $$ = new cStmtsNode($1); }

statement: variable ASSIGN expr ';'
                                { $$ = new cAssignNode($1, $3); }
    |   IF expr THEN statement
                                { $$ = new cIfNode($2, $4, nullptr); }
    |   IF expr THEN statement ELSE statement
                                { $$ = new cIfNode($2, $4, $6); }
/*
    |   REPEAT statements UNTIL expr ';'
                                {}
*/
    |   WHILE expr DO statement
                                { $$ = new cWhileNode($2, $4); }
    |   FOR IDENTIFIER ASSIGN expr TO expr DO statement
                                {}
    |   FOR IDENTIFIER ASSIGN expr DOWNTO expr DO statement
                                {}
    |   IDENTIFIER '(' exprList ')' ';'
                                { $$ = new cProcCallNode($1, $3); }
    |   IDENTIFIER ';'
                                { $$ = new cProcCallNode($1, nullptr); }
    |   WRITE '(' exprList ')' ';'
                                { $$ = new cWriteNode($3); }
    |   block
                                { $$ = $1; }
    |   NIL ';'
                                { $$ = new cNilNode(); }
    |   error ';'
                                { $$ = nullptr; }

exprList: exprList ',' oneExpr
                                { $$ = $1; $$->AddExpr($3); }
        | oneExpr
                                { $$ = new cExprListNode($1); }
        | /* empty */
                                { $$ = nullptr; }
oneExpr: expr
                                { $$ = $1;}

func_call:  IDENTIFIER '(' exprList ')'
                                { $$ = new cFuncExprNode($1,$3); }

variable: variable '.' varpart
                                { $$ = $1; $$->AddElement($3); }
        | variable '[' exprList ']'
                                { $$ = $1; $$->AddElement($3); }
        | varpart
                                { $$ = new cVarExprNode($1); }

varpart:  IDENTIFIER
                                { $$ = $1; }

expr:       expr '=' addit
                                { $$ = new cBinaryExprNode($1, '=', $3); }
        |   expr '>' addit
                                { $$ = new cBinaryExprNode($1, '>', $3); }
        |   expr '<' addit
                                { $$ = new cBinaryExprNode($1, '<', $3); }
        |   expr LE addit
                                { $$ = new cBinaryExprNode($1, LE, $3); }
        |   expr GE addit
                                { $$ = new cBinaryExprNode($1, GE, $3); }
        |   expr NOT_EQUAL addit
                                { $$ = new cBinaryExprNode($1, NOT_EQUAL, $3);}
        |   addit
                                { $$ = $1; }

addit:      addit '+' term
                                { $$ = new cBinaryExprNode($1, '+', $3); }
        |   addit '-' term
                                { $$ = new cBinaryExprNode($1, '-', $3); }
        |   addit OR term
                                { $$ = new cBinaryExprNode($1, OR, $3); }
        |   term
                                { $$ = $1; }
        |   '-' term
                                { $$ = new cUnaryExprNode('-', $2); }

term:       term '*' fact
                                { $$ = new cBinaryExprNode($1, '*', $3); }
        |   term '/' fact
                                { $$ = new cBinaryExprNode($1, '/', $3); }
        |   term MOD fact
                                { $$ = new cBinaryExprNode($1, MOD, $3); }
        |   term DIV fact
                                { $$ = new cBinaryExprNode($1, DIV, $3); }
        |   term AND fact
                                { $$ = new cBinaryExprNode($1, AND, $3); }
        |   fact
                                { $$ = $1; }

fact:        '(' expr ')'
                                { $$ = $2; }
        |   INT_VAL
                                { $$ = new cIntExprNode($1); }
        |   REAL_VAL
                                { $$ = new cRealExprNode($1); }
        |   variable
                                { $$ = $1; }
        |   func_call
                                { $$ = $1; }
        |   NOT fact
                                { $$ = new cUnaryExprNode(NOT, $2); }

%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cout << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}
