#include <stdio.h>
#include <nifti1_io.h>
#include <znzlib.h>
#include <nifti1.h>
#include <stdlib.h>
typedef enum {false ,true} bool;

int main(int argc, char * argv[])
{
    int write_to_file(char * filename,nifti_1_header * hdr, float * data);
    char * filename, *file_save;
    filename = argv[1]; //data file
    file_save = argv[2]; //save file

    nifti_image * img = NULL;
    nifti_1_header * hdr = NULL;
    float *data_tmp=NULL;
    hdr = nifti_image_read(filename,0);
    printf("%d\n",hdr->sizeof_hdr);
    /*
    data_tmp = malloc(sizeof(nifti_image *)*400*400*451);
    img = nifti_image_read(filename,1);
    data_tmp = img->data;
    if(data_tmp!=NULL) printf("success\n");
    write_to_file(file_save,hdr,data_tmp);
    free(data_tmp);
    free(img);
    */
return 0;
}

int write_to_file(char * filename,nifti_1_header * hdr,float * data)
{
    FILE * fh = fopen(filename,"w");
    if(fh==NULL) return(EXIT_FAILURE);
    printf("size_t is %zu\n%d elements in total\n",sizeof(data),(hdr->dim[0]*hdr->dim[1]*hdr->dim[2]));
    size_t r = fwrite(data,(size_t)(hdr->bitpix / 8),(400*400*451),fh);
    printf("wrote %zu elements\n",r);
    fclose(fh);
    return EXIT_SUCCESS;
} 

