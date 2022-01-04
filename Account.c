#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>

int db_person=0;
char pil;
char acc[99];
char username['0'][99], password['0'][99], plat['0'][99];
char input_plat[99], input_user[99], input_pass[99];

bool user_allow = false;
bool user_exist = false;
bool pass_exist = false;
bool exist=false;
bool inputted=true;
int compare_user, compare_plat, compare_pass;
int i ,j ,k ,count;
FILE*in_data;


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}



int main(){
        in_data = fopen("db_car.txt", "r");
    if (NULL != in_data){
        fseek (in_data, 0, SEEK_END);
        count = ftell(in_data);
        exist = true;
        }fclose(in_data);
    if (exist == false){
        in_data = fopen("db_car.txt", "w");
            fseek (in_data, 0, SEEK_END);
            count = ftell(in_data);
        fclose (in_data);
    }
    in_data = fopen("db_car.txt", "r");
        if (count == 0) {
            inputted = false;
        }else if(count > 0){
            for(i=1; !feof(in_data) ; i++){
                db_person++;
                fscanf(in_data, "%[^#]#%[^#]#%[^\n]\n", &username[i], &password[i], &plat[i]);
            }
        }
    home :
    exist=false;
    count = 20-db_person;
    system("cls");
    printf("===Welcome To car parking===");
    printf("\n\nCar slot available: %i\n\n", count);
    printf("Press '1' to Register.\nPress '2' to Login.\n");
    printf("\nInput : ");
    switch(getch()){

    //REGISTER----------------------------------------------------------------------------------------------------------------------------
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
                    printf("\n\nDo you wish to try again?(y/n)");
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
                printf("\nEnter car plat number\t\t: ");
                scanf(" %[^\n]s", input_plat);
                strupr(input_plat);
                    count = strlen(input_plat);
                        for(i=0 ; i<=count ; i++){
                            if( !(input_plat[i]>='A' && input_plat[i]<='Z') && !(input_plat[i]>='0' && input_plat[i]<='9') && !(input_plat[i]=='\0') && !(input_plat[i]==32)){
                                    j++;
                                    break;
                            }
                        }
                    if(j==1){
                        printf("===The plat should not contain any special characters!===");
                        printf("Do you wish to try again?(y/n)");
                            switch(getch()){
                                case 'Y':
                                case 'y':
                                system("cls");
                                    goto reg_plat;
                                break;
                                case 'N':
                                case 'n':
                                db_person--;
                                    goto home;
                                break;
                                default:
                            printf("\n\nPlease enter a valid answer!");
                            system("pause");
                        goto reg;
                    }}
            printf("\nEnter Pass\t\t\t: "); scanf("%s", input_pass);
                strcpy (username[db_person],input_user);
                strcpy (plat[db_person],input_plat);
                strcpy (password[db_person],input_pass);
            in_data= fopen("db_car.txt", "a");
                fprintf(in_data, "%s#%s#%s\n", username[db_person],password[db_person], plat[db_person]);
            fclose(in_data);
            printf("\n========================== \n");
            printf("Data has been succesfully registered!\n");
            printf("Now Login with User and Password\n");
            printf("\nPress any key to continue..."); 
            getch();
            goto home;
        break;

    //LOGIN----------------------------------------------------------------------------------------------------------------------------
        case'2':
            login:
            user_exist = false;
            pass_exist=false;
            for(i=1; !feof(in_data) ; i++){
                fscanf(in_data, "%[^#]#%[^#]#%[^\n]\n", &username[i], &password[i], &plat[i]);
            }
            system("cls");
            printf("=========================== ");
            printf("\n\t== Login == ");
            printf("\n=========================== \n");
            printf("\nUsername\t: "); scanf("%s", input_user);
            printf("\nPassword\t: "); scanf("%s", input_pass);

            system("cls");
            printf("Fetching data"); delay(1); printf("."); delay(1); printf("."); delay(1); printf(".\n\n");
                for (i=1 ; i<=db_person ; i++){
                    if(strcmp(input_user,username[i])==0){
                        user_exist=true;
                        break;
                    }
                }
                for (j=1 ; j<=db_person ; j++){
                    if(strcmp(input_user,password[j])==0){
                        pass_exist=true;
                        break;
                    }
                }
            if(pass_exist==true && user_exist==true){
                if(i==j){
                    printf("Welcome %s", username);
                }
                else if(i!=j){
                    printf("Sorry, wrong username or password!\n\n");
                    system("pause");
                    goto home;
                }
            }
            else if(pass_exist==false && user_exist==true){
                printf("Sorry %s, Wrong password\n\n", username[i]);
                system("pause");
                goto home;
            }
            else{
                printf("Sorry, wrong username or password!");
                printf("\n\nPress any key to continue...");
                getch();
                goto home;
            }
            printf("\n========================== \n");
        break;
        case'6':
            return 0;
        break;
        default :
            printf("\n=== Please Input a valid answer!!! ===\n");
            system("pause");
            goto home;

    }
}