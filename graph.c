#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ver vertex, * pVertex;
 struct ver {
	
	int vertexNum;
	int edgeNum;
	pVertex next;
};

pVertex neighVertex[100];
int vertexHash[100];
int vertexCount = 0, edgeCount = 0;

void inputInfo();
pVertex createNode(int vertexNum,int edgeNum);
pVertex addNodeToVer(pVertex ptrl,int verNum,int edgeNum);
void dfs(pVertex ptrl[]);
void vertexDfs(pVertex ptrl[], int v,int matr[],int index);

int main()
{
	int temp[100];
	inputInfo();
	vertexDfs(neighVertex,0,temp,0);


	return 0;
}
void inputInfo()
{
	int tempOne = 0, tempTwo = 0, tempThree = 0;
	scanf("%d%d",&vertexCount,&edgeCount);
	for (int i = 0; i < edgeCount; i++)
	{
		scanf("%d%d%d",&tempOne,&tempTwo,&tempThree);
		if (neighVertex[tempTwo] == NULL)
			neighVertex[tempTwo] = createNode(tempTwo,-1);
		if (neighVertex[tempThree] == NULL)
			neighVertex[tempThree] = createNode(tempThree,-1);
		neighVertex[tempTwo]->next = addNodeToVer(neighVertex[tempTwo]->next,tempThree,tempOne);
		neighVertex[tempThree]->next = addNodeToVer(neighVertex[tempThree]->next,tempTwo,tempOne);
	}


}
pVertex addNodeToVer(pVertex ptrl,int verNum, int edgeNum)
{
	pVertex temp = ptrl,tempOne = NULL;
	if (temp == NULL)
	{
		ptrl = createNode(verNum,edgeNum);
		return ptrl;
	}
	if (temp->edgeNum > edgeNum)
	{
		tempOne = createNode(verNum,edgeNum);
		tempOne->next = temp;
		ptrl = tempOne;
		return ptrl;
	}
	while (temp->next != NULL && temp->next->edgeNum < edgeNum)
		temp = temp->next;
	tempOne = createNode(verNum,edgeNum);
	tempOne->next = temp->next;
	temp->next = tempOne;
	return ptrl;
}
pVertex createNode(int vertexNum,int edgeNum)
{
	pVertex ptrl = (pVertex)malloc(sizeof(vertex));
	ptrl->edgeNum = edgeNum;
	ptrl->vertexNum = vertexNum;
	ptrl->next = NULL;
	return ptrl;
}

void vertexDfs(pVertex ptrl[], int v,int matr[],int index)
{
	pVertex temp = ptrl[v]->next;
	vertexHash[v] = 1;
	if (v == vertexCount - 1)
	{
		for (int i = 0; i < index; i++)
			printf("%d ", matr[i]);
		printf("\n");
		return;
	}
	while (temp != NULL)
	{
		if (/*temp->vertexNum > v &&*/vertexHash[temp->vertexNum] == 0)
		{
			matr[index] = temp->edgeNum;
		
				/*	printf("%d ", temp->edgeNum);

			else
				printf("%d\n", temp->edgeNum);*/
			vertexHash[temp->vertexNum] = 1;
			vertexDfs(ptrl, temp->vertexNum,matr,index + 1);
			vertexHash[temp->vertexNum] = 0;
		}
		temp = temp->next;
	}
}
