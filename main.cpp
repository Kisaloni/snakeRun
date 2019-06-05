#include <iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<cksupport.h>
using namespace std;

/*******************Global Variables***************************/
bool Gameover = false;
int Snack_x[21]={2},Snack_y[21]={2};
enum Dir{Left=0,Right,up,down,Stop};
Dir d=Right;
int fd_x=20,fd_y=20;
int len=0;
int Score=0;
int s_m=100,s_a=50;
int highScore=0;
/*******************Function Declaration***********************/
void Setup();
void Draw();
void Input();
void logic();
void First_Show();
void Menu();
void Border();
/*******************Main()************************************/
int main()
{
    Setup();
    First_Show();
    Menu();
    gotoxy(0,30);
    return 0;
}

/*******************Function Definitions***********************/
void Setup()
{
    Gameover=false;
    Set_col(0,15);
    d=Stop;
    len=1;
    Snack_x[0]=49;
    Snack_y[0]=14;
    fd_x=rand()%99,fd_y=rand()%29;
    Score=0;
    ifstream scoreFile("HighScore");
    scoreFile>>highScore;
    scoreFile.close();
}
/*************************************************************/
void Menu()
{
    int ch;
    do
    {
        Setup();
        system("cls");
        Border();
        Set_tcol(9);
        gotoxy(40,14);
        cout<<"1.Play";
        gotoxy(40,16);
        cout<<"2.High Score";
        gotoxy(40,18);
        cout<<"3.How to play";
        gotoxy(40,20);
        cout<<"4.Exit";
        gotoxy(0,31);
        cin>>ch;
        switch(ch)
        {
            case 1:
                while(!Gameover)
                {
                    system("cls");
                    Draw();
                    Input();
                    logic();
                    Sleep(s_m);
                }
                break;
            case 2:
                system("cls");
                Border();
                Set_tcol(14);
                gotoxy(40,14);
                {
                    ifstream scoreFile("HighScore");
                    scoreFile>>highScore;
                    scoreFile.close();
                }
                cout<<"High score: "<<highScore;
                getch();
                break;
            case 3:
                {
                    system("cls");
                    Set_tcol(14);
                    gotoxy(40,2);
                    ifstream file("HTP");
                    char str[255];
                    while(!file.eof())
                    {
                        file.getline(str, 255);
                        cout<<str<<endl;
                    }
                    file.close();
                }
                getch();
                break;
            case 4:break;
            default :cout<<"Invalid Choice";break;
        }
    }while(ch!=4);
}
/***********************First Show****************************/
void First_Show()
{
    Border();
    Set_tcol(10);
    for(int j=0;j<3;j++)
    {
        gotoxy(30,14+j);
        for(int i=0;i<40;i++)
        {
            cout<<"#";
        }
        cout<<"\n";
    }
    Set_tcol(9);
    gotoxy(45,15);
    cout<<"SNACK RUN";
    Set_tcol(14);
    gotoxy(0,31);
    cout<<"Press Any Key To Continue...";
    getch();
}
/************************************************************/
/************************border*********************************/
void Border()
{
    int d=0;
    Set_tcol(12);
    for(int i=0;i<101;i++)
    {
        Sleep(d);
        cout<<(char)178;
    }
    for(int i=0;i<31;i++)
    {
        Sleep(d);
        gotoxy(100,i);
        cout<<(char)178;
    }
    for(int i=99;i>=0;i--)
    {
        Sleep(d);
        gotoxy(i,30);
        cout<<(char)178;
    }
    for(int i=29;i>=0;i--)
    {
        Sleep(d);
        gotoxy(0,i);
        cout<<(char)178;
    }
    /*************************border***********************/
}
/************************************************************/
void Draw()
{
    Border();
    {
        /***********************Snack**************************/
        Set_tcol(10);
        for(int i=0;i<len;i++)
        {
            if(i==0)
            {
                gotoxy(Snack_x[i],Snack_y[i]);
                cout<<(char)233;
            }
            else if(i==len-1)
            {
                gotoxy(Snack_x[i],Snack_y[i]);
                cout<<(char)248;
            }
            else
            {
                gotoxy(Snack_x[i],Snack_y[i]);
                cout<<(char)240;
            }
        }
    }
    {/**********************food*******************************/
        gotoxy(fd_x,fd_y);
        Set_tcol(9);
        cout<<(char)233;
    }
    {/*************************score***************************/
        gotoxy(105,14);
        Set_tcol(13);
        cout<<"Score : "<<Score;
    }
}
/***************************************************************/
void Input()
{
    int ch;
    if(kbhit())
    {
        ch=getch();
        if(ch=='a'||ch=='A')//left
        {
            d=Left;
        }
        else if(ch=='d'||ch=='D')//right
        {
            d=Right;
        }
        else if(ch=='w'||ch=='W')//up
        {
            d=up;
        }
        else if(ch=='s'||ch=='S')//down
        {
            d=down;
        }
        else if(ch=='p'||ch=='p')//pause
        {
            Set_tcol(14);
            gotoxy(105,15);
            cout<<"PAUSED";
            getch();
        }
    }
}

