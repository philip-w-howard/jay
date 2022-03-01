//*******************************************************
// Purpose: Utility routines used for code generation
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
//
// Date: 2/25/2016
//
//*******************************************************

#include <iostream>
#include <stdio.h>
#include <string>
#include "emit.h"

using std::string;

// Output files
static FILE* Output;

static int  Next_Label = 1;

//*****************************************
// Open output files and write the prefix
bool InitOutput(const std::string filename)
{
    Output = fopen(filename.c_str(), "w");
    if (Output == NULL)
    {
        std::cerr << "Unable to open output file." << std::endl;
        return false;
    }

    return true;
}
//*****************************************
// output postfix, copy functions to tail of main file and close files
bool FinalizeOutput()
{
    fclose(Output);

    return true;
}
//*****************************************
// Generate a unique label for GOTO statements
std::string GenerateLabel()
{
    Next_Label++;
    std::string label("$PASCAL_LABEL");
    label += std::to_string(Next_Label);
    return label;
}
//*****************************************
// write an integer constant to the output
void EmitInt(int val)
{
    fprintf(Output, " %d ", val);
}
//*****************************************
void EmitString(std::string str)
{
    fprintf(Output, "%s", str.c_str());
}
