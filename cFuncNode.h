#pragma once
//**************************************
// cFuncNode
//
// Defines class for functions
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cCodeNode.h"
#include "cSymbol.h"

class cFuncNode : public cDeclNode
{
    public:
        cFuncNode(cSymbol *name, cCodeNode *code) : cDeclNode() 
        {
            AddChild(name);
            AddChild(code);
        }

        virtual string NodeType() { return string("Func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
