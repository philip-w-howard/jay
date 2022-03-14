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
        virtual void Output(long index);

    protected:
        class cLogItem
        {
            public:
                cLogItem(double *data, string format)
                {
                    m_data = data;
                    m_format = format;
                    m_isFloat = true;
                }

                cLogItem(long *data, string format)
                {
                    m_data = data;
                    m_format = format;
                    m_isFloat = false;
                }

                string GetText()
                {
                    if (m_format.find("%") == string::npos)
                    {
                        if (m_isFloat)
                            return std::to_string(*(double*)m_data);
                        else
                            return std::to_string(*(long*)m_data);
                    }
                    else
                    {
                        char buff[256];

                        if (m_isFloat)
                            sprintf(buff, m_format.c_str(), *(double*)m_data);
                        else
                            sprintf(buff, m_format.c_str(), *(long*)m_data);

                        return string(buff);
                    }
                }

                string GetLabel()
                {
                    return m_format;
                }
            protected:
                void *m_data;
                bool m_isFloat;
                string m_format;
                string m_label;
        };
        int m_frequency;
        string m_filename;
        std::vector<cLogItem> m_items;
        std::ofstream m_file;

};
