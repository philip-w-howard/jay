//*****************************************************
//
// Visitor implementation to generate stackl code
//
// Author: Phil Howard
// Email:  phil.howard@oit.edu
//
#include <string>

#include "emit.h"
#include "astnodes.h"
#include "cCodeGen.h"

#include "cVarImpl.h"

static string front_matter =
    "//**********************************\n"
    "// This is the beginning of the generated code\n"
    "// There should be decls, etc. here\n"
    "#include <string>\n"
    "using std::string;\n"
    "#include \"cVarImpl.h\"\n";

static string end_matter =
    "//**********************************\n"
    "// This is the ending of the generated code\n"
    "// There should be a close curly here\n";

static string init_header =
    "void InitTables() {\n";

static string init_trailer =
    "}\n";

static string init_body = "";

//*************************************************
cCodeGen::cCodeGen(std::string filename) : cVisitor()
{
    InitOutput(filename.c_str());
    EmitString(front_matter);
}

//*************************************************
cCodeGen::~cCodeGen()
{
    EmitString(init_header);
    EmitString(init_body);
    EmitString(init_trailer);
    EmitString(end_matter);
    FinalizeOutput();
}

//*************************************************
void cCodeGen::Visit(cAstNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cCodeNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cDeclNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cDeclsNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cFlowNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cFuncNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cHeaderNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cIdSettingNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cIntValNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cRealValNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSettingNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSettingsNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSetupNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cStockNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSymbol *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSystemNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cTrailerNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cTypeNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cUnitsNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cValueNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cValueSettingNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cVarNode *node)
{
    if (node->GetType()->IsFloat())
        EmitString("static double ");
    else
        EmitString("static long ");

    EmitString(node->GetName());
    EmitString(";\n");

    init_body += "static cVarImpl *" + node->GetName() + "_Impl = " + 
        "new cVarImpl( \"" + node->GetName() + "\", " + 
        to_string(node->GetType()->IsFloat()) +
        ", &" + node->GetName() + ");\n";

}

