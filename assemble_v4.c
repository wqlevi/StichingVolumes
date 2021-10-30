#include <stdio.h>
#define M 128
#define S 512
#define X 16*2
/*
 * This is a 1D demo
 */
int main()
{
	int tmp[S];
	int arr[M];
	int num=1;
	/* create sample crop*/
	for (int i=0; i<M; i++)
	{
	arr[i] = num;
	num++;
	}
	/* leave first crop zeros*/
	for (int i = 0;i<M;i++)
	{
	tmp[i] = 0;
	}
	/* appending along 1D */
	for (int i = M; i<S; i+=X) // 128,128+32,128+2*32
	{
//		printf("%d\n",i);
		for (int j=0; j<X;j++) 
		{
			tmp[i+j] = arr[M-X+j];
		}
	}	
	/* inspect values */
	for (int i=0;i<S;i++)
	{
	printf("the %dth element is %d\n",i,tmp[i]);
	}
	
	return 0;
}
