#pragma once
//**************************************
// cAstNode.h
//
// pure virtual base class for all AST nodes
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
//

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

#include "cVisitor.h"

// The following are defined in lex.h, but can't include due to circularity
extern int yylineno;        // Need to be able to store line numbers
extern int yynerrs;         // Increment on each semantic error

// Declare the Semantic Error routine used at parse time.
// By declaring it here, all AST node implementations have access to it.
void SemanticParseError(std::string error);

class cAstNode
{
    public:
        //*************************************
        // Constructor
        cAstNode() : m_LineNum(yylineno), m_hasSemanticError(false) {}

    protected:
        //*************************************
        // Add a child to this node
        void AddChild(cAstNode *child)
        {
            m_children.push_back(child);
        }

        //*************************************
        // Copy all children from one node into this node
        void AddAllChildren(cAstNode *node)
        {
            if (node != nullptr && node->HasChildren())
            {
                for (auto it=node->m_children.begin(); 
                        it != node->m_children.end(); 
                        it++)
                {
                    if ( (*it) != nullptr) AddChild(*it);
                }
            }
        }

        //*************************************
        bool HasChildren()      { return !m_children.empty(); }

        //*************************************
        int NumChildren()       { return (int)m_children.size(); }

        //*************************************
        // Return a child by index
        cAstNode* GetChild(int child)
        {
            if (child >= (int)m_children.size()) return nullptr;
            return m_children[child];
        }

        //*************************************
        // Set a child by index. The child must already exist
        void SetChild(int index, cAstNode *child)
        {
            m_children[index] = child;
        }

    //*****************************************
    // The following are only used by the ToString function. They should
    // not be called anywhere else.

        //*************************************
        // Return the name of the node type
        virtual string NodeType() = 0; //      { return "AST"; }

        //*************************************
        // Must be overriden by nodes that have attributes
        virtual string AttributesToString()   { return string(""); }

    public:
        //*************************************
        // The following functions are public, but their use is limited:
        //    ToString should only be called by main
        //
        //    The VisitAllChildren should only be called by the Visitor base
        //    class.
        //    The Visit() function should only be called within derivitives of
        //    the Visitor class.
        //    SemanticError() function should only be called within derivitives
        //    of the Visitor class.
        //*************************************

        //*************************************
        // return a string representation of the node
        string ToString() 
        {
            string result("");

            result += "<" + NodeType();
            result += AttributesToString();

            if (HasChildren())
            {
                result += ">";
                for (auto it=m_children.begin(); it != m_children.end(); it++)
                {
                    if ( (*it) != nullptr) result += (*it)->ToString();
                }
            }

            if (HasChildren()) 
                result += "</" + NodeType() + ">\n";
            else
                result += " />";

            return result;
        }

        //*************************************
        // Used to print semantic errors
        void SemanticError(string message)
        {
            std::cout << "ERROR: " << message << " near line " << m_LineNum 
                << "\n";
            yynerrs++;
            m_hasSemanticError = true;
        }

        void VisitAllChildren(cVisitor* visitor)
        {
            for (auto it=m_children.begin(); it<m_children.end(); it++)
            {
                if ((*it) != nullptr) (*it)->Visit(visitor);
            }
        }

        //*************************************
        // Used by visitor pattern. Every node must override with:
        //    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual void Visit(cVisitor *visitor) = 0;

        //*************************************
        // Do a deep check to see if this node or its children have semantic
        // errors
        bool HasSemanticError()
        {
            if (m_hasSemanticError) 
                return true;
            else
            {
                for (auto it=m_children.begin(); it != m_children.end(); it++)
                {
                    if ( (*it) != nullptr && (*it)->HasSemanticError())
                    {
                        return true;
                    }
                }
            }

            return false;
        }

    private:
        vector<cAstNode *> m_children;      // list of all children
        int m_LineNum;                      // The source line at the time the
                                            // node was created
        bool m_hasSemanticError;
};

