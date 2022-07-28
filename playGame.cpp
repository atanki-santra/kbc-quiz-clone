#include "playGame.h"

Game::Game(){}

Game::Game(string name){
    this->name=name;
    this->questionNo=1;
    this->score=scoreArr[0];
    this->section="1";
}

Game Game::operator++(int){
    this->score=this->scoreArr[this->questionNo];
    this->questionNo++;
    if(this->questionNo==6){
        this->section="2";
        vq.clear();
    }
    else if(this->questionNo==11){
        this->section="3";
        vq.clear();
    }
    else if(this->questionNo==16){
        this->section="4";
        vq.clear();
    }
    Game result;
    result.questionNo = this->questionNo;
    result.score=this->score;
    return result;
}

Game Game::operator--(int){
    if(this->questionNo<=5){
        this->questionNo=0;
    }
    else if(this->questionNo<=10){
        this->questionNo=5;
    }
    else if(this->questionNo<=15){
        this->questionNo=10;
    }
    this->score=this->scoreArr[this->questionNo];
    Game result;
    result.questionNo = this->questionNo;
    result.score=this->score;
    return result;
}

void Game::rules(){
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
    cout<<"-> Answering the 16th Questions will be Optional, but if you opt to answer the question you will not able to use"<<endl;
    cout<<"\ta. Any Lifeline."<<endl;
    cout<<"\tb. Quit option."<<endl;
    cout<<"->If the player answer all the questions he/she wins.\n"<<endl;
    cout<<"THESE WERE ALL THE RULES\nNOW ENJOY THE QUIZ! HAVE FUN!"<<endl;
}

ostream& operator<<(ostream& sout,const Game& g){
    sout<<g.name<<"\tScore: "<<g.score<<"\n\nUpcoming Question "<<g.questionNo<<endl<<endl;;
    return sout;
}

Game::~Game(){
}

void Game::getQuestion(string sec){
    //opening file
    ifstream fin;
    fin.open(sec);
    //checking whether file opening was successful
    if(!fin){
        cout<<"Error in opening Questions file"<<endl;
    }

    ostringstream oss;
    //generating random index number for question to be extracted
    srand(time(NULL));

    qindex:
    q_index=((rand()%20)+1);
    vector<int>::iterator it;
    it= find(vq.begin(),vq.end(),q_index);
    if(it!=vq.end()){
        goto qindex;
    }
    vq.push_back(q_index);


    oss<<"<"<<q_index<<">";
    string target = oss.str();
    string qno,temp;


    //extracting question corresponding to the index number
    while(!fin.eof()){
        getline(fin,qno,':');
        if(target.compare(qno)==0){
            getline(fin,question);
            getline(fin,qp2);
            fin.close();
        }
        else{
            getline(fin,temp);
        }
    }
}

void Game::getOptions(string sect){
    //opening file
    ifstream fin;
    fin.open(sect);
    //checking whether file opening was successful
    if(!fin){
        cout<<"Error in opening Options file"<<endl;
    }

    ostringstream oss;
    oss<<"<"<<q_index<<">";
    string target = oss.str();
    string qno,temp,str;

    //extracting options set corresponding to the index number
    while(!fin.eof()){
        getline(fin,qno,':');

        if(target.compare(qno)==0){
            getline(fin,str);
            istringstream iss(str);
            int i=0;
            while(!iss.eof()){
                getline(iss,opt[i],':');
                i++;
            }
            fin.close();
        }
        else{
            getline(fin,temp);
        }
    }
    shuffle(opt);
}

//Modern Version Fisher Yates Algorithm
void Game::shuffle(string* options){
    srand(time(NULL));
    string temp;
    for(int li = 3; li>1;li--){
        int ri = rand()%(li+1);
        temp = options[li];
        options[li]=options[ri];
        options[ri]=temp;
    }
}

