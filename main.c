#include <stdio.h>

int main() {
    int choice;

    printf("_______________________________________________________________");
    printf("\n\n\t\tWelcome to Password Manager\n\n");
    printf("_______________________________________________________________");
    printf("\n\n\t1 for existing user  OR  2 to create new user");
    printf("\n\nEnter your choice:  ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Case1");
            break;

        case 2:
            printf("Case 2");
            break;
    }


    return 0;
}
