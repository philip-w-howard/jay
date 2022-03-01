//*******************************************************
// Purpose: Utility routines used for code generation
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
//
// Date: 2/25/2016
//
//*******************************************************

#include <string>

//*****************************************
// Open output files and write the prefix
bool InitOutput(const std::string filename);

//*****************************************
// output postfix, copy functions to tail of main file and close files
bool FinalizeOutput();

//*****************************************
// Generate a unique label for GOTO statements
std::string GenerateLabel();

//*****************************************
// Various functions for emiting things to output file
void EmitInt(int val);
void EmitString(std::string str);

