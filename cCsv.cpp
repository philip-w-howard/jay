#include "cCsv.h"

void cCsv::MarkColumns()
{
    m_file.open(m_filename, std::ios::app);
    if (m_file)
    {
        for (auto item : m_doubles)
        {
            m_file << item.second << ", ";
        }
        for (auto item : m_longs)
        {
            m_file << item.second << ", ";
        }
        m_file << "\n";
        m_file.close();
    }
    else
    {
        cout << "File " << m_filename << " was not found!\n";
    }
}

//output to file "m_filename.csv" every m_frequency steps
void cCsv::Output(long index)
{
    m_file.open(m_filename, std::ios::app);
    if (m_file)
    {
        if (index % m_frequency == 0)
        {
            m_file << index << ", ";
            //print all items
            for (auto item : m_doubles)
            {
                m_file << *item.first << ", ";
            }
            for (auto item : m_longs)
            {
                m_file << *item.first << ", ";
            }
            m_file << "\n";
        }
        m_file.close();
    }
    else
    {
        cout << "File " << m_filename << " was not found!\n";
    }

}

