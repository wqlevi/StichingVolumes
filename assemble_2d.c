#include <stdio.h>
#include <stdlib.h>

#define M 128

#define X 512
#define Y 698
#define I 16*2 // step size x(z)
#define J 15*2 // step size y
#define RES_X 128-I
#define RES_Y 128-J

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
				mat[j*size_x+i] = i*size_x+j; // for crop initialization
			}
		}
	}	
	return mat;
}

int main()
{
	int write_to_file(int count, int *data, char const *fileName); 

	int *crop,*img;
	crop = make_sample(M,M,0);// crop
	img = make_sample(X,Y,1); // image
	if(crop == NULL || img == NULL) exit(1);
	for(int j=M; j<Y; j+=J)
	{
		for (int i=M; i<X; i+=I)
		{
		//	printf("x is %d, y is %d \n",i,j);
		/* When crops are at x boundaries*/
		/* When crops are at y boundaries*/
		/* When crops are not at boundaries */

			for(int q=0;q<J;q++) // y_step
			{
				for(int p=0;p<I;p++) // x_step
				{
					img[(j+q)*X+i+p] = crop[M*((RES_Y)+q)+(RES_X)+p];
				
				}
			}
			
			
		}
	}	

	write_to_file(X*Y,img,"example.csv");
	return 0;
}
/* Writting image to csv*/
int write_to_file(int count, int *data, char const *fileName) 
{ 
  FILE *f = fopen(fileName, "w"); 
  if (f == NULL) return -1; 
  for (int i=0;i<count;i++) { 
    // you might want to check for out-of-disk-space here, too 
	fprintf(f,"%d\n",data[i]);
  } 
  fclose(f); 
  return 0; 
} 