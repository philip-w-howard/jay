#pragma once
//**************************************
// cOutputNode
//
// Defines class for output settings (log and csv)
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSettingNode.h"
#include "cSymbol.h"

class cOutputNode : public cSettingNode
{
    public:
        cOutputNode(cSymbol *root, cSymbol *property, string *format)
            : cSettingNode(root->GetName() + "." + property->GetName())
        {
            m_format = *format;
            AddChild(root);
            AddChild(property);
        }

        virtual string AttributesToString()
        {
            return " format=\"" + m_format + "\"";
        }

        virtual string NodeType() { return GetName(); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        string m_format;
};
