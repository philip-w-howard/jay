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
#include "cTypeNode.h"

class cFlowNode : public cDeclNode
{
    public:
        cFlowNode(cSymbol *name, cTypeNode *type, cSettingsNode *settings) 
            : cDeclNode(name) 
        {
            std::vector<string> allowed = 
            {"delta", "update", "min", "max", "source", "destination"};
            std::vector<string> required = 
            { "min", "max", "source", "destination" };
            settings->CheckAllowedSettings(allowed);
            settings->CheckRequiredSettings(required);
            
            AddChild(type);
            AddChild(settings);
            if (type->IsFloat())
                m_isFloat = true;
            else
                m_isFloat = false;
        }

        bool IsFloat() { return m_isFloat; }

        virtual string NodeType() { return string("Flow"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        bool m_isFloat;
};
