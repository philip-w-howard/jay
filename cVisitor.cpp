//******************************************************
// Implementation of visitor base class
//
// Author: Philip Howard
// Email: phil.howard@oit.edu
//
//

#include "lex.h"
#include "cVisitor.h"
#include "astnodes.h"

void cVisitor::Visit(cAstNode *node)            { node->VisitAllChildren(this); }
void cVisitor::Visit(cCodeNode *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclNode *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclsNode *node)          { node->VisitAllChildren(this); }
void cVisitor::Visit(cFlowNode *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cFuncNode *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cHeaderNode *node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cIdSettingNode *node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cIntValNode *node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cRealValNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cSettingNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cSettingsNode *node)       { node->VisitAllChildren(this); }
void cVisitor::Visit(cSetupNode *node)          { node->VisitAllChildren(this); }
void cVisitor::Visit(cStockNode *node)          { node->VisitAllChildren(this); }
void cVisitor::Visit(cSymbol *node)             { node->VisitAllChildren(this); }
void cVisitor::Visit(cSystemNode *node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cTrailerNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cTypeNode *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cUnitsNode *node)          { node->VisitAllChildren(this); }
void cVisitor::Visit(cValueNode *node)          { node->VisitAllChildren(this); }
void cVisitor::Visit(cValueSettingNode *node)   { node->VisitAllChildren(this); }
void cVisitor::Visit(cVarNode *node)            { node->VisitAllChildren(this); }
