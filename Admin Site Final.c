#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

char pw[]={"iutpas"};
struct std_personal
    {
        char name[20];
        char age[4];
        char mobile_no[12];
    };
typedef struct std_personal p_info;

struct std_academic
    {
        char std_id[8];
        char department[4];
        char programme[20];
        char academic_year[11];
    };
typedef struct std_academic a_info;

struct std_library
    {
        int books_issued ;
        int books_returned ;
        int d_i ;
        int m_i ;
        int y_i ;
        int d_s ;
        int m_s ;
        int y_s ;
        int et ;
        float fine;
        char books_issuedc [10];
        char books_returnedc [10];
        char d_ic[10];
        char m_ic[10];
        char y_ic[10]   ;
        char d_sc[10] ;
        char m_sc[10] ;
        char y_sc[10];
        char etc[10];
        char finec[10];
    };
typedef struct std_library l_info;

struct std_net
    {
        float t_md;
        float o_md;
        float fined;
        char t_m[10];
        char o_m[10];
        char fine[10];
    };
typedef struct std_net n_info;

struct std_bank
    {

        float allowanced;
    };
typedef struct std_bank b_info;

struct total
    {
        p_info personal;
        a_info academic;
        l_info library;
        n_info net;
        b_info balance;
        struct total *next;
    };
typedef struct total student;

FILE *p,*p2;
student *start;


void create(FILE *p,student *record);
void display(student *record,int i);
void write(FILE *p2,student *record);
student *load(FILE *p,student *record);
student *update(student *record);
student *netlog(FILE *p,student *record );
student *lib(FILE *p,student *record );
student *issue(FILE *p,student *record );
student *bank(FILE *p,student *record);
student *locate(student* record);
void security();
void menu();
float pm=38,cm=2.5;
char target_id[8];