void logic()
{
    {/*********to move snack**********/
        for(int i=len-1;i>0;i--)
        {
            Snack_x[i]=Snack_x[i-1];
            Snack_y[i]=Snack_y[i-1];
        }
        switch(d)
        {
            case 0:
                Snack_x[0]--;
                break;
            case 1:
                Snack_x[0]++;
                break;
            case 2:
                Snack_y[0]--;
                break;
            case 3:
                Snack_y[0]++;
                break;
            case 4:break;
            default :
                cout<<"Error in switch dir";
                break;
        }
        Sleep(s_a);
    }
    {/*****condition for crash********/
        if(Snack_x[0]==0||Snack_x[0]==100||Snack_y[0]==0||Snack_y[0]==30)
        {
            Gameover=true;
            gotoxy(105,15);
            Set_tcol(14);
            cout<<"GAME OVER";
            if(Score>highScore)
            {
                ofstream file("HighScore");
                file<<Score;
                file.close();
                Set_tcol(12);
                gotoxy(30,14);
                cout<<"You created a new high score: "<<Score;
            }
            gotoxy(0,31);
            cout<<"Press Space bar to continue... ";
            for(;;)
            {
                char ch=getch();
                if(ch==' ')
                {
                    break;
                }
            }
        }
        for(int i=1;i<len;i++)
        {
            if(Snack_x[i]==Snack_x[0]&&Snack_y[i]==Snack_y[0])
            {
                Gameover=true;
                gotoxy(105,15);
                Set_tcol(14);
                cout<<"GAME OVER";
                gotoxy(0,31);
                if(Score>highScore)
                {
                    ofstream file("HighScore");
                    file<<Score;
                    file.close();
                    Set_tcol(12);
                    gotoxy(40,14);
                    cout<<"You created a new high score: "<<Score;
                }
                cout<<"Press Space bar to continue... ";
                for(;;)
                {
                    char ch=getch();
                    if(ch==' ')
                    {
                        break;
                    }
                }
            }
        }
    }
    {/************food******************/
        if(Snack_x[0]==fd_x&&Snack_y[0]==fd_y)
        {
            len++;
            for(int i=len-1;i>0;i--)
            {
                Snack_x[i]=Snack_x[i-1];
                Snack_y[i]=Snack_y[i-1];
            }
            Score+=50;
            {
                fd_x=rand()%99;
                fd_y=rand()%29;
            }
        }
    }
    {/*************Winning Stroke************/
        if(len==21)
        {
            gotoxy(105,15);
            Set_tcol(2);
            cout<<"*";
            Set_tcol(3);
            cout<<"*";
            Set_tcol(2);
            cout<<"*";
            Set_tcol(13);
            cout<<"Y";
            Set_tcol(7);
            cout<<"O";
            Set_tcol(12);
            cout<<"U";
            Set_tcol(9);
            cout<<" W";
            Set_tcol(10);
            cout<<"O";
            Set_tcol(8);
            cout<<"N";
            Set_tcol(2);
            cout<<"*";
            Set_tcol(3);
            cout<<"*";
            Set_tcol(2);
            cout<<"*";
            Gameover=true;
            gotoxy(0,31);
            Set_tcol(10);
            cout<<"Press Space bar to continue... ";
            for(;;)
            {
                char ch=getch();
                if(ch==' ')
                {
                    break;
                }
            }

        }
    }
}
