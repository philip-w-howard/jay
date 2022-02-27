//**************************************
// cSymbol.cpp
//
// Defines class used to represent symbols.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>

using std::string;

#include "lex.h"
#include "astnodes.h"
#include "jayparse.h"
#include "cSymbol.h"

// ******************************************
// Default constructor
cSymbol::cSymbol()
{
    m_id = ++nextId;
    m_name = string("unnamed_") + std::to_string(m_id);
}

// **************************************************
// Constructor: this is the one that actually gets used
// param is name of symbol
cSymbol::cSymbol(string name) : cAstNode()
{
    m_id = ++nextId;
    m_name = name;
}

// ****************************************************
// return name of symbol
string cSymbol::GetName() 
{ 
    return m_name; 
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
