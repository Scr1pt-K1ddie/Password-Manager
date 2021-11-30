#include <stdio.h>

int main()
{
    char a[255];
    gets(a);
    char* extension = ".txt";
    char fileSpec[strlen(a)+strlen(extension)+1];
    FILE *out;

    snprintf( fileSpec, sizeof( fileSpec ), "%s%s", a, extension );


    out = fopen( fileSpec, "w" );
    fclose(out);
    int current_curson= ftell(out);
    printf("%d",current_curson);
    return 0;
}
