#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>


int db_person=0;
char pil;
char acc[99];
char username['0'][99], password['0'][99]; plat['0'][99];
char input_plat[99], input_user[99], input_pass[99];

bool user_allow = false;
bool exist=false;
int i ,j ,k ,count;


int main(){
    home :
    system("cls");
    printf("\nWelcome To car parking\n\nPress '1' Create.\nPress '2' Login.\n"); 
    printf("\nInput : ");
    switch(getch()){
        case'1': 
            system("cls");
            create:
            exist = false;
            j=0;
            db_person++;
            printf("============================ ");
            printf("\n\t== Create == ");
            printf("\n============================ \n");
            printf("\nEnter Username\t\t\t: "); scanf("%s", input_user);
            plat_input:
            exist = false;
            printf("\nEnter Plat number\t\t:"); scanf("%[^\n]s", input_plat);
                strupr(input_plat);
                for(i=0 ; i<db_person ; i++){
                    if (strcmp(input_plat, plat[i])==0){
                        exist = true;
                        break;
                    }
                }
                if (exist==true)
                {
                    printf("===Plat number is not available===\n");
                    printf("Do you wish to exit from creating data?(y/n)");
                        switch(getch()){
                            case 'Y':
                            case 'y':
                                goto home;
                            break;
                            case 'N':
                            case 'n':
                                goto plat_input;
                            break;
                            default:
                        printf("\n\nPlease enter a valid answer!");
                        system("pause");
                    goto create;
                        }
                }
                count = strlen(input_plat);
                    for(i=0 ; i<=count ; i++){
                        if(!(input_plat[i] >='A' && input_plat[i] <='Z') && !(input_plat[i]>='0' && input_plat[i]<='9') && !(input_plat[i]=='\0')){
                                j++;
                                break;
                        }
                    }
                if(j==1){
                    printf("===The plat should not contain any special characters!===");
                    printf("Do you wish to exit from creating data?(y/n)");
                        switch(getch()){
                            case 'Y':
                            case 'y':
                                goto home;
                            break;
                            case 'N':
                            case 'n':
                                goto plat_input;
                            break;
                            default:
                        printf("\n\nPlease enter a valid answer!");
                        system("pause");
                    goto create;
                }}
            printf("\nEnter Pass\t\t\t: "); scanf("%s", input_pass);

            printf("\n========================== \n");

            printf("Now Login with User and Password\n");
            printf("\nPress any key to continue..."); 
            getch();
        break;
        case'2':
            login:
            system("cls");
            printf("=========================== ");
            printf("\n\t== Login == ");
            printf("\n=========================== \n");
            printf("\nUsername\t: "); scanf("%s", username);
            printf("\nPassword\t: "); scanf("%s", password);
            printf("\nPlat Number\t:"); scanf("%s", plat);
            printf("\n========================== \n");
        break;
        case'6':
            return 0;
        break;
        default :
            printf("\nWrong...");
            goto home;

    }
    }
    
    
