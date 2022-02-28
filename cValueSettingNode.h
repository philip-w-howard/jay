#pragma once
//**************************************
// cValueSettingNode.h
//
// Defines class used to represent a value setting
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>
#include "cSettingNode.h"

class cValueSettingNode : public cSettingNode
{
    public:
        // param is name of symbol
        cValueSettingNode(string name, cValueNode *value) : cSettingNode()
        {
            m_name = name;
            AddChild(value);
        }

        virtual string NodeType() { return "ValueSetting"; }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        virtual string AttributesToString()
        {
            return " name=\"" + m_name + "\"";
        }

    protected:
        string m_name;
};
