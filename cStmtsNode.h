#pragma once
//**************************************
// cStmtsNode.h
//
// Defines AST node that represents a list of statements
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cStmtNode.h"

class cStmtsNode : public cAstNode
{
    public:
        // param is first stmt in the list of statements
        cStmtsNode(cStmtNode *stmt) : cAstNode()
        {
            AddChild(stmt);
        }

        // Add a statement to the list
        void AddStmt(cStmtNode *stmt) { AddChild(stmt); }

        virtual string NodeType() { return string("stmts"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
