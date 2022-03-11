#include "cCsv.h"
//output to file "m_filename.csv" every m_frequency steps
void cCsv::Output(long index)
{
    std::fstream file;
    file.open(m_filename, std::ios_base::app);
    if (index % m_frequency == 0)
    {
        file << index << ", ";
        //print all items
        for (auto item : m_doubles)
        {
            file << *item.first << ", ";
        }
        for (auto item : m_longs)
        {
            file << *item.first << ", ";
        }
        file << "\n";
    }
    file.close();
}

