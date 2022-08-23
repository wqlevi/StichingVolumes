#include <stdio.h>
#include <stdlib.h>
#include <nifti1_io.h>
#ifndef _NIFTI1_IO_H_
#define _NIFTI1_IO_H_
#endif
#include <znzlib.h>
#include <nifti1.h>

int main(void)
{
char * filename;
size_t char_size = 64;
size_t character = 0;
//float * pixdim=NULL;
float pixdim[8];
int sizehdr;
nifti_image * nii = NULL;
nifti_1_header * hdr = NULL;
filename = malloc(char_size*sizeof(char *));
filename = "/home/qiwang/working_buff/GT_3T/MPRAGE_t1.nii";
hdr = nifti_image_read(filename,0);//read only header

if(hdr!=NULL) printf("success\n");

printf("%d is size of hdr\n",hdr->sizeof_hdr);
for (int i=0;i<8;i++)
{printf("%f\t",hdr->pixdim[i]);
}

free(hdr);
//free(pixdim);
return EXIT_SUCCESS;
}

