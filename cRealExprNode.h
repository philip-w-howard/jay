#pragma once
//**************************************
// cRealExprNode.h
//
// Defines AST node for a real constant (literal)
// Inherits from cExprNode so real constants can be used in any expression.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cExprNode.h"

class cRealExprNode : public cExprNode
{
    public:
        // param is the value of the constant (literal)
        cRealExprNode(double value)
        {
            m_value = value;
        }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("REAL"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        double m_value;     // value of the constant (literal)
};
