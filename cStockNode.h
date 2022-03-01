#pragma once
//**************************************
// cStockNode
//
// Defines class for stocks
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSettingsNode.h"
#include "cSymbol.h"
#include "cTypeNode.h"

class cStockNode : public cDeclNode
{
    public:
        cStockNode(cSymbol *name, cTypeNode *type, cSettingsNode *settings) 
            : cDeclNode(name) 
        {
            AddChild(type);
            AddChild(settings);
        }

        virtual string NodeType() { return string("Stock"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
