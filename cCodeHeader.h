#pragma once
//*****************************************************
//
// Visitor implementation to generate stackl code
//
// Author: Phil Howard
// Email:  phil.howard@oit.edu
//

#include "cVisitor.h"
#include "cHeaderNode.h"
#include "emit.h"

class cCodeHeader : public cVisitor
{
    public:
        cCodeHeader() {}

        virtual void Visit(cHeaderNode *node)
        {
            EmitString("\n//************** header *************\n");
            EmitString(node->GetText());
            EmitString("\n\n");
        }
};
