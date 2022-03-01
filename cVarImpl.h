#include <string>
#include <unordered_map>

// I'm sure there is a template way to do this, but hey, I'm a C programmer
#define ADDFUNC(name, var) \
    void name (double x) { \
        if (m_isFloat) m_d_ ## var = x; \
        else m_l_ ## var = (long)x; \
    } \

class cVarImpl
{
    public:
        cVarImpl(string name, bool isFloat, void *dataref)
        {
            m_name = name;
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

        ADDFUNC(Addmax, max)
        ADDFUNC(Addmin, min)
        ADDFUNC(Addinitialize, init)

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

