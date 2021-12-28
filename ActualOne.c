#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

#define SIZE 255

void Generate_password(char *PTR);
void Make_lower(char *Search1);
void appendSecureNotes();
void checkSecureNotes();
void SecureNotes();
void viewSecureNotes();
void interface();
void separators();
void signUpScreen();
int checkVaultStatus();

int resetPassword();
int forgotPassword();
int question();
int signup();
int checkAttempts();

char Identification(char Master_Password[SIZE]);
char inVault();
char save();
char view();
char AlreadyExistsUser();

int status = 0;
char UserName[SIZE];
int CountingCharacter=0;
int AppendSecureNotesFile=0;
int main()
{

    int choice, test, check = 0, ch, n = 0, i = 0, password_choice = 0, q = 0, Dots = 0, passChoice = 0, select = 0, k, userAttempts;
    char Master_Password[SIZE];
    char questionn[SIZE];
    int temp = 0;

    status = 0;
    userAttempts = 0;

    system("cls");
    interface();
    printf("\n\nEnter your choice:  ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls"); //for clearing the output screen
        separators();
        printf("\n\n\tYou can login to your vault here\n\n");
        separators();
        printf("\n\nEnter the Username: ");
        scanf("%s", &UserName);

        // here, we have to check if the user's vault is disabled or not
        temp = checkVaultStatus();

        if (temp == 10)
        {
            system("cls"); //for clearing the output screen
            separators();
            printf("\n\n\tYou can login to your vault here\n\n");
            separators();
            printf("\n\nEnter the Username: ");
            scanf("%s", &UserName);
        }

        // masking password logic here too
        do
        {
            printf("Press 1 if you want to Hide the password\nPress 2 if you want to display the password\n");
            scanf("%d", &password_choice);
            if (password_choice != 1 && password_choice != 2)
            {
                printf("\nError, invalid choice.");
            }

        } while (password_choice != 1 && password_choice != 2);

        if (password_choice == 1)
        {
            // for Master Password
            i = 0;
            printf("Please Enter your Master Password: ");
            while ((ch = getch()) != 13)
            {
                if (ch == 8)
                {
                    i--;
                    putch('\b');
                    printf(" ");
                    putch('\b');
                }
                if (ch != 8)
                {
                    Master_Password[i] = ch;
                    putch('*');
                    i++;
                }
            }
            Master_Password[i] = '\0';

            // to show the password
            printf("\n\nDo you want to show the Master password now: 1 for yes/2 for no? ");
            printf("Your reply: ");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("\n%s", Master_Password);
            }
        }

        if (password_choice == 2)
        {
            printf("\nEnter the new Password: ");
            scanf("%s", &Master_Password);
        }
        printf("\n\nLogging you In.");
        while (Dots != 4)
        {
            Sleep(1000);
            Dots += 1;
            printf(".");
        }

        Identification(Master_Password);

        if (status == 0)
            inVault();

        else if (status == 1)
        {
            do
            {
                printf("\nWrong Password");

                printf("\nEnter 1 to go back to main menu OR enter 2 to reset password OR press 3 to enter password again:\t");
                scanf("%d", &passChoice);

                if (passChoice == 2)
                {
                    forgotPassword();
                }

                else if (passChoice == 1)
                {
                    main();
                }

                else if (passChoice == 3)
                {
                    do
                    {
                        printf("\nWrong Password");
                        printf("\nEnter the Password again: ");
                        scanf("%s", &Master_Password);

                        Identification(Master_Password);

                        if (status == 0)
                        {
                            inVault();
                            exit(0);
                        }

                        printf("\nWrong Password");
                        userAttempts++;
                        checkAttempts(userAttempts);

                        printf("\nEnter 1 to go back to main menu OR enter 2 to reset password OR press 3 to enter password again:\t");
                        scanf("%d", &passChoice);

                        if (passChoice == 2)
                        {
                            forgotPassword();
                        }

                        else if (passChoice == 1)
                        {
                            main();
                        }

                    } while (status == 1 && passChoice == 3);
                }

                else
                {
                    printf("\nInvalid Choice. Try again.");
                }

            } while (passChoice != 1 && passChoice != 2);

            printf("\nPassword reset successful, you may login to your vault now. Re-directing you to the main menu");
            Dots = 0;
            while (Dots != 4)
            {
                Sleep(1000);
                Dots += 1;
                printf(".");
            }
            main();
        }

        if (status == 3)
        {
            printf("\nNo User found. Create a user first.\n\n");
            printf("\n    Enter 0 to try again\n    Enter 1 to return to create user\n    Enter 2 to exit program.");
            scanf("%d", &select);

            while (select != 0 && select != 1 && select != 2)
            {
                printf("\nError! Invalid Choice. Choose Again.");
                printf("\n    Enter 0 to try to login again\n    Enter 1 to create a new user\n    Enter 2 to exit program.");
                scanf("%d", &select);
            }

            switch (select)
            {
            case 0:
                main();
                break;

            case 1:
                signUpScreen();
                break;

            case 2:
                exit(0);
                break;

            default:
                break;
            }

            main();
        }

        break;

    case 2:

        signUpScreen();
        main();
        break;
    }

    return 0;
}

