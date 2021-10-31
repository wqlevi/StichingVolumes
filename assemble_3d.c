/*
 *  Mainly updated version of 3D stitching
 *  Author : Qi Wang
 */


#include <stdio.h>
#include <stdlib.h>

#define M 128

#define X 512
#define Y 698
#define Z 640
#define I 16*2 // step size x,z
#define J 15*2 // step size y
#define RES_X 128-I // overlapped length x,z
#define RES_Y 128-J


int main()
{
  int * make_sample(int size_x, int size_y, _Bool zeros);
	int write_to_file(int count, int col, int *data, char const *fileName);
	int * assemble_2d(int * image, int * crop , bool asym);

	int *crop,*image;
	bool asym;
	crop = make_sample(M,M,M,0);// crop
	//image = make_sample(X,Y,1); // image
	//image = assemble_2d(image,crop,asym);
	//write_to_file(X*Y,X,image,"example.csv");
	write_to_file( M*M,M,crop,"example_crop.csv");

	return 0;
}


int * make_sample(int size_x, int size_y, int size_z, _Bool zeros){
	/*
	 * This creates a dummy 2D crop
	 */
	int *mat;
	mat = malloc(sizeof(int)*size_x*size_y*size_z);
  for(int k = 0; k<size_z; k++)
  {
    for (int j = 0; j<size_y; j++)
  	{
  		for (int i = 0; i<size_x; i++)
  		{
  			if(zeros)
  			{
  				mat[i*size_x+j] = 0; // for image allocation
  			}
  			else
  			{
  				// crop initialization(element = start 1)
  				mat[k*size_x*size_y+j*size_x+i] = j+i+k;
  			}
  		}
  	}
  }
	return mat;
}


/* Writting image to csv*/
int write_to_file(int count, int col, int *data, char const *fileName)
{
  FILE *f = fopen(fileName, "w");
  if (f == NULL) return -1;
  int idx = 1;
	for (int i=0;i<count;i++) {
	fprintf(f,"%d",data[i]); // data starts from 0-index
	if(idx%col == 0) fprintf(f,"\n");
	else fprintf(f,",");
	idx++;
  }
  fclose(f);
  return 0;
}
