#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TOP_SIZE 256
#define MAX_NAME_SIZE 128
typedef struct strPnode strName;
typedef struct strPStack strForStack;
struct strPnode {
	char name[MAX_NAME_SIZE];
	int  usedFunction[MAX_TOP_SIZE];
	int usedFunctionCount;

};
struct strPStack {
	char name[MAX_TOP_SIZE];
	int stackLocation;
};
//char strName[MAX_TOP_SIZE][MAX_NAME_SIZE];
//char strStack[MAX_TOP_SIZE][MAX_NAME_SIZE];
strName str[MAX_TOP_SIZE];
strForStack strStack[MAX_TOP_SIZE];
int strStackTop = -1, strTop = -1;

int searchStrFromStrNameUsedFunction(strName str, int located);
int searchStrFromStrName(char tempStr[]);

void showFinal();
void inputInfo();
int main()
{


	inputInfo();
	showFinal();

	return 0;
}
//int searchStrFromUsedFunction(int locate,)
//{
//
//}
int searchStrFromStrNameUsedFunction(strName str,int located)
{
	for (int i = 0; i < str.usedFunctionCount; i++)
	{
		if (str.usedFunction[i] == located)
			return 1;
	}
	return -1;

}
int searchStrFromStrName(char tempStr[])
{
	for (int i = 0; i <= strTop; i++)
	{
		if (strcmp(tempStr, str[i].name) == 0)
			return i;
	}

	return -1;
}

void inputInfo()
{
	int funcChoice = -1, temp = -1;
	char tempStr[MAX_NAME_SIZE];
	struct strPnode* tempPtrl = NULL;
	do {
		scanf("%d", &funcChoice);
		if (funcChoice == 8)
		{
			scanf("%s", tempStr);
			strcpy(strStack[++strStackTop].name, tempStr);
			temp = searchStrFromStrName(tempStr);
			if (temp == -1)
			{
				strcpy(str[++strTop].name, tempStr);
				str[strTop].usedFunctionCount = 0;
				strStack[strStackTop].stackLocation = strTop;
			}
			else
			{
				strStack[strStackTop].stackLocation = temp;
			}

		}
		else if (funcChoice == 0)
		{
			if (strStackTop > 0)
			{
				temp = searchStrFromStrNameUsedFunction(str[strStack[strStackTop - 1].stackLocation], strStack[strStackTop].stackLocation);
				if (temp == -1)
				{
					tempPtrl = &str[strStack[strStackTop - 1].stackLocation];
					tempPtrl->usedFunction[tempPtrl->usedFunctionCount++] = strStack[strStackTop].stackLocation;
				}
				
				strStackTop--;
			}
			else
			{
				strStackTop--;
			}
		}

	} while (strStackTop != -1);
}
void showFinal()
{
	for (int i = 0; i <= strTop; i++)
	{
		if (str[i].usedFunctionCount > 0)
		{
			printf("%s:", str[i].name);
			for (int j = 0; j < str[i].usedFunctionCount; j++)
			{
				printf("%s", str[str[i].usedFunction[j]].name);
				if (j < str[i].usedFunctionCount - 1)
					printf(",");
			}
			printf("\n");
		}
	}

}
