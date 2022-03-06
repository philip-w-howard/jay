#pragma once
//************************************************************
// Class to implement a log file
// Constructor specifies the filename and the frequency.
// frequency of 1 means log every step.
// frequency of N means log every Nth step

class cLog
{
    public:
        cLog(string filename, int frequency = 1);
        void AddItem(double *item, string format);
        void AddItem(long *item, string format);
        virtual void Output(long index);
};
