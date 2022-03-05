#pragma once
//**************************************
// cOutputListNode
//
// Defines class for output settings (log and csv)
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cCodeNode.h"
#include "cTypeNode.h"
#include "cSymbol.h"

class cOutputListNode : public cDeclNode
{
    public:
        cOutputListNode(string name, int interval, cSettingsNode *settings) 
            : cDeclNode(new cSymbol(name))
        {
            m_interval = interval;
            AddChild(settings);
        }

        virtual string AttributesToString()
        {
            return " interval=\"" + std::to_string(m_interval) + "\"";
        }

        virtual string NodeType() { return GetName(); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        long m_interval;
};
