//***************************************************
// Definition for a class that implements Jay variables
//
// The class is templated, where the template variable is the 
// system that the variable is defined in.

#include <string>
#include <unordered_map>
using std::string;

// Template variable is the Jay system the variable is defined in
template <class T> class cVarImpl
{
    public:
        // dataref is a pointer to the location that maintains the variable's
        // value
        //
        // object is the Jay system that the variable is defined in
        cVarImpl(string name, bool isFloat, void *dataref, T* object)
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

            cVarImpl::VarList[name] = this;
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

        void Addinitialize(double val)
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

        // This function gets called in order to update the variable
        void UpdateValue()
        {
            double d_value = 0;
            long l_value = 0;

            if (m_d_func != nullptr) d_value = (m_object->*m_d_func)();
            if (m_l_func != nullptr) l_value = (m_object->*m_l_func)();

            if (m_isFloat)
            {
                if (m_do_delta)
                    *m_d_dataref += (d_value + l_value);
                else
                    *m_d_dataref = (d_value + l_value);
            }
            else
            {
                if (m_do_delta)
                    *m_l_dataref += ((long)d_value + l_value);
                else
                    *m_l_dataref = ((long)d_value + l_value);
            }

            if (m_isFloat)
            {
                if (*m_d_dataref > m_d_max) *m_d_dataref = m_d_max;
                if (*m_d_dataref < m_d_min) *m_d_dataref = m_d_min;
            }
            else
            {
                if (*m_l_dataref > m_l_max) *m_l_dataref = m_l_max;
                if (*m_l_dataref < m_l_min) *m_l_dataref = m_l_min;
            }
        }

        static std::unordered_map<string, cVarImpl*> VarList;
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
};

