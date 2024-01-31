#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <cstring>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include"headfile.h"
#define maxplayer 2


char r1, r2;
char result;
char score = 0;
char lives = 3;
int out=0;
extern struct person players[maxplayer];


int main()
{
    readfromfile();
    printf("欢迎来到游戏：速算\n按任意键开始游戏\n");
    system("pause");
    mainmenu();
    writetofile();
    return 0;
}

void mainmenu()
{
    char input;
    while (2)
    {
        system("cls");
        printf("1. 注册\n");
        printf("2. 登录\n");
        printf("3. 玩家数据\n");
        printf("4. 游客模式\n");
        printf("5. 退出\n");
        
        input = _getch();
        system("cls");
        switch (input){
            case '1':
                newplayer();
                system("cls");
                extern char k;//进入游客模式
                if (k == '1')
                {
                    k = '\0';
                    mode1();
                    lives = 3;
                    score = 0;
                }
                break;
            case '2':
                login();
                break;
            case '3':
                system("cls");
                prtdata();
                system("pause");
                break;
            case'4':
                mode1();
                break;
            default:
                out = 1;
                break;
        }
        if (out == 1)
        {
            break;
        }
    }
}
