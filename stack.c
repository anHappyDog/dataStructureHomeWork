#include<stdio.h>
#include<string.h>
#include<ctype.h>

int my_stack[100];
int top = -1;
void getNum(char inputStr[]);
int ifEmpty();
int ifFull();
int readNum(int i, char inputStr[]);
int main()
{
	char inputStr[128];
	gets(inputStr);
	getNum(inputStr);

	return 0;
}
int ifEmpty()
{
	return top == -1;
}
int ifFull()
{
	return top == 100;
}
void popStack()
{
	if (ifEmpty())
	{
		printf("error ");
		return;
	}
	printf("%d ", my_stack[top--]);
}
void pushStack(int num)
{
	if (ifFull())
	{
		printf("error ");
		return;
	}
	my_stack[++top] = num;
}
void getNum(char inputStr[])
{
	int ifminus = 1;
	int tempNum = 0;
	for (int i = 0; i < strlen(inputStr); i++)
	{

		if (isdigit(inputStr[i]))
		{
			tempNum = tempNum + inputStr[i] - '0';
		}
		else if (inputStr[i] == '-')
		{
			ifminus = -1;
		}
		else if (inputStr[i] == ' ')
		{
			tempNum *= ifminus;
			if (tempNum == 1)
			{
				pushStack( readNum(i + 1,inputStr));
			}
			else if (tempNum == 0)
			{
				popStack();
			}
			else if (tempNum == -1)
				exit(0);
			tempNum = 0;
			ifminus = 1;
		}
	}

}
int readNum(int i, char inputStr[])
{
	int ifminus = 1;
	int tempNum = 0;
	if (inputStr[i] == '-')
	{
		ifminus = -1;
		i++;
	}
	for (i; i < strlen(inputStr) && isdigit(inputStr[i]); i++)
	{
		tempNum = tempNum * 10 + inputStr[i] - '0';
	}
	tempNum *= ifminus;
	return tempNum;
}
