#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
struct Record
{
    int id;
    char recvNum[20];
    double time;
    int pck;
    int net;
};

struct Package
{
    int pkgID;
    char pggName[20];
    double onNetCallRate;
    double offNetCallRate;
}packages[3];

typedef struct Record Record;

struct User
{
    int userID;
    char ownContactNo[15];
    int totalRecords;
}users[5];//by default we consider that we have five users


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
void RefreshUserInfo()
{
    FILE* fp;
    fp = fopen("userlist.txt","w");
    //printf("Hello");
    if(fp == NULL)
    {
        printf("userlist file has some problem!\nFirst fix the problem\n");
        fclose(fp);
        return;
    }
    else
    {
        int fLineNo = 1;
        while(fLineNo <= 5)
        {
            fprintf(fp,"%d\n%s\n%d\n",users[fLineNo-1].userID,users[fLineNo-1].ownContactNo,users[fLineNo-1].totalRecords);
            fLineNo++;
        }

        fclose(fp);
    }
}
void LoadAllUserInfo()
{
    FILE* fp;
    fp = fopen("userlist.txt","r");
    //printf("Hello");
    if(fp == NULL)
    {
        printf("userlist file has some problem!\nFirst fix the problem\n");
        fclose(fp);
        return;
    }
    else
    {
        char line[20];

        int fLineNo = 1;
        while (fgets(line, sizeof(line), fp)) {
            if(fLineNo%3 == 1) //user id
            {
                users[fLineNo/3].userID = atoi(line);
            }
            else if(fLineNo%3 == 2) // own no
            {
                line[strlen(line)-1] = '\0';
                strcpy(users[fLineNo/3].ownContactNo,line);
            }
            else
            {
                users[(fLineNo/3)-1].totalRecords = atoi(line);
                FILE* file;
            }

            /*if(fLineNo%3 == 0)
            {
                printf("%d %s %d\n",users[(fLineNo/3)-1].userID,users[(fLineNo/3)-1].ownContactNo,users[(fLineNo/3)-1].totalRecords);
            }*/
            fLineNo++;
        }

        fclose(fp);
    }


}


void addRecord(int userID,char number[],double time,int pck,int net)
{
    //struct User user = users[userID-1];
    LoadAllUserInfo();

    FILE* file;
    char recd[12] = "record";
    char num[3];
    num[0] = '0'+userID;
    num[1] = '\0';
    strcat(recd,num);
    strcat(recd,".txt");
    //printf("%s",recd);
    file = fopen(recd,"a");

    fprintf(file,"%d\n",users[userID-1].totalRecords+1);
    fprintf(file,"%s\n",number);
    fprintf(file,"%lf\n",time);
    fprintf(file,"%d\n",pck);
    fprintf(file,"%d\n",net);

    fclose(file);

    users[userID-1].totalRecords = users[userID-1].totalRecords+1;
    printf("\nRecord added to ...\n");
    printf("%s and total records %d\n\n",users[userID-1].ownContactNo,users[userID-1].totalRecords);

    RefreshUserInfo();

}

void ShowRecord(int y)
{
    FILE* file;
    char recd[12] = "record";
    char num[3];
    num[0] = '0'+ y;
    num[1] = '\0';
    strcat(recd,num);
    strcat(recd,".txt");
    //printf("%s",recd);
    file = fopen(recd,"r");

    int fLineNo = 1;

    char recordID[10];
    char receiverNum[10];
    char time[10];
    char pkg[10];
    char net[10];

    char line[256];
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("RECORD LIST ==> \n\n");
    while (fgets(line, sizeof(line), file)) {
        if(fLineNo%5 == 1)
        {
            //printf("%s",line);
            line[strlen(line)-1] = '\0';
            //printf("%s",line);
            strcpy(recordID,line);
        }
        if(fLineNo%5 == 2)
        {
            line[strlen(line)-1] = '\0';
            strcpy(receiverNum,line);
        }
        if(fLineNo%5 == 3)
        {
            line[strlen(line)-1] = '\0';
            strcpy(time,line);
        }
        if(fLineNo%5 == 4)
        {
            line[strlen(line)-1] = '\0';
            strcpy(pkg,line);
        }
        if(fLineNo%5 == 0)
        {
            line[strlen(line)-1] = '\0';
            strcpy(net,line);
        }

        if(fLineNo%5 == 0)
        {
            printf("Record # %s : Receiver Number : %s | Duration : %s | Package : %s | Net-Type : %s\n",recordID,receiverNum,time,pkg,net);
        }

        fLineNo++;
    }
    printf("----------------------------------------------------------------------------------------------------\n\n");

    fclose(file);

}



