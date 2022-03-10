/*
 *  Mainly updated version of 3D stitching
 *  Author : Qi Wang
 */


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <nifti1_io.h>
#include <nifti1.h>

#define M 128

#define X 512
#define Y 698
#define Z 640
#define I 16*2 // step size x,z
#define J 15*2 // step size y
#define K 16*2 // step size z
#define RES_X 128-I // overlapped length x,z
#define RES_Y 128-J
#define RES_Z 128-K // overlapped length x,z


typedef enum {false, true} bool;
typedef float MU_DATATYPE;

int main(int argc, char ** argv)
{
//  	int * make_sample(int size_x, int size_y, int size_z, _Bool zeros);
	int write_to_file(int count, int cols,int rows, int *data, char const *fileName);
	int * assemble_3d(int * image, int * crop , bool asym);
	struct dirent **nameList;
	int n;
	char * file_path = argv[1];
	char * filename;
	nifti_image * crop;
	/* scan directory for patches */
	n = scandir(file_path,&nameList,NULL,alphasort);
	if (n == -1) exit(EXIT_FAILURE);
	while (n--)
	{
	if (n == 2) filename=nameList[n]->d_name;
	}



	/* read/write crop again */
	crop = nifti_image_read(filename,1);// I/O need to be customized functions(ignoring header)
	nifti_image_write(crop);
	free(crop);
	return 0;
}

static int read_nifti_file(char * const datafile)
{
	FILE * fp;
	int ret,i;
	MY_DATATYPE *data = NULL;
	fp = fopen(datafile,"r");
	ret = fseek(fp,384,SEEKSET);	
	if(ref != 0) exit(1);
	data = (MY_DATATYPE *) calloc(M*M*M,sizeof(MY_DATATYPE));
	if (data == NULL) exit(1);
	ret = fread(data, sizeof(MY_DATATYPE),M*M*M,fp);
	fclose(fp);
	exit(EXIT_SUCCESS);
}


int * make_sample(int size_x, int size_y, int size_z, _Bool zeros){
	/*
	 * This creates a dummy 3D crop
	 */
	int *mat;
	mat = calloc(size_x*size_y*size_z,sizeof(int));
  for(int k = 0; k<size_z; k++)
  {
    for (int j = 0; j<size_y; j++)
  	{
  		for (int i = 0; i<size_x; i++)
  		{
  			{
  				// crop initialization(element = start 1)
  				mat[k*size_x*size_y+j*size_x+i] = j+i+k;
  			}
  		}
  	}
  }
	return mat;
}

/*Write to txt loaded by python*/
int write_to_file(int count, int cols,int rows, int *data, char const *fileName)
{
  FILE *f = fopen(fileName, "w");
  if (f == NULL) return -1;
  int idx = 1;
  int x=cols,y=rows,z=cols;
  fprintf(f,"# Array shape: (%d, %d, %d)\n",z,y,x);

    for (int i=0;i<count;i++)
    {
        fprintf(f,"%d",data[i]); // data starts from 0-index
        if((idx%cols == 0)&&(idx%(cols*rows) != 0)) fprintf(f,"\n");
        else if(idx%(rows*cols) == 0) fprintf(f,"\n# New slice\n");
        //else fprintf(f,"   ");
        else fprintf(f,",");
        idx++;
    }
  fclose(f);
  return 0;
}

int * assemble_3d(int * image, int * crop, bool init_crop )
{
  int Bound_X=0,Bound_Y=0,Bound_Z=0;
  int * passing_value(int * image, int * crop, int Bound_X,int Bound_Y,int Bound_Z,int i ,int j,int k);
  int size_init = 128;
  bool init_crop_z = true;
  //FILE * f=fopen("prin.txt","w");
	if (crop == NULL || image == NULL) exit(1);
	for(int k=0; k<Z; k+=K)
	{
		if(init_crop_z&&(k!=0))
		{
			k=(M-K);
			init_crop_z=false;
			//printf("chanegedZ");
			continue;
		}
		init_crop = true;
		for(int j=0; j<Y; j+=J)
		// if only both step sizes are identical, it's easier...
		{
			if(init_crop&&(j!=0))
			{
				j=(M-J);
				init_crop=false;
				//printf("chaneged");
				continue;
			}
			for (int i=0; i<X; i+=I)
			{
				
        	if(((i==0)+(j==0)+(k==0)) == 3) // init crop
				{
					Bound_X = RES_X;
					Bound_Y = RES_Y;
					Bound_Z = RES_Z;
				//	fprintf(f,"all: %d,%d,%d\tp:%d,q:%d,m:%d\n",i,j,k,Bound_X,Bound_Y,Bound_Z);
					i=(M-I);
					continue;
				} // 128*128 initial
        
				else if((((i<128)+(j<128)+(k<128)) < 3)&&(((i<128)+(j<128)+(k<128)) != 0))	   // either one of axis < 128
				{
					i<size_init ? (Bound_X = RES_X) : (Bound_X = 0); // on YZ axis
					j<size_init ? (Bound_Y = RES_Y) : (Bound_Y = 0); // on XZ axis
					k<size_init ? (Bound_Z = RES_Z) : (Bound_Z = 0); // on XY axis
				//	fprintf(f,"either: %d,%d,%d\tp:%d,q:%d,m:%d\n",i,j,k,Bound_X,Bound_Y,Bound_Z);
					continue;
		
				}
       			else if(((i<128)+(j<128)+(k<128)) == 3) continue;
				else Bound_Y=Bound_X=Bound_Z=0;
       			//fprintf(f,"none: %d,%d,%d\tp:%d,q:%d,m:%d\n",i,j,k,Bound_X,Bound_Y,Bound_Z);
				image = passing_value(image,crop,Bound_X,Bound_Y,Bound_Z,i,j,k);
			}
		}
	}
  //fclose(f);
	return image;
}


int * passing_value(int * image, int * crop, int Bound_X,int Bound_Y,int Bound_Z,int i ,int j,int k)
{
  for(int m=0;m<K+Bound_Z;m++)
  {
    for(int q=0;q<J+Bound_Y;q++) // y_step
    {
      for(int p=0;p<I+Bound_X;p++) // x_step
      {
        image[(m+k)*(X*Y)+(q+j)*X+i+p] = crop[M*M*(m+RES_Z)+M*((RES_Y-Bound_Y)+q)+(RES_X-Bound_X)+p];
      }
    }
  }
	return image;
}
