#include<iostream>

#include "system.h"

using namespace std;



class BirthFlow : public Flow
{
    Variable * birthRate = nullptr;

    public:
    BirthFlow(string func, Stock * src, Stock * end, Variable * bR): Flow(func, src, end)
    {
        birthRate = bR;
    }

    //virtual ~BirthFlow() {};

    //private:
    int calculateRate()
    {
        return end->getQuantity()*(birthRate->getValue())/100;
    }
};

class DeathFlow: public Flow
{
    float deathRate = 1.1;

    public:
    DeathFlow(string func, Stock * src, Stock * end): Flow(func, src, end){}

    //virtual ~DeathFlow() {};

    //private:
    int calculateRate()
    {
        return source->getQuantity()*deathRate/100;
    }
};


int main()
{
    //init model
    System Population(1900, 200);
    Population.setTimeUnit(string("year(s)"));
    
    //stocks
    Stock * nullStock = nullptr;
    Stock pop(0, -1, 100);
    Population.addStock("Population", &pop);

    //vars
    Variable BirthRate(20.1);
    Population.addVar("BirthRate", BirthRate);
    Variable DeathRate(1.1);
    Population.addVar("DeathRate", DeathRate);

    //flows
    BirthFlow Births("Population*Birth_Rate/100", nullStock, &pop, &BirthRate);
    Population.addFlow("Births", &Births);
    DeathFlow Deaths("Population*Death_Rate/100", &pop, nullStock);
    Population.addFlow("Deaths", &Deaths);

    //Intial state
    cout << "\nInitial state of system:" << endl;
    Population.systemLog();

    //run some steps
    Population.stepForward(10);

    //read outputs
    Population.systemLog();

    //change some things

    //run again some steps

    //read outputs
}
