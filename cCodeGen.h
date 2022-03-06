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

        virtual void Visit(cFlowNode *node);
        virtual void Visit(cFuncNode *node);
        virtual void Visit(cIdSettingNode *node);
        virtual void Visit(cOutputListNode *node);
        virtual void Visit(cOutputNode *node);
        virtual void Visit(cSimulationNode *node);
        virtual void Visit(cSetupNode *node);
        virtual void Visit(cStockNode *node);
        virtual void Visit(cSystemNode *node);
        virtual void Visit(cSysVarNode *node);
        virtual void Visit(cValueSettingNode *node);
        virtual void Visit(cVarNode *node);
    protected:
        std::string to_string(bool val)
        { return val ? "true" : "false"; }

        std::string m_curr_decl;
        std::string m_curr_system;
};