void interface()
{
    printf("_______________________________________________________________");
    printf("\n\n\t\tWelcome to Password Manager\n\n");
    printf("_______________________________________________________________");
    printf("\n\n\t1 for existing user  OR  2 to create new user");
}

void separators()
{
    printf("_______________________________________________________________");
}

int signup(char Master_Password[SIZE], char Question[SIZE], int q)
{
    // variable filename declaration
    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1]; // +1 for '/0' character, only necessary while writing/appending.
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    char chosenQuestion[SIZE];

    FILE *fpointer = fopen(fileName, "a+");

    switch (q)
    {
    case 1:
        strcpy(chosenQuestion, "The question you chose is: What was the name of your first school?");
        break;
    case 2:
        strcpy(chosenQuestion, "The question you chose is: In which city were you born?");
        break;
    case 3:
        strcpy(chosenQuestion, "The question you chose is: What was your childhood nickname?");
        break;
    case 4:
        strcpy(chosenQuestion, "The question you chose is: What was the name of the first college you attended?");
        break;
    }

    // printing into the file
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", UserName);
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", Master_Password);
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", chosenQuestion);
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", Question);
    fprintf(fpointer, "\n");
   // fprintf(fpointer, "_");

    // closing the file
    fclose(fpointer);
}

char Identification(char Master_Password[SIZE])
{

    char Verification[SIZE] = "Access Granted";
    char *p; // pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1];
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    FILE *fpointer = fopen(fileName, "r");
    // In case of no file
    if (fpointer == NULL)
    {
        // printf("\nNo User found. Create a user first.\n\n");
        status = 3; // assigning 3 to 'status' so when the control goes back to main function, The program does not open Vault.
        return '2';
    }

    // loop start
    while (fgets(get_line, sizeof(get_line), fpointer))
    {

        // extracting the new line from get_line variable
        if ((p = strchr(get_line, '\n')) != NULL)
        {
            *p = '\0';
        }

        // In case of existing user

        // comparing the username with the get_line, if the get_line==Username then access granted
        if ((strcmp(get_line, UserName) == 0))
        {

            while (fgets(get_line, sizeof(get_line), fpointer))
            {
                if ((p = strchr(get_line, '\n')) != NULL)
                {
                    *p = '\0';
                }
                if ((strcmp(get_line, Master_Password) == 0))
                {
                    status = 0;
                    return '0';
                }
                else if ((strcmp(get_line, Master_Password) != 0))
                {
                    status = 1;
                    return '0';
                }
            }
        }
    }
    status = 2;

    // closing the file
    fclose(fpointer);
    return '0';
}

