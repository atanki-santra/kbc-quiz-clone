#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int main()
{
    cout<<"These are the rules for the quiz\n"<<endl;
    cout<<"-> The player will have to answer 16 questions one by one."<<endl;
    cout<<"-> Each question will have 4 options with only one option being the correct option."<<endl;
    cout<<"-> Player has to enter the option number to select the answer."<<endl;
    cout<<"-> If answered correctly, the player will be awarded with points and will move forward"<<endl;
    cout<<"if not, the player will loose and the earned points will be displayed."<<endl;
    cout<<"-> The 5th, 10th & 15th question will be checkpoints, if you cross them they will be the minimum points you will earn"<<endl;
    cout<<"-> If you answer incorrectly you will loose the game and your points will be the same as your last checkpoint."<<endl;
    cout<<"-> The player will have an option to Quit on each question and go safely with the points secured."<<endl;
    cout<<"In order to quit enter Q/q."<<endl;
    cout<<"-> The player will be given 3 lifelines\n\ta.50:50 = F/f\n\tb.Double Dip = T/t\n\tc.Audience Poll = P/p"<<endl;
    cout<<"The input to call the lifelines are given with the respective lifeline name"<<endl;
    cout<<"-> The instructions to use a lifeline will be diplayed when asked for a lifeline"<<endl;
    cout<<"-> A prompt to confirm the selection of lifeline will also be there."<<endl;
    cout<<"-> Answering the 16th Questions will be Optional, but if you opt to answer the question you will not able to use"<<endl;
    cout<<"\ta. Any Lifeline."<<endl;
    cout<<"\tb. Quit option."<<endl;
    cout<<"->If the player answer all the questions he/she wins.\n"<<endl;
    cout<<"THESE WERE ALL THE RULES\nNOW ENJOY THE QUIZ! HAVE FUN!"<<endl;
}

