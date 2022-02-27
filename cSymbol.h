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
        cSymbol(string name);

        // return name of symbol
        string GetName();
        
        virtual string AttributesToString();
        virtual string NodeType();
        virtual void Visit(cVisitor *visitor);
    protected:
        static long long nextId;        // Next avail symbol ID
        long long m_id;                 // Unique ID for this symbol
        string m_name;                  // name of symbol
};
