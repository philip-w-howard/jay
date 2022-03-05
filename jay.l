%{
//**************************************
// jay.l
//
// Scanner definition file for jay system modeling compiler
//
// Author: Phil Howard 
//

#include "astnodes.h"
#include "lex.h"
#include "jayparse.h"

//#define DEBUG
#ifdef DEBUG
#define DO_RETURN(a) return Return(a)
#else
#define DO_RETURN(a) return (a)
#endif

int Return(int val);
int ProcessIdentifier(const char *name);
int ProcessCode(const char *text);
int ProcessString(string text);
//YYSTYPE yylval;
%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

OPERATOR          [=;:{}<>\.]

%%

[ \t\n\r]                   {} // ignore whitespace
"//".*                      {} // ignore comments
system                      DO_RETURN(SYSTEM);
systems                     DO_RETURN(SYSTEMS);
simulation                  DO_RETURN(SIMULATION);
log                         DO_RETURN(LOG);
csv                         DO_RETURN(CSV);
start                       DO_RETURN(START);
header                      DO_RETURN(HEADER);
trailer                     DO_RETURN(TRAILER);
update                      DO_RETURN(UPDATE);
delta                       DO_RETURN(DELTA);
end                         DO_RETURN(END);
units                       DO_RETURN(UNITS);
setup                       DO_RETURN(SETUP);
stock                       DO_RETURN(STOCK);
flow                        DO_RETURN(FLOW);
var                         DO_RETURN(VAR);
function                    DO_RETURN(FUNCTION);
source                      DO_RETURN(SOURCE);
destination                 DO_RETURN(DESTINATION);
min                         DO_RETURN(MIN);
max                         DO_RETURN(MAX);
infinite                    DO_RETURN(INFINITE);
initial                     DO_RETURN(INITIAL_VAL);
type                        DO_RETURN(TYPE);
discrete                    DO_RETURN(DISCRETE);
continuous                  DO_RETURN(CONTINUOUS);
milliseconds                DO_RETURN(MILLISECONDS);
seconds                     DO_RETURN(SECONDS);
minutes                     DO_RETURN(MINUTES);
hours                       DO_RETURN(HOURS);
days                        DO_RETURN(DAYS);
years                       DO_RETURN(YEARS);

[_a-zA-Z][_a-zA-Z0-9]*        DO_RETURN(ProcessIdentifier(yytext));
-?[0-9]+                    { yylval.int_val = atoi(yytext); 
                              DO_RETURN(INT_VAL);
                            }
-?[0-9]+\.[0-9]+            { yylval.real_val = atof(yytext);
                              DO_RETURN(REAL_VAL);
                            }
{OPERATOR}                  DO_RETURN(yytext[0]);
"$"[^$]+"$"                 DO_RETURN(ProcessCode(yytext));
["][^"]*["]                 DO_RETURN(ProcessString(yytext));
.                           DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

//************************************************
int ProcessIdentifier(const char *name)
{
    yylval.symbol = g_symbolTable.GlobalLookup(name);
    if (yylval.symbol == nullptr)
    {
        yylval.symbol = new cSymbol(name);
    }

    return IDENTIFIER;
}
//************************************************
int ProcessCode(const char *text)
{
    yylval.code_node = new cCodeNode(text);

    return CODE;
}
int ProcessString(string text)
{
    // delete the quotes
    text = text.substr(1, text.length()-2);

    yylval.string = new string(text);

    return STR_CONST;
} 
