#pragma once
//**************************************
// cSystemNode.h
//
// Defines AST node for a lang program
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSymbol.h"
#include "cDeclsNode.h"

class cSystemNode : public cAstNode
{
    public:
        // param is the decls that makes up the program
        cSystemNode(cSymbol *name, cDeclsNode *decls) : cAstNode()
        {
            AddChild(name);
            AddChild(decls);
        }

        string GetName()
        {
            return dynamic_cast<cSymbol*>(GetChild(0))->GetName();
        }

        virtual string NodeType() { return string("system"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
