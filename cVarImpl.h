#include <string>
#include <unordered_map>
using std::string;

class cVarImpl
{
    public:
        cVarImpl(string name, bool isFloat, void *dataref)
        {
            m_name = name;
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

        void Addmin(double val)
        {
            if (m_isFloat)
                m_d_min = val;
            else
                m_l_min = val;
        }

        void Addmax(double val)
        {
            if (m_isFloat)
                m_d_max = val;
            else
                m_l_max = val;
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

        void Addupdate(double (*func)())
        {
            m_d_func = func;
            m_do_delta = false;
        }

        void Addupdate(long (*func)())
        {
            m_l_func = func;
            m_do_delta = false;
        }

        void Adddelta(double (*func)())
        {
            m_d_func = func;
            m_do_delta = true;
        }

        void Adddelta(long (*func)())
        {
            m_l_func = func;
            m_do_delta = true;
        }

        void UpdateValue()
        {
            double d_value = 0;
            long l_value = 0;

            if (m_d_func != nullptr) d_value = m_d_func();
            if (m_l_func != nullptr) l_value = m_l_func();

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
        }

        static std::unordered_map<string, cVarImpl*> VarList;
    private: 
        string m_name;
        bool m_isFloat;
        double m_d_init;
        double m_l_init;
        double m_d_min;
        double m_l_min;
        double m_d_max;
        double m_l_max;

        double *m_d_dataref;
        long *m_l_dataref;

        double (*m_d_func)() = nullptr;
        long (*m_l_func)() = nullptr;
        bool m_do_delta;
};

