#ifndef ADMINCONTROL_H
#define ADMINCONTROLS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <conio.h>

using namespace std;

class admin{
    private:
        string username;
        string password;
    public:
        bool checkUser(string);
        bool checkUser(string,int);
        bool login();
        void clearHOF();
        void changePass();
        void addAdmin();
        void menu();
};

#endif // ADMINCONTROL_H
