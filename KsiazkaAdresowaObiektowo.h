#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;

class User
{
    int idOfUser=0;
    string userName, password;


public:
    User(int=0, string="", string="");
    ~User();

    friend string loadLineOfText();

    void userRegistration(vector<User> &users);
    int logging(vector<User> users);
    void passwordChange(vector<User> &users, int idUser);
    void enterTheUsersDetails(vector<User> &users);
    void saveUsersToTxtFile(vector<User> &users);
    void readUsersFromTxtFile(vector<User> &users);

};
