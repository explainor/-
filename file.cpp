#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include <time.h>
#include<conio.h>
#define maxplayer 2
#define timelimit 10
char password1[20];
char password2[20];

int r1, r2;
int result;
int answer;
int score = 0;
int lives = 3;
char k = '\0';
char m='1';

struct person {
    char name[50] = {""};
    char password[20] = {""};
    struct{
        int mode1score[5] = { 0 };
        int mode2score[5] = { 0 };
    }record;
};
person players[maxplayer];
void check(void* p)
{
    if (p == NULL)
    {
        printf("Error,failed to find the file");
        return;
    }
}
//检查是否为野指针
void writetofile()
{
    FILE* infile = fopen("data.txt", "w");
    check(infile);
    fwrite(&players, sizeof(players[maxplayer]), 1, infile);
    fclose(infile);
}
//结束程序前内存写入文件
void readfromfile()
{
    FILE*outfile=fopen("data.txt", "r");
    check(outfile);
    fread(&players[maxplayer], sizeof(players[maxplayer]), 1, outfile);
    fclose(outfile);
}
//开始程序后文件写入内存
void newname(int i)
{
    char tempname[20];
    printf("请输入用户名：(不多于19字符，区分大小写)\n");
    scanf("%s", &tempname);
    getchar();
    strncpy(players[i].name, tempname, sizeof(players[i].name) - 1);
    players[i].name[sizeof(players[i].name)] = '\0';
}
//设置新用户名
void passwordset(int i)
{
    char code1[21];
    char code2[21];
    void Input();
    int n;
    {
        printf("新密码：(不多于20字符)\n");
        scanf("%s", &code1);
        printf("确认密码：\n");
        scanf("%s", &code2);
        n = strcmp(code1, code2);
        getchar();
    }
    if (n == 0)
    {
        printf("注册成功\n按任意键后返回主界面登录\n");
        strncpy(players[i].password, code1, sizeof(players[i].password) - 1);
        players[i].password[sizeof(players[i].password) - 1] = '\0';
        system("pause");
    }
    else
    {
        char tempname[20] = { '\0'};
        strncpy(players[i].name, tempname, sizeof(players[i].name) - 1);
        printf("设置失败，两次密码不一致\n按任意键返回主界面\n");
        system("pause");
    }
}
//新用户设置密码
void newplayer()
{
    static int i=0;
    for (; i < maxplayer; i++)
    {
        if (players[i].name[0] == '\0')
        {
            newname(i);
            passwordset(i);
            break;
        }
    }
    if (i < maxplayer)
        return;
    else
        {
        system("cls");
        printf("玩家已满，是否进入游客模式\n1.游客模式\n2.回到主界面");
        k = _getch();
        }

}
//新用户注册
void passwordcheck(int num)
{
        printf("请输入密码\n");
        strncpy(password2, players[num-1].password, sizeof(password2));
        int i = 2;
        scanf("%s", password1);
        for (; strcmp(password1 , password2)!=0 && (i >= 0); )
        {
            printf("密码错误，请重新输入：(您还有%d次机会)\n", i);
            scanf("%s", password1);
            i--;
            if (i == 0 && password1 != password2)
            {
                printf("真是贵人多忘事呀！\n按任意键返回主菜单\n");
                system("pause");
                while (getchar() != '\n')
                {
                    getchar();
                }
                break;
            }
        }
    }
//登录检查密码
void genr()
{
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random integer in the range from 1 to 100
    r1 = std::rand() % 20 + 10;
    r2 = std::rand() % 50 + 10;

    // Print the generated random integer
    printf("X1=%d，X2=%d,X1*X2=?\n", r1, r2);
    result = r1 * r2;
}
//随机数产生
int getanswer()
{
    int userInput = 0;

    printf("请在%d秒内输入答案并回车，超时判定为负\n",timelimit);
    time_t startTime = time(NULL);//设定一个计时器
    time_t currentTime;
    scanf("%d", &userInput);
    if((currentTime=time(NULL)) - startTime > timelimit)
    {
        printf("已超过十秒，本轮判负\n");
        userInput = 9999;//赋给函数一个特殊返回值来标记超时
        Sleep(1500);
        system("cls");
        return userInput;
    }
    else
    {
        system("cls");
        return userInput;
    }
}
//读取玩家回答
int compare()
{
    if (result == answer)
    {
        score++;
        printf("答案正确！");
        printf("剩余生命：%d     总分:%d\n", lives, score);
    }
    else
    {
        lives--;
        printf("再接再厉！");
        printf("剩余生命：%d     总分:%d\n", lives, score);
    }
    return score;
}
//结果判定
void mode1()
{
    system("cls");
    printf("游戏将在三秒后开始，请做好准备\n");
    Sleep(3000);
    system("cls");
    printf("剩余生命：%d     总分:%d\n", lives, score);
    for (int i = 0; lives > 0; i++)
    {
        genr();
        result = r1 * r2;
        answer = getanswer();
        getchar();
        compare();
        Sleep(1000);
        system("cls");
        printf("剩余生命：%d     总分:%d\n", lives, score);
    }
    printf("游戏结束！   总分:%d\n", score);
    Sleep(1000);

}
//模式一
void login()
{
    for (int i = 0; players[i].name[0] != '\0'&&i<=maxplayer; i++)
    {
        printf("%d.%s\n", i + 1, players[i].name);
    }
    printf("请输入您要登录的账号序号\n");
    int input;
    scanf("%d", &input);
    if (input > maxplayer)
    {
        printf("输入错误捏,2秒后返回主界面\n");
    }
    else
    {
        for (int i = 0; i <= maxplayer; i++)
        {
            if (players[i].name[0] != '\0' && input <= i + 1)
            {
                passwordcheck(input);
                if (strcmp(password1, password2) == 0)
                {
                    printf("已解锁，按任意键继续\n");
                    system("pause");
                    while (2)
                    {
                        mode1();
                        for (int c = 0; c <= 5; c++)
                        {
                            int done = 0;
                            if (players[i].record.mode1score[c] < score)
                            {
                                players[i].record.mode1score[c] = score;
                                done = 1;
                            }
                            if (done == 1)
                            {
                                break;
                            }
                        }
                        printf("得分已录入\n1.继续游戏\n2.返回主界面\n");
                        m = _getch();
                        if (m != '1')
                        {
                            lives = 3;
                            score = 0;
                            break;
                        }

                        lives = 3;
                        score = 0;
                    }
                }
                break;
            }
            if (m != '1')
            {
                break;
            }
        }
    }
    return;
}
//用户登录及游戏
void prtdata()
        { 
            for (int i=0; i <= maxplayer; i++)
            {    
                printf("%d.%s",i+1, players[i].name);
                for (int j=0; j <= 5; j++)
                {
                    printf("    %d", players[i].record.mode1score[j]);
                }
                printf("\n");
            }
        }
//打印数据