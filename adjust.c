#include<stdio.h>
#include<stdlib.h>

typedef struct SortArray sArray;
typedef struct BTree* BTnode;
struct BTree {

	int formerNum;
	int nowNum;
	BTnode ochild;
	BTnode lchild;
	BTnode rchild;
};
struct SortArray {
	int num;
	int count;

};
int lrchildCount = 0;
sArray* sortArray;
BTnode createNode(int num);
BTnode searachTree(BTnode ptrl, int num);
BTnode createChildTree(BTnode ptrl, int inputNum[], int count);
BTnode inputProcess();
void bubbleSort();
int cmp(const void* a, const void* b);
void inputSort();
void showFinal(BTnode ptrl);
int main()
{
	BTnode ptrl = inputProcess();
	inputSort();
	showFinal(ptrl);
	return 0;
}

BTnode createNode(int num)
{
	BTnode ptrl = (BTnode)malloc(sizeof(struct BTree));
	ptrl->formerNum = num;
	ptrl->ochild = NULL;
	ptrl->lchild = NULL;
	ptrl->rchild = NULL;
	return ptrl;
}
BTnode searachTree(BTnode ptrl,int num)
{
	int tFront = -1,tRear = 0;
	BTnode TreeStack[256],temp = ptrl;
	TreeStack[++tFront] = temp;
	while (!( tFront>tRear&& temp == NULL))
	{
		temp = TreeStack[tFront++];
		if (temp != NULL)
		{
			if (temp->formerNum == num)
				return temp;
			else
			{
				TreeStack[++tRear] = temp->lchild;
				TreeStack[++tRear] = temp->ochild;
				TreeStack[++tRear] = temp->rchild;
			}
		}
	}

	return NULL;
}
BTnode createChildTree(BTnode ptrl, int inputNum[],int count)
{
	if (count == 4)
	{
		ptrl->lchild = createNode(inputNum[1]);
		ptrl->ochild = createNode(inputNum[2]);
		ptrl->rchild = createNode(inputNum[3]);
	}
	else if (count == 3)
	{
		ptrl->lchild = createNode(inputNum[1]);
		ptrl->rchild = createNode(inputNum[2]);
	}
	else if (count == 2)
	{
		ptrl->lchild = createNode(inputNum[1]);
	}
	return ptrl;
}
BTnode inputProcess()
{
	int inputCount = 0;
	int inputNum[5],tempNum = 0,iTop = -1;
	BTnode temp = NULL,ptrl = NULL;
	while (inputNum[0] != -1)
	{
		do
		{
			scanf("%d",&tempNum);
			if (tempNum > -1 && tempNum < 100)
				lrchildCount++;
			inputNum[++iTop] = tempNum;
		} while (tempNum!=-1);
		if (inputNum[0] != -1)
		{
			temp = searachTree(ptrl, inputNum[0]);
			if (temp == NULL)
			{
				ptrl = createNode(inputNum[0]);
				ptrl = createChildTree(ptrl, inputNum, iTop);
			}
			else
			{
				temp = createChildTree(temp, inputNum, iTop);
			}
		}
		iTop = -1;
	}
	return ptrl;
}
void inputSort()
{
	sortArray = (struct SortArray*)malloc(sizeof(sArray)* lrchildCount);
	for (int i = 0; i < lrchildCount; i++)
	{
		scanf("%d %d",&sortArray[i].num,&sortArray[i].count);
	}
	bubbleSort();
	//qsort(sortArray,lrchildCount,sizeof(sArray),cmp);
}
int cmp(const void* a, const void* b)
{
	return ((struct SortArray*)b)->count - ((struct SortArray*)a)->count;

}
void bubbleSort()
{
	sArray temp;
	for (int i = 0; i < lrchildCount - 1; i++)
	{
		for (int j = 0; j < lrchildCount - i - 1; j++)
		{
			if (sortArray[j].count < sortArray[j + 1].count||(sortArray[j].count == sortArray[j + 1].count)&&sortArray[j].num > sortArray[j + 1].num)
			{
				temp = sortArray[j];
				sortArray[j] = sortArray[j + 1];
				sortArray[j + 1] = temp;
			}
			
		}
	}

}
void showFinal(BTnode ptrl)
{
	int count = 0;
	int qfront = 0,qRear = 0;
	BTnode Queue[256],temp = ptrl;
	Queue[0] = ptrl;
	while (!(qfront > qRear && temp == NULL))
	{
		temp = Queue[qfront++];
		if (temp != NULL)
		{
			if (temp->formerNum < 100)
			{

				printf("%d->%d\n",sortArray[count].num, temp->formerNum);
				count++;
			}
			Queue[++qRear] = temp->lchild;
			Queue[++qRear] = temp->ochild;
			Queue[++qRear] = temp->rchild;
		}

	}


}




