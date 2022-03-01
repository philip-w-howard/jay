#pragma once
//**************************************
// cVarNode
//
// Defines class for Variables
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <vector>

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSettingsNode.h"
#include "cTypeNode.h"
#include "cSymbol.h"

class cVarNode : public cDeclNode
{
    public:
        cVarNode(cSymbol *name, cTypeNode *type, cSettingsNode *settings) 
            : cDeclNode(name) 
        {
            std::vector<string> allowed = {"delta", "update", "min", "max"};
            std::vector<string> required = { "min", "max" };
            settings->CheckAllowedSettings(allowed);
            settings->CheckRequiredSettings(required);

            AddChild(type);
            AddChild(settings);
        }

        virtual string NodeType() { return string("Var"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
