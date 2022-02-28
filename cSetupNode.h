#pragma once
//**************************************
// cSetupNode
//
// Defines class for stocks
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSettingsNode.h"

class cSetupNode : public cDeclNode
{
    public:
        cSetupNode(cSettingsNode *settings) : cDeclNode() 
        {
            AddChild(settings);
        }

        virtual string NodeType() { return string("Setup"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
