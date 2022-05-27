#include<stdio.h>
#include<stdlib.h>


int* num = NULL;
int allcount = 0;
void selectSort(int count);
void adjust( int i, int n);
void bubbleSort(int count);
void heapSort(int count);
void swap(int* a, int* b);
void quickSort(int k[], int left, int right);
void mPass(int x[], int y[], int n, int t);
void mergeSort(int count);
void merge(int x[], int tmp[], int left, int leftend, int rightend);
int main()
{
	int count, mode;
	scanf("%d %d", &count, &mode);
	num = (int*)malloc(sizeof(int) * count);
	for (int i = 0; i < count; i++)
	{
		scanf("%d", &num[i]);
	}
	//printf("\n%d %d\n",count,mode);
	//for (int i = 0; i < count; i++)
	//{
	//	printf("%d ", num[i]);
	//}
	switch (mode)
	{
	case 1:
		selectSort(count);
		break;
	case 2:
		bubbleSort(count);
		break;
	case 3:
		heapSort(count);
		break;
	case 4:
		mergeSort(count);
		break;
	case 5:
		quickSort(num, 0, count - 1);
		break;
	}
	for (int i = 0; i < count; i++)
	{
		printf("%d", num[i]);
		if (i != count - 1)
			printf(" ");
	}
	printf("\n%d\n", allcount);
}
void selectSort(int count)
{

	int lowest = 0, temp = 0;
	for (int i = 0; i <= count - 1; i++)
	{
		lowest = i;
		for (int j = i + 1; j <= count - 1; j++)
		{
			allcount++;
			if (num[j] < num[lowest])
			{

				lowest = j;
			}
			
		}
		if (lowest != i)
			{
				temp = num[lowest];
				num[lowest] = num[i];
				num[i] = temp;
			}
	}
}
void bubbleSort(int count)
{
	int flag = 0, temp = 0;
	for (int i = 0; i < count - 1; i++)
	{
		flag = 0;
		for (int j = 0; j < count - i - 1; j++)
		{
			allcount++;
			if (num[j] > num[j + 1])
			{
				flag = 1;
				temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
		if (flag == 0)
			break;
	}



}
void adjust( int i, int n)
{
	int j, temp;
	temp = num[i];
	j = 2 * i + 1;
	while (j < n) {
		allcount++;
		if (j < n-1 && num[j] < num[j + 1])
			j++;
		if (temp >= num[j])
			break;
		num[(j-1) / 2] = num[j];
		j = 2 * j + 1;
	}
	num[(j-1) / 2] = temp;
}
void heapSort(int count)
{
	int i;
	int temp = 0;
	for (i = count / 2 - 1; i >=0; i--)
	{
		adjust(i,count);
	}
	for (i = count - 1; i >= 1; i--)
	{
		temp = num[i];
		num[i] = num[0];
		num[0] = temp;
		adjust(0,i);
	}

}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void quickSort(int k[], int left, int right)
{
	int i, last;
	if (left < right) {
		last = left;
		for (i = left + 1; i <= right; i++)
		{
			allcount++;
			if (num[i] < num[left])
				swap(&k[++last], &k[i]);
		}
			swap(&k[left], &k[last]);
		quickSort(k, left, last - 1);
		quickSort(k, last + 1, right);

	}

}
void merge(int x[], int tmp[], int left, int leftend, int rightend)
{
	int i = left, j = leftend + 1, q = left;
	while (i <= leftend && j <= rightend)
	{
		allcount++;
		if (x[i] <= x[j])
			tmp[q++] = x[i++];
		else
			tmp[q++] = x[j++];
	}
	while (i <= leftend)
		tmp[q++] = x[i++];
	while (j <= rightend)
		tmp[q++] = x[j++];
	for (i = left; i <= rightend; i++)
		x[i] = tmp[i];
}
void mergeSort(int count)
{
	int* tmp;
	tmp = (int*)malloc(sizeof(int)* count);
	if (tmp != NULL)
	{
		mPass(num, tmp, 0, count - 1);
		free(tmp);
	}

}
void mPass(int x[], int y[], int n, int t)
{
	int center;
	if (n < t)
	{
		center = (n + t) / 2;
		mPass(x,y,n,center);
		mPass(x,y,center + 1,t);
		merge(x, y, n, center, t);
	}
}
