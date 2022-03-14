#include "cCsv.h"

void cCsv::MarkColumns()
{
    if (m_file.is_open())
    {
        m_file << "Sequence, ";
        for (auto item : m_items)
        {
            m_file << item.GetLabel() << ", ";
        }
        m_file << "\n";

        m_labelsAreDone = true;
    }
    else
    {
        cout << "File " << m_filename << " was not found!\n";
    }
}

//output to file "m_filename.csv" every m_frequency steps
void cCsv::Output(long index)
{
    if (!m_labelsAreDone) MarkColumns();

    if (m_file.is_open())
    {
        if (index % m_frequency == 0)
        {
            m_file << index << ", ";
            //print all items
            for (auto item : m_items)
            {
                m_file << item.GetText() << ", ";
            }
            m_file << "\n";
        }
    }
    else
    {
        cout << "File " << m_filename << " was not found!\n";
    }

}

