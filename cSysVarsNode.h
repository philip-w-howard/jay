#pragma once
//**************************************
// cSysVarsNode.h
//
// Defines AST node that represents a list of systems
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSysVarNode.h"

class cSysVarsNode : public cAstNode
{
    public:
        // param is first stmt in the list of statements
        cSysVarsNode(cSysVarNode *var) : cAstNode()
        {
            AddChild(var);
        }

        // Add a statement to the list
        void AddSystem(cSysVarNode *var) { AddChild(var); }

        virtual string NodeType() { return string("sysVars"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