char inVault()
{

    int mainChoice, test, newChoice;
    char random_pass;
    char web[SIZE], username[SIZE], pass[SIZE];
    int log_out = 0;
    char anotherTest;
    system("cls");
    separators();

    // In Vault prompts
    printf("\n\n\t\tWelcome to your Vault\n\n");
    separators();
    printf("\nChoose the item you want to Create/View\n");

    do
    {
        printf("\n 1 for Credentials\n 2 for SecureNotes\n -1 to log out of the vault.");
        printf("\n\nEnter your choice:  ");
        scanf("%d", &mainChoice);
    } while (mainChoice != 1 && mainChoice != 2 && mainChoice != -1);
    if (mainChoice == -1)
    {
        printf("\nLogging Out");
        while (log_out < 2)
        {
            Sleep(800);
            printf(".");
            log_out += 1;
        }
        main();
    }
    /*-------If Credentials-------------*/
    if(mainChoice==1)
    {
    system("cls");
    // prompts for credentials
    printf("\n1 to view saved credentials\n2 for saving new credentials");
    printf("\nTo go back: press -1");
    printf("\n\nEnter your choice:  ");
    scanf("%d", &newChoice);
    if (newChoice == -1)
    {
        inVault();
        return 0;
    }

    }
    /*mainChoice=1-----------END---------------*/

    /*-------If SecureNotes-------------*/
    if(mainChoice==2)
    {
    system("cls");
    // prompts for credentials
    printf("\n1 Create SecureNotes\n2 View SecureNotes\n3 Append SecureNotes");
    printf("\nTo go back: press -1");
    printf("\n\nEnter your choice:  ");
    scanf("%d", &newChoice);
    if (newChoice == -1)
    {
        inVault();
        return 0;
    }

    }
    /*mainChoice=2-----------END---------------*/
    switch (mainChoice)
    {

    case 1:
        switch (newChoice)
        {

        case 1:
            printf("Saved logins");
            view();
            printf("\nEnter 0 to go back to main menu:\t");
            scanf("%d", &test);
            if (test == 0)
            {
                inVault();
            }
            break;

        case 2:
            printf("\n\nEnter the Website Name: ");
            scanf("%s", &web);
            printf("\n\nEnter the UserName: ");
            scanf("%s", &username);
            printf("\nDo you want to generate a random password? ");
            printf("\nPress Y for Yes\nPress N for No");
            random_pass=getch();
            if(random_pass=='Y'||random_pass=='y')
                {
                    Generate_password(pass);
                }
            else
            {printf("\n\nEnter the Password: ");
            scanf("%s", &pass);}
            Make_lower(web);
            save(web, username, pass);

            printf("\nEnter 0 to go back to main menu:\t");
            scanf("%d", &test);
            if (test == 0)
            {
                inVault();
            }

            break;
        } // newchoice switch closed

        break; // mainchoice case 1 break

    case 2:

        switch(newChoice)
        {
        case 1:
            checkSecureNotes();
            // checkingSNfunction here
            // then 'if' to enter SecureNotes function

            if(CountingCharacter==0)
                {
                    SecureNotes();
                }
                else {printf("\n\nYou have already created a secure notes\nYou can either Append or View it now.\n");}

            while (anotherTest != '0')
            {

                printf("\nEnter 0 to go back to main menu:\t");
                anotherTest=getche();
                getch();

            }
            inVault();
            break;
        case 2:
            viewSecureNotes();

             while (anotherTest != '0')
            {
                printf("\nEnter 0 to go back to main menu:\t");
                anotherTest=getche();
                getch();

            }
            inVault();
            break;
        case 3:
            appendSecureNotes();
            while (anotherTest != '0')
            {
                printf("\nEnter 0 to go back to main menu:\t");
                anotherTest=getche();
                getch();

            }
            inVault();
            break;
        }    // for secure notes
        break;
    }
}

char save(char website[SIZE], char userName[SIZE], char pass[SIZE])
{
    // variable name file declaration
    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1];           // added 1 for the '/0' character
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension); // here taking UserName and extension strings ( concatenating them ) and then storing into fileName.

    time_t currentTime;
    time(&currentTime);

    FILE *fPtr;
    fPtr = fopen(fileName, "a");

    if (fPtr == NULL)
    {
        printf("\nNo User found. Create a user first.\n\n");
        printf("\n%s", fileName);
        return 'B';
    }

    fprintf(fPtr, "\n");
    fprintf(fPtr, "%s", website);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "The UserName is:\t%s", userName);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "The password is:\t%s", pass);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "Date and time this record was added: %s", ctime(&currentTime));
    fprintf(fPtr, "\n");
    fprintf(fPtr, "%s", website);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "_");
    fclose(fPtr);
    system("cls");
    printf("\nRecord Added");
}

