#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME_SIZE 21

typedef struct node {
	int studNum;
	char name[MAX_NAME_SIZE];
	int chairNum;
}Node, * Pnode;
typedef struct stu {
	Pnode head;
}Stu, * pStu;

pStu ptrl = NULL;
int n = 0, maxChairNum = 0, stuCount = 0;
int hash[101] = { 0 };
Pnode createNode(int stuNum, char name[], int chairNum);
void readTextFromFile();
void writeTextToFile();
void bubbleSort();
void bubbleSortForStu();
void checkPtrlOne();
void checkPtrlTwo();
int maxNum();
int main()
{

	scanf("%d", &n);
	ptrl = (pStu)malloc(sizeof(Stu) * n);
	readTextFromFile();
	bubbleSort();
	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%d %s %d\n", ptrl[i].head->studNum, ptrl[i].head->name, ptrl[i].head->chairNum);
	checkPtrlOne();

	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%d %s %d\n", ptrl[i].head->studNum, ptrl[i].head->name, ptrl[i].head->chairNum);
	checkPtrlTwo();
	bubbleSortForStu();
	writeTextToFile();

	return 0;
}
void bubbleSortForStu()
{
	Pnode temp = NULL;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (ptrl[j].head->studNum > ptrl[j + 1].head->studNum)
			{
				temp = ptrl[j].head;
				ptrl[j].head = ptrl[j + 1].head;
				ptrl[j + 1].head = temp;
			}

		}
	}


}
void checkPtrlTwo()
{
	int x = 1;
	int q = maxNum();

	for (int i = 0; i < stuCount; i++)
	{
		if (hash[ptrl[i].head->chairNum] > 0)
		{
			ptrl[i].head->chairNum = q + x;
			x++;
		}
		else
		{
			hash[ptrl[i].head->chairNum]++;
		}
	}
}
int maxNum()
{
	int maxChairNum = 0;
	for (int i = 0; i < stuCount; i++)
	{
		maxChairNum = (maxChairNum > ptrl[i].head->chairNum) ? maxChairNum : ptrl[i].head->chairNum;
	}
	return maxChairNum;
}
void checkPtrlOne()
{
	int temp = stuCount;
	int q = maxNum();
	q = q > n ? n : q;
	for (int i = 0; i < stuCount; i++)
		hash[ptrl[i].head->chairNum]++;
	for (int i = 1; i <= q; i++)
	{
		q = maxNum();
		q = q > n ? n : q;
		if (hash[i] == 0)
		{
			ptrl[--temp].head->chairNum = i;
		}
	}
	memset(hash, 0, sizeof(hash));
}
void bubbleSort()
{
	Pnode temp = NULL;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (ptrl[j].head->chairNum > ptrl[j + 1].head->chairNum)
			{
				temp = ptrl[j].head;
				ptrl[j].head = ptrl[j + 1].head;
				ptrl[j + 1].head = temp;
			}
			else if (ptrl[j].head->chairNum == ptrl[j + 1].head->chairNum && ptrl[j].head->studNum > ptrl[j + 1].head->studNum)
			{
				temp = ptrl[j].head;
				ptrl[j].head = ptrl[j + 1].head;
				ptrl[j + 1].head = temp;
			}

		}
	}


}
Pnode createNode(int stuNum, char name[], int chairNum)
{
	Pnode pptrl = (Pnode)malloc(sizeof(Node));
	strcpy(pptrl->name, name);
	pptrl->chairNum = chairNum;
	pptrl->studNum = stuNum;
	return pptrl;
}
void readTextFromFile()
{
	int stuNum = 0, chairNum = 0;
	char name[MAX_NAME_SIZE];
	FILE* fp = fopen("in.txt", "r");
	if (fp == NULL)
	{
		printf("打开文件失败");
		return;
	}
	while (fscanf(fp, "%d %s %d", &stuNum, name, &chairNum) == 3)
	{
		maxChairNum = (maxChairNum < chairNum) ? chairNum : maxChairNum;
		ptrl[stuCount++].head = createNode(stuNum, name, chairNum);
	}
	fclose(fp);
}
void writeTextToFile()
{
	FILE* fp = fopen("out.txt", "w");
	if (fp == NULL)
	{
		printf("打开文件失败");
		return;
	}
	for (int i = 0; i < n; i++)
		fprintf(fp, "%d %s %d\n", ptrl[i].head->studNum, ptrl[i].head->name, ptrl[i].head->chairNum);
	fclose(fp);
}
int searchChairNum(int  Chairnum)
{
	int left = 0, mid = 0, right = stuCount - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (ptrl[mid].head->chairNum == Chairnum)
			return 1;
		else if (ptrl[mid].head->chairNum > Chairnum)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return 0;
}
