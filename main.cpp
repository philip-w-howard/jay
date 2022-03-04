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

#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <getopt.h>
#include "cSymbolTable.h"
#include "lex.h"
#include "astnodes.h"
#include "jayparse.h"
#include "cCodeHeader.h"
#include "cCodeGen.h"
#include "cCodeTrailer.h"
#include "emit.h"

#ifndef _GNU_SOURCE
#error "not gnu"
#endif

static const char *JAY_VERSION = "0.0.1";

// define global variables
cSymbolTable g_symbolTable;
long long cSymbol::nextId;

typedef struct
{
    bool do_ast;
    char output_file[256];
    char ast_file[256];
    char input_file[256];
} args_t;

//*******************************************************
static void print_version()
{
    fprintf(stderr, "%s\n", JAY_VERSION);
}

//*******************************************************
static void print_help()
{
    fprintf(stderr, 
            "jay <options> <input file>\n"
            "Options can be abrieviated to a single letter\n"
            "--ast <ast filename> generate AST file\n"
            "--help print help message and exit\n"
            "--version print version\n"
            "--output <output file> specify the output file\n"
           );
    exit(1);
}

//*******************************************************
static void process_args(int argc, char **argv, args_t *args)
{
    args->do_ast = false;

    strcpy(args->output_file, "jay_generated_output.cpp");

    strcpy(args->ast_file, "jay_generated_output.ast");

    strcpy(args->input_file, "");

    struct option long_opts[] =
    {
        {"ast",     optional_argument, NULL, 'a'},    // optional
        {"output",  required_argument, NULL, 'o'},    // required
        {"version", no_argument, NULL, 'v'},    // no argument
        {"help",    no_argument, NULL, 'h'},     // no argument,
        {NULL,      0, NULL, 0}
    };

    int opt;
    int long_index;

    while ( (opt = getopt_long(argc, argv, ":a::o:vh", long_opts, &long_index)) > 0)
    {
        switch (opt)
        {
            case 'a':
                args->do_ast = true;
                if (optarg != NULL) strcpy(args->ast_file, optarg);
                break;
            case 'h':
                print_help();
                exit(0);
                break;
            case 'o':
                strcpy(args->output_file, optarg);
                break;
            case 'v':
                print_version();
                break;
            default:
                print_help();
                break;
        }
    }

    if (optind > 0 && optind < argc)
        strcpy(args->input_file, argv[optind]);
    else
    {
        fprintf(stderr, "Must specify an input file\n");
        exit(1);
    }
}

//*******************************************************
int main(int argc, char **argv)
{
    args_t args;
    process_args(argc, argv, &args);

    int result = 0;

    yyin = fopen(args.input_file, "r");
    if (yyin == nullptr)
    {
        fprintf(stderr, "ERROR: Unable to open file %s\n", argv[1]);
        exit(-1);
    }

    result = yyparse();
    if (yyast_root != nullptr && result == 0 && yynerrs == 0)
    {
        InitOutput(args.output_file);

        cCodeHeader header;
        yyast_root->Visit(&header);

        {
            // code gen needs to be in its own scope so destructor gets called
            cCodeGen coder;
            yyast_root->Visit(&coder);
        }

        cCodeTrailer trailer;
        yyast_root->Visit(&trailer);

        FinalizeOutput();

        if (args.do_ast)
        {
            std::ofstream ast(args.ast_file);
            if (!ast.good())
            {
                fprintf(stderr, "Unable to open AST file: %s\n", args.ast_file);
                exit(1);
            }
            ast << yyast_root->ToString() << std::endl;
            ast.close();
        }
    } else {
        std::cout << yynerrs << " Errors in compile\n";
    }

    if (result == 0 && yylex() != 0)
    {
        std::cout << "Junk at end of program\n";
    }

    return result;
}
