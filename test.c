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
float * pixdim=NULL;
nifti_image * nii = NULL;
nifti_1_header * hdr = NULL;
filename = malloc(char_size*sizeof(char *));
filename = "/home/qiwang/Desktop/matched_bet04.nii";
hdr = nifti_image_read(filename,0);//read only header

if(nii!=NULL) printf("success\n");
pixdim = hdr->pixdim;

for(int i=0; i<8; i++)
{
if((i==1)||(i==2)||(i==3))
{
pixdim[i] = 0.6;
}
printf("%f is the 0th element\n",pixdim[i]);
}

free (hdr);
free (pixdim);
return EXIT_SUCCESS;
}

