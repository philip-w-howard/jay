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
#include "cTypeNode.h"
#include "cSymbol.h"

class cFuncNode : public cDeclNode
{
    public:
        cFuncNode(cSymbol *name, cTypeNode *type, cCodeNode *code) 
            : cDeclNode(name) 
        {
            AddChild(type);
            AddChild(code);
        }

        virtual string NodeType() { return string("Func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
