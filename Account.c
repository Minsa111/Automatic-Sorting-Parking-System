#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>


double db_person=0;
char pil;
char acc[99];
char username['0'][99], password['0'][99]; plat['0'][99];
char input_plat[99], input_user[99], input_pass[99];

bool user_allow = false;
bool exist=false;
int compare_user, compare_plat, compare_pass;
int i ,j ,k ,count;


int main(){
    home :
    system("cls");
    printf("===Welcome To car parking===\n\nPress '1' Register.\nPress '2' Login.\n"); 
    printf("\nInput : ");
    switch(getch()){
        case'1': 
            system("cls");
            if (db_person == 20){
                printf("Sorry there's no parking slot available");
                system ("pause");
                goto home;
            }
            reg:
            exist = false;
            j=0;
            db_person++;
            printf("============================ ");
            printf("\n\t== Register == ");
            printf("\n============================ \n");
            printf("\nEnter Username\t\t\t: "); scanf("%s", input_user);

            // nyari kalo username udah ada apa belum.
                for(i=1; i<=db_person ; i++){
                    if(strcmp(input_user, username[i])==0){
                        exist=true;
                        break;
                    }
                }
                if(exist==true){
                    printf("=== Sorry, username is not available ===");
                    printf("\n\nDo you want to try again?(y/n)");
                    switch(getch()){
                        case'y':
                        case'Y':
                            goto reg;
                        break;
                        case'n':
                        case'N':
                            db_person--;
                            goto home;
                        break;
                    }
                }
                reg_plat:
                printf("Enter car plat number!");
                scanf("%s", input_plat);
                strupr(input_plat);
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
                                db_person--;
                                    goto home;
                                break;
                                case 'N':
                                case 'n':
                                    goto reg_plat;
                                break;
                                default:
                            printf("\n\nPlease enter a valid answer!");
                            system("pause");
                        goto reg;
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
            printf("\nUsername\t: "); scanf("%s", input_user);
            printf("\nPassword\t: "); scanf("%s", input_pass);
            printf("\nCar Plat Number\t:"); scanf("%[^\n]", input_plat);
            strupr(input_plat);
            
            printf("\n========================== \n");
        break;
        case'6':
            return 0;
        break;
        default :
            printf("\n=== Please Input a valid answer!!! ===");
            system("pause");
            goto home;

    }
    }
    
    
