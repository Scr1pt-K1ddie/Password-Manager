#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 255

void interface();
void separators();

int signup(char Username[SIZE], char Master_Password[SIZE]);
char Identification(char Username[SIZE], char Master_Password[SIZE]);

char inVault();
char save();
char view();

int status = 0;

int main() {
    int choice;
    char UserName[SIZE], Master_Password[SIZE];

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
            Identification(UserName, Master_Password);

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
            signup(UserName, Master_Password);
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
int signup(char Username[SIZE], char Master_Password[SIZE]) {
    FILE *fpointer = fopen("Vault.txt", "a+");
    // printing into the file
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", Username);
    fprintf(fpointer, "\n");
    fprintf(fpointer, "%s", Master_Password);
    fprintf(fpointer, "\n");
    fprintf(fpointer, "_");
    // closing the file
    fclose(fpointer);
}

char Identification(char Username[SIZE], char Master_Password[SIZE]) {
    char Verification[SIZE] = "Access Granted";
    char *p;// pointer for storing extracted newline from get_line
    char get_line[SIZE];

    FILE *fpointer = fopen("Vault.txt", "r");
    // In case of empty file
    if (fpointer == NULL) {
        printf("\nNo User found. Create a user first.\n\n");
        return '2';
    }
    // loop start
    while (fgets(get_line, sizeof(get_line), fpointer)) {

        // extracting the new line from get_line variable
        if ((p = strchr(get_line, '\n')) != NULL) {
            *p = '\0';
        }

        // comparing the username with the get_line, if the get_line==Username then access granted
        if ((strcmp(get_line, Username) == 0)) {
            while (fgets(get_line, sizeof(get_line), fpointer)) {
                if ((p = strchr(get_line, '\n')) != NULL) {
                    *p = '\0';
                }
                if ((strcmp(get_line, Master_Password) == 0)) {
                    return 0;
                } else if ((strcmp(get_line, Master_Password) != 0)) {
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

char inVault() {

    int newChoice;
    char web[SIZE],username[SIZE],pass[SIZE];

    system("cls");
    separators();
    printf("\n\n\t\tWelcome to your Vault\n\n");
    separators();
    printf("\n1 to view saved credentials Or 2 for saving new credentials");
    printf("\n\nEnter your choice:  ");
    scanf("%d", &newChoice);

    switch (newChoice) {

        case 1:
            printf("Saved logins");
            view();
            break;

        case 2:

            printf("\n\nEnter the name: ");
            scanf("%s", &web);
            printf("\n\nEnter the Name: ");
            scanf("%s", &username);
            printf("\n\nEnter the password: ");
            scanf("%s", &pass);

            save(web,username,pass);

            break;
    }
}

char save(char website[SIZE], char userName[SIZE], char pass[SIZE]){
    FILE *fPtr;
    fPtr = fopen("Vault.txt", "a");
    fprintf(fPtr, "\n");
    fprintf(fPtr, "%s", website);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "%s", userName);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "%s", pass);
    fprintf(fPtr, "\n");
    fprintf(fPtr, "_");
    fclose(fPtr);
    system("cls");
    printf("\nRecord Added");
}

char view(void){
    char currentLine[SIZE];
    FILE *filePointer;
    int check=0;
    char *p,*d;

    filePointer = fopen("Vault.txt", "r");


    while (fgets(currentLine, sizeof(currentLine), filePointer)) {

        if ((p = strchr(currentLine, '\n')) != NULL) {
            *p = '\0';
        }

        if ((strcmp(currentLine, "_") == 0)) {
            check = 1;
            if ((d = strchr(currentLine, '_')) != NULL) {
                *d = '\0';
            }
            /* check++;
            if(check==0)
                printf("\nThe website is:  %s", currentLine);

            if(check==1)
                printf("\nThe username is:  %s", currentLine);

            if(check==2)
                printf("\nThe password is:  %s", currentLine); */
        }

        if (check == 1) {
            printf("\n%s", currentLine);
        }
    }
    check =0;
    fclose(filePointer);
}