char view(void)
{
    system("cls");
    printf("--------------------------------------");
    printf("\n    CREDENTIALS VIEW MODE        \n");
    printf("--------------------------------------");
    char search[SIZE];
    printf("\n\nEnter the website name you want to search: ");
    scanf("%s",search);
    Make_lower(search);
    char currentLine[SIZE];
    FILE *filePointer;
    int check = 0;
    char *p, *d;

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension)];
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    filePointer = fopen(fileName, "r");

    while (fgets(currentLine, sizeof(currentLine), filePointer))
    {

        if ((p = strchr(currentLine, '\n')) != NULL)
        {
            *p = '\0';
        }

        if ((strcmp(currentLine, search ) == 0))
        {
            check +=1 ;

        }

        if (check == 1)
        {
            printf("\n%s", currentLine);
        }
    }
    check = 0;
    fclose(filePointer);
}

char AlreadyExistsUser()
{

    int Dots = 0;
    char *p; // pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1];
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    FILE *fpointer = fopen(fileName, "r");

    if (fpointer == NULL)
    {
        return 'C';
    }

    // loop start
    while (fgets(get_line, sizeof(get_line), fpointer))
    {

        // extracting the new line from get_line variable
        if ((p = strchr(get_line, '\n')) != NULL)
        {
            *p = '\0';
        }

        if ((strcmp(get_line, UserName) == 0))
        {
            printf("\nError\nUser Already Exists.\nPlease try again to create a new Vault");
            printf("\nRe-directing you to the Main-menu.\n");
            // loading
            while (Dots != 4)
            {
                Sleep(1000);
                Dots += 1;
                printf(".");
            }

            main();
        }
        //In case of existing user
    }
    // closing the file
    fclose(fpointer);
    return '0';
}

int question()
{

    int test;

    printf("\nChoose your security questions to reset your password in case you forget it.");
    printf("\n1) What was the name of your first school?");
    printf("\n2) In which city were you born?");
    printf("\n3) What was your childhood nickname?");
    printf("\n4) What was the name of the first college you attended?");
    printf("\nChoose one of the above:\t");
    scanf("%d", &test);

    return test;
}

int forgotPassword()
{

    FILE *filePointer;
    char getLine[SIZE];
    char *p, answer[SIZE], showQuestion[SIZE];
    int check = 0;

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1];
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    filePointer = fopen(fileName, "r");

    while (fgets(getLine, sizeof(getLine), filePointer))
    {

        if ((p = strchr(getLine, '\n')) != NULL)
        {
            *p = '\0';
            check++;
        }

        if (check == 4)
        {
            printf("\n%s", getLine);
        }

        if (check == 5)
        {
            printf("\nEnter the answer of the question: ");
            scanf("%s", answer);

            if (strcmp(answer, getLine) == 0)
            {
                resetPassword();
                return 0;
            }

            else if (strcmp(answer, getLine) != 0)
            {
                printf("Wrong Answer\nExiting Program");
                exit(0);
            }
        }
    }
    fclose(filePointer);
}

