#pragma once
//**************************************
// cFlowNode
//
// Defines class for flows
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSettingsNode.h"
#include "cSymbol.h"

class cFlowNode : public cDeclNode
{
    public:
        cFlowNode(cSymbol *name, cSettingsNode *settings) 
            : cDeclNode(name) 
        {
            std::vector<string> allowed = 
            {"delta", "update", "min", "max", "source", "destination"};
            std::vector<string> required = 
            { "min", "max", "source", "destination" };
            settings->CheckAllowedSettings(allowed);
            settings->CheckRequiredSettings(required);
            
            AddChild(settings);
        }

        virtual string NodeType() { return string("Flow"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
