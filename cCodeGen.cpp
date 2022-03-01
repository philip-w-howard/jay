//*****************************************************
//
// Visitor implementation to generate stackl code
//
// Author: Phil Howard
// Email:  phil.howard@oit.edu
//

#include "emit.h"
#include "astnodes.h"
#include "cCodeGen.h"

static string front_matter =
    "//**********************************\n"
    "// This is the beginning of the generated code\n"
    "// There should be decls, etc. here\n";

static string end_matter =
    "//**********************************\n"
    "// This is the ending of the generated code\n"
    "// There should be a close curly here\n";

//*************************************************
cCodeGen::cCodeGen(std::string filename) : cVisitor()
{
    InitOutput(filename.c_str());
    EmitString(front_matter);
}

//*************************************************
cCodeGen::~cCodeGen()
{
    EmitString(end_matter);
    FinalizeOutput();
}

//*************************************************
void cCodeGen::Visit(cAstNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cCodeNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cDeclNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cDeclsNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cFlowNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cFuncNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cHeaderNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cIdSettingNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cIntValNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cRealValNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cSettingNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cSettingsNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cSetupNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cStockNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cSymbol *node)
{
}
//*************************************************
void cCodeGen::Visit(cSystemNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cTrailerNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cTypeNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cUnitsNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cValueNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cValueSettingNode *node)
{
}
//*************************************************
void cCodeGen::Visit(cVarNode *node)
{
}

