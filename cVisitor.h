#pragma once
//*************************************************
// Definition of Visitor base class
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
//

// Need forward declaration of all classes.
// Forward declare them to avoid circular include problems

class cAstNode;
class cCodeNode;
class cDeclNode;
class cDeclsNode;
class cFlowNode;
class cFuncNode;
class cHeaderNode;
class cIdSettingNode;
class cIntValNode;
class cOutputListNode;
class cOutputNode;
class cProgramNode;
class cRealValNode;
class cSettingNode;
class cSettingsNode;
class cSetupNode;
class cSimulationNode;
class cStockNode;
class cSymbol;
class cSystemNode;
class cSystemsListNode;
class cSystemsNode;
class cSysVarNode;
class cSysVarsNode;
class cTrailerNode;
class cTypeNode;
class cUnitsNode;
class cValueNode;
class cValueSettingNode;
class cVarNode;

class cVisitor
{
    public:
        cVisitor() {}

        // A visit method for every AST node
        virtual void Visit(cAstNode *node);
        virtual void Visit(cCodeNode *node);
        virtual void Visit(cDeclNode *node);
        virtual void Visit(cDeclsNode *node);
        virtual void Visit(cFlowNode *node);
        virtual void Visit(cFuncNode *node);
        virtual void Visit(cHeaderNode *node);
        virtual void Visit(cIdSettingNode *node);
        virtual void Visit(cIntValNode *node);
        virtual void Visit(cOutputListNode *node);
        virtual void Visit(cOutputNode *node);
        virtual void Visit(cProgramNode *node);
        virtual void Visit(cRealValNode *node);
        virtual void Visit(cSettingNode *node);
        virtual void Visit(cSettingsNode *node);
        virtual void Visit(cSetupNode *node);
        virtual void Visit(cSimulationNode *node);
        virtual void Visit(cStockNode *node);
        virtual void Visit(cSymbol *node);
        virtual void Visit(cSystemNode *node);
        virtual void Visit(cSystemsListNode *node);
        virtual void Visit(cSystemsNode *node);
        virtual void Visit(cSysVarNode *node);
        virtual void Visit(cSysVarsNode *node);
        virtual void Visit(cTrailerNode *node);
        virtual void Visit(cTypeNode *node);
        virtual void Visit(cUnitsNode *node);
        virtual void Visit(cValueNode *node);
        virtual void Visit(cValueSettingNode *node);
        virtual void Visit(cVarNode *node);


};
