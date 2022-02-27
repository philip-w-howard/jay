#pragma once
//**************************************
// cSymbolTable.h
//
// Defines a nested symbol table.
// Individual levels of the symbol table use a std::unordered_map from the STL
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Dec. 15, 2016
//

#include <string>
#include <unordered_map>
#include <list>

using std::string;
using std::unordered_map;
using std::list;

#include "cSymbol.h"

class cSymbolTable
{
    public:
        // Type for a single symbol table
        typedef unordered_map<string, cSymbol *> symbolTable_t;

        // Increasing the scope must create a symbol table, so we call
        // that function to do the actual work of creating the object
        cSymbolTable()
        { 
            IncreaseScope();
        }

        // Increase the scope: add a level to the nested symbol table
        // Return value is the newly created scope
        symbolTable_t *IncreaseScope()
        {
            symbolTable_t *table = new symbolTable_t();
            m_SymbolTable.push_front(table);

            return table;
        }

        // Decrease the scope: remove the outer-most scope.
        // Returned value is the outer-most scope AFTER the pop.
        //
        // NOTE: do NOT clean up memory after poping the table. Parts of the
        // AST will probably contain pointers to symbols in the popped table.
        symbolTable_t *DecreaseScope()
        {
            // Avoid seg faults if someone tries to DecreaseScope past the
            // global scope.
            if (m_SymbolTable.size() > 1) m_SymbolTable.pop_front();

            return m_SymbolTable.front();
        }

        // insert a symbol into the table
        void Insert(cSymbol *sym)
        {
            (*m_SymbolTable.front())[sym->GetName()] = sym;
        }

        // Do a lookup in the nested table. Return the symbol for the outer-most
        // match. 
        // Returns nullptr if no match is found.
        cSymbol *GlobalLookup(string name)
        {
            cSymbol *sym = nullptr;

            auto it = m_SymbolTable.begin();

            while (it != m_SymbolTable.end())
            {
                sym = FindInTable(*it, name);
                if (sym != nullptr) return sym;

                it++;
            }

            return nullptr;
        }

        // Find a symbol in the outer-most scope.
        // Returns nullptr if the symbol is not found.
        cSymbol *LocalLookup(string name)
        {
            return FindInTable(m_SymbolTable.front(), name);
        }

    protected:
        // Utility routine to do a lookup in a single level's table
        // params are the table to do the lookup in and the name of the symbol
        // Returns nullptr if the symbol isn't found.
        // NOTE: this is static because it is the symbolTable_t that is passed
        //      as a param that it operates. It does not act on the class
        //      where the call takes place.
        static cSymbol *FindInTable(symbolTable_t *table, string& name)
        {
            auto got = table->find(name);

            if (got == table->end())
                return nullptr;
            else
                return got->second;
        }

        // list of symbol tables. The list contains the different levels
        // in the nested table.
        list<symbolTable_t *> m_SymbolTable;
};

// Declaration for the global symbol table.
// Definition is in main.cpp
extern cSymbolTable g_symbolTable;