void Game::getAnswer(string sec){
//opening file
    ifstream fin;
    fin.open(sec);
    //checking whether file opening was successful
    if(!fin){
        cout<<"Error in opening Answers file"<<endl;
    }

    ostringstream oss;

    oss<<"<"<<q_index<<">";
    string target = oss.str();
    string qno,temp;

    //extracting answer corresponding to the index number
    while(!fin.eof()){
        getline(fin,qno,':');
        if(target.compare(qno)==0){
            getline(fin,answer);
            fin.close();
        }
        else{
            getline(fin,temp);
        }
    }
    a_index= indexAns(answer);
}

int Game::indexAns(string a){
    for(int i =0; i<4; i++){
        if(opt[i]==a){
            return i;
        }
    }
}

void Game::initQues(){
    getQuestion("QS"+section+".txt");
    getOptions("OptS"+section+".txt");
    getAnswer("AnsS"+section+".txt");
}

void Game::ask(){
    DisplayQ(question);
    DisplayOpt(("A."+opt[0]),("B."+opt[1]));
    DisplayOpt(("C."+opt[2]),("D."+opt[3]));
}

string Game::dashes(int n){
    string d=string(n,'-');
    return d;
}

string Game::blanks(int n){
    string b=string(n,' ');
    return b;
}

void Game::DisplayQ(string Q){
    if(qp2=="#:")
        qp2="";
    Q = blanks((100-question.length())/2) + Q;
    qp2 = blanks((100-qp2.length())/2) + qp2;
    cout<<" "<<dashes(100)<<"  "<<endl;
    cout<<"/ "<<setw(100)<<left<<Q<<" \\"<<endl;
    cout<<"\\ "<<setw(100)<<qp2<<" /"<<endl;
    cout<<" "<<dashes(100)<<"  "<<endl;
}

void Game::DisplayOpt(string Opt1, string Opt2){
    cout<<"  "<<dashes(50)<<" "<<" "<<dashes(50)<<"  "<<endl;
    cout<<"< "<<setw(50)<<Opt1<<">"<<"< "<<setw(50)<<Opt2<<">"<<endl;
    cout<<"  "<<dashes(50)<<" "<<" "<<dashes(50)<<"  "<<endl;
}

bool Game::checkAns(char c){
    bool flag;
    flag =(a_index==(c-97)||a_index==(c-65));
    return flag;
}

void Game::fiftyFifty(){
    srand(time(NULL));
    //randomly choosing options
    int r1,r2;
    do{
        r1= rand()%4;
        r2= rand()%4;
    }while(r1==r2||r1==a_index||r2==a_index);
    opt[r1]= " ";
    opt[r2]= " ";
}

void Game::audiencePoll(){
    srand(time(NULL));
    int rno[4];
    reinitialise:
    int lim=100;
    for(int i=0; i<3; i++){
        rno[i]=(rand()%lim)+1;
        lim-=rno[i];
    }
    rno[3]=lim;

    //if two array elements come out to be same we will reinitialise
    for(int i=0;i<3;i++){
        for(int j=i+1;j<4;j++){
            if(rno[i]==rno[j]){
                goto reinitialise;
            }
        }
    }

    //highest value in rno[] will be assigned to the answer
    //a_index
    int hvi = 0;//highest value index
    for(int i =1;i<4;i++){
        if(rno[i]>rno[hvi]){
            hvi=i;
        }
    }
    int prob = (rand()%100)+1;
    if(prob<95){
        if(a_index!=hvi){
            //swap
            rno[hvi] = rno[a_index]+rno[hvi];
            rno[a_index] = rno[hvi]-rno[a_index];
            rno[hvi]=rno[hvi]-rno[a_index];
        }
    }
    else{
        if(a_index==hvi){
            //swap
            int ri;
            do{
                ri=(rand()%4);//random index
            }while(ri==a_index);
            cout<<"ri : "<<ri<<endl;
            rno[ri] = rno[a_index]+rno[ri];
            rno[a_index] = rno[ri]-rno[a_index];
            rno[ri]=rno[ri]-rno[a_index];
        }
    }
    for(int i=0; i<4;i++){
        cout<<(char)('A'+i)<<" : "<<string(rno[i],'\xfe')<<endl;
    }
}

