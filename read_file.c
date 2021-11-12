#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    char * filename = argv[1];
    short par;
    FILE * f = fopen(filename,"r");
    fseek(f,4,SEEK_SET);
    fread(&par,(size_t)1,1,f);
    printf("%d is the parameter\n",par);
    fclose(f);
    return EXIT_SUCCESS;
}