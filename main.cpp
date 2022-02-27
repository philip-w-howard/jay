//**************************************
// main.cpp
//
// Main function for jay compiler
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "cSymbolTable.h"
#include "lex.h"
#include "astnodes.h"
#include "jayparse.h"

// define global variables
cSymbolTable g_symbolTable;
long long cSymbol::nextId;

// takes two string args: input_file, and output_file
int main(int argc, char **argv)
{
    std::cout << "Jay V 0.0\n";

    int result = 0;

    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == nullptr)
        {
            fprintf(stderr, "ERROR: Unable to open file %s\n", argv[1]);
            exit(-1);
        }
    }

    if (argc > 2)
    {
        FILE *output = fopen(argv[2], "w");
        if (output == nullptr)
        {
            fprintf(stderr, "ERROR: Unable to open file %s\n", argv[2]);
            exit(-1);
        }

        // redirect stdout to the output
        int output_fd = fileno(output);
        if (dup2(output_fd, 1) != 1)
        {
            fprintf(stderr, "Unable to duplicate the file descriptor\n");
            exit(-2);
        }
    }

    result = yyparse();
    if (yyast_root != nullptr && result == 0 && yynerrs == 0)
    {
        std::cout << yyast_root->ToString() << std::endl;
    } else {
        std::cout << yynerrs << " Errors in compile\n";
    }

    if (result == 0 && yylex() != 0)
    {
        std::cout << "Junk at end of program\n";
    }

    return result;
}