void Game::quit(const Game& g){
    cout<<"Better Luck Next Time"<<endl;
    cout<<"\nYour final standing is :\n"<<g;
}

void Game::record(){
        ofstream fout;
        fout.open("Hall of Fame.txt",ios::app | ios::out);
        if(!fout){
            cout<<"Error in opening Hall of Fame.txt"<<endl;
        }
        fstream fmv;
        fmv.open("Misc values.txt");
        if(!fmv){
            cout<<"Error in opening Misc values.txt"<<endl;
        }
        fstream tfile;
        tfile.open("temp.txt", ios::in | ios::out | ios::trunc);
        if(!tfile){
            cout<<"Error in opening temp.txt"<<endl;
        }
        int srno;
        string temp;
        while(!fmv.eof()){
            getline(fmv,temp);
            string temp2;
            istringstream iss(temp);
            while(!iss.eof()){
                getline(iss,temp2,':');
                if("srno"==temp2){
                    getline(iss,temp2);
                    srno = stoi(temp2);
                    srno++;
                    tfile<<"srno:"<<srno;
                    goto out;
                }
            }
        }
        out:
        fmv.close();
        fmv.open("Misc values.txt",ios::in | ios::out | ios::trunc);
        if(!fmv){
            cout<<"Error in opening Misc values.txt"<<endl;
        }
        tfile.seekg(0,ios::beg);
        while(!tfile.eof()){
            getline(tfile,temp);
            fmv<<temp<<endl;
        }
        fout<<srno<<","<<name<<","<<score<<endl;
        fout.close();
        fmv.close();
        tfile.close();
}

