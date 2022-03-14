#pragma once
//************************************************************
// Class to implement a log file
// Constructor specifies the filename and the frequency.
// frequency of 1 means log every step.
// frequency of N means log every Nth step

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>

#include <stdio.h>

using std::string;
using std::cout;
using std::pair;

class cLog
{
    public:
        cLog(string filename, int frequency = 1);
        ~cLog();
        void AddItem(double *item, string format);
        void AddItem(long *item, string format);
        void Print(long index);
        virtual void Output(long index);

    protected:
        int m_frequency;
        string m_filename;
        std::vector<pair<double*, string>>m_doubles;
        std::vector<pair<long*, string>>m_longs;
        std::ofstream m_file;
};
