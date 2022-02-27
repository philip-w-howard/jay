%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Dec. 6, 2017
//

#include "astnodes.h"
#include "lex.h"
#include "pascalishparse.h"

//#define DEBUG
#ifdef DEBUG
#define DO_RETURN(a) return Return(a)
#else
#define DO_RETURN(a) return (a)
#endif

int Return(int val);
int ProcessIdentifier(const char *name);
//YYSTYPE yylval;
%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

OPERATOR          [+\-*/<=>\^\(\)\[\];,\.\:]

%%

[ \t\n\r]                   {} // ignore whitespace
"{".*"}"                    {} // ignore comments
"<="                        DO_RETURN(LE);
"<>"                        DO_RETURN(NOT_EQUAL);
">="                        DO_RETURN(GE);
":="                        DO_RETURN(ASSIGN);
[a-zA-Z][a-zA-Z0-9]*        DO_RETURN(ProcessIdentifier(yytext));
[0-9]+                      { yylval.int_val = atoi(yytext); 
                              DO_RETURN(INT_VAL);
                            }
[0-9]+\.[0-9]+              { yylval.real_val = atof(yytext);
                              DO_RETURN(REAL_VAL);
                            }
{OPERATOR}                  DO_RETURN(yytext[0]);
.                           DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

//************************************************
static char *strlwr(char *str)
{
    char *temp = str;
    while (*temp)
    {
        *temp = tolower(*temp);
        temp++;
    }

    return str;
}
//************************************************
int ProcessIdentifier(const char *name)
{
    char buff[256];
    strncpy(buff, name, sizeof(buff)-1);
    buff[sizeof(buff)-1] = 0;

    strlwr(buff);

    yylval.symbol = g_symbolTable.GlobalLookup(buff);
    if (yylval.symbol == nullptr)
    {
        yylval.symbol = new cSymbol(buff);
    }

    return yylval.symbol->GetTokenType();
}