int Game::play(){
    system("CLS");
                string name;
                cout<<"Player! Please Enter Your Name :"<<endl;
                cin>>name;
                Game player(name);
                //ask for showing rules
                system("CLS");
                cout<<name<<", would you like to visit the rules of the quiz?(Y/N)"<<endl;
                bool f2 = true;
                do{
                    char ch = getch();
                    if(ch=='y'||ch=='Y'){
                        player.rules();
                        f2=false;
                    }
                    else if(ch=='n'||ch=='N'){
                        cout<<"Let's Start with the Quiz then!"<<endl;
                        f2=false;
                    }
                }while(f2);

                //ask wether the player is ready
                cout<<"Are you Ready? (Press Y to continue)"<<endl;
                f2 = true;
                do{
                    char ch = getch();
                    if(ch=='y'||ch=='Y'){
                        cout<<"Okay Let's Start!"<<endl;
                        f2=false;
                    }
                }while(f2);
                //start game
                f2 = true;
                bool fl=false,ff = true,dd=true,ap=true,lq=true,qs=false,show=true;
                char ans;
                do{
                    if(!fl){
                        player.initQues();
                    }
                    if(player.questionNo==16&&show){
                        system("CLS");
                        cout<<"Do you want to attempt the 16th Question?(Y/N)\nYou will not be allowed to quit or use any left lifelines for this Question.\n"<<endl;
                        do{
                            char ch = getch();
                            if(ch=='y'||ch=='Y'){
                                break;
                            }
                            else if(ch=='n'||ch=='N'){
                                player.record();
                                cout<<"\nYour Final Standing is :"<<endl;
                                cout<<player;
                                cout<<"Press any key to continue...."<<endl;
                                getch();
                                goto BYE;
                            }
                        }while(true);
                        ff = false,dd=false,ap=false,lq=false,qs=true,fl=true,show=false;
                    }
                    system("CLS");
                    player.ask();
                    ans=getch();
                    switch(ans){
                            case 'a':
                            case 'b':
                            case 'c':
                            case 'd':
                            case 'A':
                            case 'B':
                            case 'C':
                            case 'D':{
                                for(int i = 0; i<5; i++){
                                        system("CLS");
                                        cout<<"checking answer";
                                        for(int j = 0; j<3; j++){
                                            Sleep(50);
                                            cout<<".";
                                        }
                                    }
                                    system("CLS");
                                if(player.checkAns(ans)){
                                    if(qs){
                                        if(player.youWon()==1){
                                            player++;
                                            player.record();
                                            cout<<"Press any key to continue...."<<endl;
                                            getch();
                                            goto BYE;
                                        }
                                    }
                                    player++;
                                    cout<<"This was the Correct Answer, "<<name<<"!\nYour score has been updated."<<endl;
                                    cout<<"\nYour current standing is :"<<endl;
                                    cout<<player;
                                    Sleep(2000);
                                    cout<<"Press Any key to move to the next question"<<endl;
                                    getch();
                                    if(fl)
                                        fl=false;
                                }
                                else{
                                    cout<<"This was the Wrong Answer, "<<name<<"!"<<endl;
                                    cout<<"It was nice playing with you, Better Luck Next time!"<<endl;
                                    player--;
                                    cout<<"\nYour Final Standing is:"<<endl;
                                    player.record();
                                    cout<<player;
                                    f2=false;
                                    if(fl)
                                        fl=false;
                                    cout<<"Do you want to play again(P) or go to the main menu(M)?"<<endl;
                                    do{
                                        char ch = getch();
                                        if(ch=='p'||ch=='P'){
                                            return 1;
                                        }
                                        else if(ch=='m'||ch=='M'){
                                            return 0;
                                        }
                                    }while(true);
                                }
                            }
                                break;
                            case 'q':
                            case 'Q':{
                                if(lq){
                                    bool q = true;
                                    cout<<"Are you sure you want to Quit?(Y/N)"<<endl;
                                    do{
                                        char ch = getch();
                                        if(ch=='y'||ch=='Y'){
                                            system("CLS");
                                            player.quit(player);
                                            f2=false;
                                            q=false;
                                            player.record();
                                            cout<<"Do you want to play again(P) or go to the main menu(M)?"<<endl;
                                            do{
                                                char ch = getch();
                                                if(ch=='p'||ch=='P'){
                                                    return 1;
                                                }
                                                else if(ch=='m'||ch=='M'){
                                                    return 0;
                                                }
                                            }while(true);
                                        }
                                        else if(ch=='n'||ch=='N'){
                                            cout<<"That's the spirit you can do it, "<<name<<"!"<<endl;
                                            q=false;
                                            fl=true;
                                        }
                                    }while(q);
                                }
                            }

                                break;
                            case 'f':
                            case 'F':{
                                if(!fl&&ff){
                                    player.fiftyFifty();
                                    fl=true;
                                    ff=false;
                                    for(int i = 0; i<5; i++){
                                        system("CLS");
                                        cout<<"implementing 50:50";
                                        for(int j = 0; j<3; j++){
                                            Sleep(50);
                                            cout<<".";
                                        }
                                    }
                                }
                                else{
                                    if(fl)
                                        cout<<"Already a Lifeline is in action"<<endl;
                                    else if(!ff)
                                        cout<<"Fifty fifty Lifeline is already exhausted"<<endl;
                                    Sleep(2000);
                                }
                            }
                                break;
                            case 'p':
                            case 'P':{
                                if(!fl&&ap){
                                    fl=true;
                                    ap=false;
                                    cout<<"implementing audience poll";
                                    for(int j = 0; j<3; j++){
                                        Sleep(200);
                                        cout<<".";
                                    }
                                    cout<<endl<<endl;
                                    player.audiencePoll();
                                    cout<<"Press any key to continue..."<<endl;
                                    getch();
                                }
                                else{
                                    if(fl)
                                        cout<<"Already a Lifeline is in action"<<endl;
                                    else if(!ap)
                                        cout<<"Audience Poll Lifeline is already exhausted"<<endl;
                                    Sleep(2000);
                                }
                            }
                                break;
                            case 't':
                            case 'T':{
                                if(!fl&&dd){
                                    lq=false;
                                    fl=true;
                                    dd=false;
                                    cout<<"implementing Double Dip";
                                    for(int j = 0; j<3; j++){
                                        Sleep(200);
                                        cout<<".";
                                    }
                                    cout<<endl<<endl;
                                    cout<<"Double Dip Lifeline is active now...";
                                    cout<<endl<<endl;
                                    cout<<"Enter your first choice"<<endl;
                                    bool f3 = true;
                                    int count=2;
                                    do{
                                        if(count==0){
                                            player--;
                                            cout<<"Option "<<ans<<" is the wrong answer."<<endl;
                                            cout<<"You have Exhausted all your Chances, "<<name<<"\nUnfortunately the Game ends here!"<<endl;
                                            cout<<"\nYour final standing is :"<<endl;
                                            cout<<player<<endl;

                                            f2=false;
                                            cout<<"Do you want to play again(P) or go to the main menu(M)?"<<endl;
                                            do{
                                                char ch = getch();
                                                if(ch=='p'||ch=='P'){
                                                    return 1;
                                                }
                                                else if(ch=='m'||ch=='M'){
                                                    return 0;
                                                }
                                            }while(true);
                                        }
                                        ans = getch();
                                        switch(ans){
                                            case 'a':
                                            case 'b':
                                            case 'c':
                                            case 'd':
                                            case 'A':
                                            case 'B':
                                            case 'C':
                                            case 'D':{
                                                count--;
                                                if(player.checkAns(ans)){
                                                    cout<<"Option "<<ans<<" is the right answer."<<endl<<endl;
                                                    Sleep(1000);
                                                    cout<<"Press any key to continue"<<endl;
                                                    getch();
                                                    system("CLS");
                                                    fl=false;
                                                    cout<<"\nYour current standing is :"<<endl;
                                                    cout<<player;
                                                    Sleep(2000);
                                                    cout<<"Press Any key to move to the next question"<<endl;
                                                    getch();
                                                    break;
                                                }
                                                else if(count == 1){
                                                    cout<<"Option "<<ans<<" is the wrong answer."<<endl<<endl;
                                                    cout<<"Enter your second choice"<<endl<<endl;
                                                    continue;
                                                }
                                            }
                                            default:{
                                                continue;
                                            }
                                        }
                                        break;
                                    }while(f3);
                                }
                                else{
                                    if(fl)
                                        cout<<"Already a Lifeline is in action"<<endl;
                                    else if(!dd)
                                        cout<<"Double Dip Lifeline is already exhausted"<<endl;
                                    Sleep(2000);
                                }
                            }
                                break;
                            default:
                                continue;
                    }
                }while(f2);
                BYE:
            return 0;
}

