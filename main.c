#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
struct Package
{
    int pkgID;
    char pggName[20];
    double onNetCallRate;
    double offNetCallRate;
}packages[3];


void LoadPackage()
{
    FILE* fp;
    fp = fopen("package.txt","r");
    //printf("Hello");
    if(fp == NULL)
    {
        printf("Package file has some problem!\nFirst fix the problem\n");
        fclose(fp);
        return;
    }
    else
    {
        char line[20];

        int fLineNo = 1;
        while (fgets(line, sizeof(line), fp)) {
            if(fLineNo%4 == 1)
            {
                packages[fLineNo/4].pkgID = atoi(line);
            }
            else if(fLineNo%4 == 2)
            {
                line[(strlen(line)-1)] = '\0';
                strcpy(packages[fLineNo/4].pggName,line);
            }
            else if(fLineNo%4 == 3)
            {
                packages[fLineNo/4].onNetCallRate = atof(line);
            }
            else if(fLineNo%4 == 0)
            {
                packages[(fLineNo/4) - 1].offNetCallRate = atof(line);
            }

            fLineNo++;
        }

        fclose(fp);
    }


}

int main()
{
    LoadPackage();

    int i = 0;
    for(;i<3;i++)
    {
        printf("%d %s %lf %lf\n",packages[i].pkgID,packages[i].pggName,packages[i].onNetCallRate,packages[i].offNetCallRate);
    }
}
