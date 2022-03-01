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
        cIdSettingNode(string name, cSymbol *identifier) 
            : cSettingNode(name)
        {
            AddChild(identifier);
        }

        string GetIdentifier() 
        { return dynamic_cast<cSymbol*>(GetChild(0))->GetName(); }

        virtual string NodeType() { return GetName(); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