void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 50; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 50);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,50);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,50);
    printf("%c",200);
    for(i = 249; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 50; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void print_heading(const char st[]){
    SetColorAndBackground(31,28);
    gotoxy(45,8);printf("%s",st);
    SetColorAndBackground(17,15);
}

void window(){
    int i;
    drawRectangle();
    SetColor(42);
    gotoxy(1,1);
    for(i=1; i<78;i++){
        gotoxy(i,1);
        printf("#");
    }
    gotoxy(1,1);
    for(i=1;i<5;i++){
        gotoxy(1,i);
        printf("#");
    }
    for(i = 1; i < 78; i++){
        gotoxy(i,5);
        printf("#");

    }
    for(i=1;i<5;i++){
        gotoxy(77,i);
        printf("#");
    }
    gotoxy(24,2);
    printf("Welcome to IUT Pocket Allowance system");
    gotoxy(35,3);
    printf("< Admin Site >");
    gotoxy(27,4);
    printf("Islamic University Of Technology");
    gotoxy(25,24);
    SetColor(17);

}

void main_window(){
    int choice;
    SetColor(42);
    int x = 2, i=0;
    start=(student *)malloc(sizeof(student));
        if((p=fopen("linkedpersonal.txt","r"))==NULL)
                            {
                                printf("<Error>\nFile has not been created\n\n");
                                exit(1);
                            }
        load(p,start);
        fclose(p);
        gotoxy(x,8);printf("1. Write");
        gotoxy(x,10);printf("2. Update");
        gotoxy(x,12);printf("3. Display");
        gotoxy(x,14);printf("4. Log Out");
        gotoxy(x,16);printf("Enter your choice: ");
        choice=getch();
        switch(choice){
            case '1':
                if((p=fopen("linkedpersonal.txt","a"))==NULL){
                    printf("<Error>");
                    exit(1);
                }
                create(p,start);
                fclose(p);
                break;
            case '2':
                if((p2=fopen("linkedpersonal.txt","w"))==NULL){
                    printf("<Error>");
                    exit(1);
                }
                update(start);
                write(p2,start);
                fclose(p2);
                system("cls");
                printf("\n\n\n                                  Logging Out");
                Sleep(1000);
                system("cls");
                main();
                break;
            case '3':
                        system("cls");
                        printf("################################################################################");
                        printf("##                  Welcome to IUT Pocket Allowance system                    ##");
                        printf("##                                < Admin Site >                              ##");
                        printf("##                              < Display Record >                            ##");
                        printf("################################################################################");
                        if((p=fopen("linkedpersonal.txt","r"))==NULL)
                            {
                                printf("<Error>\nFile has not been created\n\n");
                                exit(1);
                            }
                        display(start,i);
                        fclose(p);
                       break;
                default :system("cls");
                        printf("\n\n\n                                  Logging Out");
                        Sleep(1000);
                        system("cls");
                        main_window();

            }


}

int main()
    {
        security();
    }
void security()
{
    int i,j,k;
        char ch;
        char pass[6];
        printf("################################################################################");
        printf("##                  Welcome to IUT Pocket Allowance system                    ##");
        printf("##                                < Admin Site >                              ##");
        printf("################################################################################");
        printf("\n\n\n                  Enter Admin Password :");

        for(i=0;i<6;i++){
        ch=getch();
        pass[i]=ch;
        printf("*");
        }
        pass[i]='\0';

        if(strcmp(pass,pw)==0)
        {
            system("cls");
            printf("\n\n\n                             Login Successful");
            Sleep(1000);
            system("cls");
            printf("\n\n\n                    Please Wait While The System Is Loading");
            Sleep(1000);
            system("cls");
            window();
            main_window();
        }
        else
            {
                printf("\n                  Wrong Password!!\n                  Try Again!!");
                Sleep(500);
                system("cls");
                main();
            }
}
student *load(FILE *p,student *record)
    {
        record->next=(student *)malloc(sizeof(student));
        fscanf(p,"%s ",&record->personal.name);
        fscanf(p,"%s ",&record->personal.age);
        fscanf(p,"%s ",&record->personal.mobile_no);
        fscanf(p,"%s ",&record->academic.std_id);
        fscanf(p,"%s ",&record->academic.programme);
        fscanf(p,"%s ",&record->academic.department);
        fscanf(p,"%s ",&record->academic.academic_year);
        fscanf(p,"%f ",&record->net.t_md);
        fscanf(p,"%f ",&record->net.o_md);
        fscanf(p,"%f ",&record->net.fined);
        fscanf(p,"%d ",&record->library.books_issued);
        fscanf(p,"%d ",&record->library.d_i);
        fscanf(p,"%d ",&record->library.m_i);
        fscanf(p,"%d ",&record->library.y_i);
        fscanf(p,"%d ",&record->library.d_s);
        fscanf(p,"%d ",&record->library.m_s);
        fscanf(p,"%d ",&record->library.y_s);
        fscanf(p,"%d ",&record->library.et);
        fscanf(p,"%f ",&record->library.fine);
        fscanf(p,"%f",&record->balance.allowanced);

        if(!feof(p))load(p,record->next);
        else
            {
                record->next=NULL;
            }
    }
  void display(student *record,int i)
    {

        printf("\n================================================================================                                  RECORD : %d\n================================================================================",i+1);
        printf("\nName : %s\n",record->personal.name);
        printf("Age : %s\n",record->personal.age);
        printf("Mobile No. : %s\n",record->personal.mobile_no);
        printf("Student ID : %s\n",record->academic.std_id);
        printf("Department : %s\n",record->academic.department );
        printf("Programme : %s\n",record->academic.programme);
        printf("Academic Year : %s\n",record->academic.academic_year);
        printf("Total  Net Used : %.2f\n",record->net.t_md);
        printf("Net Overtime : %.2f\n",record->net.o_md);
        printf("Net Fine : %.2f\n",record->net.fined);
        printf("Books Issued : %d\n",record->library.books_issued);
        printf("Date Issued : %d",record->library.d_i);
        printf("/%d",record->library.m_i);
        printf("/%d\n",record->library.y_i);
        printf("Date Submitted : %d",record->library.d_s);
        printf("/%d",record->library.m_s);
        printf("/%d\n",record->library.y_s);
        printf("Library Extra Time : %d\n",record->library.et);
        printf("Library Fine : %.2f\n",record->library.fine);
        printf( "Pocket Allowance : %.2f\n", record->balance.allowanced);

        if(record->next!=NULL)
            {
                i++;
                display(record->next,i);
            }

        else
        {
            printf("\n================================================================================                                        EOF\n================================================================================\n");
            char c;
            printf("\n\nPress '1' to exit \n");
            c=getch();
            if(c=='1'){
                system("cls");
                printf("\n\n\n                                  Logging Out");
                Sleep(1000);
                system("cls");
                main();
            }
        }

    }
void create(FILE *p,student *record)
    {
        clearWindow();
        int print=37;
        gotoxy(49,7);printf("Personal Info");
        gotoxy(print,8);printf("Enter name : ");
        scanf("%s",&record->personal.name);
        gotoxy(print,9);printf("Enter age : ");
        scanf("%s",&record->personal.age);
        gotoxy(print,10);printf("Enter mobile no. : ");
        scanf("%s",&record->personal.mobile_no);
        gotoxy(49,11);printf("Academic info");
        gotoxy(print,12);printf("Enter Student ID : ");
        scanf("%s",&record->academic.std_id);
        gotoxy(print,13);printf("Enter Department : ");
        scanf("%s",&record->academic.department);
        gotoxy(print,14);printf("Enter Programme : ");
        scanf("%s",&record->academic.programme);
        gotoxy(print,15);printf("Enter Academic Year : ");
        scanf("%s",&record->academic.academic_year);
        netlog(p,record);
        lib(p,record);
        bank(p,record);
        fprintf(p,"\n%s ",record->personal.name);
        fprintf(p,"%s ",record->personal.age);
        fprintf(p,"%s ",record->personal.mobile_no);
        fprintf(p,"%s ",record->academic.std_id);
        fprintf(p,"%s ",record->academic.department );
        fprintf(p,"%s ",record->academic.programme);
        fprintf(p,"%s ",record->academic.academic_year);
        fprintf(p,"%.2f ",record->net.t_md);
        fprintf(p,"%.2f ",record->net.o_md);
        fprintf(p,"%.2f ",record->net.fined);
        fprintf(p,"%d ",record->library.books_issued);
        fprintf(p,"%d ",record->library.d_i);
        fprintf(p,"%d ",record->library.m_i);
        fprintf(p,"%d ",record->library.y_i);
        fprintf(p,"%d ",record->library.d_s);
        fprintf(p,"%d ",record->library.m_s);
        fprintf(p,"%d ",record->library.y_s);
        fprintf(p,"%d ",record->library.et);
        fprintf(p,"%.2f ",record->library.fine);
        fprintf(p,"%.2f",record->balance.allowanced);



        gotoxy(print,46);printf("(Enter 'q' to quit and 'h' to return");
        if(getch()=='q')
            {
                record->next=NULL;
                exit(1);
            }
        else
            {
                system("cls");
                record->next=(student*)malloc(sizeof(student));
                drawRectangle();
                window();
                main_window();
                create(p,record->next);
            }
            return;

    }
student *netlog(FILE *p,student *record)
    {
        unsigned int j=0,h=0,m=0,s=0,elapsed;
        struct tm *pm1,*pm2;
        char str1[100],str2[100];
        time_t t1,t2;
        static int max=200;
        clock_t start, end;
        int count,print=37;
        double fine_sec=.25;
        float t_m,o_m;
        char name[20],id[8];

        gotoxy(49,16);printf("Net info");
        gotoxy(print,17);printf("Enter name : ");
        scanf("%s",&name);
        gotoxy(print,18);printf("Enter student ID :",id);
        scanf("%s",&id);

        if(strcmp(record->academic.std_id,id)==0 && strcmp(record->personal.name,name)==0  )
            {
                gotoxy(print,20);printf("1.Connect");
                gotoxy(print,21);printf("2.Disconnect");
                gotoxy(print,22);printf("<press 'c' to connect 'd' to disconnect>");
                if(getch()=='c')
                    {
                        start = clock();
                        t1=time(NULL);
                        pm1=localtime(&t1);
                        strftime(str1,100,"  %A %I:%M:%S %p",pm1);
                        gotoxy(print,23);printf("Net Connected!!!");
                    }
                if(getch()=='d')
                    {
                        end = clock();
                        t2=time(NULL);
                        pm2=localtime(&t2);
                        strftime(str2,100,"  %A %I:%M:%S %p",pm2);
                        gotoxy(print,24);printf("Net Disconnected!!!");
                    }
                elapsed = (end - start) /CLOCKS_PER_SEC;
                record->net.t_md=(elapsed*60);
                gotoxy(print,25);printf("Total usage!!! => %.2f minutes", record->net.t_md);
                if(record->net.t_md>max)
                    {
                        record->net.o_md=record->net.t_md-max;
                        gotoxy(print,26);printf("Overtime!!! => %.2f minutes",record->net.o_md);
                        record->net.fined=fine_sec*record->net.o_md;
                        gotoxy(print,27);printf("Fine!!! => BDT %.2f",record->net.fined);
                    }
                else
                    {
                        record->net.o_md=0;
                        record->net.fined=0;
                        gotoxy(print,26);printf("Overtime!!! => 0:0:0\n");
                        gotoxy(print,27);printf("Fine!!! => BDT 00.00\n\n");
                    }
            }
        else
            {
                fflush(stdin);
                netlog(p,record);
            }
        return record;

    }
student *lib(FILE *p,student *record)
    {
        char name[20],id[8];
        int print=37;
        gotoxy(47,28);printf("Library info");
        gotoxy(print,29);printf("Enter name : ");
        scanf("%s",&name);
        gotoxy(print,30);printf("Enter student ID :",id);
        scanf("%s",&id);
        if(strcmp(record->academic.std_id,id)==0 && strcmp(record->personal.name,name)==0  )
            {
                issue(p,record);
            }
        else
            {
                lib(p,record);
            }
        return record;
    }
student *issue(FILE *p,student *record)
    {

        int elapsed;
        int isu,print=37;
        struct tm *pm1,*pm2;
        time_t t1,t2;
        char str[100],str2[100];
        char c;
        gotoxy(print,31);printf("Enter number of books issued <MAX 5>: ");
        scanf("%d",&record->library.books_issued);
        if(record->library.books_issued==0)
            {
                record->library.fine=0.00;
                record->library.d_i=0;
                record->library.m_i=0;
                record->library.y_i=0;
                record->library.d_s=0;
                record->library.m_s=0;
                record->library.y_s=0;
                record->library.et=0;
            }
        else if(record->library.books_issued<=5)
            {
                gotoxy(print,33);printf("1.Issue");
                gotoxy(print,34);printf("2.Submit");
                gotoxy(print,35);printf("<press 'i' to issue 's' to submit>");
                clock_t start, end;
                if(getch()=='i')
                    {
                        start = clock();
                        t1=time(NULL);
                        pm1=localtime(&t1);
                        record->library.d_i=pm1->tm_mday;
                        record->library.m_i=pm1->tm_mon+1;
                        record->library.y_i=pm1->tm_year+1900;
                        gotoxy(print,36);printf("Books issued!!! on %d/%d/%d",pm1->tm_mday,pm1->tm_mon+1,pm1->tm_year+1900);
                    }
                if(getch()=='s')
                    {
                        end = clock();
                        t2=time(NULL);
                        pm2=localtime(&t2);
                        record->library.d_s=pm2->tm_mday;
                        record->library.m_s=pm2->tm_mon+1;
                        record->library.y_s=pm2->tm_year+1900;
                        elapsed = (end - start) /CLOCKS_PER_SEC;
                        if((pm2->tm_mon+1)==1 || (pm2->tm_mon+1)==3 ||
                            (pm2->tm_mon+1)==5 ||(pm2->tm_mon+1)==7 ||
                            (pm2->tm_mon+1)==8 ||(pm2->tm_mon+1)==10||
                            (pm2->tm_mon+1)==12 )
                            {
                                if((pm2->tm_mday+elapsed)>31 )
                                    {
                                        record->library.d_s=((pm2->tm_mday+elapsed)%31)+1;
                                        record->library.m_s=(pm2->tm_mon+1)+1;
                                        if(record->library.m_s>12)
                                                {
                                                    record->library.m_s=(pm2->tm_mon+1)%12+1;
                                                    record->library.y_s=pm2->tm_year+1900+1;
                                                }
                                    }
                                    else
                                    {
                                        record->library.d_s=(pm2->tm_mday+elapsed);
                                        record->library.m_s=(pm2->tm_mon+1);
                                        record->library.m_s=(pm2->tm_mon+1);
                                        record->library.y_s=pm2->tm_year+1900;
                                    }
                            }
                        else if((pm2->tm_mon+1)==2 )
                                {
                                    if((pm2->tm_mday+elapsed)>28 )
                                        {
                                            record->library.d_s=((pm2->tm_mday+elapsed)%28)+1;
                                            record->library.m_s=(pm2->tm_mon+1)+1;
                                            if(record->library.m_s>12)
                                                {
                                                    record->library.m_s=(pm2->tm_mon+1)%12+1;
                                                     record->library.y_s=pm2->tm_year+1900+1;
                                                }
                                        }
                                    else
                                    {
                                        record->library.d_s=(pm2->tm_mday+elapsed);
                                        record->library.m_s=(pm2->tm_mon+1);
                                        record->library.m_s=(pm2->tm_mon+1);
                                        record->library.y_s=pm2->tm_year+1900;
                                    }
                                }
                            else if((pm2->tm_mon+1)==4 ||
                            (pm2->tm_mon+1)==6 ||(pm2->tm_mon+1)==9 ||(pm2->tm_mon+1)==11)
                                {
                                    if((pm2->tm_mday+elapsed)>30 )
                                        {
                                            record->library.d_s=((pm2->tm_mday+elapsed)%30)+1;
                                            record->library.m_s=(pm2->tm_mon+1)+1;
                                            if(record->library.m_s>12)
                                                {
                                                    record->library.m_s=(pm2->tm_mon+1)%12+1;
                                                     record->library.y_s=pm2->tm_year+1900+1;
                                                }
                                        }
                                    else
                                    {
                                        record->library.d_s=(pm2->tm_mday+elapsed);
                                        record->library.m_s=(pm2->tm_mon+1);
                                        record->library.m_s=(pm2->tm_mon+1);
                                        record->library.y_s=pm2->tm_year+1900;
                                    }
                                }


                        gotoxy(print,37);printf("Books submitted!!! on %d/%d/%d",record->library.d_s,record->library.m_s,record->library.y_s);

                    }
                int max=5;
                if(elapsed>max)record->library.et=elapsed-max;
                else record->library.et=0;
                gotoxy(print,38);printf("Extra time : %d days\n",record->library.et);

                        record->library.fine=.25*record->library.et;
                        gotoxy(print,39);printf("Library Fine : BDT %.2f",record->library.fine);
            }
        else
            {
                issue(p,record);
            }
        return record;
    }
student *bank(FILE *p,student *record)
    {
        float rate,p_m;
        int print=37;
        gotoxy(47,40);printf("Bank Info");
        gotoxy(print,41);printf("Enter Dollar Rate: ");
        scanf("%f",&rate);
        gotoxy(print,42);printf("Net Fine : BDT %.2f",record->net.fined);
        gotoxy(print,43);printf("Library Fine : BDT %.2f",record->library.fine);
        record->balance.allowanced=(pm*rate)-(cm*rate)-record->library.fine-record->net.fined;

        gotoxy(print,44);printf("Pocket Allowance : BDT %.2f",record->balance.allowanced);
        return record;
    }

student *update(student *record)
    {

        student *t1,*t2;
        gotoxy(37,8);printf("Enter Student ID to remove : ");
        scanf("%s",&target_id);
        if(strcmp(record->academic.std_id,target_id)==0)
        {
            t1=start->next;
            free(start);
            start=t1;
        }
        else
        {
            t2=locate(start);
            if(t2==NULL)
            {
                system("cls");
                printf("\n================================================================================                           STUDENT RECORD NOT FOUND  \n================================================================================");
                Sleep(1000);
                system("cls");
                printf("\n\n\n                                  Logging Out");
                Sleep(1000);
                system("cls");
                main();
            }
            else
            {
                t1=t2->next->next;
                free(t2->next);
                t2->next=t1;
            }
        }

}
void write(FILE *p2,student *record)
    {
                        fprintf(p2,"\n%s ",record->personal.name);
                        fprintf(p2,"%s ",record->personal.age);
                        fprintf(p2,"%s ",record->personal.mobile_no);
                        fprintf(p2,"%s ",record->academic.std_id);
                        fprintf(p2,"%s ",record->academic.department );
                        fprintf(p2,"%s ",record->academic.programme);
                        fprintf(p2,"%s ",record->academic.academic_year);
                        fprintf(p2,"%.2f ",record->net.t_md);
                        fprintf(p2,"%.2f ",record->net.o_md);
                        fprintf(p2,"%.2f ",record->net.fined);
                        fprintf(p2,"%d ",record->library.books_issued);
                        fprintf(p2,"%d ",record->library.d_i);
                        fprintf(p2,"%d ",record->library.m_i);
                        fprintf(p2,"%d ",record->library.y_i);
                        fprintf(p2,"%d ",record->library.d_s);
                        fprintf(p2,"%d ",record->library.m_s);
                        fprintf(p2,"%d ",record->library.y_s);
                        fprintf(p2,"%d ",record->library.et);
                        fprintf(p2,"%.2f ",record->library.fine);
                        fprintf(p2,"%.2f",record->balance.allowanced);
                         if(record->next!=NULL)write(p2,record->next);


    }

student *locate(student* record)
    {
        if(strcmp(record->next->academic.std_id,target_id)==0)
            {
                return(record);
            }
        else if(strcmp(record->next->academic.std_id,target_id)!=0)
            {
                if(record->next->next==NULL)
                    {
                        return (NULL);
                    }

                else locate(record->next);
            }
    }
