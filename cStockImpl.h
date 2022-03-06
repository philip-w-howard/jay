#pragma once
//***************************************************
// Definition for a class that implements Jay stocks
//
// The class is templated, where the template variable is the 
// system that the variable is defined in.

#include <string>
using std::string;

// Template variable is the Jay system the variable is defined in
// do stocks need to be templated as well?
template <class T> class cStockImpl
{
    public:
        // dataref is a pointer to the location that maintains the variable's
        // value
        //
        // object is the Jay system that the variable is defined in
        cStockImpl(string name, bool isFloat, void *dataref, T* object)
        {
            m_name = name;
            m_object = object;
            m_do_delta = true;

            if (isFloat)
            {
                m_isFloat = true;
                m_d_dataref = (double *)dataref;
            }
            else
            {
                m_isFloat = false;
                m_l_dataref = (long *)dataref;
            }
        }

        // Add a minimum value
        void Addmin(double val)
        {
            if (m_isFloat)
                m_d_min = val;
            else
                m_l_min = (long)val;
        }

        // add a maximum value
        void Addmax(double val)
        {
            if (m_isFloat)
                m_d_max = val;
            else
                m_l_max = (long)val;
        }

        void Addinitial(double val)
        {
            if (m_isFloat)
            {
                m_d_init = val;
                *m_d_dataref = val;
            }
            else
            {
                m_l_init  = (long)val;
                *m_l_dataref = (long)val;
            }
        }

        void Addupdate(double (T::*func)())
        {
            m_d_func = func;
            m_do_delta = false;
        }

        void Addupdate(long (T::*func)())
        {
            m_l_func = func;
            m_do_delta = false;
        }

        void Adddelta(double (T::*func)())
        {
            m_d_func = func;
            m_do_delta = true;
        }

        void Adddelta(long (T::*func)())
        {
            m_l_func = func;
            m_do_delta = true;
        }
    
        void add(double toAdd)
        {
            *m_d_dataref += toAdd;
        }

        double subtract(double toTake)
        {
            //this logic needs to be redone to account for negative values & min/max
            double difference = 0;
            if (*m_d_dataref > toTake)
            {
                *m_d_dataref += toTake;
                return toTake;
            }
            else //take whatever is left
            {
                toTake = *m_d_dataref;
                *m_d_dataref += toTake;
                return toTake;
            }

        }


    private: 
        T *m_object;
        string m_name;
        bool m_isFloat;
        double m_d_init;
        long m_l_init;
        double m_d_min;
        long m_l_min;
        double m_d_max;
        long m_l_max;

        //actual vaue stored in stock
        double *m_d_dataref;
        long *m_l_dataref;

        double (T::*m_d_func)() = nullptr;
        long (T::*m_l_func)() = nullptr;
        bool m_do_delta;
};

