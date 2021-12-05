#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int main()
{
    char backspace_char;
    char check[256];
    char password[256];
    int ch,i=0,n=0; // ch is to store the character , i is iterator (acts as index number too), n is for sub-menu inside the case 1 of main-menu.
    int choice=0; // for the main menu
    printf("Press 1 if you want to Hide the password\nPress 2 if you want to display the password\n");
    scanf("%d",&choice);
    system("cls");
    printf("Please Enter your Password: ");
    if(choice==1){

    while((ch=getch())!= 13){
    if(ch == 8)
    {
      i--;
      putch('\b');
      printf(" ");
      putch('\b');
    }
    if(ch!= 8)
    {
      password[i]=ch;
      putch('*');
      i++;
    }

    }

    password[i]='\0';
    printf("\n\nDo you want to show the password now: 1 for yes/2 for no? ");
    printf("Your reply: ");
    scanf("%d",&n);
    if(n==1)
        {
           printf("\n%s",password);

        }
    }
    if(choice==2){
    scanf("%s",password);
    }

    // for comparing.
    printf("\n%d",strlen(password));
    printf("String to compare: ");
    scanf("%s",check);
    if((strcmp(password,check))==0)
        {
            printf("\nok");
        }
    return 0;
}
