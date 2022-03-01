#pragma once
//*****************************************************
//
// Visitor implementation to generate stackl code
//
// Author: Phil Howard
// Email:  phil.howard@oit.edu
//

#include "cVisitor.h"
#include "cTrailerNode.h"
#include "emit.h"

class cCodeTrailer : public cVisitor
{
    public:
        cCodeTrailer() {}

        virtual void Visit(cTrailerNode *node)
        {
            EmitString("\n//************** trailer *************\n");
            EmitString(node->GetText());
            EmitString("\n\n");
        }
};
