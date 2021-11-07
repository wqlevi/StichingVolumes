#include <stdio.h>
#include <nifti/nifti1_io.h>
#include <nifti/znzlib.h>
#include <stdlib.h>
typedef enum {false ,true} bool;

int main()
{
    char * filename;
    size_t char_size = 32;
    size_t character;
    filename = malloc(char_size*sizeof(char *));
    nifti_image * img = NULL;
    character = getline(&filename,&char_size,stdin);
    img = nifti_image_read(filename,1);
    if(!img==NULL) printf("success\n");
    printf("%zu is char length, %s is the filename\n",character,filename);
return 0;
}
