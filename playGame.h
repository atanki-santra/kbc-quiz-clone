#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

class Game{
    private:
        string name;
        int score;
        int scoreArr[17]={0,1000,2000,3000,5000,10000,20000,40000,80000,160000,320000,640000,1250000,2500000,5000000,10000000,70000000};
        int questionNo;
        string section;
        int q_index;
        int a_index;
        string question;
        string qp2;
        string opt[4];
        string answer;

    public:
        Game();
        Game(string);
        Game operator++(int);
        Game operator--(int);
        ~Game();
        void rules();
        void ready();
        friend ostream& operator<<(ostream&, const Game&);

        vector <int> vq;
        void initQues();
        void getQuestion(string);
        void getOptions(string);
        void getAnswer(string);
        void shuffle(string*);
        int indexAns(string );
        void ask();
        string dashes(int);
        string blanks(int);
        void DisplayQ(string);
        void DisplayOpt(string, string);
        bool checkAns(char);
        void fiftyFifty();
        void audiencePoll();
        void quit(const Game&);
        void record();
        int play();
        int youWon();
};

#endif //PLAYGAME_H
