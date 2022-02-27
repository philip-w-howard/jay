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
class cDeclNode;
class cDeclsNode;
class cEquationNode;
class cIntValNode;
class cRealValNode;
class cSymbol;
class cSystemNode;

class cVisitor
{
    public:
        cVisitor() {}

        // A visit method for every AST node
        virtual void Visit(cAstNode *node);
        virtual void Visit(cDeclNode *node);
        virtual void Visit(cDeclsNode *node);
        virtual void Visit(cEquationNode *node);
        virtual void Visit(cIntValNode *node);
        virtual void Visit(cRealValNode *node);
        virtual void Visit(cSymbol *node);
        virtual void Visit(cSystemNode *node);
};
