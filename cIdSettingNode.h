#pragma once
//**************************************
// cIdSettingNode.h
//
// Defines class used to represent a value setting
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>
#include "cSettingNode.h"

class cIdSettingNode : public cSettingNode
{
    public:
        // param is name of symbol
        cIdSettingNode(string name, cSymbol *identifier) : cSettingNode()
        {
            m_name = name;
            AddChild(identifier);
        }

        virtual string NodeType() { return "IdSetting"; }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        virtual string AttributesToString()
        {
            return " name=\"" + m_name + "\"";
        }

    protected:
        string m_name;
};
