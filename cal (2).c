#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Btree* BTnode;
typedef struct Mstack mstack;
struct Btree {
	int jIndex;
	char chr;
	int num;
	BTnode lchild;
	BTnode rchild;
};
struct Mstack {
	int jIndex;
	char chr;
	int num;
};

mstack finalStack[256];
char chrStack[256];

int fTop = -1, cTop = -1;
void addItemToFianlStack(int num, char chr, int mode);
void addChrToChrStack(char chr);
char pushStack();
void chrProcess(char chr);
void showFinalStack();//²âÊÔ
int calFinal();
void showFinalResults(BTnode ptrl,int finalAnswer);
void strProcess(char inputStr[]);
BTnode treeProcess();
BTnode createNode(int num, char chr, int mode, BTnode lch, BTnode rch);
void showNode(BTnode ptrl);
int main()
{
	BTnode finalPtrl = NULL;
	int finalAnswer = 0;
	char inputStr[256];
	gets(inputStr);
	strProcess(inputStr);
	//showFinalStack();
	finalAnswer = calFinal();
	finalPtrl = treeProcess();
	showFinalResults(finalPtrl,finalAnswer);
	return 0;
}
void showNode(BTnode ptrl)
{ 
	if (ptrl->jIndex == 1)
	{
		printf("%d", ptrl->num);
	}
	else
	{
		printf("%c", ptrl->chr);
	}

}
void showFinalResults(BTnode ptrl, int finalAnswer)
{
	if (ptrl != NULL)
	{
		showNode(ptrl);
		if (ptrl->lchild != NULL)
		{
			printf(" ");
			showNode(ptrl->lchild);
		}
		if (ptrl->rchild != NULL)
		{
			printf(" ");
			showNode(ptrl->rchild);
		}

	}
	printf("\n%d\n",finalAnswer);
}
void addItemToFianlStack(int num,char chr,int mode)
{
	finalStack[++fTop].jIndex = mode;
	if (mode == 1)//Êý×Ö
		finalStack[fTop].num = num;
	else if (mode == 2)//×Ö·û
		finalStack[fTop].chr = chr;
}
void addChrToChrStack(char chr)
{
	chrStack[++cTop] = chr;
}
char pushStack()
{
	return chrStack[cTop--];
}
//²âÊÔ
void showFinalStack()
{
	for (int i = 0; i <= fTop; i++)
	{
		if (finalStack[i].jIndex == 1)
			printf("%d", finalStack[i].num);
		else if (finalStack[i].jIndex == 2)
			printf("%c",finalStack[i].chr);
	}
	printf("\n");
}
void chrProcess(char chr)
{

	if (chr == '(')
		addChrToChrStack(chr);
	else if (chr == ')')
	{
		while (chrStack[cTop] != '(')
			addItemToFianlStack(0,pushStack(),2);
		pushStack();
	}
	else if (chr == '+' || chr == '-')
	{
		if (cTop == -1||chrStack[cTop] =='(')
			addChrToChrStack(chr);
		else
		{
			while (cTop > -1 && chrStack[cTop] != '(')
				addItemToFianlStack(0,pushStack(),2);
			addChrToChrStack(chr);
		}

	}
	else if (chr == '*' || chr == '/')
	{
		if (cTop == -1 || chrStack[cTop] == '('|| chrStack[cTop] == '+' || chrStack[cTop] == '-')
			addChrToChrStack(chr);
		else
		{
			while (cTop > -1 && chrStack[cTop] != '('&&chrStack[cTop]!='+'&&chrStack[cTop]!='-')
				addItemToFianlStack(0, pushStack(), 2);
			addChrToChrStack(chr);
		}
	}
}
void strProcess(char inputStr[])
{
	int temp_num = 0,temp_index = 0;
	for (int i = 0; i < strlen(inputStr); i++)
	{
		if (inputStr[i] == ' ')
			continue;
		if (isdigit(inputStr[i]))
		{
			temp_num = temp_num * 10 + inputStr[i] - '0';
			temp_index = 1;
		}
		else if (!isdigit(inputStr[i]))
		{
			if (temp_index == 1)
			{
				addItemToFianlStack(temp_num,0,1);//Êý×Ö
				temp_index = 0;
				temp_num = 0;
			}
			chrProcess(inputStr[i]);
		}
	}
	while (cTop > -1)
	{
		addItemToFianlStack(0,pushStack(),2);
	}
}
int calFinal()
{
	int tempStack[256],tTop = -1;
	int tempOne = 0, tempTwo = 0;
	for (int i = 0; i <= fTop; i++)
	{
		if (finalStack[i].jIndex == 1)
		{
			tempStack[++tTop] = finalStack[i].num;
		}
		else
		{
			tempOne = tempStack[tTop--];
			tempTwo = tempStack[tTop--];
			switch (finalStack[i].chr)
			{
			case '+':
				tempStack[++tTop] = tempOne + tempTwo;
				break;
			case '-':
				tempStack[++tTop] = tempTwo - tempOne;
				break;
			case '/':
				tempStack[++tTop] = tempTwo / tempOne;
				break;
			case '*':
				tempStack[++tTop] = tempOne * tempTwo;
				break;
			}
		}
	}
	return tempStack[0];
}
BTnode createNode(int num, char chr, int mode,BTnode lch,BTnode rch)
{
	BTnode ptrl = (BTnode)malloc(sizeof(struct Btree));
	ptrl->jIndex = mode;
	if (mode == 1)
		ptrl->num = num;
	else if (mode == 2)
		ptrl->chr = chr;
	ptrl->lchild = lch;
	ptrl->rchild = rch;
	return ptrl;
}
BTnode treeProcess()
{
	int tTop = -1;
	BTnode tempStack[256],temp = NULL,tempOne = NULL,tempTwo =NULL;
	for (int i = 0; i <= fTop; i++)
	{
		if (finalStack[i].jIndex == 1)
		{
			temp = createNode(finalStack[i].num, 0, 1,NULL,NULL);
			tempStack[++tTop] = temp;
		}
		else if (finalStack[i].jIndex == 2)
		{
			tempOne = tempStack[tTop--];
			tempTwo = tempStack[tTop--];
			temp = createNode(0,finalStack[i].chr,2,tempTwo,tempOne);
			tempStack[++tTop] = temp;
		}
	}
	return tempStack[0];
}