int resetPassword()
{
    FILE *filePointer, *tempFile;
    char currentLine[SIZE];
    char *p, password[SIZE], re_password[SIZE];
    int check = 0, line = 3, password_choice = 0, i = 0, ch, n = 0;

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1];
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    filePointer = fopen(fileName, "r");
    tempFile = fopen("temp.txt", "w");

    do
    {
        do
        {
            printf("Press 1 if you want to Hide the password\nPress 2 if you want to display the password\n");
            scanf("%d", &password_choice);
            if (password_choice != 1 && password_choice != 2)
            {
                printf("\nError, invalid choice.");
            }

        } while (password_choice != 1 && password_choice != 2);

        if (password_choice == 1)
        {
            // for Master Password
            i = 0;
            printf("Please Enter your Master Password: ");
            while ((ch = getch()) != 13)
            {
                if (ch == 8)
                {
                    i--;
                    putch('\b');
                    printf(" ");
                    putch('\b');
                }
                if (ch != 8)
                {
                    password[i] = ch;
                    putch('*');
                    i++;
                }
            }
            password[i] = '\0';

            // to show the password
            printf("\n\nDo you want to show the Master password now: 1 for yes/2 for no? ");
            printf("Your reply: ");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("\n%s", password);
            }

            // for re-enter master_password
            i = 0;
            printf("\nRe-Enter the Master Password: ");
            while ((ch = getch()) != 13)
            {
                if (ch == 8)
                {
                    i--;
                    putch('\b');
                    printf(" ");
                    putch('\b');
                }
                if (ch != 8)
                {
                    re_password[i] = ch;
                    putch('*');
                    i++;
                }
            }
            re_password[i] = '\0';

            // to show the password
            printf("\n\nDo you want to show the Re-Entered Master password now: 1 for yes/2 for no? ");
            printf("Your reply: ");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("\n%s", re_password);
            }
            // end of the case
        }

        if (password_choice == 2)
        {

            printf("\nEnter the new Password: ");
            scanf("%s", &password);
            printf("\nRe-Enter the new Password: ");
            scanf("%s", &re_password);
        }
        if (strcmp(password, re_password) != 0)
        {
            printf("\n\nRe-Entered password could not match, Please Enter Again.\n");
        }
    } while (strcmp(password, re_password) != 0 && strlen(password) < 8);

    // -----------------------------------------------------------

    while (fgets(currentLine, sizeof(currentLine), filePointer))
    {

        if ((p = strchr(currentLine, '\n')) != NULL)
        {
            *p = '\0';
            check++;
        }

        if (check == line)
        {
            fprintf(tempFile, "%s", password);
            fprintf(tempFile, "\n");
        }
        else
        {
            fprintf(tempFile, "%s", currentLine);
            fprintf(tempFile, "\n");
        }
    }

    fclose(filePointer);
    fclose(tempFile);

    filePointer = fopen(fileName, "w");

    tempFile = fopen("temp.txt", "r");

    while (fgets(currentLine, sizeof(currentLine), tempFile))
    {

        if ((p = strchr(currentLine, '\n')) != NULL)
        {
            *p = '\0';
        }
        fprintf(filePointer, "%s", currentLine);
        fprintf(filePointer, "\n");
    }
    fclose(filePointer);
    fclose(tempFile);
    printf("\nPassword Changed Successfully");
    remove("temp.txt");
}

void signUpScreen()
{

    int test, ch, n = 0, i = 0, password_choice = 0, q = 0, Dots = 0;
    char Master_Password[SIZE], Re_Master_Password[SIZE];
    char questionn[SIZE];

    i = 0; // clearing i

    system("cls"); //for clearing the output screen
    separators();
    printf("\n\n\tCreate a new vault here\n\n");
    separators();
    printf("\nEnter the Username: ");
    scanf("%s", &UserName);
    // do starts
    printf("Press 1 if you want to Hide the password\nPress 2 if you want to display the password\n");
    scanf("%d", &password_choice);

    do
    {

        if (password_choice == 1)
        {
            // for Master Password
            i = 0;
            printf("Please Enter your Master Password: ");
            while ((ch = getch()) != 13)
            {
                if (ch == 8)
                {
                    i--;
                    putch('\b');
                    printf(" ");
                    putch('\b');
                }
                if (ch != 8)
                {
                    Master_Password[i] = ch;
                    putch('*');
                    i++;
                }
            }
            Master_Password[i] = '\0';

            // to show the password
            printf("\n\nDo you want to show the Master password now: 1 for yes/2 for no? ");
            printf("Your reply: ");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("\n%s", Master_Password);
            }

            // for re-enter master_password
            i = 0;
            printf("\nRe-Enter the Master Password: ");
            while ((ch = getch()) != 13)
            {
                if (ch == 8)
                {
                    i--;
                    putch('\b');
                    printf(" ");
                    putch('\b');
                }
                if (ch != 8)
                {
                    Re_Master_Password[i] = ch;
                    putch('*');
                    i++;
                }
            }
            Re_Master_Password[i] = '\0';

            // to show the password
            printf("\n\nDo you want to show the Re-Entered Master password now: 1 for yes/2 for no? ");
            printf("Your reply: ");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("\n%s", Re_Master_Password);
            }
        }

        if (password_choice == 2)
        {

            printf("\nEnter the new Password: ");
            scanf("%s", &Master_Password);
            printf("\nRe-Enter the new Password: ");
            scanf("%s", &Re_Master_Password);
        }
        if (strcmp(Master_Password, Re_Master_Password) != 0)
        {
            printf("\n\nRe-Entered password could not match, Please Enter Again.\n");
        }
    } while (strcmp(Master_Password, Re_Master_Password) != 0 && strlen(Master_Password) < 8);

    AlreadyExistsUser();

    if (AlreadyExistsUser() == '0')
    {
        main();
    }

    test = question();

    switch (test)
    {
    case 1:
        printf("The question you chose is:\nWhat was the name of your first school?");
        printf("\nEnter the answer of the question:\t");
        scanf("%s", questionn);
        q = 1;
        break;

    case 2:
        printf("The question you chose is:\nIn which city were you born?");
        printf("\nEnter the answer of the question:\t");
        scanf("%s", questionn);
        q = 2;
        break;

    case 3:
        printf("The question you chose is:\nWhat was your childhood nickname?");
        printf("\nEnter the answer of the question:\t");
        scanf("%s", questionn);
        q = 3;
        break;

    case 4:
        printf("The question you chose is:\nWhat was the name of the first college you attended?");
        printf("\nEnter the answer of the question:\t");
        scanf("%s", questionn);
        q = 4;
        break;
    }

    printf("\nUser Created Successfully. You may logIn to your Vault Now.\n");
    printf("\nRe-directing to the Main-menu.\n");
    // loading
    Dots = 0;
    while (Dots != 4)
    {
        Sleep(1000);
        Dots += 1;
        printf(".");
    }

    signup(Master_Password, questionn, q);
}

