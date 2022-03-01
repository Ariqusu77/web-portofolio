#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <windows.h>
#include <time.h>
#include <conio.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;

string quest[21];
COORD coord= {0,0};
char bahan[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ans[4] = {' ',' ',' ','\0'};
int MetX[21], MetY[21], status[21];
int count=0,score=0;
bool gameover = false;
string pesan;

void Gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void minimeteor(int x, int y, string que)
{
    Gotoxy(x,y-2)  ; cout << "\xDB\xDB\xDB";
    Gotoxy(x-2,y-1); cout << "\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
    Gotoxy(x-4,y)  ; cout << "\xDB\xDB\xDB " << que << " \xDB\xDB\xDB";
    Gotoxy(x-2,y+1); cout << "\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
    Gotoxy(x,y+2)  ; cout << "\xDB\xDB\xDB";
}

void spawn ()
{
    int i,k;
    string smt = ""; 
    i = rand()%72;
    MetX[(count/5)%20]= i+4;
    MetY[(count/5)%20]= 4;
    status[(count/5)%20]= 1;
    for(int j=0; j<3; j++)
    {
        k = rand()%51;
        smt += bahan[k] ;
    }
    quest[(count/5)%20]=smt;
}

void draw()
{
    //batas atas
    for (int i=0; i <= 81; i++)
    {
        Gotoxy(i,0);
        cout << "\xDB";
    }
    //batas kiri
    for (int j=1; j <= 36; j++)
    {
        Gotoxy(0,j);
        cout << "\xDB";
    }
    //gambar utama
    for (int k=0; k<=100; k++)
    {
        if(status[k] != 0)
        {
            if(status[k] == 1)
            {
                minimeteor(MetX[k], MetY[k], quest[k]);
            }
        }
        else {break;}
    }
    //batas kanan
    for (int m=1; m<= 36; m++)
    {
        Gotoxy(81,m);
        cout << "\xDB";
    }
    //batas bawah
    for (int n=1; n<=80; n++)
    {
        Gotoxy(n,36);
        cout << "\xDB";
    }
    //user display

    cout << "\nscore :" << score;
    cout << "\ninput :" << ans ;
}

void logic()
{
    int i=0;

    while(status[i]!=0)
    {
        if(status[i]==1)
        {
            MetY[i] += 1;
        }

        if(quest[i] == ans)
        {
            status[i]= 2;
            score += 1;
        }

        if(MetY[i] == 33)
        {
            gameover = true;
        }

        i++;
    }

    if (ans[2]!=' ')
    {
       ans[0]=ans[1]=ans[2]=' '; 
    }

    if(count%5 ==0) spawn();
}

void input()
{
    int i=0;
    char ch;

    if (_kbhit())
    {
        ch=_getch();
        if(ch!='\r')
        {
            while (ans[i] != ' ' && i<3 )
            {
                i++;
            }
            ans[i]=ch;
        }else{
            ans[0]=ans[1]=ans[2]=' ';
        }
    }
}

int main()
{
    system("mode 650");
    srand (time(0));
    while (!gameover)
    {
        system("cls");

        draw();
        input();
        logic();

        sleep_for(250ms);
        count++;
    }
    return 0;
    cin >> pesan;
}