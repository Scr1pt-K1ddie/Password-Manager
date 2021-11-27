#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 255

void interface();
void separators();

int signup(char Username[SIZE], char Master_Password[SIZE]);
char Identification(char Username[SIZE], char Master_Password[SIZE]);

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
            printf("\nEnter the Username: ");
            scanf("%s", &UserName);
            printf("\nEnter the Password: ");
            scanf("%s", &Master_Password);
            Identification(UserName, Master_Password);
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
    // closing the file
    fclose(fpointer);
}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EmptyDeclOrStmt"
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
                    printf("Access granted");
                    return 0;
                }
            }
        }
        // end of the loop body
    }
    return '0';
    // closing the file
    fclose(fpointer);
}
#pragma clang diagnostic pop
