#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <windows.h>
//#include "User.h"

using namespace std;

class UsersDataFile
{
   // vector<User> users;

public:
    UsersDataFile(int=0, int=0, string="", string="");
    ~UsersDataFile();

    friend string loadLineOfText();

    void enterTheUsersDetails();
    void saveUsersToTxtFile();
    void readUsersFromTxtFile();

};
