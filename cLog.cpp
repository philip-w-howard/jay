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

    //initialize and touch file
    m_file.open(m_filename);
}

cLog::~cLog()
{
    m_file.close();
}
void cLog::AddItem(double *item, string format, string label)
{
    m_items.push_back(cLogItem(item, format, label));
}
void cLog::AddItem(long *item, string format, string label)
{
    m_items.push_back(cLogItem(item, format, label));
}

//output to file "m_filename" every m_frequency steps
void cLog::Output(long index)
{
    char buff[256];

    if (m_file.is_open())
    {
        if (index % m_frequency == 0)
        {
            //print all items
            for (auto item : m_items)
            {
                m_file << item.GetText() << "\n";
            }
            m_file << "\n";
        }
    }
    else
    {
        cout << "File " << m_filename << " was not found!\n";
    }
}
