#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define SIZE 255

void interface();
void separators();

int signup( char Master_Password[SIZE]);
char Identification(char Master_Password[SIZE]);

char inVault();
char save();
char view();

int status = 0;
char UserName[SIZE];

int main() {
    int choice;
    char Master_Password[SIZE];

    interface();
    printf("\n\nEnter your choice:  ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            system("cls");//for clearing the output screen
            separators();
            printf("\n\n\tYou can login to your vault here\n\n");
            separators();
            printf("\n\nEnter the Username: ");
            scanf("%s", &UserName);
            printf("\nEnter the Password: ");
            scanf("%s", &Master_Password);
            Identification(Master_Password);

            if (status == 0) inVault();
            else if (status == 1)
                printf("\nWrong Password");
            if (status == 2)
                printf("Wrong Username");

            break;

        case 2:
            system("cls");//for clearing the output screen
            separators();
            printf("\n\n\tCreate a new vault here\n\n");
            separators();
            printf("\nEnter the Username: ");
            scanf("%s", &UserName);
            printf("\nEnter the Password: ");
            scanf("%s", &Master_Password);
            signup(Master_Password);
            break;
    }


    return 0;
}

void interface() {
    printf("_______________________________________________________________");
    printf("\n\n\t\tWelcome to Password Manager\n\n");
    printf("_______________________________________________________________");
    printf("\n\n\t1 for existing user  OR  2 to create new user");
}

void separators() {
    printf("_______________________________________________________________");
}
int signup(char Master_Password[SIZE]) {

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);
    FILE *fpointer = fopen(fileName, "a+");
    // printing into the file
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", UserName);
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", Master_Password);
    fprintf(fpointer, "\n");
    fprintf(fpointer, "_");
    // closing the file
    fclose(fpointer);
}

char Identification(char Master_Password[SIZE]) {


    char Verification[SIZE] = "Access Granted";
    char *p;// pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);

    FILE *fpointer = fopen(fileName, "r");
    // In case of no file
    if (fpointer == NULL)
        {
        printf("\nNo User found. Create a user first.\n\n");
        status=3;
        return '2';
        }

    // loop start
  while (fgets(get_line, sizeof(get_line), fpointer)) {

        // extracting the new line from get_line variable
        if ((p = strchr(get_line, '\n')) != NULL) {
            *p = '\0';
        }

        // comparing the username with the get_line, if the get_line==Username then access granted
        if ((strcmp(get_line, UserName) == 0)) {

            while (fgets(get_line, sizeof(get_line), fpointer)) {
                if ((p = strchr(get_line, '\n')) != NULL) {
                    *p = '\0';
                }
                if ((strcmp(get_line, Master_Password) == 0)) {
                    return '0';
                } else if ((strcmp(get_line, Master_Password) != 0)) {
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

char inVault() {

    int  mainChoice, test, newChoice;
    char web[SIZE], username[SIZE], pass[SIZE];

    system("cls");
    separators();
    printf("\n\n\t\tWelcome to your Vault\n\n");
    separators();
    printf("\nChoose the item you want to Create/View\n");

    do {
        printf("\n 1 for Credentials\n 2 for SecureNotes");
        printf("\n\nEnter your choice:  ");
        scanf("%d", &mainChoice);
    } while (mainChoice != 1 && mainChoice != 2);
    system("cls");
    printf("\n1 to view saved credentials\n2 for saving new credentials");
    printf("\nTo go back: press -1");
    printf("\n\nEnter your choice:  ");
    scanf("%d",&newChoice);
    if (newChoice == -1 ) {
        inVault();
        return 0;
    }

    switch (mainChoice) {

        case 1:
            switch (newChoice) {

                case 1:
                    printf("Saved logins");
                    view();
                    printf("\nEnter 0 to go back to main menu:\t");
                    scanf("%d", &test);
                    if (test == 0) {
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
                    if (test == 0) {
                        inVault();
                    }

                    break;
            }// newchoice switch closed

            break;// mainchoice case 1 break

        case 2:


            break;
    }
}

char save(char website[SIZE], char userName[SIZE], char pass[SIZE]) {
    // variable name file declaration
    char *extension = ".txt";
    char fileName[strlen(UserName)+strlen(extension)+1]; // added 1 for the '/0' character
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension); // here taking UserName and extension strings ( concatenating them ) and then storing into fileName.

    FILE *fPtr;
    fPtr = fopen(fileName, "a");

    if (fPtr == NULL)
        {
        printf("\nNo User found. Create a user first.\n\n");
        printf("\n%s",fileName);
        return 'B';
        }

    fprintf(fPtr, "\n");
    fprintf(fPtr, "The name is:\t\t%s", website);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "The username is:\t%s", userName);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "The password is:\t%s", pass);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "_");
    fclose(fPtr);
    system("cls");
    printf("\nRecord Added");
}

char view(void) {
    char currentLine[SIZE];
    FILE *filePointer;
    int check = 0;
    char *p, *d;

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);



    filePointer = fopen(fileName, "r");


    while (fgets(currentLine, sizeof(currentLine), filePointer)) {

        if ((p = strchr(currentLine, '\n')) != NULL) {
            *p = '\0';
        }

        if ((strcmp(currentLine, "_") == 0)) {
            check = 1;
            if ((d = strchr(currentLine, '_')) != NULL) {
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
