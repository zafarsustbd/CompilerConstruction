/** a program to eliminate left recursion **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define REP(i,n)    for(i=0;i<n;i++)
#define FOR(i,x,y)  for(i=x;i<=y;i++)

char str[100],temp[100],mm[100][100];

void removeLeftRecursion(char str[])
{
    int i,j,k,x,in;

    k = x = 0;
    in = -1;
    memset(temp,'\0',sizeof(temp));
    REP(i,strlen(str))
    {
        if(str[i]=='|' || str[i]==' ' || str[i]=='=')
        {
            if(strlen(temp))
            {
                strcpy(mm[k++],temp);
                memset(temp,'\0',sizeof(temp));
                x = 0;
            }
        }
        else if(str[i]!='=')
        {
            temp[x++] = str[i];
        }
    }
    if(strlen(temp))
    {
        strcpy(mm[k++],temp);
        memset(temp,'\0',sizeof(temp));
        x = 0;
    }

    FOR(i,1,k-1)
    {
        if(mm[i][0]!=mm[0][0])
        {
            in = i;
            break;
        }
    }

    int ff = 0;
    FOR(i,1,k-1)
    {
        if(mm[i][0]==mm[0][0])
            ff = 1;
    }
    if(!ff)
    {
        printf("Given Grammer is not Immediate Left Recursive.");
        return ;
    }

    if(in == -1)
    {
        printf("%c -> Z%c'\n",mm[0][0],mm[0][0]);
        printf("%c' -> ");
        FOR(i,1,k-1)
        {
            if(strlen(mm[i])<2)
                continue;
            if(i>1)
                printf("|");
            FOR(j,1,strlen(mm[i])-1)
                printf("%c",mm[i][j]);
            printf("%c'",mm[0][0]);
        }
        printf("|[\n");

    }
    else
    {
        printf("%c -> ",mm[0][0]);
        int f = 0;
        REP(i,strlen(mm[in]))
        {
            if(mm[in][i]==mm[0][0])
            {
                f = 1;
                printf("%c'",mm[0][0]);
            }
            else
                printf("%c",mm[in][i]);
        }
        if(!f)
            printf("%c'",mm[0][0]);
        printf("\n");
        printf("%c' -> ",mm[0][0]);
        int fl = 0;
        FOR(j,1,k-1)
        {
            if(j==in)
                continue;
            if(fl)
                printf("|");
            fl = 1;
            f = 0;
            if(mm[j][0]!=mm[0][0])
                printf("%c",mm[j][0]);
            FOR(i,1,strlen(mm[j])-1)
            {
                if(mm[j][i]==mm[0][0])
                {
                    f = 1;
                    printf("%c'",mm[0][0]);
                }
                else
                    printf("%c",mm[j][i]);
            }
            if(!f)
                printf("%c'",mm[0][0]);
        }
        printf("|[\n");
    }
}

/*

Sample Input:

A = Aa
A = Aa|B
S = S+S|S*S|S
E = E+T|T
T = T*F|F
F = (E)|id

*/

int main()
{
    printf("For Specifying Non-Terminal use Uppercase Letter\nFor Specitying Terminal use Lowercase Letter\n");
    while(gets(str))
    {
        removeLeftRecursion(str);
        printf("\n\n");
    }
    return 0;
}
