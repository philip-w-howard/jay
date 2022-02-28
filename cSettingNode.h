#pragma once
//**************************************
// cSettingNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"

class cSettingNode : public cAstNode
{
    public:
        cSettingNode() : cAstNode() {}

        void AddSetting(cSettingNode *setting) { AddChild(setting); }
};
