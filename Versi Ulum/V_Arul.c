#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

FILE *add, *read, *write, *admin;

char logged_user[99], logged_plat[99], user[99], pass[99], plat[99];
char input_user[99], input_pass[99], input_plat[99];
bool duplicate, update, asc;
bool user_is_admin, user_allow;

void create(), login(), loading();
void edit();

int main(){

    home:
    system("cls");
    printf("\nWelcome\n\nPress '1' Register.\nPress '2' Login.\nPress '0' Exit.\n"); 
    printf("\nInput : ");
    
    switch(getch()){
        case '1' : 
            create(); goto home; break;

        case '2' :
            login();
            system("cls");
            loading(1);

            if(user_allow == true){
                parking:
                system("cls");
                if(user_is_admin == true){
                    printf("\nWelcome, %s Handsome", logged_user);
                    printf("\n\n=== FOR ADMIN ===\n");
                    printf("\n1. Display Vehicles Parked.\n2. Edit Data (Help).\n0. Logout.\n");
                    printf("\nInput : ");
                    switch(getch()){
                        case '1' : goto parking;
                        case '2' : edit(); goto parking;
                        case '0' : system("cls"); loading(0); goto home; break;
                        default: system("cls"); printf("\nWrong...\nPress any key..."); getch(); goto parking;
                    }
                }else{
                    printf("\nWelcome, %s", logged_user);
                    printf("\nPlat Number is %s", logged_plat);
                    printf("\n\n=== VEHICLE PARKING ===\n");
                    printf ("\n1. Arrival of Vehicle\n2. Display Vehicles Parked\n3. Edit Data\n4. Leave\n0. Logout\n");
                    printf("\nInput : ");
                    switch(getch()){
                        case '1' : goto parking;
                        case '2' : goto parking;
                        case '3' : edit(); goto parking;
                        case '4' : goto parking;
                        case '0' : system("cls"); loading(0); goto home; break;
                        default: system("cls"); printf("\nWrong...\nPress any key..."); getch(); goto parking;
                    }
                }
            }else{
                system("cls");
                printf("\nWrong Username or Password \nPress any key to login again...."); getch(); goto home; 
            }
            break; 

        case '0' :
            return(0);

        default : printf("\n\nInput error...\nPress any key..."); getch(); goto home;
    }
    
}

void loading(int logged){
    printf("======================= ");
    printf("\n == System Parking == ");
    printf("\n======================= ");
	if(logged == 1){
        printf("\n\nSedang Login");
    } else if (logged == 0){
        printf("\n\nSedang Logout");
    }
	Sleep(500); printf("..."); Sleep(50); printf("..."); Sleep(40); printf(".."); Sleep(500); printf(".."); Sleep(900); printf(".");
}

void login(){
    user_allow = false; user_is_admin = false;
    char admin_user[99], admin_pass[99], username[99], password[99];
    read = fopen("db_car.txt", "r"); admin = fopen("admin.txt", "r");

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
}

void create(){
    duplicate = false; asc = false;
    add = fopen("db_car.txt", "a"); read = fopen("db_car.txt", "r");

    system("cls");
    printf("============================== ");
    printf("\n\t== Register == ");
    printf("\n============================== \n");
    printf("\nEnter Plat Number\t: "); fflush(stdin); scanf("%[^\n]", plat); strupr(plat);
    for(int i = 0; i <= strlen(plat) ; i++){ 
        if( (plat[i] >= 33  && plat[i] <= 47)||  
            (plat[i] >= 58 && plat[i] <= 64) ||  
            (plat[i] >= 91 && plat[i] <= 96) ||  
            (plat[i] >= 123 && plat[i] <= 126)){
                asc=true;
        }
    }
    while(fscanf(read,"%[^|]|%[^|]|%[^\n]\n", input_user, input_pass, input_plat) != EOF){
        if(strcmp(input_user, user) == 0){ 
            duplicate = true; 
        }
    }
    if(asc == false){
        strcpy(input_plat, plat);
        printf("Enter User\t\t: "); fflush(stdin); scanf("%[^\n]", user);
        if(duplicate == false){
            strcpy(input_user, user);
            printf("Enter Pass\t\t: "); fflush(stdin); scanf("%[^\n]", pass);
            strcpy(input_pass, pass);
            printf("\n============================== \n");
            fprintf(add,"%s|%s|%s\n", input_user, input_pass , input_plat);
            printf("Data has been succesfully registered!\n");
            printf("Now Login with User and Password\n");
            printf("============================== \n");
        }else{
            printf("\nUsername Detected Duplicate \n");
        }
    }else{
        printf("\nThe Plat should not contain any special characters!\n");
        }
    
    fclose(add); fclose(read);
    printf("\nPress any key to return..."); getch();
}

void edit(){
    system("cls");
    read = fopen("db_car.txt", "r"); write = fopen("db_car_temp.txt", "w");
    update = false;

    printf("=== Update Data ===\n\n");
    printf("Insert password to change your data: "); scanf("%s", pass);
    while(fscanf(read,"%[^|]|%[^|]|%[^\n]\n", input_user, input_pass, input_plat) != EOF){
        if(strcmp(input_pass, pass) == 0){
            update = true;
            printf("\n===Your current data===\n\n");
            printf("Username\t: %s\n", input_user);
            printf("Password\t: %s\n", input_pass);
            printf("Plat\t\t: %s\n", input_plat);

            edit_data:
            printf("\n===Your New Data===\n\n");
            printf("Enter New Plat Number\t: "); fflush(stdin); scanf("%[^\n]", plat); strupr(plat);
            for(int i = 0; i <= strlen(plat) ; i++){ 
                if( (plat[i] >= 33  && plat[i] <= 47)||  
                    (plat[i] >= 58 && plat[i] <= 64) ||  
                    (plat[i] >= 91 && plat[i] <= 96) ||  
                    (plat[i] >= 123 && plat[i] <= 126)){
                        asc=true;
                }
            }
            if(asc == false){
                strcpy(input_plat, plat);
                printf("Enter New Username\t: "); fflush(stdin); scanf("%[^\n]", input_user);
                printf("Enter New Password\t: "); fflush(stdin); scanf("%[^\n]", input_pass);
                fprintf(write,"%s|%s|%s\n", input_user, input_pass , input_plat);
                printf("\nData successfully edited!\n");
                printf("========================== \n");
            }else{
                printf("\nThe Plat should not contain any special characters!\n");
                goto edit_data;
            }
        }else{
            fprintf(write,"%s|%s|%s\n", input_user, input_pass , input_plat);
        }
    }
    if(update == false){
        printf("\nWrong password.....\n");
    }
    fclose(read); fclose(write);
    remove("db_car.txt"); rename("db_car_temp.txt","db_car.txt");
    getch();
}
