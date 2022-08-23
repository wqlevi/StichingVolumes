#include <stdlib.h>
#include <stdio.h>
#define M 128
#define N 128

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
/*
 * 128*128*128 takes 1.3 sec
 * 512*698*512 takes 31.5 sec
 */

int main()
{   
    int write_to_file(int count, int col,int rows, int *data, char const *fileName);
    int * make_sample(int size_x, int size_y, int size_z, _Bool zeros);
    int *image;
	int * assemble(int * image);
    //crop = make_sample(M,N,M,1);
    
//**************
	bool asym;
	image = make_sample(X,Y,Z,0);
	image = assemble(image);
	write_to_file(X*Y*Z,X,Y,image,"example.txt");
	free(image);
  //***********
    return 0;
}


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
  free(data);
  return 0;
}

int * make_sample(int size_x, int size_y, int size_z, _Bool zeros)
{
	/*
	 * This creates a dummy 3D crop
	 */
	int *mat;
	mat = calloc(size_x*size_y*size_z,sizeof(int));
	if(zeros)
	{
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
	}
	return mat;
}

int * assemble(int * image)
{
	bool asym_y,asym_z;
	asym_y = asym_z = true;
	int Bound_X=0,Bound_Y=0,Bound_Z=0;
	FILE *f = fopen("print_image.txt", "w");
    for(int k=0; k<Z; k+=K)
	{
		asym_y=true;
		if(asym_z&&(k!=0))
		{
			k=M;
			asym_z=false;

		}
		for(int j=0; j<Y; j+=J)
		// if only both step sizes are identical, it's easier...
		{
			// a patch that works for temporal asymetric matrix, by jumping loop idx
			if(asym_y&&(j!=0)) // BUG here
			{
				j=M;
				asym_y=false;
			}
			for (int i=0; i<X; i+=I)
			{
				if((i<128)&&(j<128)&&(k<128)) continue; // 128*128 initial
				else if((((i<128)+(j<128)+(k<128)) < 3)&&(((i<128)+(j<128)+(k<128)) !=0))	   // either one of axis < 128
				{
					fprintf(f,"surface\n");
					if(j<128) Bound_Z =	RES_Z; // on Z axis
					if(i<128) Bound_X = RES_X; // on Y axis
					if(j<128) Bound_Y =	RES_Y; // on X axis
				}
				else Bound_Y=Bound_X=Bound_Z=0;

				fprintf (f,"x:%d,y:%d,z:%d\n",i,j,k);
				fprintf(f,"%d\n",((i<128)+(j<128)+(k<128)));

				
				for(int m=0;m<K+Bound_Z;m++)
				{
					for(int q=0;q<J+Bound_Y;q++) // y_step
					{
						for(int p=0;p<I+Bound_X;p++) // x_step
						{
							//image[(m+k)*(X*Y)+(q+j)*X+i+p] = crop[M*M*(m+RES_Z)+M*((RES_Y-Bound_Y)+q)+(RES_X-Bound_X)+p];
							image[(m+k)*(X*Y)+(q+j)*X+i+p] = 1;
						}
					}
				}
				

			}
		}
	}
	fclose (f);
	free(f);
	return image;
}