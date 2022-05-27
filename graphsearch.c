#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ver vertex, * pVertex;
struct ver {

	int num;
	pVertex next;
};

pVertex queue[101];
pVertex neighVertex[101];
int vertexHash[101];
int vertexCount = 0, edgeCount = 0, vertexDelete = 0;
int front = 0, rear = 0;

void inputInfo();
void dfs();
void deleteVertex();
pVertex createNode(int num);
void vertexDfs(pVertex ptrl[], int v);
void bfs();
void vertexBfs(pVertex ptrl[], int v);
int main()
{

	inputInfo();
	dfs();
	bfs();
	deleteVertex();
	dfs();
	bfs();
	return 0;
}
void vertexBfs(pVertex ptrl[], int v)
{
	int x;
	pVertex temp = NULL,tempOne = NULL;
	if (ptrl[v] == NULL)
		return;
	if (vertexHash[v] == 0)
	{
		printf("%d ", v);
		vertexHash[v] = 1;
	}
	temp = neighVertex[v]->next;
	while (temp != NULL)
	{
		if (vertexHash[temp->num] == 0)
		{
			printf("%d ",temp->num);
			vertexHash[temp->num] = 1;
			queue[front++] = temp;
		}
		temp = temp->next;
	}
	while (rear < front)
	{
		temp = queue[rear++];
		vertexBfs(ptrl,temp->num);
	}
}
void bfs()
{
	memset(vertexHash,0,sizeof(vertexHash));
	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexHash[i] == 0)
		{
			vertexBfs(neighVertex,i);
		}
	}
	printf("\n");
}
void deleteVertex()
{
	pVertex prev = NULL, temp = NULL;
	for (int i = 0; i < vertexCount; i++)
	{
		if (i == vertexDelete)
		{
			prev = temp= neighVertex[i];
			while (temp != NULL)
			{
				prev = temp;
				temp = temp->next;
				free(prev);
				
			}
			neighVertex[i] = NULL;
		}
		else
		{
			temp = neighVertex[i];
			while (temp != NULL)
			{
				
				if (temp->num == vertexDelete)
				{
					prev->next = temp->next;
					free(temp);
					break;
				}
				prev = temp;
				temp = temp->next;
			}
		}
	}


}
void dfs()
{
	memset(vertexHash, 0, sizeof(vertexHash));
	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexHash[i] == 0)
		{
			vertexDfs(neighVertex, i);
		}
	}
	printf("\n");
}
void vertexDfs(pVertex ptrl[], int v)
{
	pVertex temp = NULL;
	if (ptrl[v] == NULL)
		return;
	if (vertexHash[v] == 0)
	{
		printf("%d ", v);
		vertexHash[v] = 1;
	}
	temp = ptrl[v]->next;
	while (temp != NULL)
	{
		if (vertexHash[temp->num] == 0)
		{
			printf("%d ", temp->num);
			vertexHash[temp->num] = 1;
			vertexDfs(ptrl,temp->num);
		}
		temp = temp->next;
	}
}
pVertex addNodeToVer(pVertex ptrl, int num)
{
	pVertex temp = NULL, tempOne = NULL;
	if (ptrl== NULL)
	{
		ptrl = createNode(num);
		return ptrl;
	}
	
	temp = ptrl;
	if (temp->num > num)
	{
		tempOne = createNode(num);
		tempOne->next = temp;
		ptrl = tempOne;
		return ptrl;
	}
	while (temp->next != NULL && temp->next->num < num)
		temp = temp->next;
	tempOne = createNode(num);
	tempOne->next = temp->next;
	temp->next = tempOne;
	return ptrl;
}
pVertex createNode(int num)
{
	pVertex ptrl = (pVertex)malloc(sizeof(vertex));
	ptrl->next = NULL;
	ptrl->num = num;
	return ptrl;
}
void inputInfo()
{
	int tempOne = 0, tempTwo = 0;
	scanf("%d%d", &vertexCount, &edgeCount);
	//printf("%d %d\n",vertexCount,edgeCount);
	
	for (int i = 0; i < edgeCount; i++)
	{
		scanf("%d%d", &tempOne, &tempTwo);
		//printf("%d %d\n",tempOne,tempTwo);
		//创建邻接表
		if (neighVertex[tempOne] == NULL)
			neighVertex[tempOne] = createNode(tempOne);
		neighVertex[tempOne]->next = addNodeToVer(neighVertex[tempOne]->next, tempTwo);
		if (neighVertex[tempTwo] == NULL)
			neighVertex[tempTwo] = createNode(tempTwo);
		neighVertex[tempTwo]->next = addNodeToVer(neighVertex[tempTwo]->next, tempOne);
	}
	scanf("%d", &vertexDelete);

}