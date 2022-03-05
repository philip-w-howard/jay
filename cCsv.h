//************************************************************
// Class to implement a csv style log file
// Constructor specifies the filename and the frequency.
// frequency of 1 means log every step.
// frequency of N means log every Nth step

#include "Log.h"

class Csv() : public Log
{
    public:
        Csv(string filename, int frequency = 1) : Log(filename, frequency)
        {}

        virtual void Output(long index);
}
