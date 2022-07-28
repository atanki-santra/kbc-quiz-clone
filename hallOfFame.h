#ifndef HALLOFFAME_H
#define HALLOFFAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>

class HOF{
    public:
        void showHOF(){
            cout<<"______  _________ ______ ______        _______ __________       _________________ ______  _____________\n";
            cout<<"___  / / /___    |___  / ___  /        __  __ \\___  ____/       ___  ____/___    |___   |/  /___  ____/\n";
            cout<<"__  /_/ / __  /| |__  /  __  /         _  / / /__  /_           __  /_    __  /| |__  /|_/ / __  __/   \n";
            cout<<"_  __  /  _  ___ |_  /____  /___       / /_/ / _  __/           _  __/    _  ___ |_  /  / /  _  /___   \n";
            cout<<"/_/ /_/   /_/  |_|/_____//_____/       \\____/  /_/              /_/       /_/  |_|/_/  /_/   /_____/   \n\n\n";
            ifstream fin("Hall of Fame.txt");
            //Sr No.,Name,Score
            string str;
            int width[3]={5,15,10};
            while(!fin.eof()){
                int it=0;
                getline(fin,str);
                istringstream iss(str);
                //cout<<str<<endl;
                string temp;
                while(!iss.eof()){
                    getline(iss,temp,',');
                    cout<<setw(width[it])<<left<<temp;
                    it++;
                }
                cout<<endl;
            }
            cout<<"Press any key to go to the Main Menu...";
            getch();
        }
};

#endif // HALLOFFAME_H