int checkAttempts(int attempts)
{

    FILE *tempPtr;

    int totalAttempts = 0, uAttempts = 0;

    tempPtr = fopen("userStatus.txt", "a");

    printf("\nYou have %d attempts left before your vault gets locked and you'll have to recover your master password", 5 - attempts);

    if (attempts == 5)
    {
        system("cls");
        printf("\nERROR. Maximum number of attempts reached! Your vault has been locked!");
        fprintf(tempPtr, "%s", UserName);
        fprintf(tempPtr, "\n");
        exit(0);
    }
}

int checkVaultStatus()
{
    FILE *fPtr, *fPtrN, *tfPtrN;
    char getLine[SIZE], currentLine[SIZE];
    char *p, *d;
    int check = 0;
    int choice = 0, Dots = 0;

    fPtr = fopen("userStatus.txt", "r");

    while (fgets(getLine, sizeof(getLine), fPtr))
    {

        if ((p = strchr(getLine, '\n')) != NULL)
        {
            *p = '\0';
            check++;
        }

        if ((strcmp(getLine, UserName) == 0))
        {
            printf("\nYour Vault is Disabled!");
            printf("\nYou need to recover your master password");
            do
            {
                printf("\nEnter 1 for resetting master password OR");
                printf("\nEnter 2 for going back to main menu   OR");
                printf("\nEnter 3 for exiting the program");
                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    forgotPassword();
                    fPtrN = fopen("userStatus.txt", "r");
                    tfPtrN = fopen("temp1", "w");

                    while (fgets(currentLine, sizeof(currentLine), fPtrN))
                    {

                        if ((d = strchr(currentLine, '\n')) != NULL)
                        {
                            *d = '\0';
                            check++;
                        }

                        if (strcmp(currentLine, UserName) == 0)
                        {
                            fprintf(tfPtrN, "\n");
                            // fprintf(tfPtrN, "\n");
                        }
                        else
                        {
                            fprintf(tfPtrN, "%s", currentLine);
                            fprintf(tfPtrN, "\n");
                        }
                    }

                    fclose(fPtrN);
                    fclose(tfPtrN);

                    tfPtrN = fopen("temp1", "r");
                    fPtrN = fopen("userStatus.txt", "w");

                    while (fgets(currentLine, sizeof(currentLine), tfPtrN))
                    {

                        if ((d = strchr(currentLine, '\n')) != NULL)
                        {
                            *d = '\0';
                        }

                        fprintf(fPtrN, "%s", currentLine);
                        fprintf(fPtrN, "\n");
                    }

                    fclose(fPtrN);
                    fclose(tfPtrN);
                    remove("temp1.txt");

                    printf("\nVault un-blocked successfully. You may login to your vault now.");
                    printf("\n");
                    printf("\nRe-directing to the login page\n");
                    while (Dots != 5)
                    {
                        Sleep(1000);
                        Dots += 1;
                        printf(".");
                    }
                    return 10;

                    break;

                case 2:
                    main();
                    break;

                case 3:
                    exit(0);
                    break;

                default:
                    printf("\nError! Invalid Choice. Enter Again");
                }

            } while (choice != 1 && choice != 2);
        }
    }

    fclose(fPtr);
}
/*-------create SecureNotes---------------*/
void SecureNotes()
{
    int localCountingCharacter=0;
    char Paragraph[SIZE];
    system("cls");
    printf("--------------------------------------");
    printf("\n    SECURENOTES CREATE MODE       \n");
    printf("--------------------------------------");
    printf("\n");
    fflush(stdin);
    fgets(Paragraph,sizeof(Paragraph),stdin);

    // creating a file and appending

    char *p;// pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);

    FILE *fpointer = fopen(fileName, "a+");

      if(fpointer==NULL)
        {
            printf("File Not Found, Error :( ");
        }

    fprintf(fpointer, "\n");
    fprintf(fpointer, "+");
    fprintf(fpointer, "\n");
    fprintf(fpointer,"%s",Paragraph);
    fprintf(fpointer, "+");

   /* */
    fclose(fpointer);
}
/*--------VIEW SECURENOTES-----------*/
void viewSecureNotes()
{
    system("cls");
    printf("--------------------------------------");
    printf("\n    SECURENOTES VIEW MODE       \n");
    printf("--------------------------------------\n");
    /*for storage file*/
    char *temp="TEMP.dat";
    char NAMEOFFILE[strlen(temp)+strlen(UserName)+1];
    snprintf(NAMEOFFILE,sizeof(NAMEOFFILE),"%s%s",UserName,temp);
    /*end*/

  char currentLine[SIZE];
  char currentLine2[SIZE]; // FOR NOT HAVING ANY CONFLICT WITH currentline
    FILE *filePointer;
    int check = 0;
    char *p, *d;

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);

