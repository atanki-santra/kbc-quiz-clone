#include "adminControls.h"

bool admin::login(){
    do{
      cout<<"Enter Username: ";
      getline(cin,username);
    }while(!checkUser(username));
    do{
        system("CLS");
        cout<<"Enter Password: ";
        string E_pass ="";
        char ch;
        //int count = 0;
        while(true){
            ch = getch();
            cout<<'*';
            if(ch==(char)13)
                break;
            E_pass+=ch;
        }
        if(E_pass==password){
            break;
        }
        else{
            cout<<"\n\nIncorrect Password\nPlease try Again"<<endl;
            Sleep(2000);
        }
    }while(true);
    cout<<"\n\nLogin Successful!"<<endl;
    Sleep(1000);
    for(int i = 0; i<5; i++){
        system("CLS");
        cout<<"Loading";
        for(int j = 0; j<3; j++){
            Sleep(50);
            cout<<".";
        }
    }
    system("CLS");
    return true;
}

bool admin::checkUser(string u){
    ifstream fin("Admins.txt");
    if(!fin){
        cout<<"Error in opening Admins.txt"<<endl;
    }
    string line,user;
    while(!fin.eof()){
        getline(fin,line);
        istringstream iss(line);
        while(!iss.eof()){
            getline(iss,user,',');
            if(u == user){
                getline(iss,password);
                fin.close();
                return true;
            }
        }
    }
    fin.close();
    cout<<"Username is not registered! Please Try again!"<<endl;
    Sleep(2000);
    system("CLS");
    return false;
}

bool admin::checkUser(string u, int n){
    ifstream fin("Admins.txt");
    if(!fin){
        cout<<"Error in opening Admins.txt"<<endl;
    }
    string line,user;
    while(!fin.eof()){
        getline(fin,line);
        istringstream iss(line);
        while(!iss.eof()){
            getline(iss,user,',');
            if(u == user){
                fin.close();
                cout<<"Username already taken! Try some other username!"<<endl;
                Sleep(2000);
                system("CLS");
                return true;
            }
        }
    }
    fin.close();
    return false;
}

void admin::menu(){
    do{
       system("CLS");

cout<<"   __    ____   __  __  ____  _  _     ___  _____  _  _  ____  ____  _____  __    ___ \n";
cout<<"  /__\\  (  _ \\ (  \\/  )(_  _)( \\( )   / __)(  _  )( \\( )(_  _)(  _ \\(  _  )(  )  / __)\n";
cout<<" /(__)\\  )(_) ) )    (  _)(_  )  (   ( (__  )(_)(  )  (   )(   )   / )(_)(  )(__ \\__ \n";
cout<<"(__)(__)(____/ (_/\\/\\_)(____)(_)\\_)   \\___)(_____)(_)\\_) (__) (_)\\_)(_____)(____)(___/\n";

       cout<<"\n\n1.Clear Hall of Fame\n2.Change Password\n3.Add Admin\n4.Back to Main Menu\n"<<endl;
       switch(getch()){
            case 49:
                clearHOF();
            break;
            case 50:
                changePass();
            break;
            case 51:
                addAdmin();
            break;
            case 52:
                goto out1;
            break;
            default:
                continue;
       }
    }while(true);
    out1:
    cout<<"";
}

void admin::clearHOF(){
    fstream file;
    file.open("Hall of Fame.txt",ios::trunc | ios::out);
    if(!file){
        cout<<"Error in opening Hall of Fame.txt file"<<endl;
    }
    file<<"NO.,NAME,SCORE"<<endl;
    file.close();
    file.open("Misc values.txt",ios::trunc | ios::out);
    if(!file){
        cout<<"Error in opening Misc values.txt file"<<endl;
    }
    file<<"srno:0"<<endl;
    file.close();
    cout<<"Hall of Fame successfully Cleared!"<<endl;
    Sleep(1000);
    cout<<"\nPress any Key to continue..."<<endl;
    getch();
}

void admin::changePass(){
    do{
        char ch;
        cout<<"Enter new Password: ";
        string p1,p2;
        while(true){
            ch = getch();
            cout<<'*';
            if(ch==(char)13)
                break;
            p1+=ch;
        }
        cout<<"\n\nRe-Enter new Password: ";
        while(true){
            ch = getch();
            cout<<'*';
            if(ch==(char)13)
                break;
            p2+=ch;
        }
        if(p1==p2){
            password=p1;
            fstream file;
            file.open("Admins.txt");
            if(!file){
                cout<<"Error in opening Admins.txt file"<<endl;
            }
            fstream tfile;
            tfile.open("temp.txt",ios::trunc | ios::in | ios::out);
            if(!tfile){
                cout<<"Error in opening temp.txt file"<<endl;
            }
            string temp;
            while(!file.eof()){
                getline(file,temp);//Utkarsh,buffalo
                istringstream iss(temp);
                string temp2;
                while(!iss.eof()){
                    getline(iss,temp2,',');
                    if(username==temp2){
                        tfile<<temp2<<','<<password<<endl;
                        getline(iss,temp2);
                    }
                    else{
                        getline(iss,temp2);
                        tfile<<temp<<endl;
                    }
                }
            }
            file.close();
            file.open("Admins.txt",ios::trunc | ios::in | ios::out);
            if(!file){
                cout<<"Error in opening Admins.txt file"<<endl;
            }
            tfile.seekg(0,ios::beg);
            while(!tfile.eof()){
                getline(tfile,temp);
                file<<temp<<endl;
            }
            file.close();
            tfile.close();
            cout<<"\n\nPassword Changed Successfully!"<<endl;
            Sleep(1000);
            cout<<"\nPress any Key to continue..."<<endl;
            getch();
            break;
        }
        else{
            cout<<"\n\nPasswords didn't match. Please Try Again!"<<endl;
            Sleep(1000);
            system("CLS");
        }
    }while(true);
}

void admin::addAdmin(){
    string user, pass;
    do{
        cout<<"Enter Username: ";
        getline(cin,user);
    }while(checkUser(user,0));
    do{
        char ch;
        cout<<"Create Password: ";
        string p1,p2;
        while(true){
            ch = getch();
            cout<<'*';
            if(ch==(char)13)
                break;
            p1+=ch;
        }
        cout<<"\n\nRe-Enter Password: ";
        while(true){
            ch = getch();
            cout<<'*';
            if(ch==(char)13)
                break;
            p2+=ch;
        }
        if(p1==p2){
            pass=p1;
            ofstream fout("Admins.txt",ios::app | ios::out);
            if(!fout){
                cout<<"Error in opening Admins.txt file"<<endl;
            }
            fout<<user<<','<<pass<<endl;
            fout.close();
            cout<<"\n\nAdmin added Successfully!"<<endl;
            Sleep(1000);
            cout<<"\nPress any Key to continue..."<<endl;
            getch();
            break;
        }
    }while(true);
}

