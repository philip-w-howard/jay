#pragma once
//***************************************************
// Definition for a class that implements Jay flows
//
// The class is templated, where the template variable is the 
// system that the variable is defined in.

#include <string>
using std::string;

#include "cStockImpl.h"

// Template variable is the Jay system the variable is defined in
template <class T> class cFlowImpl
{
    public:
        // dataref is a pointer to the location that maintains the variable's
        // value
        //
        // object is the Jay system that the variable is defined in
        cFlowImpl(string name, bool isFloat, void *dataref, T* object)
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

        void Addsource(cStockImpl<T> *source)
        {
            m_source = source;
        }

        void Adddestination(cStockImpl<T> *destination)
        {
            m_destination = destination;
        }

        void Step() 
        {
            //execute flow function to determine flow rate
            double d_value = 0;
            long l_value = 0;

            if (m_d_func != nullptr) d_value = (m_object->*m_d_func)();
            if (m_l_func != nullptr) l_value = (m_object->*m_l_func)();

            //limit flow rate
            if (m_isFloat)
            {
                if (d_value > m_d_max) d_value = m_d_max;
                if (d_value < m_d_min) d_value = m_d_min;
            }
            else
            {
                if (l_value > m_l_max) l_value = m_l_max;
                if (l_value < m_l_min) l_value = m_l_min;
            }
            
            //templates could clean this up

            //apply flow rate to src and destination
            if (m_isFloat)
            {
                if (m_source != nullptr && m_destination != nullptr)
                {
                    m_destination->add(m_source->subtract(d_value));
                }
                else if (m_destination != nullptr)
                {
                    m_destination->add(d_value);
                }
                else if (m_source != nullptr)
                {
                    m_source->subtract(d_value);
                }
            }
            else
            {
                if (m_source != nullptr && m_destination != nullptr)
                {
                    m_destination->add(m_source->subtract(l_value));
                }
                else if (m_destination != nullptr)
                {
                    m_destination->add(l_value);
                }
                else if (m_source != nullptr)
                {
                    m_source->subtract(l_value);
                }
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

        double *m_d_dataref;
        long *m_l_dataref;

        double (T::*m_d_func)() = nullptr;
        long (T::*m_l_func)() = nullptr;
        bool m_do_delta;

        cStockImpl<T> *m_source = nullptr;
        cStockImpl<T> *m_destination = nullptr;
};

