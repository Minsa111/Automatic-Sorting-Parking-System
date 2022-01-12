#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>

int slot_count=0;
int word_count=0;
int db_person=0;
int acc[30];
char input[99];
char slot['0'][99];
char username['0'][99], password['0'][99], plat['0'][99];
char temp_username[99], temp_password[99], temp_plat[99];
char input_plat[99], input_user[99], input_pass[99];
char temp_input_plat[99], temp_input_user[99], temp_input_pass[99];
int curr_car;
char admin[99], admin_pass[99];
bool logged=false;
bool char_only=false;
bool slot_empty = true;
bool correct=false;
bool user_allow = false;
bool user_exist = false;
bool pass_exist = false;
bool exist=false;
bool inputted=true;
bool input_space=false;
bool logging=false;
bool user_is_admin=false;
bool car_exist=false;
bool user_found=false;
bool plat_found= false;
int compare_user, compare_plat, compare_pass;
int i ,j ,k ,count;
FILE *in_data, *read, *admin_data;
void logged_user(); void logged_admin(); void delay();


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
    fclose(read);
    home :
    system("cls");
    slot_count=0;

    admin_data = fopen("admin.txt" , "r");
        fscanf(admin_data, "%[^#]#%[^\n]\n", admin, admin_pass);
    fclose(admin_data);
