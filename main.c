#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int check=0;
    char *p;
    char *d;
    char *j;
    char storage1[256];
    char string[256]="paad";
    char ch;
    FILE *fptr;
    fptr=fopen("saad1.txt","r");
    while(1)
        {
            fgets(storage1,sizeof(storage1),fptr);
            if((p=strchr(storage1,'\n'))!=NULL)
                {
                    *p='\0';
                }
            if((d=strchr(storage1,'*'))!=NULL)
                {
                    *d='\0';
                }
            if((j=strchr(storage1,'_'))!=NULL)
                {
                    *j='\0';
                }
            if(strcmp(storage1,string)==0)
                {
                    printf("%s",storage1);
                    while(strchr(storage1,'&')==NULL)
                        {
                            fgets(storage1,sizeof(storage1),fptr);
                            printf("%s",storage1);
                        }


                        break;
                }
        }
    fclose(fptr);
/*    fptr=fopen("saad1.txt","a");
    fclose(fptr);
    fptr=fopen("saad1.txt","r+");
    while(1){storage=fgetc(fptr);
    if(storage=='*'){break;}}

    while(1)
        {
            storage=fgetc(fptr);
            if(storage=='*')
                {
                    fseek(fptr,-1,SEEK_CUR);
        fprintf(fptr,"_");
        fprintf(fptr,"\nkAli");
        fprintf(fptr,"\n_");
        fprintf(fptr,"\n*");
                    break;
                }
        }

/*    fprintf(fptr,"*");
    fprintf(fptr,"\n");
    fprintf(fptr,"*");
    fclose(fptr);
*/

    return 0;
}
