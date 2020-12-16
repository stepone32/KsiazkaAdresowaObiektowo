#include "User.h"

using namespace std;

string loadLineOfText();

User::User(int id, int logId, string name, string passw)
{
    idOfUser=id;
    idOfLoggedUser=logId;
    userName=name;
    password=passw;
}

User::~User()
{

}

void User::userRegistration()
{
    User user;
    string userName, password;
    cout << "Podaj nazwe uzytkownika: ";
    userName=loadLineOfText();

    if(users.empty())
    {
        cout << "Podaj haslo: ";
        password=loadLineOfText();
        user.userName=userName;
        user.password=password;
        user.idOfUser=user.idOfUser+1;
        users.push_back(user);
        cout << "Konto zalozone." << endl;
        Sleep(1000);
    }
    else if(!users.empty())
    {
        for(vector<User>::iterator itr = users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
        {
            if(itr->userName == userName)
            {
                cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                userName=loadLineOfText();
            }
        }
        user=users.back();
        cout << "Podaj haslo: ";
        password=loadLineOfText();
        user.userName=userName;
        user.password=password;
        user.idOfUser=user.idOfUser+1;
        users.push_back(user);
        cout << "Konto zalozone." << endl;
        Sleep(1000);
    }
}

int User::logging()
{
    User userLog;
    string userName, password;
    cout << "Podaj nazwe uzytkownika: ";
    userName=loadLineOfText();

    for(vector<User>::iterator itr = users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
    {
        if(itr->userName == userName)
        {
            for(int proby=0; proby<3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ":";
                password=loadLineOfText();
                if(itr->password==password)
                {
                    cout << "Zalogowales sie.";
                    Sleep(1000);
                    idOfLoggedUser=itr->idOfUser;
                    return 0;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba.";
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem";
    Sleep(1500);
    return 0;
}

int User::getLoggedUserId()
{
    return idOfLoggedUser;
}

void User::passwordChange()
{
    string password;
    cout << "Podaj haslo:";
    password=loadLineOfText();

    for(vector<User>::iterator itr=users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
    {
        if(itr->idOfUser==idOfLoggedUser)
        {
            itr->password=password;
            cout << "Haslo zostalo zmienione." << endl;
            Sleep(1500);
        }
    }
}

void User::enterTheUsersDetails()
{
    User dataOfUser;
    if(!users.empty())
        dataOfUser = users.back();
    else
        dataOfUser.idOfUser=0;

    dataOfUser.idOfUser = dataOfUser.idOfUser + 1;
    cout<<"Podaj nazwie uzytkownika: ";
    dataOfUser.userName = loadLineOfText();
    cout<<"Podaj haslo uzytkownika: ";
    dataOfUser.password = loadLineOfText();

    users.push_back(dataOfUser);
    cout<<"User zostal utworzony."<<endl;
    Sleep(1500);
}

void User::saveUsersToTxtFile()
{
    fstream fileUsers;
    fileUsers.open("Uzytkownicy.txt", ios::out );

    for(vector<User>::iterator itr = users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
    {
        fileUsers<<itr->idOfUser<<'|'<<itr->userName<<'|'<<itr->password<<'|'<<'\n';
    }
    fileUsers.close();
}

void User::readUsersFromTxtFile()
{
    User dataOfUser;

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream fileUsers;

    if(fileUsers.good()==true)
    {
        fileUsers.open("Uzytkownicy.txt", ios::in );
    }
    else if (fileUsers.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku 'Uzytkownicy.txt'!"<<endl;
        Sleep(3000);
        fileUsers.open("Uzytkownicy.txt", ios::out );
        if(fileUsers.good()==true)
        {
            cout<<"Zostal utworzony nowy plik 'Uzytkownicy.txt'z baza danych uzytkownikow!"<<endl;
            Sleep(3000);
        }
        else if (fileUsers.good()==false)
        {
            cout<<"Nie udalo sie utworzyc pliku ""Uzytkownicy.txt""!"<<endl;
            Sleep(3000);
            exit(0);
        }
    }

    while(getline(fileUsers,lineInTxtFile,'|') )
    {
        switch(numberOfTheLineInTxtFile)
        {
        case 1:
            dataOfUser.idOfUser = atoi(lineInTxtFile.c_str());
            break;
        case 2:
            dataOfUser.userName = lineInTxtFile;
            break;
        case 3:
            dataOfUser.password = lineInTxtFile;
            break;
        }
        ++numberOfTheLineInTxtFile;
        if(numberOfTheLineInTxtFile==4)
        {
            numberOfTheLineInTxtFile=1;
            users.push_back(dataOfUser);
        }
    }
    fileUsers.close();
}
