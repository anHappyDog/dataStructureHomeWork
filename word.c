#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_WORD_SIZE 128

typedef struct BTree* BTnode;
struct BTree {
	char data[MAX_WORD_SIZE];
	int count;
	BTnode lchild;
	BTnode rchild;
};

BTnode createTree(BTnode ptrl, char m_data[]);
BTnode readFile(BTnode ptrl);
void showFinal(BTnode ptrl);
void readTree(BTnode ptrl);
BTnode createNode(char mdata[]);
int main()
{
	BTnode ptrl = NULL;
	ptrl = readFile(ptrl);
	showFinal(ptrl);
	return 0;
}
BTnode createNode(char mdata[])
{
	BTnode ptrl = (BTnode)malloc(sizeof(struct BTree));
	//ptrl->data = mdata;
	strcpy(ptrl->data,mdata);
	ptrl->count = 1;
	ptrl->lchild = NULL;
	ptrl->rchild = NULL;
	return ptrl;
}
BTnode createTree(BTnode ptrl, char m_data[])
{
	if (ptrl == NULL)
	{
		ptrl = createNode(m_data);
		return ptrl;
	}
	if (strcmp(ptrl->data, m_data) == 0)
		ptrl->count++;
	else if (strcmp(ptrl->data, m_data) > 0)
		ptrl->lchild = createTree(ptrl->lchild, m_data);
	else
		ptrl->rchild = createTree(ptrl->rchild, m_data);
	return ptrl;
}
void readTree(BTnode ptrl)
{


	if (ptrl != NULL)
	{
		readTree(ptrl->lchild);
		printf("%s %d\n", ptrl->data, ptrl->count);
		readTree(ptrl->rchild);
	}


}
void showFinal(BTnode ptrl)
{
	int l = 0;
	BTnode temp = ptrl;
	while (temp)
	{
		l++;
		temp = temp->rchild;
	}
	l = l > 3 ? 3 : l;
	temp = ptrl;
	for (int i = 0; i < l; i++)
	{
		printf("%s", temp->data);
		if (i < l - 1)
			printf(" ");
		else
			printf("\n");
		temp = temp->rchild;
	}
	readTree(ptrl);
}
BTnode readFile(BTnode ptrl)
{
	int top = 0;
	char temp_chr;
	char temp_word[MAX_WORD_SIZE];
	FILE* articleFile = fopen("article.txt", "r");
	if (articleFile == NULL)
	{
		printf("´ò¿ªÊ§°Ü!\n");
		return NULL;
	}
	while (!feof(articleFile))
	{
		temp_chr = fgetc(articleFile);
		if (isalpha(temp_chr))
		{
			temp_chr = tolower(temp_chr);
			temp_word[top++] = temp_chr;
		}
		else if (!isalpha(temp_chr) && top > 0)
		{
			temp_word[top] = '\0';
			ptrl = createTree(ptrl, temp_word);
			top = 0;
		}
	}
	if (top > 0)
	{
		temp_word[top] = '\0';
		ptrl = createTree(ptrl, temp_word);
		top = 0;
	}
	return ptrl;
}
