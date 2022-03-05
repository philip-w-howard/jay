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
    "#include <vector>\n"
    "#include \"cVarImpl.h\"\n"
    "#include \"cStockImpl.h\"\n"
    "#include \"cFlowImpl.h\"\n";

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
void cCodeGen::Visit(cFlowNode *node)
{
    string output = "";

    output += "cFlowImpl<" + m_curr_system + "> *" + node->GetName() + "_Impl;\n";
    EmitString(output);

    init_body += "\n" + node->GetName() + "_Impl = " + 
        "new cFlowImpl<" + m_curr_system + ">( \"" + node->GetName() + "\", " + 
        "false , nullptr, this);\n";

    init_body += "m_flows.push_back(" +  node->GetName() + "_Impl);\n";
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
void cCodeGen::Visit(cOutputListNode *node)
{
    if (node->GetType() == "log")
    {
        EmitString("Log *" + node->GetName() + " = new Log(\"" + 
                node->GetName() + "\", " + std::to_string(node->GetInterval()) + ");\n");
    }
    else if (node->GetType() == "ast")
    {
        EmitString("Log *" + node->GetName() + " = new Log(\"" + 
                node->GetName() + "\", " + std::to_string(node->GetInterval()) + ");\n");
    }
    else
    {
        fprintf(stderr, "Invalid type of output\n");
    }

    m_curr_decl = node->GetName();
    node->VisitAllChildren(this);
    m_curr_decl = "";
}
//*************************************************
void cCodeGen::Visit(cOutputNode *node)
{
    EmitString(m_curr_decl + "->AddChild(&" + node->GetName() + ", \"" + 
            node->GetFormat() + "\");\n");
}
//*************************************************
void cCodeGen::Visit(cSetupNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSimulationNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSysVarNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cSystemsListNode *node)
{
    node->VisitAllChildren(this);
}
//*************************************************
void cCodeGen::Visit(cStockNode *node)
{
    string output = "";

    if (node->GetType()->IsFloat())
        output += "double ";
    else
        output += "long ";

    output += node->GetName() + ";\n";
    output += "cStockImpl<" + m_curr_system + "> *" + node->GetName() + "_Impl;\n";
    EmitString(output);

    init_body += "\n" + node->GetName() + "_Impl = " + 
        "new cStockImpl<" + m_curr_system + ">( \"" + node->GetName() + "\", " + 
        to_string(node->GetType()->IsFloat()) +
        ", &" + node->GetName() + ", this);\n";

    init_body += "m_stocks.push_back(" +  node->GetName() + "_Impl);\n";
    m_curr_decl = node->GetName();
    node->VisitAllChildren(this);
    m_curr_decl = "";
}
//*************************************************
void cCodeGen::Visit(cSystemNode *node)
{
    m_curr_system = node->GetName();
    EmitString("class " + node->GetName() + "\n{\npublic:\n");

    EmitString("std::vector<cStockImpl<" + node->GetName() + ">*>m_stocks;\n");
    EmitString("std::vector<cFlowImpl<" + node->GetName() + ">*>m_flows;\n");
    EmitString("std::vector<cVarImpl<" + node->GetName() + ">*>m_vars;\n");

    node->VisitAllChildren(this);

    EmitString(m_curr_system + "()\n{\n");
    EmitString(init_body);
    EmitString("\n}\n");
    init_body = "";

    EmitString(
            "void Step()\n"
            "{\n"
            "   for (auto var : m_vars)\n"
            "       var->Step();\n"
            "   for (auto flow : m_flows)\n"
            "       flow->Step();\n"
            "}\n"
            );
    EmitString("\n};\n\n");

    m_curr_system = "";
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
        output += "double ";
    else
        output += "long ";

    output += node->GetName() + ";\n";
    output += "cVarImpl<" + m_curr_system + "> *" + node->GetName() + "_Impl;\n";
    EmitString(output);


    init_body += "\n" + node->GetName() + "_Impl = " + 
        "new cVarImpl<" + m_curr_system + ">( \"" + node->GetName() + "\", " + 
        to_string(node->GetType()->IsFloat()) +
        ", &" + node->GetName() + ", this);\n";
    init_body += "m_vars.push_back(" +  node->GetName() + "_Impl);\n";

    m_curr_decl = node->GetName();
    node->VisitAllChildren(this);
    m_curr_decl = "";
}

