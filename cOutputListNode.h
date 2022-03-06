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
        cOutputListNode(cSymbol *name, int interval, cSettingsNode *settings, string type) 
            : cDeclNode(name)
        {
            m_interval = interval;
            m_type = type;
            AddChild(settings);
        }

        string GetType() { return m_type; }
        long GetInterval() { return m_interval; }

        virtual string AttributesToString()
        {
            return " type=\"" + m_type + "\" interval=\"" + std::to_string(m_interval) + "\"";
        }

        virtual string NodeType() { return GetName(); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        long m_interval;
        string m_type;
};
