#pragma once
//**************************************
// cSettingsNode.h
//
// Defines a class to represent a list of settings.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cSettingNode.h"

class cSettingsNode : public cAstNode
{
    public:
        // param is the first setting in this settings
        cSettingsNode(cSettingNode *setting = nullptr) : cAstNode()
        {
            if (setting != nullptr) AddChild(setting);
        }

        // Add another setting to the list
        void AddSetting(cSettingNode *setting) { AddChild(setting); }

        virtual string NodeType() { return string("settings"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
