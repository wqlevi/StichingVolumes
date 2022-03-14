#include <stdio.h>
#include <nifti1_io.h>
#include <znzlib.h>
#include <nifti1.h>
#include <stdlib.h>
typedef enum {false ,true} bool;
/*
 * A program for purly assemble image of real nifti crops 
 */
int main(){
    nifti_1_header hdr;
    FILE * fp;
    int ret, i ;

    char *filename = "/home/qiwang/working_buff/GT_3T/MPRAGE_t1.nii";
    fp = fopen(filename,"r");
    ret = fread(&hdr,348,1,fp);
    fprintf(stderr,"\n%d header information",hdr.sizeof_hdr);
    fclose(fp);
}
