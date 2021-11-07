#include <stdio.h>
#include <stdlib.h>
#include <nifti1_io.h>

int main()
{
    char * filename;
    nifti_image * nii = NULL;
    filename = "T1.nii.gz";
    nii = nifti_image_read(filename,1);
    if(nii!=NULL) printf("scus!\n");
    return 0;
}