/*If appendingSecureNotes variable is 1*/

    char String_[SIZE]="SN";
    char filename2[strlen(String_)+strlen(extension)+strlen(UserName)+1];
    snprintf(filename2,sizeof(filename2),"%s%s%s",UserName,String_,extension);
     char checkingstring[SIZE];
    FILE *Storage;
    Storage=fopen(NAMEOFFILE,"r");
    fgets(checkingstring,sizeof(checkingstring),Storage);

    if(strchr(checkingstring,'1')!=NULL)
        {
            AppendSecureNotesFile=1;
        }
    fclose(Storage);


    FILE *AppendingFile;
    /*------------------*/

if(AppendSecureNotesFile!=1){

    filePointer = fopen(fileName, "r");



    while (fgets(currentLine, sizeof(currentLine), filePointer)) {

        if ((p = strchr(currentLine, '\n')) != NULL) {
            *p = '\0';
        }

        if ((strcmp(currentLine, "+") == 0)) {
            check += 1;
            if ((d = strchr(currentLine, '+')) != NULL) {
                *d = '\0';
            }
        }

        if (check == 1) {
            printf("\n%s", currentLine);
        }


    }
    check = 0;
    fclose(filePointer);
}
if(AppendSecureNotesFile==1)
    {


    AppendingFile=fopen(filename2,"r");
    while(fgets(currentLine2,sizeof(currentLine2),AppendingFile))
        {
            printf("%s",currentLine2);
        }
    }
}

