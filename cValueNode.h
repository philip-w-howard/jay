#pragma once
//**************************************
// cValueNode.h
//
// Defines an AST base class for values
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"

class cValueNode : public cAstNode
{
    public:
        // param is the value of the integer constant
        cValueNode() : cAstNode() {}

        virtual string GetTextValue() = 0;
};
