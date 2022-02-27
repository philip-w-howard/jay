#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent arbitrary code blobs
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>

using std::string;

#include "cAstNode.h"

class cCodeNode : public cAstNode
{
    public:
        cCodeNode();

        // param is name of symbol
        cCodeNode(string contents) : cAstNode()
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