/*-------CHECKING SECURENOTES FUNCTION----------*/
void checkSecureNotes()
{
    char *p;// pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);

    FILE *fpointer = fopen(fileName, "r");

      if(fpointer==NULL)
        {
            printf("File Not Found, Error :( ");
            exit(1);
        }
        while(fgets(get_line,sizeof(get_line),fpointer))
            {
                if((p=strchr(get_line,'\n'))!=NULL)
                    {
                        *p='\0';
                    }
                if(strchr(get_line,'+')!=NULL)
                    {
                        CountingCharacter +=1;
                    }
            }

}
/*------APPEND SECURENOTES---------*/
void appendSecureNotes()
{
    system("cls");
    printf("--------------------------------------");
    printf("\n    SECURENOTES APPEND MODE       \n");
    printf("--------------------------------------");
    /*for storage file*/
    char *temp="TEMP.dat";
    char NAMEOFFILE[strlen(temp)+strlen(UserName)+1];
    snprintf(NAMEOFFILE,sizeof(NAMEOFFILE),"%s%s",UserName,temp);
    /*end*/
    char AppendingString[SIZE];
    char *extension=".txt";
    char String_[SIZE]="SN";
    char filename2[strlen(String_)+strlen(extension)+strlen(UserName)+1];
    snprintf(filename2,sizeof(filename2),"%s%s%s",UserName,String_,extension);
    FILE *AppendingFile;
    FILE *OrigianlFile;
    FILE *Storage;
    char temp_store[SIZE];
    char storage[1000];
    int i=0,check=0,check2=0;
    char CharStore;
    char anotherTempFile[SIZE];
    char storageStorage[SIZE];
    int check3=0;
    /*for original file*/
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);
    OrigianlFile=fopen(fileName,"r");
    while(!feof(OrigianlFile))
        {
            fgets(temp_store,sizeof(temp_store),OrigianlFile);
            if(strchr(temp_store,'+')!=NULL)
                {
                    check +=1;
                }
            if(check==1)
                {
                    strcpy(storage,temp_store);
                }
        }
    fclose(OrigianlFile);

    AppendingFile=fopen(filename2,"a+");
    Storage=fopen(NAMEOFFILE,"r");
    while(fgets(storageStorage,sizeof(storageStorage),Storage)){
    if(strchr(storageStorage,'2')!=NULL)
        {
            check3=2;
            break;
        }
    }
    fclose(Storage);

    if(check3!=2)
    {
             for(i=0; i<strlen(storage);i++)
                    {
                        putc(storage[i],AppendingFile);
                    }
    }
    Storage=fopen(NAMEOFFILE,"a");
    fprintf(Storage,"2");
    fclose(Storage);

    fclose(AppendingFile);
    rewind(AppendingFile);

    AppendingFile=fopen(filename2,"r");
    while(fgets(anotherTempFile,sizeof(anotherTempFile),AppendingFile))
        {
            printf("\n%s",anotherTempFile);
        }
    fclose(AppendingFile);

    AppendingFile=fopen(filename2,"a");
    fflush(stdin);
        gets(AppendingString);
        fprintf(AppendingFile,"%s",AppendingString);
        fclose(AppendingFile);
        /*Making the variable store permanently*/
        AppendSecureNotesFile=1;

        Storage=fopen(NAMEOFFILE,"a");
        fprintf(Storage,"1");
        fclose(Storage);
}
/*------make_lowercase function*/
void Make_lower(char *Search1)
{
    int i;
    int length= strlen(Search1);
    for(i=0;i<length;i++)
        {
            Search1[i]=tolower(Search1[i]);
        }
}
/*-------PASS-GEN-LOGIC--------*/
void Generate_password(char *PTR)
{
    system("cls");
    char condition_check='n';
    do{
            system("cls");

    int length_Password,i;
    printf("\n\nEnter the length of the password: ");
    scanf("%d",&length_Password);
    srand(time(NULL));
    char Characters[SIZE]="QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*";
    for(i=0;i<length_Password;i++)
        {
            PTR[i]=Characters[rand()%strlen(Characters)];
        }
        PTR[i]='\0';
    printf("\n%s",PTR);
    printf("\nDo you want to generate any other password?");
    printf("\nPress Y for Yes\nPress N for No");
    condition_check=getch();

    }while(condition_check == 'y' || condition_check=='Y');
    printf("\n%s is your Randomly Generated Password now.",PTR);
    printf("\nPress Enter to continue");
    getch();
}
