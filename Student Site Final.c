#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>


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
    };
typedef struct std_library l_info;

struct std_net
    {
        float t_md;
        float o_md;
        float fined;
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

student *search(FILE *p,student *record);
student *load(FILE *p,student *record);

FILE *p;
student *start;
char id[8];
int main()
    {
        start=(student *)malloc(sizeof(student));
        if((p=fopen("linkedpersonal.txt","r"))==NULL)
            {
                printf("<Error>");
                exit(1);
            }
        load(p,start);
        fclose(p);

        printf("################################################################################");
        printf("##                  Welcome to IUT Pocket Allowance system                    ##");
        printf("##                              < Student Site >                              ##");
        printf("################################################################################");
        printf("\nEnter student ID :");
        scanf("%s",&id);
        search(p,start);
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
student *search(FILE *p,student *record)
    {
       if(strcmp(record->academic.std_id,id)==0)
        {
            printf("\n================================================================================                               STUDENT RECORD\n================================================================================");
            printf("Name : %s\n",record->personal.name);
            printf("Age : %s\n",record->personal.age);
            printf("Mobile No. : %s\n",record->personal.mobile_no);
            printf("Student ID : %s\n",record->academic.std_id);
            printf("Department : %s\n",record->academic.department );
            printf("Programme : %s\n",record->academic.programme);
            printf("Academic Year : %s\n",record->academic.academic_year);
            printf("Total  Net Used : %f\n",record->net.t_md);
            printf("Net Overtime : %f\n",record->net.o_md);
            printf("Net Fine : %f\n",record->net.fined);
            printf("Books Issued : %d\n",record->library.books_issued);
            printf("Date Issued : %d",record->library.d_i);
            printf("/%d",record->library.m_i);
            printf("/%d\n",record->library.y_i);
            printf("Date Submitted : %d",record->library.d_s);
            printf("/%d",record->library.m_s);
            printf("/%d\n",record->library.y_s);
            printf("Library Extra Time : %d\n",record->library.et);
            printf("Library Fine : %f\n",record->library.fine);
            printf( "Pocket Allowance : %f\n", record->balance.allowanced);
            char c;
            printf("\n\nPress '1' to return to home screen '2' to exit\n");
            c=getch();
            if(c=='1')
                {
                    system("cls");
                    main();
                }
            else exit(1);
        }
        else
            {

                if(record->next!=NULL)search(p,record->next);
                else
                    {
                        char c;
                                printf("\n================================================================================                           STUDENT RECORD NOT FOUND  \n================================================================================");
                                printf("\n\nPress '1' to return to home screen '2' to exit\n");
                                c=getch();
                                if(c=='1')
                                    {
                                        system("cls");
                                        main();
                                    }
                                else exit(1);
                    }
            }
}
