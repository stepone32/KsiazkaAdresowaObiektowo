#include <iostream>

using namespace std;

class DataManage
{
    public:
    virtual void readData()=0;
    virtual void saveData()=0;
    virtual void printData()=0;
};
