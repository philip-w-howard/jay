#pragma once
//**************************************
// cUnitsNode.h
//
// Defines an AST node for an time units
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>
#include "cSettingNode.h"

class cUnitsNode : public cSettingNode
{
    public:
        cUnitsNode(string units) : cSettingNode("units")
        {
            m_units = units;
        }

        virtual string AttributesToString() 
        {
            return " units=\"" + m_units + "\"";
        }
        virtual string NodeType() { return string("units"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        string m_units;
};
