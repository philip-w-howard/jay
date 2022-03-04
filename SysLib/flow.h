//flow.h
//
//purpose: represent a flow as part of a dynamic system
//

#pragma once

#include "stock.h"
#include <iostream>
#include "string.h"

using std::string;
using std::cout;
using std::endl;

class Flow
{

protected:
    string function = string("");
    Stock * source = nullptr;
    Stock * end = nullptr;

public:

    //USE BASE MEMBER INITIALIZATION
    Flow()
    {
        //was getting template errors, this fixed it.    
    }

    Flow (string flowFunction, Stock * sourceStock, Stock * endStock)
    {
        function = flowFunction;
        source = sourceStock;
        end = endStock;
    }

    void process()
    {
        if (source != nullptr && end != nullptr)
        {
            //end->add(source->subtract(1));
            end->add(source->subtract(calculateRate()));
        }
        else if (end != nullptr)
        {
            end->add(calculateRate());
        }
        else if (source != nullptr)
        {
            source->subtract(calculateRate());
        }
    }

    void logStatus()
    {
        cout << "\tFunction: " << function << "\n"
            << "\tSource Stock: " << "\n"
            << "\tEnd Stock: " 
            << endl;
    }

    //overloaded to allow C++ to compile expressions
    //would a function ptr be cheaper? 
    //yes, but not as flexible, this lets us assign infolinks at compilation
    virtual int calculateRate()
    {
        return 0;
    }
};

