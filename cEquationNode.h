#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent symbols.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>

using std::string;

#include "cAstNode.h"

class cEquationNode : public cAstNode
{
    public:
        cEquationNode();

        // param is name of symbol
        cEquationNode(string contents) : cAstNode()
        {
            m_contents = contents;
        }

        // return name of symbol
        string GetContents() { return m_contents; }
        
        virtual string AttributesToString()
        {
            string result(" text=\"");
            result += m_contents;
            result += "\"";
            return result;
        }

        virtual string NodeType() { return "equation"; }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        string m_contents;              // text of equation
};
