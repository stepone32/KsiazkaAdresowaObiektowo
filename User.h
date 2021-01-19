#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

class User
{
    int idOfUser, idOfLoggedUser;
    string userName, password;
    vector<User> users;

public:
    User(int=0, int=0, string="", string="");
    ~User();

    friend string loadLineOfText();

    int getLoggedUserId();
    void userRegistration();
    int logging();
    void passwordChange();
    void saveUsersToTxtFile();
    void readUsersFromTxtFile();

};
