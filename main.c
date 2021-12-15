#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define SIZE 255

void interface();
void separators();

int signup();
int resetPassword();
int forgotPassword();
int question();

char Identification(char Master_Password[SIZE]);
char inVault();
char save();
char view();
char AlreadyExistsUser();

int status = 0;
char UserName[SIZE];

int main()
{

    int choice, test, check = 0, ch, n = 0, i = 0, password_choice = 0, q = 0, Dots = 0, passChoice = 0, select = 0;
    char Master_Password[SIZE], Re_Master_Password[SIZE];
    char questionn[SIZE];

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

        } // end of the case

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
                printf("\nEnter 1 to go back to main menu or enter 2 to reset password");
                scanf("%d", &passChoice);

                if (passChoice == 2)
                {
                    forgotPassword();
                }

                else if (passChoice == 1)
                {
                    main();
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
                printf("\n    Enter 0 to try again\n    Enter 1 to to create a new user\n    Enter 2 to exit program.");
                scanf("%d", &select);
            }

            switch (select)
            {
            case 0:
                main();
                break;

            case 1:

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
                // end of the case
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
        // do ends

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

        // _________________________________________________________________

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
    fprintf(fpointer, "_");
    // closing the file
    fclose(fpointer);
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

        //In case of existing user

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
    char web[SIZE], username[SIZE], pass[SIZE];
    int log_out = 0;

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
            printf("\n\nEnter the Password: ");
            scanf("%s", &pass);
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

        break;
    }
}

char save(char website[SIZE], char userName[SIZE], char pass[SIZE])
{
    // variable name file declaration
    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1];           // added 1 for the '/0' character
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension); // here taking UserName and extension strings ( concatenating them ) and then storing into fileName.

    FILE *fPtr;
    fPtr = fopen(fileName, "a");

    if (fPtr == NULL)
    {
        printf("\nNo User found. Create a user first.\n\n");
        printf("\n%s", fileName);
        return 'B';
    }

    fprintf(fPtr, "\n");
    fprintf(fPtr, "The Website name is:\t%s", website);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "The UserName is:\t%s", userName);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "The password is:\t%s", pass);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "_");
    fclose(fPtr);
    system("cls");
    printf("\nRecord Added");
}

char view(void)
{
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

        if ((strcmp(currentLine, "_") == 0))
        {
            check = 1;
            if ((d = strchr(currentLine, '_')) != NULL)
            {
                *d = '\0';
            }
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
