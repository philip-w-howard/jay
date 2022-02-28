#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode() {}

        cDeclNode(cSymbol *name) : cAstNode() 
        {
            if (g_symbolTable.GlobalLookup(name->GetName()) != nullptr)
            {
                SemanticParseError(name->GetName() + " is already defined");
            }
            else
            {
                g_symbolTable.Insert(name);
            }
            AddChild(name);
        }

        virtual bool IsReal() { return false; }
};
