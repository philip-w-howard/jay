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
        void AddSetting(cSettingNode *setting) 
        {
            if (HasSetting(setting->GetName()))
            {
                SemanticParseError("Duplicate setting: " + setting->GetName());
            }
            else
            {
                AddChild(setting); 
            }
        }

        cSettingNode *GetSetting(string name)
        {
            cSettingNode *setting;
            for (int ii=0; ii<NumChildren(); ii++)
            {
                setting = dynamic_cast<cSettingNode*>(GetChild(ii));
                if (setting->GetName() == name) return setting;
            }

            return nullptr;
        }

        bool HasSetting(string name)
        {
            if (GetSetting(name) != nullptr) return true;
            return false;
        }

        virtual string NodeType() { return string("settings"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
