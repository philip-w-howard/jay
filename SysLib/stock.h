//stockh
//
//purpose: represent a stock as part of a dynamic system
//
#pragma once

#include <iostream>

using std::cout;
using std::endl;

class Stock
{

private:
    int min = -1;
    int max = -1;
    int init = -1;
    int quantity = -1;


public:

    //USE BASE MEMEBER ASSOSCIATION
    Stock(int minimum = 0, int maximum = 100, int initialQuantity = 0)
    {
        min = minimum;
        max = maximum;
        init =  initialQuantity;
        quantity = initialQuantity;
    }

    //MUTATORS
    void add(int toAdd)
    {
        quantity += toAdd;
    }

    int subtract (int toTake)
    {
        int difference = 0;
        if (quantity > toTake)
        {
            quantity += toTake;
            return toTake;
        }
        else //take whatever is left
        {
            toTake = quantity;
            quantity += toTake;
            return toTake;
        }

    }

    //accessors
    int getQuantity()
    {
        return quantity;
    }

    void logStatus()
    {   
        cout << "\tQuantity: " << quantity << "\n"
            << "\tMaximum: " << max << "\n"
            << "\tMinimum: " << min
            << "\tInitial Quantity: " << min
            << endl;
    }


};
