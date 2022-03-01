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
            m_contents = contents.substr(1, contents.length()-2);
        }

        // return name of symbol
        string GetContents() { return m_contents; }
        
        virtual string ToString()
        {
            string result("<code>\n<![CDATA[");
            result += m_contents;
            result += "]]>\n</code>";
            return result;
        }

        virtual string NodeType() { return "equation"; }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        string m_contents;              // text of equation
};
