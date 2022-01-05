#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

FILE *add, *read, *admin;

int i;
int pil, pil2;
char acc[99], logged_user[99], user[99], logged_plat[99];
char input_user[99], input_pass[99], input_plat[99];
bool duplicate, asc;
bool user_is_admin, user_allow;

int main(){
    account :
    system("cls");
    printf("\nWelcome\n\nPress '1' Register.\nPress '2' Login.\nPress '3' Exit.\n"); 
    printf("\nInput : "); scanf("%d", &pil);
    switch(pil){
        case 1 : 
            duplicate = false; asc = false;
            add = fopen("log.txt", "a"); read = fopen("log.txt", "r");

            reg:
            system("cls");
            printf("============================ ");
            printf("\n\t== Register == ");
            printf("\n============================ \n");
            printf("\nEnter User\t\t: "); fflush(stdin); scanf("%[^\n]", input_user);
            strcpy(user, input_user);
            while(fscanf(read,"%[^|]|%[^|]|%[^\n]\n", input_user, input_pass, input_plat) != EOF){
                if(strcmp(input_user, user) == 0){ 
                    duplicate = true; 
                }
            }
            printf("Enter Pass\t\t: "); fflush(stdin); scanf("%[^\n]", input_pass);
            printf("Enter Car Plat Number\t: "); fflush(stdin); scanf("%[^\n]", input_plat); strupr(input_plat);
            printf("\n========================== \n");
            for(i = 0; i <= strlen(input_plat) ; i++){
                if( (input_plat[i] >= 33  && input_plat[i] <= 47)||  
                    (input_plat[i] >= 58 && input_plat[i] <= 64) ||  
                    (input_plat[i] >= 91 && input_plat[i] <= 96) ||  
                    (input_plat[i] >= 123 && input_plat[i] <= 126)){
                        asc = true;
                }
            }
            if(asc == false){
                if(duplicate == false){
                    fprintf(add,"%s|%s|%s\n", input_user, input_pass , input_plat);
                    printf("Data has been succesfully registered!\n");
                    printf("Now Login with User and Password\n");
                    fclose(add); fclose(read);
                    printf("\nPress any key to login..."); getch(); goto login;
                }else{
                    printf("\nInputan Username Terdeteksi Duplikasi\n");
                }
            }else{
                printf("\nThe Plat should not contain any special characters!\n");
            }
            printf("\nPress any key to return..."); getch(); goto account; break;

        case 2 : 
            user_allow = false; user_is_admin = false;
            char admin_user[99], admin_pass[99], username[99], password[99];
            read = fopen("log.txt", "r"); admin = fopen("admin.txt", "r");

            login:
            system("cls");
            printf("=========================== ");
            printf("\n\t== Login == ");
            printf("\n=========================== \n");
            printf("\nUser\t\t: "); fflush(stdin); scanf("%[^\n]", username);
            printf("Password\t: "); fflush(stdin); scanf("%[^\n]", password);
            printf("\n========================== \n");
            while(fscanf(read,"%[^|]|%[^|]|%[^\n]\n", input_user, input_pass, input_plat) != EOF){
                if(strcmp(username, input_user) == 0 && strcmp(password, input_pass) == 0){
                    user_allow = true; user_is_admin = false;
                    strcpy(logged_user, username);
                    strcpy(logged_plat, input_plat);
                }
            }
            while(fscanf(admin,"%[^|]|%[^\n]\n", admin_user, admin_pass) != EOF){
                if(strcmp(username, admin_user) == 0 && strcmp(password, admin_pass) == 0){
                    user_is_admin = true; user_allow = true;
                    strcpy(logged_user, admin_user);
                }
            }
            fclose(read); fclose(admin);

            if(user_allow == true){
                parking:
                system("cls");
                printf("\nWelcome, %s", logged_user);
                if(user_is_admin == true){
                    printf("\n\n === FOR ADMIN ===\n");
                    printf("1. Display Vehicles Parked.\n2. Change Password.\n0. Logout.\n");
                    printf("\nInput : "); scanf("%d", &pil2);
                    switch(pil2){
                        case 1 : printf("display"); goto parking;
                        case 2 : printf("Password"); goto parking;
                        case 0 : system("cls"); goto account; break;
                        default: system("cls"); printf("\nWrong...\nPress any key..."); getch(); goto parking;
                    }
                }else{
                    printf("\n\n === VEHICLE PARKING ===\n");
                    printf("\nPlat Number is %s", logged_plat);
                    printf ("\n1. Arrival Of Vehicle\n2. Display Vehicles Parked\n3. Departure Of Vehicle\n0. Logout\n");
                    printf("\nInput : "); scanf("%d", &pil2);
                    switch(pil2){
                        case 1 : printf("add"); goto parking;
                        case 2 : printf("display"); goto parking;
                        case 3 : printf("departure"); goto parking;
                        case 0 : system("cls"); goto account; break;
                        default: system("cls"); printf("\nWrong...\nPress any key..."); getch(); goto parking;
                    }
                }
            }else{
                printf("\nWrong Username or Password \nPress any key to login again...."); getch(); goto account; 
            }
            break; 

        case 3 :
            return(0);

        default : printf("\nWrong..."); goto account;
    }
    
}
