#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>



char pil;
char acc[99];
char username[99], password[99]; plat[99];
char input_plat[99], input_user[99], input_pass[99];
bool user_allow = false;



int main(){
    home :
    system("cls");
    printf("\nWelcome To car parking\n\nPress '1' Login.\nPress '2' Create.\n"); 
    printf("\nInput : ");
    
    switch(getch()){
        case'1': 
            system("cls");
            printf("============================ ");
            printf("\n\t== Create == ");
            printf("\n============================ \n");
            printf("\nEnter Username\t\t\t: "); scanf("%s", input_user);
            printf("\nEnter Plat number\t\t:"); scanf("%s", input_plat);
            printf("\nEnter Pass\t\t\t: "); scanf("%s", input_pass);
            printf("\n========================== \n");

            printf("Now Login with User and Password\n");
            printf("\nPress any key to continue..."); getch();

        break;
        case'2':
                system("cls");
                printf("=========================== ");
                printf("\n\t== Login == ");
                printf("\n=========================== \n");
                printf("\nUsername\t: "); scanf("%s", username);
                printf("\nPassword\t: "); scanf("%s", password);
                printf("\nPlat Number\t:");
                printf("\n========================== \n");
        break;
        case'6':
            return 0;
        break;
        default :
            printf("\nWrong...");
            goto home;
    }

    if(user_allow == true){
        printf("\nCode untuk Sistem Parkirnya Disini");
    }else{
        printf("\nWrong Username or Password \nPress any key to login again...."); getch(); goto home; 
    }
    return 0;
}