void ModifyRecord(int y,char number[])
{
    struct Record records[100];
    int size=0;


    FILE* file;
    char recd[12] = "record";
    char num[3];
    num[0] = '0'+ y;
    num[1] = '\0';
    strcat(recd,num);
    strcat(recd,".txt");
    file = fopen(recd,"r");

    int fLineNo = 1;





    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if(fLineNo%5 == 1)
        {
            line[strlen(line)-1] = '\0';
            records[size].id = atoi(line);
        }
        if(fLineNo%5 == 2)
        {
            line[strlen(line)-1] = '\0';
            strcpy(records[size].recvNum,line);
        }
        if(fLineNo%5 == 3)
        {
            line[strlen(line)-1] = '\0';
            records[size].time = atof(line);
        }
        if(fLineNo%5 == 4)
        {
            line[strlen(line)-1] = '\0';
            records[size].pck = atoi(line);
        }
        if(fLineNo%5 == 0)
        {
            line[strlen(line)-1] = '\0';
            records[size].net = atoi(line);
        }

        if(fLineNo%5 == 0)
        {
            size++;
        }

        fLineNo++;
    }
    //printf("----------------------------------------------------------------------------------------------------\n\n");

    fclose(file);

    int flag = 0;
    int i;
    int idx = 0;
    for(i=0; i < size; i++)
    {
        //printf("%s\n",records[i].recvNum);
        if(!strcmp(number,records[i].recvNum))
        {
            flag = 1;
            idx = i;
            break;
        }
    }

    if(flag == 0)
    {
        printf("Your entered number doesn't in record list\n");
        return;
    }

    printf("Enter new receiver number : \n");
    char newnum[20];
    scanf("%s",newnum);

    printf("Enter new Time duration : \n ");
    double newtime;
    scanf("%lf",&newtime);

    printf("Enter new package :(1-3) \n");
    int newpck;
    scanf("%d",&newpck);

    printf("Enter new net type : (0-1) \n");
    int newnet;
    scanf("%d",&newnet);


    strcpy(records[idx].recvNum,newnum);
    records[idx].time = newtime;
    records[idx].pck = newpck;
    records[idx].net = newnet;



    file = fopen(recd,"w");

    for(i = 0; i < size ; i++)
    {
        fprintf(file,"%d\n",records[i].id);
        fprintf(file,"%s\n",records[i].recvNum);
        fprintf(file,"%lf\n",records[i].time);
        fprintf(file,"%d\n",records[i].pck);
        fprintf(file,"%d\n",records[i].net);
    }

    fclose(file);

    printf("Your data successfully updated\n");



}

void ShowPackageDetails()
{
     int i;
     printf("------------------------------------------------------------------------------------------------------------------------------\n");
     for(i = 0; i<3;i++)
     {
         printf("Package ID # %d | Package Name : %s | On net Rate (per minute) : %lf tk | Off net Rate (per minute) : %lf tk \n",packages[i].pkgID,packages[i].pggName,packages[i].onNetCallRate,packages[i].offNetCallRate);
    }
     printf("------------------------------------------------------------------------------------------------------------------------------\n\n");

}