//acc data
    in_data = fopen("db_acc.txt", "r");
        if (NULL != in_data){
            fseek (in_data, 0, SEEK_END);
            count = ftell(in_data);
            exist = true;
        }fclose(in_data);

    if (exist == false){
        in_data = fopen("db_acc.txt", "w");
            fseek (in_data, 0, SEEK_END);
            count = ftell(in_data);
        fclose (in_data);
        }

    in_data = fopen("db_acc.txt", "r");
        if (count == 0) {
            inputted = false;
        }else if(count > 0){
            for(i=1; !feof(in_data) ; i++){
                db_person++;
                fscanf(in_data, "%[^#]#%[^#]#%[^\n]\n", username[i], password[i], plat[i]);
            }
        }fclose(in_data);
        
    // car data
    exist=false;

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
    read = fopen("db_car.txt", "r");
    if(count==0){
        inputted=false;
    }else if(count>0){
        for(i=1 ; !feof(read) ; i++){
            slot_count++;
            fscanf(read, "%[^\n]\n", slot[i]);
        }
    }
        fclose(read);

    logging=false;
    exist=false;
    printf("===Welcome To car parking===");

    count = 20-slot_count;

        if(count<1){
            printf("\n\nNo parking slot available\n\n");
        }else{
            printf("\n\nCar slot available: %i\n\n", count);
        }
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
                printf("\nEnter Username\t\t\t: "); fflush(stdin); scanf("%[^\n]", input_user);
                    word_count = strlen(input_user);
                        for(i=0 ; i<=word_count ; i++){
                            if( !(input_user[i]>='A' && input_user[i]<='Z') && !(input_user[i]>='a' && input_user[i]<='z') && !(input_user[i]>='0' && input_user[i]<='9') && !(input_user[i]=='\0') && (input_user[i]==' ')){
                                input_space=true;
                                break;
                            }
                        }
  
            if (input_space==true){
                printf("Sorry, the username should not have a space.\nUse underscore( _ ) instead.");
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
                        default:
                        printf("Please enter a valid answer\n");
                        system("pause");
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
            in_data= fopen("db_acc.txt", "a");
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
            in_data= fopen("db_acc.txt", "r");
            for(i=1; !feof(in_data) ; i++){
                fscanf(in_data, "%[^#]#%[^#]#%[^\n]\n", username[i], password[i], plat[i]);
            }fclose(in_data);
            system("cls");
            printf("=========================== ");
            printf("\n\t== Login == ");
            printf("\n=========================== \n");
            printf("\nUsername\t: "); scanf("%s", &input_user);
            printf("\nPassword\t: "); scanf(" %[^\n]", input_pass);

                for (i=1 ; i<=db_person ; i++){
                    if(strcmp(input_user,username[i])==0){
                        user_exist=true;
                        if(strcmp(input_pass, password[i])==0){
                            pass_exist=true;
                            break;
                        }
                    }

                }
                if(strcmp(admin,input_user)==0 && strcmp(input_pass,admin_pass)==0){
                    user_is_admin=true;
                }
            system("cls");
            //printf("Fetching data"); delay(1); printf("."); delay(1); printf("."); delay(1); printf(".\n\n");

                    if (user_is_admin==false){
                        if(pass_exist==true && user_exist==true){
                            logging=true;
                            logged_user();goto home;
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
                        printf("Something went wrong XP\n\n");
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
    if(logging==true){
        strcpy(temp_username,username[i]);
        strcpy(temp_password,password[i]);
        strcpy(temp_plat,plat[i]);
        panel:
        system("cls");
        correct=false;
            printf("Welcome %s!", temp_username);
            printf("\n\nWhat do you want to do?\n");
            printf("1. Edit data\n2. Insert car\n3. Take car\n4. Check car\n5. Log out\n");
                switch(getch()){
//user case 1=======================================================================================================================
                    case '1':
                    i=1;
                    slot_count=0;
                    exist=false; correct=false; car_exist=false;

                        printf("insert password to change your data: ");
                        scanf("%s", &input_pass);
                        read = fopen("db_acc.txt", "r");
                            while(fscanf(read,"%[^#]#%[^#]#%[^\n]\n", temp_input_user, temp_input_pass, temp_input_plat) != EOF){
                                if(strcmp(temp_username, temp_input_user) == 0 && strcmp(temp_password, temp_input_pass) == 0){
                                    correct=true;
                                    system("cls");
                                    //printf("Loading"); delay(1); printf("."); delay(1); printf("."); delay(1); printf(".\n\n");
                                break;
                                }
                            }fclose(read);
                            if(correct==false){
                                printf("Wrong password :(\n\n");
                                system("pause");
                                goto panel;
                            }else if(correct==true){
                            edit_data:
                                i=1;
                                slot_count=0;
                                exist=false; 
                                correct=false;
                                car_exist=false;  
                                char_only=false;
                                db_person=0;
                                input_space=false;

                                read = fopen ("db_car.txt", "r");
                                fseek (read, 0, SEEK_END);
                                count = ftell(read);
                                fclose(read);
                                if(count>1){
                                read = fopen ("db_car.txt", "r");
                                    for(i=1 ; !feof(read) ; i++){
                                        slot_count++;
                                        fscanf(read, "%[^\n]\n", slot[i]);
                                    }
                                fclose(read);
                                }
                                for(i=k ; k<=slot_count ; k++){
                                    if(strcmp(temp_username,slot[k])==0){
                                    car_exist=true;
                                        break;
                                    }
                                }
                                read = fopen("db_acc.txt", "r");
                                    for(i=1 ; !feof(read) ; i++){
                                        db_person++;
                                        fscanf(read,"%[^#]#%[^#]#%[^\n]\n", username[i], password[i], plat[i]);
                                    }
                                fclose(read);
                                for(i=1 ; i<=db_person ; i++){
                                    if(strcmp(username[i], temp_username)==0){
                                        exist=true;
                                        break;
                                    }
                                }if (exist==true){
                                    word_count=0;
                                    count=i;
                                    system("cls");
                                    printf("===Your current data===\n\n");
                                    printf("Username\t: %s\n", username[count]);
                                    printf("Password\t: %s\n", password[count]);
                                    printf("Plat\t\t: %s\n", plat[count]);
                            
                                    printf("\n\n===Your New Data===\n\n");
                                    printf("Username\t: "); fflush(stdin); scanf("%[^\n]", input_user);
                                    word_count = strlen(input_user);
                                        for(i=0 ; i<=word_count ; i++){
                                            if( !(input_user[i]>='A' && input_user[i]<='Z') && !(input_user[i]>='a' && input_user[i]<='z') && !(input_user[i]>='0' && input_user[i]<='9') && !(input_user[i]=='\0') && (input_user[i]==' ')){
                                                input_space=true;
                                                break;
                                            }
                                        }
                                    if (input_space==true){
                                        printf("%i", i);
                                        printf("%s", input_user);
                                        printf("Sorry, the username should not have a space.\nUse underscore( _ ) instead.\n");
                                        system ("pause");
                                        input_space=false;
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
                                                default :
                                                printf("\n=== Please Input a valid answer!!! ===\n");
                                                system("pause");
                                                goto panel;
                                            }
                                        }
                                    printf("Password\t: "); fflush(stdin); scanf("%[^\n]", input_pass);
                                    printf("Plat\t\t: "); fflush(stdin); scanf("%[^\n]", input_plat);
                                        strupr(input_plat);
                                            word_count = strlen(input_plat);
                                                for(i=0 ; i<=word_count ; i++){
                                                    if( !(input_plat[i]>='A' && input_plat[i]<='Z') && !(input_plat[i]>='a' && input_plat[i]<='z') && !(input_plat[i]>='0' && input_plat[i]<='9') && !(input_plat[i]=='\0') && !(input_plat[i]==' ')){
                                                            char_only=true;
                                                            break;
                                                    }
                                                }
                                            if(char_only==true){
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
                                    strcpy(temp_username, input_user);
                                    strcpy(temp_password, input_pass);
                                    strcpy(temp_plat, input_plat);
                                    if(car_exist==true){
                                        strcpy(slot[k], input_user);
                                    }
                                    if(strcmp(username[count], input_user)==0 && strcmp(password[count], input_pass)==0 && strcmp(plat[count], input_plat)==0){
                                    in_data = fopen("db_acc.txt", "w");
                                        for(i=1 ; i<=db_person ; i++){
                                                fprintf(in_data, "%s#%s#%s\n", username[i],password[i], plat[i]);
                                        }
                                    fclose(in_data);
                                        if(strcmp(slot[k], input_user)){
                                        in_data = fopen("db_car.txt", "w");
                                            for(i=1 ; i<=slot_count ; i++){
                                                fprintf(in_data, "%s\n", slot[i]);
                                            }
                                        fclose(in_data);
                                        }
                                    }
                                        printf("Data succesfully edited");
                                        system("pause");
                                        goto panel;
                                }else if(exist==false){
                                    printf("Data is not found :(\n\n");
                                    system("pause");
                                    goto panel;
                                }
                            }
                    break;
//end of user case 1======================================================================================================================================
// case 2=================================================================================================================================================
                    case '2':
                    slot_count=0;
                    read = fopen("db_car.txt", "r");
                    fseek (read, 0, SEEK_END);
                    count = ftell(read);
                    fclose(read);
                        if(count>0){
                        read = fopen("db_car.txt", "r");                    
                            for(i=1 ; !feof(read) ; i++){
                                slot_count++;
                                fscanf(read, "%[^\n]\n", slot[i]);
                            }
                        fclose(read);
                        }else{
                            inputted=false;
                        }

                    slot_empty=true;
                    if(slot_count<=20 && slot_count >= 0){
                        for (i=1 ; i<=slot_count ; i++){
                            if (strcmp(slot[i], temp_username)==0){
                                slot_empty=false;
                                break;
                            }
                        }
                    }else{
                        printf("Sorry no more slot available\n");
                        system("pause");
                        goto panel;
                    }
                    system("cls");
                    //printf("Inserting car "); delay(1); printf(". "); delay(1); printf(". "); delay(1); printf(". ");
                    if(slot_empty==false){
                        printf("You already inputted your car at slot '%i'!\n", i);
                        system ("pause");
                        goto panel;
                    }else if(slot_empty==true){
                        system("cls");
                        slot_count++;
                        strcpy(slot[slot_count], temp_username);
                        in_data = fopen("db_car.txt", "w");
                            for(i=1; i<=slot_count ; i++){
                                fprintf(in_data, "%s\n", slot[i]);
                            }
                        printf("car inputted at slot '%i'.", slot_count);
                        fclose(in_data);
                        system("pause");
                        goto panel;
                    }else{
                        printf("\nSomething went wrong :(\n\n");
                        slot_count--;
                        system("pause");
                        goto panel;
                    }
                    slot_empty=true;
                    break;
//case 3|| TAKE CAR ============================================================================================================================================================
                    case '3':
                    slot_empty=true;
                    slot_count=0;
                        read = fopen("db_car.txt", "r");
                            for(i=1 ; !feof(read) ; i++){
                                slot_count++;
                                fscanf(read, "%[^\n]\n", slot[i]);
                            }
                        fclose(read);
                    for(i=1 ; i<=slot_count ; i++){
                        if(strcmp(temp_username, slot[i])==0){
                            slot_empty=false;
                            break;
                        }
                    }
                    //printf("Taking car out "); delay(1); printf(". "); delay(1); printf(". "); delay(1); printf(". ");
                    system("cls");
                    if(slot_empty==false){
                            for(j=i ; j<=slot_count; j++){
                                strcpy(slot[j],slot[j+1]);
                            }
                            slot_count--;
                            in_data = fopen("db_car.txt", "w");
                                for(i=1; i<=slot_count ; i++){
                                    fprintf(in_data, "%s\n", slot[i]);
                                }
                            fclose(in_data);
                                printf("\n\nTake car success!\n\n");
                                system("pause");
                                goto panel;
                    }else if(slot_empty==true){
                        printf("You haven't inserted a car yet\n\n");
                        system("pause");
                        goto panel;
                    }else{
                        printf("Something went wrong");
                        goto panel;
                    }
                    break;
//CASE 4 CHECK CAR================================================================================================================================================================================================
                    case '4':
                slot_empty=true;
                slot_count=0;
            read = fopen("db_acc.txt", "r");
                for(i=1; !feof(read) ; i++){
                    db_person++;
                fscanf(read, "%[^#]#%[^#]#%[^\n]\n", username[i], password[i], plat[i]);
            }fclose(read);
                    read = fopen("db_car.txt", "r");
                        for(i=1 ; !feof(read) ; i++){
                            slot_count++;
                            fscanf(read, "%[^\n]\n", slot[i]);
                        }
                    fclose(read);
                    for(i=1 ; i<=slot_count ; i++){
                        if(strcmp(temp_username, slot[i])==0){
                            slot_empty=false;
                            break;
                        }
                    }
                    for(i=1 ; i<=db_person ; i++){
                        if(strcmp(temp_username, username[i])==0){
                            break;
                        }
                    }
                        printf("\t===Your data===\n\n");
                        printf("Username\t: %s\n", username[i]);
                        printf("Plat\t\t: %s\n", plat[i]);
                        if(slot_empty==true){
                            printf("Car status\t: Not inserted\n\n");
                            system("pause");
                            goto panel;
                        }else if(slot_empty==false){
                            printf("Car status\t: Inserted\n\n");
                            system("pause");
                            goto panel;
                        }else{
                            printf("err,  something went wrong\n");
                            system("pause");
                            goto panel;
                        }
                    break;
//case 5 LOG OUT==========================================================================================================================================================
                    case '5':
                        //printf("Logging out"); delay(1); printf(" ."); delay(1); printf(" ."); delay(1); printf(" .");
                    break;
                    default:
                        printf("Please put a valid answer!!!\n\n");
                        system("pause");
                        goto panel;
                    break;
                }
    }else if (logging==false){
        printf("err, error...\n\n");
        system("pause");
    }else{
        printf("err, error...\n\n");
        system("pause");
    }
}
//ADMIN LOGIN==========================================================================================================================
    void logged_admin(){
        panel_admin:
        car_exist=false;
        system("cls");
        printf("Welcome handsome :D\n\n");
        printf("What do you want to do?\n");
        printf("1. Edit data\n2. Check data");
        switch(getch()){
            case '1':
            edit_admin:
            exist=false;
            db_person=0; slot_count=0;
            
            system("cls");
        read = fopen("db_acc.txt", "r");
            fseek (read, 0, SEEK_END);
            count = ftell(read);
        fclose(read);
        if(count>0){
        read = fopen("db_acc.txt", "r");
            for(i=1; !feof(read) ; i++){
                db_person++;
                fscanf(read, "%[^#]#%[^#]#%[^\n]\n", username[i], password[i], plat[i]);
            }
        fclose(read);
        }
        read = fopen("db_car.txt", "r");
            for(i=1; !feof(read) ; i++){
                slot_count++;
                fscanf(read, "%[^\n]\n", slot[i]);
            }
        fclose(read);
            k=0;
            printf("Insert username or plat number: "); fflush(stdin); scanf(" %[^\n]", input);
                for(i=1; i<=db_person ; i++){
                    if(strcmp(input,username[i])==0){
                        exist=true;
                        break;
                    }else if(strcmp(input,plat[i])==0){
                        k++;
                        acc[k]=i;
                        plat_found=true;
                    }
                }
                if(exist==true){
                    edit_admins:
                    j=0;
                    count=i;
                    input_space=false; exist=false;
                    plat_found=false;

                    system("cls");
                        printf("===Data found===\n\n");
                        printf("Username\t: %s\n", username[count]);
                        printf("Password\t: %s\n", password[count]);
                        printf("Plat\t\t: %s\n", plat[count]);
                        
                        printf("\n\n===Edit Data===\n\n");
                            printf("Username\t: "); fflush(stdin); scanf(" %[^\n]", input_user);
                                word_count = strlen(input_user);
                                    for(i=0 ; i<=word_count ; i++){
                                        if( !(input_user[i]>='A' && input_user[i]<='Z') && !(input_user[i]>='a' && input_user[i]<='z') && !(input_user[i]>='0' && input_user[i]<='9') && !(input_user[i]=='\0') && (input_user[i]==' ')){
                                            input_space=true;
                                            break;
                                        }
                                    }
                            if (input_space==true){
                                printf("Sorry, the username should not have a space.\nUse underscore( _ ) instead.");
                                system ("pause");
                                goto edit_admins;
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
                                            goto edit_admin;
                                        break;
                                        case'n':
                                        case'N':
                                            goto panel_admin;
                                        break;
                                    }
                                }
                            printf("Password\t: "); fflush(stdin); scanf(" %[^\n]", input_pass);
                            printf("Plat\t\t: "); fflush(stdin); scanf(" %[^\n]", input_plat);
                                strupr(input_plat);
                                    word_count = strlen(input_plat);
                                        for(i=0 ; i<=word_count ; i++){
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
                                                    goto edit_admin;
                                                break;
                                                case 'N':
                                                case 'n':
                                                    goto panel_admin;
                                                break;
                                                default:
                                            printf("\n\nPlease enter a valid answer!");
                                            system("pause");
                                        goto edit_admin;
                                        }
                                    }
                        for ( i = 1; i <=slot_count; i++){
                            if(strcmp(slot[i], username[count])==0){
                                strcpy(slot[i], input_user);
                                in_data = fopen ("db_car.txt", "w");
                                    for (i=1 ; i<=slot_count ; i++){
                                        fprintf(in_data, "%s\n", slot[i]);                                
                                    }
                                fclose(in_data);
                                break;
                            }
                        }
                        strcpy(username[count], input_user);
                        strcpy(password[count], input_pass);
                        strcpy(plat[count], input_plat);

                        
                    in_data = fopen("db_acc.txt", "w");
                        for(i=1; i<=db_person ; i++){
                            fprintf(in_data, "%s#%s#%s\n", username[i], password[i], plat[i]);
                        }
                    fclose(in_data);
                    printf("Data succesfully changed\n\n");
                    system("pause");
                    goto panel_admin;

//plat edit============================================================================================================================================================
                }else if(plat_found==true){
                    edit_plat_admin:
                    j=0;
                    user_found=false;
                    system("cls");
                    for(i=1 ; i<=k ; i++){
                        printf("===Data found===");
                        printf("\n\n Data ==%i==\n",i);
                        printf("Username\t: %s\n", username[acc[i]]);
                        printf("Password\t: %s\n", password[acc[i]]);
                        printf("Plat\t\t: %s\n", plat[acc[i]]);
                    }
                    printf("input the username that u wanted to edit: ");
                    scanf("%s", &input_user);
                    for(i=1; i<=k ; i++){
                        if(strcmp(input_user, username[acc[i]])==0){
                            user_found=true;
                            break;
                        }
                    }
                    if (user_found==true){
                        car_exist=false;
                        system("cls");
                        printf("===Current Data===\n\n");
                        printf("Username\t: %s\n", username[acc[i]]);
                        printf("Password\t: %s\n", password[acc[i]]);
                        printf("Plat\t\t: %s\n", plat[acc[i]]);
                        printf("edit\n\n");
                        printf ("New Username\t: "); scanf("%s", &input_user);
                        printf ("New Password\t: "); scanf( " %[^\n]", input_pass);
                        printf ("New Plat\t\t: "); scanf(" %[^\n]", input_plat); strupr(input_plat);
                        strcpy(temp_input_user, username[acc[i]]);
                        strcpy(username[acc[i]], input_user);
                        strcpy(password[acc[i]], input_pass);
                        strcpy(plat[acc[i]], input_plat);

                        for(j=1 ; j<=slot_count ; j++){
                            if(strcmp(slot[j], temp_input_user)==0){
                                car_exist=true;
                                strcpy(slot[j], username[acc[i]]);
                                break;
                            }
                        }
                        if(car_exist==true){
                            in_data = fopen("db_car.txt", "w");
                            i=1;
                                do{
                                    fprintf(in_data, "%s\n", slot[i]);
                                    i++;
                                }while (i<=slot_count);
                            fclose(in_data);
                        }
                        in_data = fopen("db_acc.txt", "w");
                            for(i=1 ; i<=db_person ; i++){
                                fprintf(in_data, "%s#%s#%s\n", username[i],password[i], plat[i]);
                            }
                        fclose(in_data);
                        printf("Data succesfully changed");
                        system("pause");
                        goto panel_admin;
                    }else if(user_found==false){
                        printf("Please enter a valid answer\n\n");
                        system("pause");
                        goto edit_plat_admin;
                    }
                    
                }else{
                    printf("No data found");
                    system("pause");
                    goto panel_admin;
                }
            break;
//Case 2=========================================================================================================================
            case'2':
            inputted=true;
            db_person=0;
            slot_count=0;
            system("cls");

        in_data = fopen("db_acc.txt", "r");
            if (NULL != in_data){
                fseek (in_data, 0, SEEK_END);
                count = ftell(in_data);
                exist = true;
        }fclose(in_data);

        in_data = fopen("db_acc.txt", "r");
        if (count == 0) {
            inputted = false;
        }else if(count > 0){
            for(i=1; !feof(in_data) ; i++){
                db_person++;
                fscanf(in_data, "%[^#]#%[^#]#%[^\n]\n", username[i], password[i], plat[i]);
            }
        }fclose(in_data);

in_data = fopen("db_car.txt", "r");
            if (NULL != in_data){
                fseek (in_data, 0, SEEK_END);
                count = ftell(in_data);
                exist = true;
        }fclose(in_data);

        in_data = fopen("db_car.txt", "r");
        if(count > 0){
            for(i=1; !feof(in_data) ; i++){
                slot_count++;
                fscanf(in_data, "%[^\n]\n", slot[i]);
            }
        }
            printf("Check data\n\n");
            for ( i = 1 ; i<=db_person ; i++){
                inputted=false;   
                printf("\n\n    Data =%i=\n", i);
                printf("Username\t: %s\n", username[i]);
                printf("Password\t: %s\n", password[i]);
                printf("Plat\t\t: %s\n", plat[i]);
                printf("Status\t\t: ");
                for (j=1 ; j<=slot_count ; j++){
                    if(strcmp(slot[j], username[i])==0){
                        printf("Inserted");
                        inputted=true;
                        break;
                    }
                }
                if(inputted==false){
                    printf("Not inserted");
                }
            }
            printf("\n\n");
            system("pause");
            goto panel_admin;
            break;

            case '3':

            break;
            default:
            system("cls");
                printf("Please enter a valid answer\n\n");
                system("pause");
                goto panel_admin;
            break;
        }
    }