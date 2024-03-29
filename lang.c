#include <stdio.h>
#include<string.h>
int CH_into_NUM(char* s);
void getSingle(char* a, char* b);
int switchSingle(char* s);
void NUM_into_CH(int purse);
void start(char*);
int judge(char*);
void plan1(void);
void plan2(void);
void plan3(void);
void error(void);
void run(void);


char Ch[11][10] = { "零","一","二","三","四","五","六","七","八","九","十" };
char name[20][20];
int name_num = 0, i;
char s[20], t[20], u[20], v[20];
int num[20];


int main(int argc, char* argv[])
{

        freopen(argv[1], "r", stdin);
        run();

    return 0;
}


int CH_into_NUM(char* s)//中文转数字
{
    if (strlen(s) == 2)return switchSingle(s);
    else if (strlen(s) == 4)
    {
        getSingle(u, s);
        if (strcmp(u, "十") == 0)
        {
            getSingle(u, s + 2);
            return (10 + switchSingle(u));
        }
        else return(10 * switchSingle(u));
    }
    else
    {
        getSingle(u, s);
        getSingle(v, s + 4);
        return (10 * switchSingle(u) + switchSingle(v));
    }
}


void getSingle(char* a, char* b)//提取单一汉字
{
    a[0] = b[0];
    a[1] = b[1];
    a[2] = '\0';
}


int switchSingle(char* s)//单一汉字转数字
{
    for (i = 0; i <= 10; i++)
        if (strcmp(s, Ch[i]) == 0)
            return i;
    return 0;
}


void NUM_into_CH(int purse)//输出中文
{
    if (purse < 0 || purse >= 100)printf("数值超出范围\n");
    else if (purse <= 10)printf("%s\n", Ch[purse]);
    else if (purse > 10 && purse < 20)printf("十%s\n", Ch[purse - 10]);
    else if (purse % 10 == 0)printf("%s十\n", Ch[purse / 10]);
    else printf("%s十%s\n", Ch[purse / 10], Ch[purse % 10]);
}


void start(char* s)//开始
{
    if (strcmp(s, "整数") == 0)
        plan1();
    else if (strcmp(s, "看看") == 0)
        plan2();
    else if (judge(s) != -1)
        plan3();
    else
        error();
}


int judge(char* s)//判断有无该钱包名并返回下标，不存在则返回-1
{
    for (i = 0; i < name_num; i++)
        if (strcmp(s, name[i]) == 0)
            return i;
    return -1;
}


void plan1(void)//输入的第一个词为“整数”时的方案
{
    scanf("%s", s);
    if (judge(s) == -1 && strcmp(s, "看看") != 0 && strcmp(s, "整数") != 0 && name_num < 20)
    {
        scanf("%s", t);
        if (strcmp(t, "等于") == 0)
        {
            scanf("%s", t);
            strcpy(name[name_num], s);
            num[name_num] = CH_into_NUM(t);
            name_num++;
        }
        else
            error();
    }
    else if (name_num >= 20)printf("钱包过多\n");
    else error();
}


void plan2(void)//输入的第一个词为“看看”时的方案
{
    scanf("%s", s);
    if (judge(s) != -1)
        NUM_into_CH(num[judge(s)]);
    else
        error();
}


void plan3(void)//当输入的第一个词在钱包名中存在时的方案
{
    scanf("%s", t);
    if (strcmp(t, "增加") == 0)
    {
        scanf("%s", t);
        num[judge(s)] += CH_into_NUM(t);
    }
    else if (strcmp(t, "减少") == 0)
    {
        scanf("%s", t);
        num[judge(s)] -= CH_into_NUM(t);
    }
    else
        error();
}


void error(void)//报错
{
    printf("重新开始，请输入有效字符\n");
}


void run(void)
{
    while (scanf("%s", s) != EOF)
        start(s);
}