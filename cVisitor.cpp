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

void cVisitor::Visit(cArrayDeclNode *node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cAssignNode *node)       { node->VisitAllChildren(this); }
void cVisitor::Visit(cAstNode *node)          { node->VisitAllChildren(this); }
void cVisitor::Visit(cBaseTypeNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cBinaryExprNode *node)   { node->VisitAllChildren(this); }
void cVisitor::Visit(cBlockNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cConstDeclNode *node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclNode *node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclsNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cExprListNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cExprNode *node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cFuncDeclNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cFuncExprNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cIdListNode *node)       { node->VisitAllChildren(this); }
void cVisitor::Visit(cIfNode *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cIntExprNode *node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cNilNode *node)          { node->VisitAllChildren(this); }
void cVisitor::Visit(cOpNode *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cProcCallNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cProcDeclNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cProgramNode *node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cRangeDeclNode *node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cRealExprNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cRecordDeclNode *node)   { node->VisitAllChildren(this); }
void cVisitor::Visit(cStmtNode *node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cStmtsNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cSymbol *node)           { node->VisitAllChildren(this); }
void cVisitor::Visit(cUnaryExprNode *node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cVarDeclNode *node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cVarDeclsNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cVarExprNode *node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cWhileNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cWriteNode *node)        { node->VisitAllChildren(this); }

