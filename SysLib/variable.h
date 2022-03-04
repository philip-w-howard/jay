//variable.h
//
//purpose: represent a variable as part of a dynamic system
//

class Variable
{

private:
    float value = -1;

public:

    //USE BASE MEMEBER ASSOSCIATION
    Variable(float initialValue = 0)
    {
        value = initialValue;
    }

    float & getValue()
    {
        return value;
    }

    void logStatus()
    {
        cout << "\tValue: " << value
            << endl;
    }


};

