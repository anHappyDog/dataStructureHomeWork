#include<stdio.h>
#include<stdlib.h>


typedef struct BTree* BTnode;
struct BTree {
	int data;
	BTnode lchild;
	BTnode rchild;
};

BTnode createNode(int mdata)
{
	BTnode ptrl = (BTnode)malloc(sizeof(struct BTree));
	ptrl->data = mdata;
	ptrl->rchild = NULL;
	ptrl->lchild = NULL;
	return ptrl;

}
BTnode createTree(BTnode ptrl, int n)
{
	if (ptrl == NULL)
	{
		ptrl =createNode(n);
		return ptrl;
	}
	if (n < ptrl->data)
		ptrl->lchild = createTree(ptrl->lchild,n);
	else
		ptrl->rchild = createTree(ptrl->rchild,n);
	return ptrl;

}
void readTree(BTnode ptrl, int n)
{
	if (ptrl->lchild == NULL && ptrl->rchild == NULL)
	{
		printf("%d %d\n",ptrl->data,n);
	}
	if (ptrl->lchild != NULL)
	{
		readTree(ptrl->lchild,n + 1);
	}
	if (ptrl->rchild != NULL)
	{
		readTree(ptrl->rchild,n + 1);
	}


}
int main()
{
	BTnode ptrl = NULL;
	int n,m;
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&m);
		ptrl = createTree(ptrl,m);
	}
	readTree(ptrl,1);
	return 0;
}
