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

void cVisitor::Visit(cAstNode *node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclNode *node)       { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclsNode *node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cEquationNode *node)   { node->VisitAllChildren(this); }
void cVisitor::Visit(cIntValNode *node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cRealValNode *node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cSymbol *node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cSystemNode *node)     { node->VisitAllChildren(this); }