void ShowTotalBill(int y)
{
    struct Record records[100];
    int size=0;


    FILE* file;
    char recd[12] = "record";
    char num[3];
    num[0] = '0'+ y;
    num[1] = '\0';
    strcat(recd,num);
    strcat(recd,".txt");
    file = fopen(recd,"r");

    int fLineNo = 1;





    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if(fLineNo%5 == 1)
        {
            line[strlen(line)-1] = '\0';
            records[size].id = atoi(line);
        }
        if(fLineNo%5 == 2)
        {
            line[strlen(line)-1] = '\0';
            strcpy(records[size].recvNum,line);
        }
        if(fLineNo%5 == 3)
        {
            line[strlen(line)-1] = '\0';
            records[size].time = atof(line);
        }
        if(fLineNo%5 == 4)
        {
            line[strlen(line)-1] = '\0';
            records[size].pck = atoi(line);
        }
        if(fLineNo%5 == 0)
        {
            line[strlen(line)-1] = '\0';
            records[size].net = atoi(line);
        }

        if(fLineNo%5 == 0)
        {
            size++;
        }

        fLineNo++;
    }
    //printf("----------------------------------------------------------------------------------------------------\n\n");

    fclose(file);

    double totalBill = 0;

    int i;
    for(i = 0; i < size ;i++)
    {
        if(records[i].net) totalBill+=records[i].time*packages[records[i].pck-1].offNetCallRate;
        else totalBill+=records[i].time*packages[records[i].pck-1].onNetCallRate;
    }

    printf("Total Bill : %lf\n\n",totalBill);

}

void SearchRecord(int y,char number[])
{
    struct Record records[100];
    int size=0;


    FILE* file;
    char recd[12] = "record";
    char num[3];
    num[0] = '0'+ y;
    num[1] = '\0';
    strcat(recd,num);
    strcat(recd,".txt");
    file = fopen(recd,"r");

    int fLineNo = 1;





    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if(fLineNo%5 == 1)
        {
            line[strlen(line)-1] = '\0';
            records[size].id = atoi(line);
        }
        if(fLineNo%5 == 2)
        {
            line[strlen(line)-1] = '\0';
            strcpy(records[size].recvNum,line);
        }
        if(fLineNo%5 == 3)
        {
            line[strlen(line)-1] = '\0';
            records[size].time = atof(line);
        }
        if(fLineNo%5 == 4)
        {
            line[strlen(line)-1] = '\0';
            records[size].pck = atoi(line);
        }
        if(fLineNo%5 == 0)
        {
            line[strlen(line)-1] = '\0';
            records[size].net = atoi(line);
        }

        if(fLineNo%5 == 0)
        {
            size++;
        }

        fLineNo++;
    }
    //printf("----------------------------------------------------------------------------------------------------\n\n");

    fclose(file);

    int flag = 0;
    int i;
    int idx = 0;
    for(i=0; i < size; i++)
    {
        //printf("%s\n",records[i].recvNum);
        if(!strcmp(number,records[i].recvNum))
        {
            flag = 1;
            idx = i;
            break;
        }
    }

    if(flag == 0)
    {
        printf("Your entered number doesn't in record list\n");
        return;
    }
    else
    {
        printf("Record Id : %d\n",records[idx].id);
        printf("Receiver Contact No : %s\n",records[idx].recvNum);
        printf("Time : %lf\n",records[idx].time);
        printf("Package : %d\n",records[idx].pck);
        printf("Net Type : %d\n\n",records[idx].net);
    }
}

