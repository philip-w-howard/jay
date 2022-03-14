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
void cLog::AddItem(double *item, string format)
{
    pair<double*, string> toAdd(item, format);
    m_doubles.push_back(toAdd);
}
void cLog::AddItem(long *item, string format)
{
    pair<long*, string> toAdd(item, format);
    m_longs.push_back(toAdd);
}

//output to file "m_filename" every m_frequency steps
void cLog::Output(long index)
{
    char buff[256];

    if (m_file.is_open())
    {
        if (index % m_frequency == 0)
        {
            //cout << index << ":\n";
            //print all items
            for (auto item : m_doubles)
            {
                sprintf(buff, item.second.c_str(), *(item.first));
                m_file << buff << "\n";
                //m_file << item.second << *item.first << "\n";
            }
            for (auto item : m_longs)
            {
                m_file << item.second << *item.first << "\n";
            }
            m_file << "\n";
        }
    }
    else
    {
        cout << "File " << m_filename << " was not found!\n";
    }
}

//output to stdout
void cLog::Print(long index)
{
    //char temp [99]; //unwise 
    if (index % m_frequency == 0)
    {
        cout << index << ":\n";
        //print all items
        for (auto item : m_doubles)
        {
            //sprintf wasn't working, skipped for time/counsel
            //sprintf(temp, item.second.c_str(), item.first); 
            //cout << temp;

            cout << item.second <<*item.first << "\n";
        }
        for (auto item : m_longs)
        {
            //sprintf(temp, item.second.c_str(), item.first); 
            //cout << temp;

            cout << item.second <<*item.first << "\n";
        }
    }
}

