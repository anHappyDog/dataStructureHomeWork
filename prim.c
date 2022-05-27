#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ver vertex, * pVertex;
struct ver {
	int id;
	int vertexNum;
	int weight;
	pVertex next;
};


pVertex neighVertex[100];
int vertexCount = 0, edgeCount = 0;
int answer[100];
pVertex addNodeToPtrl(pVertex ptrl, int id, int vertexNum, int weight);
pVertex createNode(int id, int vertexNum, int weight);
void bubblesort(int val[], int n);
void inputInfo();
void prim();
int main()
{
	inputInfo();
	prim();

}
void inputInfo()
{
	int tempOne = 0, tempTwo = 0, tempThree = 0, tempFour = 0;
	scanf("%d%d",&vertexCount,&edgeCount);
	for (int i = 0; i < edgeCount; i++)
	{
		scanf("%d%d%d%d",&tempOne,&tempTwo,&tempThree,&tempFour);
		if (neighVertex[tempTwo] == NULL)
			neighVertex[tempTwo] = createNode(-1,tempTwo,-1);
		if (neighVertex[tempThree] == NULL)
			neighVertex[tempThree] = createNode(-1,tempThree,-1);
		neighVertex[tempTwo]->next = addNodeToPtrl(neighVertex[tempTwo]->next,tempOne,tempThree,tempFour);
		neighVertex[tempThree]->next = addNodeToPtrl(neighVertex[tempThree]->next,tempOne,tempTwo,tempFour);
	}
}
void bubblesort(int val[], int n)
{
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (val[j] > val[j + 1])
			{
				val[j] ^= val[j + 1];
				val[j + 1] ^= val[j];
				val[j] ^= val[j + 1];
			}
		}
	}

}
pVertex addNodeToPtrl(pVertex ptrl, int id, int vertexNum, int weight)
{
	pVertex temp = NULL,tempOne = NULL;
	if (ptrl == NULL)
	{
		temp = createNode(id,vertexNum,weight);
		return temp;
	}
	temp = ptrl;
	if (temp->weight > weight)
	{
		tempOne = createNode(id,vertexNum,weight);
		tempOne->next = temp;
		ptrl = tempOne;
		return ptrl;
	}
	while (temp->next != NULL && temp->next->weight < weight)
		temp = temp->next;
	tempOne = createNode(id,vertexNum,weight);
	tempOne->next = temp->next;
	temp->next = tempOne;
	return ptrl;
}
pVertex createNode(int id, int vertexNum, int weight)
{
	pVertex ptrl = (pVertex)malloc(sizeof(vertex));
	ptrl->id = id;
	ptrl->vertexNum = vertexNum;
	ptrl->weight = weight;
	ptrl->next = NULL;
	return ptrl;

}
void prim()
{
	pVertex temp = NULL;
	int includedVer[100] = { 0 };
	int allWeight = 0;
	int usedVer[100] = { 0 };
	int includedCount = 1,top = 0,minWeight = 100000000,minVer = -1,minId = -1,selectedVer = -1;
	//nt lowcost[100], tend[100];
	usedVer[0] = 1;
	for (int i = 0; i < vertexCount - 1; i++)
	{
		minWeight = 100000000;
		minVer = -1;
		minId = -1;
		selectedVer = -1;
		for (int j = 0; j < includedCount; j++)
		{
		
			temp = neighVertex[includedVer[j]]->next;
			
			while (temp !=NULL&&usedVer[temp->vertexNum] == 1)
				temp = temp->next;
			if (temp != NULL)
			{
				if (minWeight > temp->weight)
				{
					minWeight = temp->weight;
					minVer = temp->vertexNum;
					minId = temp->id;
					selectedVer = j;
				}
			}
		}
		includedVer[includedCount++] = minVer;
		usedVer[minVer] = 1;
		//printf("%d ",minId);
		allWeight += minWeight;
		answer[top++] = minId;
		//neighVertex[selectedVer]->next = deleteNode(neighVertex[selectedVer]->next,minId);
		//neighVertex[minVer]->next = deleteNode(neighVertex[minVer]->next,selectedVer);
		//继续处理邻接表使之仍然有序
	}
	bubblesort(answer,top);
	printf("%d\n",allWeight);
	for (int i = 0; i < top; i++)
	{
		printf("%d ",answer[i]);
	}

}
