#include <stdio.h>
#include <stdlib.h>

void interface();
void separators();

int main() {
    int choice;

    interface();
    printf("\n\nEnter your choice:  ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            system("cls");//for clearing the output screen
            separators();
            printf("\n\n\tYou can login to your vault here\n\n");
            separators();
            break;

        case 2:
            printf("Case 2");
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