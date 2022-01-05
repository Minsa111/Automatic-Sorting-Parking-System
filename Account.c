#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>

int db_person=0;
char input[99];
char pil;
char acc[99];
char username['0'][99], password['0'][99], plat['0'][99];
char temp_username[99], temp_password[99], temp_plat[99];
char input_plat[99], input_user[99], input_pass[99];
char temp_input_plat[99], temp_input_user[99], temp_input_pass[99];
int curr_car;
char admin[99], admin_pass[99];
bool correct=false;
bool user_allow = false;
bool user_exist = false;
bool pass_exist = false;
bool exist=false;
bool inputted=true;
bool input_space=false;
bool logged=false;
bool user_is_admin=false;
int compare_user, compare_plat, compare_pass;
int i ,j ,k ,count;
FILE *in_data, *read, *admin_data;
void logged_user(); void logged_admin();


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
    admin_data = fopen("admin.txt" , "r");
        fscanf(admin_data, "%[^#]#%[^\n]\n", admin, admin_pass);
    fclose(admin_data);
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
        }fclose(in_data);
    home :
    exist=false;
    count = 20-db_person;
    system("cls");
    printf("===Welcome To car parking===");
    printf("\n\nCar slot available: %i\n\n", count);
    printf("Press '1' to Register.\nPress '2' to Login.\nPress '3' to Exit.");
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
            input_space=false;
            exist = false;
            j=0;
            db_person++;
                printf("============================ ");
                printf("\n\t== Register == ");
                printf("\n============================ \n");
                printf("\nEnter Username\t\t\t: "); scanf("%s", input_user);

            for(i=0 ; i<=count ; i++){
                if((input_user[i]==32)){
                    input_space=true;
                    break;
                }
            }
            if (input_space==true){
                printf("Sorry, the username should not have a space.\n Use underscore( _ ) instead.");
                system ("pause");
                db_person--;
                goto home;
            }

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
                exist = false;
                j=0;
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
            printf("\nEnter Pass\t\t\t: "); 
            scanf(" %[^\n]s", input_pass);
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
            user_is_admin=false;
            user_exist = false;
            pass_exist=false;
            in_data= fopen("db_car.txt", "r");
            for(i=1; !feof(in_data) ; i++){
                fscanf(in_data, "%[^#]#%[^#]#%[^\n]\n", &username[i], &password[i], &plat[i]);
            }fclose(in_data);
            system("cls");
            printf("=========================== ");
            printf("\n\t== Login == ");
            printf("\n=========================== \n");
            printf("\nUsername\t: "); scanf("%s", input_user);
            printf("\nPassword\t: "); scanf(" %[^\n]", input_pass);

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
                if(strcmp(admin,input_user)==0 && strcmp(input_pass,admin_pass)==0){
                    user_is_admin=true;
                }
            system("cls");
            printf("Fetching data"); delay(1); printf("."); delay(1); printf("."); delay(1); printf(".\n\n");

                    if (user_is_admin==false){
                        if(pass_exist==true && user_exist==true){
                            if(i==j){
                                logged=true;
                                logged_user();goto home;
                            }
                            else if(i!=j){
                                printf("Sorry, wrong username or password!\n\n");
                                system("pause");
                                goto home;
                            }
                        }else if(pass_exist==false && user_exist==true){
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
                    }else if(user_is_admin==true){
                        logged_admin();goto home;
                    }else {
                        printf("Something wenr wrong XP\n\n");
                        system("pause");
                        goto home;
                    }
            printf("\n========================== \n");
        break;
        case'3':
            return 0;
        break;
        default :
            printf("\n=== Please Input a valid answer!!! ===\n");
            system("pause");
            goto home;
    }
}

