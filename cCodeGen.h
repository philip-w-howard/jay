#pragma once
//*****************************************************
//
// Visitor implementation to generate stackl code
//
// Author: Phil Howard
// Email:  phil.howard@oit.edu
//

#include "cVisitor.h"

class cCodeGen : public cVisitor
{
    public:
        cCodeGen();
        ~cCodeGen();

        virtual void Visit(cAstNode *node);
        virtual void Visit(cCodeNode *node);
        virtual void Visit(cDeclNode *node);
        virtual void Visit(cDeclsNode *node);
        virtual void Visit(cFlowNode *node);
        virtual void Visit(cFuncNode *node);
        virtual void Visit(cHeaderNode *node);
        virtual void Visit(cIdSettingNode *node);
        virtual void Visit(cIntValNode *node);
        virtual void Visit(cRealValNode *node);
        virtual void Visit(cSettingNode *node);
        virtual void Visit(cSettingsNode *node);
        virtual void Visit(cSetupNode *node);
        virtual void Visit(cStockNode *node);
        virtual void Visit(cSymbol *node);
        virtual void Visit(cSystemNode *node);
        virtual void Visit(cTrailerNode *node);
        virtual void Visit(cTypeNode *node);
        virtual void Visit(cUnitsNode *node);
        virtual void Visit(cValueNode *node);
        virtual void Visit(cValueSettingNode *node);
        virtual void Visit(cVarNode *node);
    protected:
        std::string to_string(bool val)
        { return val ? "true" : "false"; }

        std::string m_curr_decl;
};
