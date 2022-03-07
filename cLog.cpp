//************************************************************
// Class to implement a log file
// Constructor specifies the filename and the frequency.
// frequency of 1 means log every step.
// frequency of N means log every Nth step

#include "cLog.h"

cLog::cLog(string filename, int frequency)
{
    m_frequency = frequency;
    m_filename = filename;
}
void cLog::AddItem(double *item, string format)
{
    pair toAdd(item, format);
    m_doubles.push_back(toAdd);
}
void cLog::AddItem(long *item, string format)
{
    pair toAdd(item, format);
    m_longs.push_back(toAdd);
}
void cLog::Output(long index)
{
    //outputs to stdout for now
    if (index % m_frequency == 0)
    {
        cout << index << ":\n";
        //print all items
        for (auto item : m_doubles)
        {
            cout << item.second <<*item.first << "\n";
        }
        for (auto item : m_longs)
        {
            cout << item.second <<*item.first << "\n";
        }
    }
}