//FUCNTION-------------------------------------------------------------------------------------------------------------------------
    //USER===============================================================================================================================
    void logged_user(){
    if(logged==true){
        panel:
        correct=false;
        strcpy(temp_username,username[j]);
        strcpy(temp_password,password[j]);
        strcpy(temp_plat,plat[j]);
            printf("Welcome %s!", temp_username);
            printf("\n\nWhat do you want to do?\n");
            printf("1. Edit data\n2. Insert car");
                switch(getch()){
//user case 1=======================================================================================================================
                    case '1':
                    i=1;
                    exist=false; correct=false;
                        printf("insert password to change your data: ");
                        scanf("%s", input_pass);
                        read = fopen("db_car.txt", "r");
                            while(fscanf(read,"%[^#]|%[^#]|%[^\n]\n", temp_input_user, temp_input_pass, temp_input_plat) != EOF){
                                if(strcmp(temp_username, temp_input_user) == 0 && strcmp(temp_password, input_pass) == 0){
                                    correct=true;
                                    system("cls");
                                    printf("Loading"); delay(1); printf("."); delay(1); printf("."); delay(1); printf(".\n\n");
                                break;
                                }
                            i++;
                            }fclose(read);
                            if(correct==false){
                                printf("Wrong password :(\n\n");
                                system("pause");
                                goto panel;
                            }else if(correct==true){
                                db_person=0;
                                read = fopen("db_car.txt", "r");
                                    for(i=1 ; !feof(read) ; i++){
                                        db_person++;
                                        fscanf(read,"%[^#]|%[^#]|%[^\n]\n", username[i], password[i], plat[i]);
                                    }
                                fclose(read);
                                for(i=1 ; i<=db_person ; i++){
                                    if(strcmp(username[i], temp_username)==0){
                                        exist=true;
                                        break;
                                    }
                                }if (exist==true){
                                    edit_data:
                                    count=i;
                                    input_space=false;
                                    system("cls");
                                    printf("===Your current data===\n\n");
                                    printf("Username\t: %s\n", username[count]);
                                    printf("Password\t: %s\n", password[count]);
                                    printf("Plat\t\t: %s\n", plat[count]);
                            
                                    printf("\n\n===Your New Data===\n\n");
                                    printf("Username\t: "); scanf(" %[^\n]", input_user);
                                    for(i=0 ; i<=count ; i++){
                                        if((input_plat[i]==32)){
                                            input_space=true;
                                            break;
                                        }
                                    }
                                    if (input_space==true){
                                        printf("Sorry, the username should not have a space.\n Use underscore( _ ) instead.");
                                        system ("pause");
                                        goto edit_data;
                                    }
                                    exist=false;
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
                                                    goto edit_data;
                                                break;
                                                case'n':
                                                case'N':
                                                    goto panel;
                                                break;
                                            }
                                        }
                                    printf("Password\t: ");scanf(" %[^\n]", input_pass);
                                    printf("Plat\t\t: ");scanf(" %[^\n]", input_plat);
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
                                                            goto edit_data;
                                                        break;
                                                        case 'N':
                                                        case 'n':
                                                            goto panel;
                                                        break;
                                                        default:
                                                    printf("\n\nPlease enter a valid answer!");
                                                    system("pause");
                                                goto edit_data;
                                                }
                                            }
                                strcpy(username[count], input_user);
                                strcpy(password[count], input_pass);
                                strcpy(plat[count], input_plat);
                                    if(strcmp(username[count], input_user)==0 && strcmp(password[count], input_pass)==0 && strcmp(plat[count], input_plat)==0){
                                        for(i=1 ; i<=db_person ; i++){
                                            in_data = fopen("db_car.txt", "w");
                                                fprintf(in_data, "%s#%s#%s\n", username[i],password[i], plat[i]);
                                            fclose(in_data);
                                            printf("Data succesfully edited");
                                        }
                                    }   
                                }else if(exist==false){
                                    printf("Data is not found:(\n\n");
                                    system("pause");
                                    goto panel;
                                }
                            }
                    break;
//end of user case 1======================================================================================================================================
                }
    }else if (logged==false){
        printf("err, error...\n\n");
        system("pause");
    }else{
        printf("err, error...\n\n");
        system("pause");
    }
}
//ADMIN LOGIN==========================================================================================================================
    void logged_admin(){
        panel:
        system("cls");
        printf("Welcome handsome :D\n\n");
        printf("What do you want to do?\n");
        printf("1. Edit data\n2. Check data");
        switch(getch()){
            case '1':
            exist=false;
                db_person==0;
                system("cls");
            read = fopen("db_car.txt", "r");
            for(i=1; !feof(read) ; i++){
                db_person++;
                fscanf(read, "%[^#]#%[^#]#%[^\n]\n", &username[i], &password[i], &plat[i]);
            }
            fclose(read);
            printf("Insert username or plat number: "); scanf(" %[^\n]", input);
                for(i=1; i<=db_person ; i++){
                    if(strcmp(input,username[i])==0 || strcmp(input,plat[i])==0){
                        exist=true;
                        break;
                    }
                }if(exist==true)
                    count=i;
                    edit_data:
                    system("cls");
                        printf("===Data found===\n\n");
                        printf("Username\t: %s\n", username[count]);
                        printf("Password\t: %s\n", password[count]);
                        printf("Plat\t\t: %s\n", plat[count]);
                        
                        printf("\n\n===Edit Data===\n\n");
                            printf("Username\t: "); scanf(" %[^\n]", input_user);
                            for(i=0 ; i<=count ; i++){
                                if((input_plat[i]==32)){
                                    input_space=true;
                                    break;
                                }
                            }
                            if (input_space==true){
                                printf("Sorry, the username should not have a space.\n Use underscore( _ ) instead.");
                                system ("pause");
                                goto edit_data;
                            }
                            exist=false;
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
                                            goto edit_data;
                                        break;
                                        case'n':
                                        case'N':
                                            goto panel;
                                        break;
                                    }
                                }
                            printf("Password\t: ");scanf(" %[^\n]", input_pass);
                            printf("Plat\t\t: ");scanf(" %[^\n]", input_plat);
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
                                                    goto edit_data;
                                                break;
                                                case 'N':
                                                case 'n':
                                                    goto panel;
                                                break;
                                                default:
                                            printf("\n\nPlease enter a valid answer!");
                                            system("pause");
                                        goto edit_data;
                                        }
                                    }
            break;
        }
    }