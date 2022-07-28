#include "final.h"

void Final::exe()
{
    MAINMENU:
    system("CLS");
    cout<<"$$\\   $$\\ $$$$$$$\\   $$$$$$\\         $$$$$$\\  $$\\   $$\\ $$$$$$\\ $$$$$$$$\\\n";
    cout<<"$$ | $$  |$$  __$$\\ $$  __$$\\       $$  __$$\\ $$ |  $$ |\\_$$  _|\\____$$  |\n";
    cout<<"$$ |$$  / $$ |  $$ |$$ /  \\__|      $$ /  $$ |$$ |  $$ |  $$ |      $$  / \n";
    cout<<"$$$$$  /  $$$$$$$\\ |$$ |            $$ |  $$ |$$ |  $$ |  $$ |     $$  /  \n";
    cout<<"$$  $$<   $$  __$$\\ $$ |            $$ |  $$ |$$ |  $$ |  $$ |    $$  /   \n";
    cout<<"$$ |\\$$\\  $$ |  $$ |$$ |  $$\\       $$ $$\\$$ |$$ |  $$ |  $$ |   $$  /    \n";
    cout<<"$$ | \\$$\\ $$$$$$$  |\\$$$$$$  |      \\$$$$$$ / \\$$$$$$  |$$$$$$\\ $$$$$$$$\\ \n";
    cout<<"\\__|  \\__|\\_______/  \\______/        \\___$$$\\  \\______/ \\______|\\________|\n";
    cout<<"                                         \\___|                            \n\n\n";
    cout<<"\n1.Start Quiz\n2.Hall of Fame\n3.Admin Controls\n4.Exit"<<endl;

    bool flag =true;
    do{
        switch(getch()){
            case 49:{
                PLAYGAME:
                Game g;
                if(g.play()==0){
                    goto MAINMENU;
                }
                else{
                    goto PLAYGAME;
                }
            }
            break;
            case 50:{
                system("CLS");
                HOF hof;
                hof.showHOF();
                goto MAINMENU;
            }
            break;
            case 51:{
                system("CLS");
                admin ad;
                ad.login();
                ad.menu();
                goto MAINMENU;
            }
            break;
            case 52:{
                system("CLS");
                bool f2 = true;
                cout<<"Do you really want to exit the Game?(Y/N)"<<endl;
                do{
                    char ch = getch();
                    if(ch=='y'||ch=='Y'){
                        flag=false;
                        f2=false;
                    }
                    else if(ch=='n'||ch=='N'){
                        goto MAINMENU;
                    }
                }while(f2);
            }
            break;
            default:{
                continue;
            }
        }
    }while(flag);
}
