//system.h 
//
//purpose: encapsulate a dynamic system

#include <iostream>
#include <string.h>
#include <unordered_map>
#include <utility>

#include "stock.h"
#include "flow.h"
#include "variable.h"

//naughty
using namespace std;

class System
{

private:
    
    int start = -1;
    int end = -1;
    int currentTime = -1;
    string timeUnit = "Time Unit(s)";

    //key value: name
    //stocks
    unordered_map <string, Stock*> stocks;
    //flows
    unordered_map <string,Flow*> flows;
    //vars
    unordered_map <string,Variable> vars;

    //internal methods
    //process a single time step
    void iterate()
    {
        currentTime++;
        for (auto flow : flows)
        {
            flow.second->process();
        }
    }

protected:

    /*
    Stock & GetStockRef( string name )
    {
        cout << flows["name"] << endl;
    }
    */

public:

    System (int startTime, int duration)
    {
        start = startTime;
        end = startTime + duration;
        currentTime = start;
    }

    //Mutators

    void stepForward(int steps)
    {
        for (int i = 0; i  < steps; i++)
        {
            iterate();
        }
    }

    void setTimeUnit(string newUnitName)
    {
        timeUnit = newUnitName;
    }

    void addStock(string name, Stock * toAdd)
    {
        stocks[name] = toAdd;
    }

    void addFlow(string name, Flow * toAdd)
    {
        flows[name] = toAdd;
    }

    void addVar(string name, Variable toAdd)
    {
        vars[name] = toAdd;
    }

    //Accessors

    //print the exact state of the system at the current time.
    void systemLog()
    {
        cout << "Start Time: " << start << "\nEnd Time: " << end 
            << "\nCurrent Time: " << currentTime << " " << timeUnit
            << "\n------------< S T O C K S >-------------" 
            << endl;
        for (auto stock : stocks)
        {
            cout << stock.first << "\n";
            stock.second->logStatus();
        }
        cout << "------------< F L O W S >-------------" << endl;
        for (auto flow : flows)
        {
            cout << flow.first << "\n";
            flow.second->logStatus();
        }
        cout << "------------< V A R I A B L E S >-------------" << endl;
        for (auto var : vars)
        {
            cout << var.first << "\n";
            var.second.logStatus();
        }
        cout << "--< E N D >--" << endl;
    }
};
