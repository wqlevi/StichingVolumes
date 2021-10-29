#include <stdio.h>
#define M 128
#define S 512
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
	for (int i = M; i<S; i+=16*2) // 64,64+16,64+2*16
	{
//		printf("%d\n",i);
		for (int j=16*2; j<M;j++) 
		{
		tmp[i+j-16*2] = arr[j];
		}
	}	
	/* inspect values */
	for (int i=0;i<S;i++)
	{
	printf("the %dth element is %d\n",i,tmp[i]);
	}
	
	return 0;
}
