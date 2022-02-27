//**************************************
// cSymbol.cpp
//
// Defines class used to represent symbols.
// Later labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>

using std::string;

#include "lex.h"
#include "astnodes.h"
#include "pascalishparse.h"
#include "cSymbol.h"

// ******************************************
// Default constructor
cSymbol::cSymbol()
{
    m_id = ++nextId;
    m_name = string("unnamed_") + std::to_string(m_id);
    m_tokenType = IDENTIFIER;
}

// **************************************************
// Constructor: this is the one that actually gets used
// param is name of symbol
cSymbol::cSymbol(string name, int tokenType) : cAstNode()
{
    if (tokenType < 0) 
    {
        m_id = ++nextId;
        m_tokenType = IDENTIFIER;
    }
    else
    {
        m_tokenType = tokenType;

        if (tokenType == TYPE_ID)
            m_id = ++nextId;
        else
            m_id = 0;
    }

    m_name = name;
}

// ****************************************************
// return name of symbol
string cSymbol::GetName() 
{ 
    return m_name; 
}

//****************************************************
void cSymbol::SetTokenType(int tokenType)
{ 
    m_tokenType = tokenType; 
}
//****************************************************
int cSymbol::GetTokenType()
{ 
    return m_tokenType; 
}

//****************************************************
cDeclNode *cSymbol::GetDecl()
{ 
    return m_decl; 
}

//****************************************************
void cSymbol::SetDecl(cDeclNode *decl)
{ 
    m_decl = decl; 
}

//****************************************************
string cSymbol::AttributesToString()
{
    string result(" id=\"");
    result += std::to_string(m_id);
    result += "\" name=\"" + m_name + "\"";
    return result;
}

//****************************************************
string cSymbol::NodeType() 
{ 
    return string("sym"); 
}

//****************************************************
void cSymbol::Visit(cVisitor *visitor)
{ 
    visitor->Visit(this); 
}
