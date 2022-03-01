#pragma once
//**************************************
// cDeclNode
//
// Defines class for trailer code
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cCodeNode.h"

class cTrailerNode : public cDeclNode
{
    public:
        cTrailerNode(cCodeNode* code) : cDeclNode() 
        { 
            AddChild(code);
        }

        string GetText()
        {
            return dynamic_cast<cCodeNode*>(GetChild(0))->GetContents();
        }

        virtual string NodeType() { return string("Trailer"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
