#pragma once
//************************************************************
// Class to implement a csv style log file
// Constructor specifies the filename and the frequency.
// frequency of 1 means log every step.
// frequency of N means log every Nth step

#include "cLog.h"

class cCsv : public cLog
{
    public:
        cCsv(string filename, int frequency = 1) : cLog(filename, frequency)
        {}

        virtual void Output(long index);
};
