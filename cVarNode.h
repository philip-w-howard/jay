#pragma once
//**************************************
// cVarNode
//
// Defines class for Variables
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSettingsNode.h"
#include "cTypeNode.h"
#include "cSymbol.h"

class cVarNode : public cDeclNode
{
    public:
        cVarNode(cSymbol *name, cTypeNode *type, cSettingsNode *settings) 
            : cDeclNode() 
        {
            AddChild(name);
            AddChild(type);
            AddChild(settings);
        }

        virtual string NodeType() { return string("Var"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
