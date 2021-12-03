#include <stdio.h>
#include <stdlib.h>
#define SIZE 255
#include <time.h>
#include <string.h>
int main()
{
    int length_Password,i;
    printf("Enter the length of the password: ");
    scanf("%d",&length_Password);
    srand(time(NULL));
    char password[SIZE];
    char Characters[SIZE]="QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*";
    for(i=0;i<length_Password;i++)
        {
            password[i]=Characters[rand()%strlen(Characters)];
        }
    printf("\nRandomly generated password: %s",password);

    return 0;
}
