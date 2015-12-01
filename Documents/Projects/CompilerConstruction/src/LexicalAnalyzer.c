
/** A Lexical analyzer for identifying different types of token used in C language.  **/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define REP(i,n)    for(i=0;i<n;i++)
#define FOR(i,x,y)  for(i=x;i<=y;i++)


 char Key[50][20]= {"auto","double","int","struct","break", "else",
    "long","long","switch","case","enum","register","typedef","char","extern",
    "return","union","const","float","short", "unsigned","continue",
    "for","signed","void","default","goto","sizeof","volatile","do",
    "if","static","while"};

char in[1000000],cur_word[1000],temp[50][20],dec[50][20] = {"int","float","double","long","short"};
int L;

void Input_process()
{
    memset(in,'\0',sizeof(in));
    int l,i;
    L = 0;
    char str[10000];
    while(gets(str))
    {
        l = strlen(str);
        REP(i,l)
        {
            if(str[i]==';' || str[i]==','){
                in[L++] = ' ';
                in[L++] = str[i];
                in[L++] = ' ';
            }
            else
                in[L++] = str[i];

        }
        in[L++] = ' ';
        in[L] = '\0';
    }
}

int getAWord(int cur)
{
    int i,p,fl;
    fl = 0,p=0;
    memset(cur_word,'\0',sizeof(cur_word));
    FOR(i,cur,L-1)
    {
        if(in[i] == ' ' && fl)
            return i;
        if(in[i] != ' ')
        {
            fl = 1;
            cur_word[p++] = in[i];
            cur_word[p] = '\0';
        }
    }

    return 0;
}

int main()
{
    freopen("Assign3.in","r",stdin);
    //freopen("Assign2.out","w",stdout);
    Input_process();

    int i,glb_key = 32,glb_dec = 5,k;
    int cur=0;
    while(1)
    {
        cur = getAWord(cur);
        if(cur == 0) break;

        if(strcmp(cur_word,"#typedef")==0)
        {
            k = 0;
            while(1)
            {
                cur = getAWord(cur);
                if(strcmp(cur_word,";")==0 || cur==0)
                    break;
                strcpy(temp[k++],cur_word);
            }
            if(strlen(temp[k-1])){
                strcpy(dec[glb_dec++],temp[k-1]);
                strcpy(Key[glb_key++],temp[k-1]);
            }
        }

        REP(i,glb_dec)
        {
            if(strcmp(dec[i],cur_word)==0)
            {
                k=0;
                while(1)
                {
                    cur = getAWord(cur);
                    if(strcmp(cur_word,";")==0 || cur==0)
                        break;
                    if(strcmp(cur_word,",")!=0)
                        strcpy(temp[k++],cur_word);
                }

                int j;
                REP(j,k)
                {
                    int l,fl = 1;
                    REP(l,glb_key)
                        if(strcmp(temp[j],Key[l])==0)
                            fl = 0;
                    if(!fl)
                    {
                        printf("%s is a reserved word x(\n",temp[j]);
                        continue;
                    }
                    fl = 1;
                    if(!isalpha(temp[j][0]) && temp[j][0]!='_')
                        fl = 0;
                    REP(l,strlen(temp[j]))
                        if(!isalpha(temp[j][l]) && !isdigit(temp[j][l]) && temp[j][l]!='_')
                            fl = 0;
                    if(!fl)
                    {
                        printf("%s is not a valid identifier :(\n",temp[j]);
                        continue;
                    }
                    printf("%s is a valid identifier :)\n",temp[j]);
                }

                break;
            }
        }
    }

    return 0;
}
