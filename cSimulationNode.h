#pragma once
//**************************************
// cSimulationNode.h
//
// Defines AST node for a Jay simulation
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSymbol.h"
#include "cDeclsNode.h"

class cSimulationNode : public cAstNode
{
    public:
        // param is the decls that makes up the program
        cSimulationNode(cDeclsNode *decls) : cAstNode()
        {
            AddChild(decls);
        }

        cDeclsNode *GetDecls() 
        { return dynamic_cast<cDeclsNode*>(GetChild(0)); }

        virtual string NodeType() { return string("system"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