void DeleteNumber(int y,char number[])
{
    struct Record records[100];
    int size=0;


    FILE* file;
    char recd[12] = "record";
    char num[3];
    num[0] = '0'+ y;
    num[1] = '\0';
    strcat(recd,num);
    strcat(recd,".txt");
    file = fopen(recd,"r");

    int fLineNo = 1;





    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if(fLineNo%5 == 1)
        {
            line[strlen(line)-1] = '\0';
            records[size].id = atoi(line);
        }
        if(fLineNo%5 == 2)
        {
            line[strlen(line)-1] = '\0';
            strcpy(records[size].recvNum,line);
        }
        if(fLineNo%5 == 3)
        {
            line[strlen(line)-1] = '\0';
            records[size].time = atof(line);
        }
        if(fLineNo%5 == 4)
        {
            line[strlen(line)-1] = '\0';
            records[size].pck = atoi(line);
        }
        if(fLineNo%5 == 0)
        {
            line[strlen(line)-1] = '\0';
            records[size].net = atoi(line);
        }

        if(fLineNo%5 == 0)
        {
            size++;
        }

        fLineNo++;
    }
    //printf("----------------------------------------------------------------------------------------------------\n\n");

    fclose(file);

    int flag = 0;
    int i;
    int idx = 0;
    for(i=0; i < size; i++)
    {
        //printf("%s\n",records[i].recvNum);
        if(!strcmp(number,records[i].recvNum))
        {
            flag = 1;
            idx = i;
            break;
        }
    }

    if(flag == 0)
    {
        printf("Your entered number doesn't in record list\n");
        return;
    }

    for(i=idx;i<size-1;i++)
    {
        records[i].id = records[i+1].id - 1;
        strcpy(records[i].recvNum,records[i+1].recvNum);
        records[i].time = records[i+1].time;
        records[i].pck = records[i+1].pck;
        records[i].net = records[i+1].net;
    }
    size--;



    file = fopen(recd,"w");

    users[y-1].totalRecords--;
    RefreshUserInfo();

    for(i = 0; i < size ; i++)
    {
        fprintf(file,"%d\n",records[i].id);
        fprintf(file,"%s\n",records[i].recvNum);
        fprintf(file,"%lf\n",records[i].time);
        fprintf(file,"%d\n",records[i].pck);
        fprintf(file,"%d\n",records[i].net);
    }

    fclose(file);

    printf("Your data successfully deleted\n");


}
int main()
{
    LoadPackage();
    LoadAllUserInfo();

    int flag = 0;

    do
    {


        int y;
        printf("Enter userID for updating : (1-5) : ");
        scanf("%d",&y);
        if(y<1 || y > 5) break;
        int x;
        printf("\n\nSelect activity from below \n");
        printf("---------------------------------\n");
        printf("1 -> Add Record\n");
        printf("2 -> List of Records\n");
        printf("3 -> Modify  record\n");
        printf("4 -> Rate  per package\n");
        printf("5 -> Total bill have to pay\n");
        printf("6 -> Search record by receiver phone number\n");
        printf("7 -> Delete record by receiver phone number\n");
        printf("8 -> Exit...\n");
        printf("---------------------------------\n");
        scanf("%d",&x);


        switch(x)
        {
        case 1 :
            printf("Enter a phone number 10 digit : ");
            char number[12];
            scanf("%s",number);

            printf("Time duration in min : ");
            double time;
            scanf("%lf",&time);

            printf("Package : Bondhu -> 1 | Family -> 2 | Adda -> 3\n");
            int pck;
            scanf("%d",&pck);

            printf("Type : On-Net -> 0 | Off-Net -> 1\n");
            int net;
            scanf("%d",&net);

            addRecord(y,number,time,pck,net);

            break;


        case 2 :
            ShowRecord(y);
            break;
        case 3 :
            printf("Enter receiver no for updating : ");
            char num[20];
            scanf("%s",num);
            ModifyRecord(y,num);
            break;
        case 4 :
            ShowPackageDetails();
            break;
        case 5 :
            ShowTotalBill(y);
            break;
        case 6 :
            printf("Enter receiver no for searching : ");
            //char num[20];
            scanf("%s",num);
            SearchRecord(y,num);
            break;
        case 7 :
            printf("Enter receiver no for deleting : ");
            //char num[20];
            scanf("%s",num);
            DeleteNumber(y,num);
            break;
        case 8 :
            flag = 1;
            break;

        default : break;

        }


    }while(!flag);
}
