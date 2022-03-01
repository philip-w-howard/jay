#pragma once
//**************************************
// cDeclNode
//
// Defines class for header code
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cCodeNode.h"

class cHeaderNode : public cDeclNode
{
    public:
        cHeaderNode(cCodeNode* code) : cDeclNode() 
        { 
            AddChild(code);
        }

        string GetText()
        {
            return dynamic_cast<cCodeNode*>(GetChild(0))->GetContents(); 
        }

        virtual string NodeType() { return string("Header"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
