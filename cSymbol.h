#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent symbols.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>

using std::string;

#include "cAstNode.h"

class cSymbol : public cAstNode
{
    public:
        cSymbol();

        // param is name of symbol
        cSymbol(string name, int tokenType=-1);

        // return name of symbol
        string GetName();
        
        // Indicate what type of token this symbol represents
        // Used because keywords are stored as symbols to allow
        // case insensitivity
        void SetTokenType(int tokenType);
        int GetTokenType();

        // Associate a decl with a symbol
        cDeclNode *GetDecl();
        void SetDecl(cDeclNode *decl);

        virtual string AttributesToString();
        virtual string NodeType();
        virtual void Visit(cVisitor *visitor);
    protected:
        static long long nextId;        // Next avail symbol ID
        long long m_id;                 // Unique ID for this symbol
        string m_name;                  // name of symbol
        cDeclNode *m_decl;              // the declaration that defines this sym
        int m_tokenType;                // The yylex() return type for this sym
};
