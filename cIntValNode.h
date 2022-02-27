#pragma once
//**************************************
// cIntValNode.h
//
// Defines an AST node for an integer constant (literals).
//
// Inherits from cValNode so that integer constants can be used anywhere 
// expressions are used.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"

class cIntValNode : public cAstNode
{
    public:
        // param is the value of the integer constant
        cIntValNode(int value) : cAstNode()
        {
            m_value = value;
        }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("INTEGER"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        int m_value;        // value of integer constant (literal)
};
