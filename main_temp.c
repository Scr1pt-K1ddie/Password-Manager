#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 255

void interface();
void separators();

int signup( char Master_Password[SIZE]);
char Identification(char Master_Password[SIZE]);
void SecureNotes();
void viewSecureNotes();

char inVault();
char save();
char view();
char AlreadyExistsUser();

int status = 0;
char UserName[SIZE];

int main() {


    int choice,ch,n=0,i=0,password_choice=0;
    char Master_Password[SIZE],Re_Master_Password[SIZE];
    int Dots=0; // for Dots
    system("cls");
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
            // masking password logic here too
             printf("Press 1 if you want to Hide the password\nPress 2 if you want to display the password\n");
            scanf("%d",&password_choice);

                if(password_choice==1)
                    {
                        // for Master Password
                        i=0;
                     printf("Please Enter your Master Password: ");
                     printf("\n");
                     while((ch=getch())!= 13)
                     {
                         if(ch == 8)
                            {
                              i--;
                              putch('\b');
                              printf(" ");
                              putch('\b');
                            }
                          if(ch!= 8)
                            {
                              Master_Password[i]=ch;
                              putch('*');
                              i++;
                            }

                     }
                     Master_Password[i]='\0';

                      // to show the password
                    printf("\n\nDo you want to show the Master password now: 1 for yes/2 for no? ");
                    printf("Your reply: ");
                    scanf("%d",&n);
                    if(n==1)
                        {
                           printf("\n%s",Master_Password);
                        }

                                } // end of the case

            if(password_choice==2)
            {
            printf("\nEnter the new Password: ");
            scanf("%s", &Master_Password);
            }
            printf("\n\nLogging you In.");
            while(Dots!=3 )
                {
                    Sleep(1000);
                    Dots+=1;
                    printf(".");
                }
            Identification(Master_Password);

            if (status == 0) inVault();
            else if (status == 1)
                printf("\nWrong Password");
            if (status == 2)
                printf("Wrong Username");

            break;

        case 2:
            i=0; // clearing i

            system("cls");//for clearing the output screen
            separators();
            printf("\n\n\tCreate a new vault here\n\n");
            separators();
            printf("\nEnter the Username: ");
            scanf("%s", &UserName);
            // do starts
            printf("Press 1 if you want to Hide the password\nPress 2 if you want to display the password\n");
            scanf("%d",&password_choice);

            do{

                if(password_choice==1)
                    {
                        // for Master Password
                        i=0;
                     printf("Please Enter your Master Password: ");
                     printf("\n");
                     while((ch=getch())!= 13)
                     {
                         if(ch == 8)
                            {
                              i--;
                              putch('\b');
                              printf(" ");
                              putch('\b');
                            }
                          if(ch!= 8)
                            {
                              Master_Password[i]=ch;
                              putch('*');
                              i++;
                            }

                     }
                     Master_Password[i]='\0';

                      // to show the password
                    printf("\n\nDo you want to show the Master password now: 1 for yes/2 for no? ");
                    printf("Your reply: ");
                    scanf("%d",&n);
                    if(n==1)
                        {
                           printf("\n%s",Master_Password);
                        }

            // for re-enter master_password
            i=0;
            printf("\nRe-Enter the Master Password: ");
            printf("\n");
            while((ch=getch())!= 13)
                     {
                         if(ch == 8)
                            {
                              i--;
                              putch('\b');
                              printf(" ");
                              putch('\b');
                            }
                          if(ch!= 8)
                            {
                              Re_Master_Password[i]=ch;
                              putch('*');
                              i++;
                            }

                     }
                     Re_Master_Password[i]='\0';

                     // to show the password
                    printf("\n\nDo you want to show the Re-Entered Master password now: 1 for yes/2 for no? ");
                    printf("Your reply: ");
                    scanf("%d",&n);
                    if(n==1)
                        {
                           printf("\n%s",Re_Master_Password);
                        }
                    // end of the case
                    }

            if(password_choice==2)
            {

            printf("\nEnter the new Password: ");
            scanf("%s", &Master_Password);
            printf("\nRe-Enter the new Password: ");
            scanf("%s", &Re_Master_Password);

            }
            if(strcmp(Master_Password,Re_Master_Password)!=0)
                {
                    printf("\n\nRe-Entered password could not match, Please Enter Again.\n");
                }
            }while(strcmp(Master_Password,Re_Master_Password)!=0 && strlen(Master_Password) < 8 );
            // do ends

            AlreadyExistsUser();
            printf("\nUser Created Successfully. You may logIn to your Vault Now.\n");
            printf("\nRe-directing to the Main-menu.\n");
            // loading
            Dots=0;
            while(Dots!=4 )
                {
                    Sleep(1000);
                    Dots+=1;
                    printf(".");
                }
            signup(Master_Password);

            main();
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
// variable filename declaration
    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1]; // +1 for '/0' character, only necessary while writing/appending.
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
        status=3; // assigning 3 to 'status' so when the control goes back to main function, The program does not open Vault.
        return '2';
        }

    // loop start
  while (fgets(get_line, sizeof(get_line), fpointer)) {

        // extracting the new line from get_line variable
        if ((p = strchr(get_line, '\n')) != NULL) {
            *p = '\0';
        }

        //In case of existing user

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

    char paragraphs[SIZE];
    int  mainChoice, test, newChoice;
    char web[SIZE], username[SIZE], pass[SIZE];
    int log_out=0;

    system("cls");
    separators();

    // In Vault prompts
    printf("\n\n\t\tWelcome to your Vault\n\n");
    separators();
    printf("\nChoose the item you want to Create/View\n");

    do {
        printf("\n 1 for Credentials\n 2 for SecureNotes\n -1 to log out of the vault.");
        printf("\n\nEnter your choice:  ");
        scanf("%d", &mainChoice);
    } while (mainChoice != 1 && mainChoice != 2 && mainChoice!=-1);
    if (mainChoice== -1)
        {
            printf("\nLogging Out");
            while(log_out<2)
                {
                    Sleep(800);
                    printf(".");
                    log_out+=1;
                }
            main();
        }
    system("cls");
 // if mainchoice is 1

    if(mainChoice==1)
    {
    // prompts for credentials
    printf("\n1 to view saved credentials\n2 for saving new credentials");
    printf("\nTo go back: press -1");
    printf("\n\nEnter your choice:  ");
    scanf("%d",&newChoice);

    /*For going back to the menu*/
    if (newChoice == -1 )
    {
        inVault();
        return 0;
    }

    } // if mainchoice is 1 ends

    /*--------------------*/

    //if mainchoice is 2
    if(mainChoice==2)
    {
         printf("\n1 to Create SecureNotes\n2 to view saved SecureNotes");
         printf("\nTo go back: press -1");
         printf("\n\nEnter your choice:  ");
         scanf("%d",&newChoice);
    }
    // For going back to the menu
    if (newChoice == -1 )
    {
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

            switch(newChoice)
            {
              case 1:
                SecureNotes();
              break;

              case 2:
                viewSecureNotes();
            }
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

char view(void) {
    char currentLine[SIZE];
    FILE *filePointer;
    int check = 0;
    char *p, *d;

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
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

char AlreadyExistsUser() {


    int Dots=0;
    char *p;// pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);

    FILE *fpointer = fopen(fileName, "r");

    if(fpointer==NULL)
        {
            return 'C';
        }

    // loop start
  while (fgets(get_line, sizeof(get_line), fpointer)) {

        // extracting the new line from get_line variable
        if ((p = strchr(get_line, '\n')) != NULL) {
            *p = '\0';
        }

        if ((strcmp(get_line, UserName) == 0))
            {
                printf("\nError\nUser Already Exists.\nPlease try again to create a new Vault");
                printf("\nRe-directing you to the Main-menu.\n");
            // loading
            while(Dots!=4 )
                {
                    Sleep(1000);
                    Dots+=1;
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
void SecureNotes()
{
    char Paragraph[SIZE];
    system("cls");
    printf("----------Secure Notes----------");
    printf("\n");
    fflush(stdin);
    fgets(Paragraph,sizeof(Paragraph),stdin);

    // creating a file and appending

    char *p;// pointer for storing extracted newline from get_line
    char get_line[SIZE];

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);

    FILE *fpointer = fopen(fileName, "a");

      if(fpointer==NULL)
        {
            printf("File Not Found, Error :( ");
        }
    fprintf(fpointer, "\n");
    fprintf(fpointer, "+");
    fprintf(fpointer, "\n");
    fprintf(fpointer,"%s",Paragraph);
    fprintf(fpointer, "+");
}
void viewSecureNotes()
{
  char currentLine[SIZE];
    FILE *filePointer;
    int check = 0;
    char *p, *d;

    char *extension=".txt";
    char fileName[strlen(UserName)+strlen(extension)+1];
    snprintf(fileName,sizeof(fileName),"%s%s",UserName,extension);



    filePointer = fopen(fileName, "r");



    while (fgets(currentLine, sizeof(currentLine), filePointer)) {

        if ((p = strchr(currentLine, '\n')) != NULL) {
            *p = '\0';
        }

        if ((strcmp(currentLine, "+") == 0)) {
            check = 1;
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