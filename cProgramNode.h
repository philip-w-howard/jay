#pragma once
//**************************************
// cProgramNode.h
//
// Defines AST node that represents a program
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSystemsNode.h"
#include "cSimulationNode.h"

class cProgramNode : public cAstNode
{
    public:
        // param is first stmt in the list of statements
        cProgramNode(cSystemsNode *systems, cSimulationNode *sim) : cAstNode()
        {
            AddChild(systems);
            AddChild(sim);
        }

        virtual string NodeType() { return string("program"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
