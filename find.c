#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NHASH 3001
#define MULT 37
#define MAX_DIC_SIZE 3500
#define MAX_WORD_SIZE 32
#define MAX_CRASH_SIZE 8




typedef struct node {
	char word[MAX_WORD_SIZE];
	char crashWord[MAX_CRASH_SIZE][MAX_WORD_SIZE];
	int crashCount;

}Hnode, * Hptrl;
typedef struct hash {
	Hptrl head;
}Hash, * Phash;

char dictionaryWord[MAX_DIC_SIZE][MAX_WORD_SIZE];
int dictionaryWordCount = 0;
int indexLocate[26][2];
Hash hashTable[NHASH];

unsigned int hash(char* str);
void funcProcess(char inputStr[], int mode);
void readWordFromFile(int mode);
void funcOne(char word[]);
void funcTwo(char word[]);
void funcThree(char word[]);
void funcFour(char word[]);
void hashProcess(char word[]);
Hptrl createNode(char word[]);
int main()
{
	int inputNum = 0;
	char inputStr[MAX_DIC_SIZE];
	scanf("%s %d", inputStr, &inputNum);
	funcProcess(inputStr, inputNum);

	return 0;
}
void readWordFromFile(int mode)
{
	int indexLoc = 0;
	char tempChr[MAX_WORD_SIZE];
	FILE* fp = fopen("dictionary3000.txt", "r");
	if (fp == NULL)
	{
		printf("打开文件失败");
		return;
	}

	while (fscanf(fp, "%s", tempChr) == 1)
	{
		if (mode != 4)
		{
			strcpy(dictionaryWord[dictionaryWordCount++], tempChr);
			if (mode == 3)
			{
				if (dictionaryWordCount > 1 && dictionaryWord[dictionaryWordCount - 1][0] != dictionaryWord[dictionaryWordCount - 2][0])
				{
					if (dictionaryWord[dictionaryWordCount - 2][0] == 'a')
					{
						indexLocate[0][0] = 0;
						indexLocate[0][1] = dictionaryWordCount - 1;
						indexLocate[1][0] = dictionaryWordCount - 1;
					}
					else
					{
						indexLocate[dictionaryWord[dictionaryWordCount - 2][0] - 'a'][1] = dictionaryWordCount - 1 - indexLocate[dictionaryWord[dictionaryWordCount - 2][0]-'a'][0];
						indexLocate[dictionaryWord[dictionaryWordCount - 1][0] - 'a'][0] = dictionaryWordCount - 1;
					}
				/*	if (indexLoc == 0)
					{
						indexLocate[indexLoc][0] = 0;
						indexLocate[indexLoc][1] = dictionaryWordCount - 1;
						indexLoc++;
						indexLocate[indexLoc][0] = dictionaryWordCount - 1;
					}
					else
					{
						indexLocate[indexLoc][1] = dictionaryWordCount  - 1- indexLocate[indexLoc][0];
						indexLocate[++indexLoc][0] = dictionaryWordCount -1;
					}*/
				}
			}
		}
		else
		{
			hashProcess(tempChr);

		}
	}
	if (mode == 3)
	{
		indexLocate[dictionaryWord[dictionaryWordCount - 2][0] - 'a'][1] = dictionaryWordCount - 1 - indexLocate[dictionaryWord[dictionaryWordCount - 2][0] - 'a'][0];
		
	}
}
void funcOne(char word[])
{
	int result = 0, locate = 0;
	for (int i = 0; i < dictionaryWordCount; i++)
	{
		if (strcmp(word, dictionaryWord[i]) == 0)
		{
			result = 1;
			locate = i + 1;
			break;
		}
		else if (strcmp(word, dictionaryWord[i]) < 0)
		{
			result = 0;
			locate = i + 1;
			break;
		}
	}

	printf("%d %d\n", result, locate);

}
void funcTwo(char word[])
{
	int result = 0, locate = 0;
	int mid = 0, left = 0, right = dictionaryWordCount - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (strcmp(word, dictionaryWord[mid]) == 0)
		{

			locate++;
			result = 1;
			break;
		}
		else if (strcmp(word, dictionaryWord[mid]) < 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
		locate++;
	}
	printf("%d %d\n", result, locate);
}
void funcThree(char word[])
{
	int locate = 0, result = 0;
	int left = 0, mid = 0, right = 0;
	if (indexLocate[word[0] - 'a'][1] == 0)
	{
		printf("0 0\n");
		return;
	}
	left = indexLocate[word[0] - 'a'][0];
	right = left + indexLocate[word[0] - 'a'][1] -1 ;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (strcmp(word, dictionaryWord[mid]) == 0)
		{

			locate++;
			result = 1;
			break;
		}
		else if (strcmp(word, dictionaryWord[mid]) < 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
		locate++;
	}
	printf("%d %d\n", result, locate);

}
void funcFour(char word[])
{
	int result = 0, locate = 1;
	int kbD = hash(word);
	if (hashTable[kbD].head == NULL)
	{
		result = 0;
	}
	else if (hashTable[kbD].head != NULL)
	{
		if (strcmp(hashTable[kbD].head->word, word) == 0)
		{
			result = 1;
		}
		else
		{
			for (int i = 0; i < hashTable[kbD].head->crashCount; i++)
			{
				locate++;
				if (strcmp(hashTable[kbD].head->crashWord[i], word) == 0)
				{
					result = 1;
					break;
				}
			}
		}
	}
	printf("%d %d\n", result, locate);
}
Hptrl createNode(char word[])
{
	Hptrl ptrl = (Hptrl)malloc(sizeof(Hnode));
	strcpy(ptrl->word, word);
	ptrl->crashCount = 0;
	return ptrl;

}
void hashProcess(char word[])
{
	int kbD = hash(word);
	if (hashTable[kbD].head == NULL)
	{
		hashTable[kbD].head = createNode(word);
	}
	else
	{
		strcpy(hashTable[kbD].head->crashWord[hashTable[kbD].head->crashCount++], word);
	}
}
void funcProcess(char word[], int mode)
{
	readWordFromFile(mode);
	switch (mode)
	{
	case 1:

		funcOne(word);
		break;
	case 2:
		funcTwo(word);
		break;
	case 3:
		funcThree(word);
		break;
	case 4:
		funcFour(word);
		break;

	}


}
unsigned int hash(char* str)
{
	unsigned int h = 0;
	char* p;
	for (p = str; *p != '\0'; p++)
		h = MULT * h + *p;
	return h % NHASH;



}
