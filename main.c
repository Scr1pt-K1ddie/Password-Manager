#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255

void interface();
void separators();

int question();
int forgotPassword();
int resetPassword();
int signup(char Master_Password[SIZE], char Question[SIZE], int q);

char Identification(char Master_Password[SIZE]);
char inVault();
char save();
char view();
char AlreadyExistsUser();

int status = 0;
char UserName[SIZE];

int main()
{
    int choice, test, check = 1, q = 0, n = 0, i = 0, Dots = 0;
    char Master_Password[SIZE];
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
        printf("\nEnter the Password: ");
        scanf("%s", &Master_Password);

        Identification(Master_Password);

        if (status == 0)
            inVault();
        else if (status == 1)
        {
            printf("\nWrong Password");
            printf("\nEnter 0 to reset password\t");
            scanf("%d", &check);

            if (check == 0)
            {
                forgotPassword();
                exit(0);
            }
        }

        if (status == 2)
        {
            printf("Wrong Username");
        }

        break;

    case 2:
        system("cls"); //for clearing the output screen
        separators();
        printf("\n\n\tCreate a new vault here\n\n");
        separators();
        printf("\nEnter the Username: ");
        scanf("%s", &UserName);

        // ---------------- new code -------------//
        do
        {

            printf("\nEnter the new Password: ");
            scanf("%s", &Master_Password);

            if (strlen(Master_Password) < 8)
            {
                printf("\n\nPlease Enter another password, minimum length of password is 7\n\n");
            }

        } while ((strlen(Master_Password)) < 8);
        // do ends

        AlreadyExistsUser();

        printf("\nUser Created Successfully. You may logIn to your Vault Now.\n");
        printf("\nRe-directing to the Main-menu.\n");
        // loading
        while (Dots != 4)
        {
            Sleep(1000);
            Dots += 1;
            printf(".");
        }

        // --------------------------------- //

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

        signup(Master_Password, questionn, q);

        main();
        // signup(Master_Password, questionn, q);
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
    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1]; // +1 for '/0' character, only necessary while writing/appending.
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);
    FILE *fpointer = fopen(fileName, "a+");

    char chosenQuestion[SIZE];
    // printing into the file

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
}

char Identification(char Master_Password[SIZE])
{
    char Verification[SIZE] = "Access Granted";
    char *p; // pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension)];
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    FILE *fpointer = fopen(fileName, "r");

    // In case of empty file
    if (fpointer == NULL)
    {
        printf("\nNo User found. Create a user first.\n\n");
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
                    return 0;
                }
                else if ((strcmp(get_line, Master_Password) != 0))
                {
                    status = 1;
                    return 0;
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

    int newChoice, mainChoice, test;
    char web[SIZE], username[SIZE], pass[SIZE];

    system("cls");
    separators();
    printf("\n\n\t\tWelcome to your Vault\n\n");
    separators();
    printf("\nChoose the item you want to Create/View\n");

    do
    {
        printf("\n 1 for Credentials\n 2 for SecureNotes");
        printf("\n\nEnter your choice:  ");
        scanf("%d", &mainChoice);
    } while (mainChoice != 1 && mainChoice != 2);

    printf("\n1 to view saved credentials Or 2 for saving new credentials");
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
            printf("\nEnter 9 to exit program or Enter 0 to go back to main menu:\t");
            scanf("%d", &test);
            if (test == 0)
            {
                inVault();
            }
            else if (test == 9)
                exit(0);
            break;

        case 2:

            printf("\n\nEnter the Website Name: ");
            scanf("%s", &web);
            printf("\n\nEnter the User Name: ");
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

char save(char website[SIZE], char username[SIZE], char pass[SIZE])
{
    FILE *fPtr;

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1]; // added 1 for the '/0' character
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    fPtr = fopen(fileName, "a");

    fprintf(fPtr, "\n");
    fprintf(fPtr, "The name is:\t\t%s", website);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "The username is:\t%s", username);
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

int question()
{

    int test;

    printf("Choose your security questions to reset your password in case you forget it.");
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
                exit(0);
            }

            else if (strcmp(answer, getLine) != 0)
            {
                printf("Wrong Answer");
            }
        }
    }
    fclose(filePointer);
}

int resetPassword()
{
    FILE *filePointer, *tempFile;
    char currentLine[SIZE];
    char *p, answer[SIZE];
    int check = 0, line = 3;

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension) + 1];
    snprintf(fileName, sizeof(fileName), "%s%s", UserName, extension);

    printf("\nEnter new password: ");
    scanf("%s", &answer);

    filePointer = fopen(fileName, "r");
    tempFile = fopen("temp.txt", "w");

    while (fgets(currentLine, sizeof(currentLine), filePointer))
    {

        if ((p = strchr(currentLine, '\n')) != NULL)
        {
            *p = '\0';
            check++;
        }

        if (check == line)
        {
            fprintf(tempFile, "%s", answer);
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

    /* FILE *filePointer, *tempFile;
    char currentLine[SIZE];
    char *p, answer[SIZE];
    int check = 0, line = 3;

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension)]; */
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

char AlreadyExistsUser()
{

    int Dots = 0;
    char *p; // pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension = ".txt";
    char fileName[strlen(UserName) + strlen(extension)];
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
