#pragma once
//**************************************
// cSysVarNode
//
// Defines class for declaration of a system variable
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"

class cSysVarNode : public cDeclNode
{
    public:
        cSysVarNode(cSymbol *system, cSymbol *name) 
            : cDeclNode(name) 
        {
            AddChild(system);
        }

        string GetSystem() { return dynamic_cast<cSymbol*>(GetChild(1))->GetName(); }

        virtual string NodeType() { return string("SysVar"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
