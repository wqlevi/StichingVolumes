#include <stdio.h>

#define M 128

#define X 512
#define Y 698
#define I 16*2
#define J 15*2

int * make_sample(int size_x, int size_y, _Bool zeros){
	/*
	 * This creates a dummy 2D crop
	 */
	int *mat;
	mat = malloc(sizeof(int)*size_x*size_y);
	for (int i = 0; i<size_x; i++)
	{
		for (int j = 0; j<size_y; j++)
		{
			if(zeros)
			{
				mat[i*size_x+j] = 0; // for image allocation
			}
			else
			{
				mat[i*size_x+j] = i*size_x+j; // for crop initialization
			}
		}
	}	
	return mat;
}

int main()
{
	int *p,*img;
	p = make_sample(M,M,0);// crop
	img = make_sample(X,Y,1); // image
	for (int i=M; i<X; i+=(M-I))
	{
		for(int j=M; j<Y; j+=(M-J))
		{
//			printf("%d is %d\n",(i*M+j),img[i*M+j]);	
			printf("%d, %d\n",i,j);
		}
	}	
	return 0;
}
