#pragma once
//**************************************
// cSystemsNode.h
//
// Defines AST node that represents a list of systems
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSystemNode.h"

class cSystemsNode : public cAstNode
{
    public:
        // param is first stmt in the list of statements
        cSystemsNode(cSystemNode *stmt) : cAstNode()
        {
            AddChild(stmt);
        }

        // Add a statement to the list
        void AddSystem(cSystemNode *stmt) { AddChild(stmt); }

        virtual string NodeType() { return string("systems"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
