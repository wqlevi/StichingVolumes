/*
 *  Mainly updated version of 2D stitching
 *  Author : Qi Wang
 */


#include <stdio.h>
#include <stdlib.h>

#define M 128

#define X 512
#define Y 698
#define I 16*2 // step size x(z)
#define J 15*2 // step size y
#define RES_X 128-I
#define RES_Y 128-J

typedef enum {false, true} bool;

int * make_sample(int size_x, int size_y, _Bool zeros){
	/*
	 * This creates a dummy 2D crop
	 */
	int *mat;
	mat = malloc(sizeof(int)*size_x*size_y);
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
				//mat[j*size_x+i] = j*size_x+i+1;
				mat[j*size_x+i] = j+i;
			}
		}
	}
	return mat;
}

int main()
{
	int write_to_file(int count, int col, int *data, char const *fileName);
	int * assemble_2d(int * image, int * crop , bool asym);
	int *crop,*image;
	bool asym;
	crop = make_sample(M,M,0);// crop
	image = make_sample(X,Y,1); // image
	//*************BEGIN
	int Bound_X=0,Bound_Y=0;
	if(I!=J) asym=true;
	image = assemble_2d(image,crop,asym);
	write_to_file(X*Y,X,image,"example.dat");
	write_to_file( M*M,M,crop,"example_crop.dat");

	return 0;
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

/* Assemblying function 2D*/
int * assemble_2d_old(int * image, int * crop, bool asym )
{
	int Bound_X=0,Bound_Y=0;

	if(crop == NULL || image == NULL) exit(1);
	for(int j=0; j<Y; j+=J)
	// if only both step sizes are identical, it's easier...
	{
		// a patch that works for temporal asymetric matrix, by jumping loop idx
		if(asym&&(j!=0))
		{
			j=M;
			asym=false;
		}
		for (int i=0; i<X; i+=I)
		{
			if((i<128)&&(j<128)) continue; // 128*128 initial
			else if((i<128)^(j<128))	   // either one of axis < 128
			{
				if(i<128) Bound_X = RES_X; // on Y axis
				if(j<128) Bound_Y = RES_Y; // on X axis
			}
			else Bound_Y=Bound_X=0;
			printf("%d,%d\n",i,j);
			for(int q=0;q<J+Bound_Y;q++) // y_step
			{
				for(int p=0;p<I+Bound_X;p++) // x_step
				{

					image[(q+j)*X+i+p] = crop[M*((RES_Y-Bound_Y)+q)+(RES_X-Bound_X)+p];
				}
			}


		}
	}
	return image;
}
int * assemble_2d(int * image, int * crop, bool asym )
{
	int * passing_value(int * image, int * crop, int Bound_X,int Bound_Y,int i, int j);

	int Bound_X=0,Bound_Y=0;
	int size_init = 128;
	if(crop == NULL || image == NULL) exit(1);
	for(int j=0; j<Y; j+=J)
	// if only both step sizes are identical, it's easier...
	{
		// a patch that works for temporal asymetric matrix, by jumping loop idx
		if(asym&&(j!=0))
		{
			j=M;
			asym=false;
		}
		for (int i=0; i<X; i+=I)
		{
			if((i<size_init)&&(j<size_init)) 
			{
				Bound_X = RES_X; // on Y axis
				Bound_Y = RES_Y;
				passing_value(image,crop,Bound_X,Bound_Y,i,j);
			} // 128*128 initial
			else if((i<size_init)^(j<size_init))	   // either one of axis < 128
			{
				if(i<size_init) Bound_X = RES_X; // on Y axis
				if(j<size_init) Bound_Y = RES_Y; // on X axis
				passing_value(image,crop,Bound_X,Bound_Y,i,j);
			}
			else 
			{
				Bound_Y=Bound_X=0;
				passing_value(image,crop,Bound_X,Bound_Y,i,j);
			}
			printf("%d,%d\n",i,j);
		}
	}
	return image;
}

int * passing_value(int * image, int * crop, int Bound_X,int Bound_Y,int i ,int j)
{
	for(int q=0;q<J+Bound_Y;q++) // y_step
	{
		for(int p=0;p<I+Bound_X;p++) // x_step
		{
			image[(q+j)*X+i+p] = crop[M*((RES_Y-Bound_Y)+q)+(RES_X-Bound_X)+p];
		}
	}
	return image;
}