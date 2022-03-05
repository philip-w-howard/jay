#pragma once
//**************************************
// cSystemsListNode.h
//
// Defines AST node that represents a list of system variables
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSysVarsNode.h"

class cSystemsListNode : public cDeclNode
{
    public:
        // param is first stmt in the list of statements
        cSystemsListNode(cSysVarsNode *sysvars) 
            : cDeclNode(new cSymbol("SystemsList"))
        {
            AddChild(sysvars);
        }

        virtual string NodeType() { return string("systemsList"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
