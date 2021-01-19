#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>
#include <cstdio>
#include "User.h"
#include "UsersDataFile.h"


using namespace std;

struct AdressData
{
    int     idOfAdressee=0;
    int     idOfUser=0;
    string  name;
    string  surname;
    string  phoneNumber;
    string  address;
    string  email;
};

char loadSign()
{
    string inputText = "";
    char sign  = {0};

    while (true)
    {
        getline(cin, inputText);

        if (inputText.length() == 1)
        {
            sign = inputText[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return sign;
}

string loadLineOfText()
{
    string inputText = "";
    getline(cin, inputText);
    return inputText;
}

int loadIntegerNumber()
{
    string inputText = "";
    int number = 0;

    while (true)
    {
        getline(cin, inputText);

        stringstream myStream(inputText);
        if (myStream >> number)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return number;
}


void enterNewAddressDetails(vector <AdressData> &dataOfTheAddressee, int logUserId, int &idOfLastAddressee)
{
    AdressData dataOfAddressee;
    if(!dataOfTheAddressee.empty())
        dataOfAddressee = dataOfTheAddressee.back();

    if(dataOfAddressee.idOfAdressee>idOfLastAddressee)
    {
        dataOfAddressee.idOfAdressee = dataOfAddressee.idOfAdressee + 1;
        idOfLastAddressee=dataOfAddressee.idOfAdressee;
    }
    else if(dataOfAddressee.idOfAdressee<idOfLastAddressee)
    {
        dataOfAddressee.idOfAdressee=idOfLastAddressee + 1;
        idOfLastAddressee=dataOfAddressee.idOfAdressee;
    }
    else if(dataOfAddressee.idOfAdressee==idOfLastAddressee)
    {
        dataOfAddressee.idOfAdressee = dataOfAddressee.idOfAdressee + 1;
        idOfLastAddressee=dataOfAddressee.idOfAdressee;
    }

    dataOfAddressee.idOfUser = logUserId;
    cout<<"Podaj imie adresata: ";
    dataOfAddressee.name = loadLineOfText();
    cout<<"Podaj nazwisko adresata: ";
    dataOfAddressee.surname = loadLineOfText();
    cout<<"Podaj numer telefonu adresata: ";
    dataOfAddressee.phoneNumber = loadLineOfText();
    cout<<"Podaj adres e-mail adresta: ";
    dataOfAddressee.email = loadLineOfText();
    cout<<"Podaj adres zamieszakania adresta: ";
    dataOfAddressee.address = loadLineOfText();

    dataOfTheAddressee.push_back(dataOfAddressee);
    cout<<"Adresat zostal utworzony."<<endl;
    Sleep(1500);
}

void saveAddedAddresseeToTxtFile(vector<AdressData> dataOfListAddressee)
{
    fstream file;
    file.open("Adresaci.txt", ios::out|ios::app );
    AdressData dataOfAddressee = dataOfListAddressee.back();

    file<<dataOfAddressee.idOfAdressee<<'|'<<dataOfAddressee.idOfUser<<'|'<<dataOfAddressee.name<<'|'<<dataOfAddressee.surname<<'|'<<dataOfAddressee.phoneNumber<<'|'<<dataOfAddressee.email<<'|'<<dataOfAddressee.address<<'|'<<'\n';

    file.close();
}

bool comp( const AdressData &l, const AdressData &r )
{
    return l.idOfAdressee < r.idOfAdressee;
}

void saveAddresseesViaTempTxtFile(vector<AdressData> &AddresseeList, int id, int &idOfLastAddresse)
{
    vector<AdressData> tempListOfAddresse;
    AdressData dataOfAddresseeFromTxtFile;
    AdressData dataOfAddresseeFromTempList;

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream file, fileTemp;
    fileTemp.open("Adresaci_tymczasowy.txt", ios::out);

    if(file.good()==true)
    {
        file.open("Adresaci.txt", ios::in );
    }

    for(vector<AdressData>::iterator itr=AddresseeList.begin(), endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        while(getline(file,lineInTxtFile,'|'))
        {
            switch(numberOfTheLineInTxtFile)
            {
            case 1:
                dataOfAddresseeFromTxtFile.idOfAdressee=atoi(lineInTxtFile.c_str());
                break;
            case 2:
                dataOfAddresseeFromTxtFile.idOfUser=atoi(lineInTxtFile.c_str());
                break;
            case 3:
                dataOfAddresseeFromTxtFile.name = lineInTxtFile;
                break;
            case 4:
                dataOfAddresseeFromTxtFile.surname = lineInTxtFile;
                break;
            case 5:
                dataOfAddresseeFromTxtFile.phoneNumber = lineInTxtFile;
                break;
            case 6:
                dataOfAddresseeFromTxtFile.email = lineInTxtFile;
                break;
            case 7:
                dataOfAddresseeFromTxtFile.address = lineInTxtFile;
                break;
            }
            ++numberOfTheLineInTxtFile;
            if(numberOfTheLineInTxtFile==8)
            {
                numberOfTheLineInTxtFile=1;
                if((dataOfAddresseeFromTxtFile.idOfAdressee==itr->idOfAdressee)&&(itr->idOfAdressee!=id)&&(itr->idOfAdressee!=idOfLastAddresse))
                {
                    tempListOfAddresse.push_back(*itr);
                }
                if((dataOfAddresseeFromTxtFile.idOfAdressee!=itr->idOfAdressee)&&(dataOfAddresseeFromTxtFile.idOfAdressee!=id)&&(dataOfAddresseeFromTxtFile.idOfAdressee!=idOfLastAddresse))
                {
                    tempListOfAddresse.push_back(dataOfAddresseeFromTxtFile);
                }
            }
        }

        if((itr->idOfAdressee==id))
        {
            tempListOfAddresse.push_back(*itr);

        }else if(!(dataOfAddresseeFromTxtFile.idOfAdressee==idOfLastAddresse)&&(itr->idOfAdressee==idOfLastAddresse)&&(itr->idOfAdressee!=id))
        {
            tempListOfAddresse.push_back(*itr);
        }
    }

    sort(tempListOfAddresse.begin(), tempListOfAddresse.end(), comp );
    dataOfAddresseeFromTempList = tempListOfAddresse.back();
    idOfLastAddresse = dataOfAddresseeFromTempList.idOfAdressee;

    for(vector<AdressData>::iterator itr2=tempListOfAddresse.begin(), endVectorWord2=tempListOfAddresse.end(); itr2!=endVectorWord2; itr2++)
    {
        fileTemp<<itr2->idOfAdressee<<'|'<<itr2->idOfUser<<'|'<<itr2->name<<'|'<<itr2->surname<<'|'<<itr2->phoneNumber<<'|'<<itr2->email<<'|'<<itr2->address<<'|'<<'\n';
    }

    file.close();
    fileTemp.close();

    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}

void readFromTxtFile(vector<AdressData> &writeToAddresseeList, int logUserId, int &idOfLastAddresse)
{
    AdressData dataOfAddresseeFromTxtFile;

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream file;

    if(file.good()==true)
    {
        file.open("Adresaci.txt", ios::in );
    }
    else if (file.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku 'Adresaci.txt'!"<<endl;
        Sleep(3000);
        file.open("Adresaci.txt", ios::out );
        if(file.good()==true)
        {
            cout<<"Zostal utworzony nowy plik 'Adresaci.txt'z baza danych adresatow!"<<endl;
            Sleep(3000);
        }
        else if (file.good()==false)
        {
            cout<<"Nie udalo sie utworzyc pliku ""Adresaci.txt""!"<<endl;
            Sleep(3000);
            exit(0);
        }
    }

    while(getline(file,lineInTxtFile,'|'))
    {
        switch(numberOfTheLineInTxtFile)
        {
        case 1:
            dataOfAddresseeFromTxtFile.idOfAdressee=atoi(lineInTxtFile.c_str());
            break;
        case 2:
            dataOfAddresseeFromTxtFile.idOfUser=atoi(lineInTxtFile.c_str());
            break;
        case 3:
            dataOfAddresseeFromTxtFile.name = lineInTxtFile;
            break;
        case 4:
            dataOfAddresseeFromTxtFile.surname = lineInTxtFile;
            break;
        case 5:
            dataOfAddresseeFromTxtFile.phoneNumber = lineInTxtFile;
            break;
        case 6:
            dataOfAddresseeFromTxtFile.email = lineInTxtFile;
            break;
        case 7:
            dataOfAddresseeFromTxtFile.address = lineInTxtFile;
            break;
        }
        ++numberOfTheLineInTxtFile;
        if(numberOfTheLineInTxtFile==8)
        {
            numberOfTheLineInTxtFile=1;
            if(dataOfAddresseeFromTxtFile.idOfUser==logUserId)
            {
                writeToAddresseeList.push_back(dataOfAddresseeFromTxtFile);
            }
            if(idOfLastAddresse<dataOfAddresseeFromTxtFile.idOfAdressee)
            {
                idOfLastAddresse=dataOfAddresseeFromTxtFile.idOfAdressee;
            }
        }
    }
    file.close();
}

void searchTheAddresseeByName(vector<AdressData> &AddresseeList)
{
    string name;
    system("cls");
    cout<<"Podaj imie adresata: ";
    name = loadLineOfText();

    for(vector<AdressData>::iterator itr = AddresseeList.begin(), endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        if(itr->name==name)
        {
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"=========================================================\n";
        }
    }
    cout << "Aby wyjsc do menu wcisnij dowolny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
    loadSign();
}

void searchTheAddresseeBySurname(vector<AdressData> &AddresseeList)
{
    string surname;
    system("cls");
    cout<<"Podaj nazwisko adresata: ";
    surname = loadLineOfText();

    for(vector<AdressData>::iterator itr = AddresseeList.begin(), endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        if(itr->surname==surname)
        {
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"=========================================================\n";
        }
    }
    cout << "Aby wyjsc do menu wcisnij dowolny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
    loadSign();
}

bool editAddressee(vector<AdressData> &AddresseeList, int &id, int logUserId)
{
    bool operationOnAddressee=false;
    cout<<"Podaj id adresata: ";
    id = loadIntegerNumber();

    AdressData dataOfAddresseeFromTxtFile;

    string lineInTxtFile;

    for(vector<AdressData>::iterator  itr = AddresseeList.begin(), endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        if(itr->idOfAdressee==id&&itr->idOfUser==logUserId)
        {
            char menuItem='0';

            while(menuItem!= '7')
            {
                switch(menuItem)
                {
                case '0':
                {
                    system("cls");
                    cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
                    cout<<"Imie adresata: "<<itr->name<<endl;
                    cout<<"Nazwisko adresata: "<<itr->surname<<endl;
                    cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
                    cout<<"Adres e-mail adresta: "<<itr->email<<endl;
                    cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
                    cout<<"=========================================================\n";

                    cout<<"1.Edytuj imie adresata."<<endl;
                    cout<<"2.Edytuj nazwisko adresata."<<endl;
                    cout<<"3.Edytuj numer telefonu adresata."<<endl;
                    cout<<"4.Edytuj adres e-mail adresta."<<endl;
                    cout<<"5.Edytuj adres zamieszakania adresta."<<endl;
                    cout<<"6.Wyjscie do Menu glowengo."<<endl;
                    menuItem = loadSign();
                }
                break;
                case '1':
                {
                    cout<<"Podaj imie adresata: ";
                    itr->name = loadLineOfText();
                    operationOnAddressee=true;
                    menuItem= '0';
                }
                break;
                case '2':
                {
                    cout<<"Podaj nazwisko adresata: ";
                    itr->surname = loadLineOfText();
                    operationOnAddressee=true;
                    menuItem= '0';
                }
                break;
                case '3':
                {
                    cout<<"Podaj numer telefonu adresata: ";
                    itr->phoneNumber = loadLineOfText();
                    operationOnAddressee=true;
                    menuItem= '0';
                }
                break;
                case '4':
                {
                    cout<<"Podaj adres e-mail adresta: ";
                    itr->email = loadLineOfText();
                    operationOnAddressee=true;
                    menuItem= '0';
                }
                break;
                case '5':
                {
                    cout<<"Podaj adres zamieszakania adresta: ";
                    itr->address = loadLineOfText();
                    operationOnAddressee=true;
                    menuItem= '0';
                }
                break;
                case '6':
                {
                    menuItem= '7';
                }
                break;
                default:
                {
                    cout<<"Wybierz poprawna opcje menu wpisujac poprawna liczbe oraz potwierdzajac klawisz 'ENTER'!";
                    Sleep(2000);
                    menuItem = '0';
                }
                break;
                }
            }
        }
    }
    if(operationOnAddressee==true)
    {
        cout<<"Adresat zostal edytowany."<<endl;
        Sleep(1500);
    }
    else
    {
        cout<<"Nie ma takiego adresata!"<<endl;
        Sleep(2000);
    }
    return operationOnAddressee;
}

void displayAdresseesId(vector<AdressData> printedVector)
{
    for(vector<AdressData>::iterator itr = printedVector.begin(), endVectorData=printedVector.end(); itr!=endVectorData; itr++)
    {
        cout<<"Numer id adresata: "<<itr->idOfAdressee<<", "<<"Imie adresata: "<<itr->name<<", "<<"Nazwisko adresata: "<<itr->surname<<endl;
    }
}

void printingTheVector(vector<AdressData> printedVector)
{
    for(vector<AdressData>::iterator itr = printedVector.begin(), endVectorData=printedVector.end(); itr!=endVectorData; itr++)
    {
        cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
        cout<<"Imie adresata: "<<itr->name<<endl;
        cout<<"Nazwisko adresata: "<<itr->surname<<endl;
        cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
        cout<<"Adres e-mail adresta: "<<itr->email<<endl;
        cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
        cout<<"=========================================================\n";
    }
    cout << "Aby wyjsc do menu wcisnij dowolny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
    loadSign();
}

bool eraseAdressee(vector<AdressData> &vectorOfDeleteAddresses, int &id, int logUserId)
{
    bool operationOnAddressee=false;
    cout<<"Podaj id adresata: ";
    id = loadIntegerNumber();

    vector<AdressData>::iterator itr = vectorOfDeleteAddresses.begin();
    AdressData dataOfAddresseeFromTxtFile;
    string lineInTxtFile;

    for(vector<AdressData>::iterator endVectorWord=vectorOfDeleteAddresses.end(); itr!=endVectorWord; itr++)
    {
        if(itr->idOfAdressee==id&&itr->idOfUser==logUserId)
        {
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"=========================================================\n";

            cout << "Jezeli chcesz usunac adresata o wybranym id:" << itr->idOfAdressee << " " << itr->name << " " << itr->surname <<" "<< "wcisnij klawisz 't'"<<endl;
            cout << "Aby wyjsc do menu wcisnij dowolny inny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
            if(loadSign()=='t')
            {
                vectorOfDeleteAddresses.erase(itr);
                cout<< "Adresat o wskazanym id zostal usuniety !"<<endl;
                operationOnAddressee=true;
                Sleep(1500);
            }
            else
            {
                break;
            }
        }
    }
    if(operationOnAddressee==false)
    {
        cout<<"Nie ma takiego adresata!"<<endl;
        Sleep(2000);
    }
    return operationOnAddressee;
}

int main()
{
    User user;
    //UsersDataFile userData;
    vector<AdressData> listOfAddresse;

    int id=0;
    int idOfLastAddresse=0;
    int logUserId=user.getLoggedUserId();
    bool resultOperation=false;

    char wybor;
    char menuItemSelection = '0';

    string surname, name;

    user.readUsersFromTxtFile();

    while(1)
    {
        if(logUserId==0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            wybor=loadSign();

            if(wybor == '1')
            {
                user.userRegistration();
                user.saveUsersToTxtFile();
            }
            else if(wybor == '2')
            {
                user.logging();
                logUserId=user.getLoggedUserId();
                readFromTxtFile(listOfAddresse,logUserId,idOfLastAddresse);
            }
            else if(wybor == '9')
            {
                cout<<"Wcisnij enter, aby zamknac program...";
                cin.get();
                exit(0);
            }
        }
        else
        {
            switch(menuItemSelection)
            {
            case '0':
            {
                system("cls");
                cout << "KSIAZKA ADRESOWA\n";
                cout << "1. Dodaj adresata."  << endl;
                cout << "2. Wyszukaj po imieniu."      << endl;
                cout << "3. Wyszukaj po nazwisku."    << endl;
                cout << "4. Wyswietl wszystkich adresatow."  << endl;
                cout << "5. Usun adresata."      << endl;
                cout << "6. Edytuj adresata."    << endl;
                cout << "7. Zmiana hasla" << endl;
                cout << "8. Wylogowanie" << endl;
                cout << "Twoj wybor:"    << endl;

                menuItemSelection=loadSign();
            }
            break;

            case '1':
            {
                enterNewAddressDetails(listOfAddresse,logUserId,idOfLastAddresse);
                saveAddresseesViaTempTxtFile(listOfAddresse,id,idOfLastAddresse);
                menuItemSelection = '0';
            }
            break;

            case '2':
            {
                searchTheAddresseeByName(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '3':
            {
                searchTheAddresseeBySurname(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '4':
            {
                printingTheVector(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '5':
            {
                displayAdresseesId(listOfAddresse);
                resultOperation=eraseAdressee(listOfAddresse,id,logUserId);
                if(resultOperation==true)
                    saveAddresseesViaTempTxtFile(listOfAddresse,id,idOfLastAddresse);
                menuItemSelection = '0';
            }
            break;

            case '6':
            {
                displayAdresseesId(listOfAddresse);
                resultOperation=editAddressee(listOfAddresse,id,logUserId);
                if(resultOperation==true)
                    saveAddresseesViaTempTxtFile(listOfAddresse,id,idOfLastAddresse);
                menuItemSelection = '0';
            }
            break;

            case '7':
            {
                user.passwordChange();
                user.saveUsersToTxtFile();
                menuItemSelection = '0';
            }
            break;

            case '8':
            {
                listOfAddresse.clear();
                menuItemSelection = '0';
                logUserId = 0;
            }
            break;

            default:
            {
                cout<<"Wybierz poprawna opcje menu wpisujac poprawna liczbe oraz potwierdzajac klawisz ENTER!";
                Sleep(2000);
                logUserId = 0;
            }
            break;

            }
        }
    }
    return 0;
}
