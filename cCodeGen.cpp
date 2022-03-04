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
    "#include \"cVarImpl.h\"\n\n"
    "#include \"cStockImpl.h\"\n\n"
    "#include \"cFlowImpl.h\"\n\n";

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
    string output = "";

    output += "cFlowImpl<" + m_curr_system + "> *" + node->GetName() + "_Impl;\n";
    EmitString(output);

    init_body += "\n" + node->GetName() + "_Impl = " + 
        "new cFlowImpl<" + m_curr_system + ">( \"" + node->GetName() + "\", " + 
        "false , nullptr, this);\n";

    m_curr_decl = node->GetName();
    node->VisitAllChildren(this);
    m_curr_decl = "";
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
    // cHeader visitor takes care of emitting header code
    //node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cIdSettingNode *node)
{
    if (m_curr_decl != "")
    {
        string name = node->GetName();
        if (name == "source" || name == "destination")
        {
            init_body += m_curr_decl + "_Impl->Add" + name + "(" +
                node->GetIdentifier() + "_Impl);\n";
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
    string output = "";

    if (node->GetType()->IsFloat())
        output += "static double ";
    else
        output += "static long ";

    output += node->GetName() + ";\n";
    output += "cStockImpl<" + m_curr_system + "> *" + node->GetName() + "_Impl;\n";
    EmitString(output);

    init_body += "\n" + node->GetName() + "_Impl = " + 
        "new cStockImpl<" + m_curr_system + ">( \"" + node->GetName() + "\", " + 
        to_string(node->GetType()->IsFloat()) +
        ", &" + node->GetName() + ", this);\n";

    m_curr_decl = node->GetName();
    node->VisitAllChildren(this);
    m_curr_decl = "";
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
    // cTrailer visitor takes care of emiting trailer code
    //node->VisitAllChildren(this);
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
    string output = "";

    if (node->GetType()->IsFloat())
        output += "static double ";
    else
        output += "static long ";

    output += node->GetName() + ";\n";
    output += "cVarImpl<" + m_curr_system + "> *" + node->GetName() + "_Impl;\n";
    EmitString(output);


    init_body += "\n" + node->GetName() + "_Impl = " + 
        "new cVarImpl<" + m_curr_system + ">( \"" + node->GetName() + "\", " + 
        to_string(node->GetType()->IsFloat()) +
        ", &" + node->GetName() + ", this);\n";

    m_curr_decl = node->GetName();
    node->VisitAllChildren(this);
    m_curr_decl = "";
}