int Game::youWon(){
cout<<"$$\\     $$\\  $$$$$$\\  $$\\   $$\\       $$\\      $$\\  $$$$$$\\  $$\\   $$\\ $$\\\n";
cout<<"\\$$\\   $$  |$$  __$$\\ $$ |  $$ |      $$ | $\\  $$ |$$  __$$\\ $$$\\  $$ |$$ |\n";
cout<<" \\$$\\ $$  / $$ /  $$ |$$ |  $$ |      $$ |$$$\\ $$ |$$ /  $$ |$$$$\\ $$ |$$ |\n";
cout<<"  \\$$$$  /  $$ |  $$ |$$ |  $$ |      $$ $$ $$\\$$ |$$ |  $$ |$$ $$\\$$ |$$ |\n";
cout<<"   \\$$  /   $$ |  $$ |$$ |  $$ |      $$$$  _$$$$ |$$ |  $$ |$$ \\$$$$ |\\__|\n";
cout<<"    $$ |    $$ |  $$ |$$ |  $$ |      $$$  / \\$$$ |$$ |  $$ |$$ |\\$$$ |    \n";
cout<<"    $$ |     $$$$$$  |\\$$$$$$  |      $$  /   \\$$ | $$$$$$  |$$ | \\$$ |$$\\ \n";
cout<<"    \\__|     \\______/  \\______/       \\__/     \\__| \\______/ \\__|  \\__|\\__|\n";
Sleep(2000);
return 1;
}

