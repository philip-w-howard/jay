#pragma once
//**************************************
// cTypeNode.h
//
// Defines an AST node for a value/function type
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>
#include "cAstNode.h"

class cTypeNode : public cAstNode
{
    public:
        cTypeNode(string type) : cAstNode()
        {
            m_type = type;
        }

        virtual string AttributesToString() 
        {
            return " type=\"" + m_type + "\"";
        }
        virtual string NodeType() { return string("type"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        string m_type;
};
