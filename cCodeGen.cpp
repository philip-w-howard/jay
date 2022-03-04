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

static string front_matter =
    "//**********************************\n"
    "// This is the beginning of the generated code\n"
    "// There should be decls, etc. here\n"
    "#include \"cVarImpl.h\"\n\n";

static string end_matter =
    "//**********************************\n"
    "// This is the ending of the generated code\n"
    "// There should be a close curly here\n";

static string init_body = "";

//*************************************************
cCodeGen::cCodeGen() : cVisitor()
{
    EmitString(front_matter);
}

//*************************************************
cCodeGen::~cCodeGen()
{
    EmitString(end_matter);
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
    if (node->IsFloat())
    {
        EmitString("\ndouble " + node->GetName() + "()\n" +
                "{ double value;\n");
    }
    else
    {
        EmitString("long " + node->GetName() + "()\n" +
                "{ long value;\n");
    }
    EmitString(node->GetCode());
    EmitString("\nreturn value;\n}\n");

    //node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cHeaderNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cIdSettingNode *node)
{
    if (m_curr_decl != "")
    {
        string name = node->GetName();
        if (name == "source" || name == "destination")
        {
            init_body += m_curr_decl + "_Impl->Add" + name + "(\"" +
                node->GetIdentifier() + "\");\n";
        }
        else if (name =="update" || name == "delta")
        {
            init_body += m_curr_decl + "_Impl->Add" + name + "(" +
                "&" + m_curr_system + "::" + node->GetIdentifier() + ");\n";
        }
        else
        {
            std::cerr << "ERROR: Invalid name in Id Setting node\n";
            exit(1);
        }
    }
    // node->VisitAllChildren(this);
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
    if (node->GetType()->IsFloat())
        EmitString("static double ");
    else
        EmitString("static long ");

    EmitString(node->GetName());
    EmitString(";\n");

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
    m_curr_system = node->GetName();
    EmitString("class " + node->GetName() + "\n{\npublic:\n");

    node->VisitAllChildren(this);

    EmitString(m_curr_system + "()\n{\n");
    EmitString(init_body);
    EmitString("\n}\n");
    init_body = "";

    EmitString("\n};\n\n");

    m_curr_system = "";
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
    if (m_curr_decl != "")
    {
        init_body += m_curr_decl + "_Impl->Add" + node->GetName() + "(" +
            node->GetValue()->GetTextValue() + ");\n";
    }

    //node->VisitAllChildren(this);
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

    init_body += "\ncVarImpl<" + m_curr_system + "> *" + node->GetName() + "_Impl = " + 
        "new cVarImpl<" + m_curr_system + ">( \"" + node->GetName() + "\", " + 
        to_string(node->GetType()->IsFloat()) +
        ", &" + node->GetName() + ", this);\n";

    m_curr_decl = node->GetName();
    node->VisitAllChildren(this);
    m_curr_decl = "";
}

