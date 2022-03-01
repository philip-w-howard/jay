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
        cValueSettingNode(string name, cValueNode *value) 
            : cSettingNode(name)
        {
            AddChild(value);
        }

        cValueNode *GetValue() 
        { return dynamic_cast<cValueNode*>(GetChild(0)); }

        virtual string NodeType() { return GetName(); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
