#pragma once
//**************************************
// cRealValNode.h
//
// Defines AST node for a real constant (literal)
// Inherits from cValNode so real constants can be used in any expression.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>
#include "cValueNode.h"

class cRealValNode : public cValueNode
{
    public:
        // param is the value of the constant (literal)
        cRealValNode(double value) : cValueNode()
        {
            m_value = value;
        }

        virtual string GetTextValue() { return std::to_string(m_value); }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("REAL"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        double m_value;     // value of the constant (literal)
};
