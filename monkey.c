#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main()
{
	int* ptrl;
	int n, m, q,index=0;
	int count;
	scanf("%d %d %d",&n,&m,&q);
	count = n;
	ptrl = (int*)malloc(sizeof(int)* n);
	for (int i = 0; i < n; i++)
		ptrl[i] = 1;
	index = q -1;
	while (count > 1)
	{
		for (int i = 0; i < m-1; i++)
		{
			if (ptrl[index] == 0)
			{
				i--;
			}
			index++;
			if (index >= n)
				index = 0;
		}
		while (ptrl[index] == 0)
		{
			index++;
			if (index >= n)
				index = 0;
		}
		ptrl[index] = 0;
		count--;
		index++; if (index >= n)
			index = 0;
	}
	for (int i = 0; i < n; i++)
	{
		if (ptrl[i] > 0)
		{
			printf("%d",i + 1);
		}
	}
return 0;
}
