#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#define MAX_WORD_SIZE 35
#define MAX_TRASH_SIZE 4
#define MAX_STOPWORD_SIZE 1000
#define MAX_DICTIONARY_SIZE 800000
#define MAX_KEYWORD_SIZE 64
#define MAX_MAT_SIZE 24 //单词数组的大小
#define MAX_READ_SIZE 64000000 //一次最多读取的article
typedef struct node {
	char* word;
	char** anotion;
	int anotionSize;
}nHash, * pHash;
typedef struct filenode FileNode, * pNode;
struct filenode {
	int firstNum;
	int lastNum;
	int webpage;
	int wordCount;
	int keyWordCnt[MAX_KEYWORD_SIZE];
	double sim;
	pNode lchild, rchild;
};


nHash dictionary[MAX_DICTIONARY_SIZE];
nHash stopwords[MAX_STOPWORD_SIZE];
nHash keywords[MAX_KEYWORD_SIZE];
pNode fileInfo = NULL, root = NULL;
FILE* resultFile = NULL;
int rankCount = 0;//需要个数
int finishedNode = 0;
int keyWordIndex[MAX_KEYWORD_SIZE], keyWordCount = 0, nodeCount = 0;
char* stopbuf = NULL, * dicbuf = NULL;
double keyShowCount[MAX_KEYWORD_SIZE];

void readStopWords();
unsigned int kbDHash(char* tempStr, int mode);
int searchHash(nHash ptrl[], char* str, int mode);
void readDictionaryWords();
void readKeyWords(int argc, char** argv);
void readArticles();
void calResult();
void showResult();//中序遍历
pNode createFileNode(int firstNum, int lastNum, int webpage, int wordCount, double sim);
pNode createSortTree(pNode root, pNode ptrl);
void btOrder(pNode root, int allcount, int mode);

int main(int argc, char** argv)
{
	readStopWords();
	readDictionaryWords();
	readKeyWords(argc, argv);
	readArticles();
	calResult();
	showResult();
	return 0;
}
void showResult()
{
	btOrder(root, 5,1);
	resultFile = fopen("results.txt", "w");
	//btOrderForFile(root, rankCount, resultFile);
	finishedNode = 0;
	btOrder(root,rankCount,2);
	fclose(resultFile);
}

void btOrder(pNode root, int allcount, int mode)
{
	if (root != NULL)
	{
		btOrder(root->lchild, allcount, mode);
		if (finishedNode < allcount&& (root->sim - 1e-6 > 0))
		{
			if (mode == 1)
				printf("%.6f %d %d-%d\n", root->sim, root->webpage, root->firstNum, root->lastNum);
			else if (mode == 2)
				fprintf(resultFile, "%.6f %d %d-%d\n", root->sim, root->webpage, root->firstNum, root->lastNum);
			finishedNode++;
		}
		btOrder(root->rchild, allcount, mode);
	}
}

void calResult()
{
	pNode tempOne = fileInfo, tempTwo = NULL;
	for (int i = 0; i < keyWordCount; i++)
	{
		if (keyShowCount[keyWordIndex[i]] > 0)
			keyShowCount[keyWordIndex[i]] = log10((double)nodeCount / keyShowCount[keyWordIndex[i]]);
	}
	while (tempOne != NULL)
	{
		for (int i = 0; i < keyWordCount; i++)
			tempOne->sim += tempOne->keyWordCnt[keyWordIndex[i]] * 100.0 / tempOne->wordCount * keyShowCount[keyWordIndex[i]];
		tempTwo = tempOne;
		tempOne = tempOne->rchild;
		root = createSortTree(root, tempTwo);
	}
}
pNode createSortTree(pNode root, pNode ptrl)
{
	if (root == NULL)
	{
		ptrl->rchild = NULL;
		return ptrl;
	}
	else
	{
		if (ptrl->sim > root->sim)
		{
			root->lchild = createSortTree(root->lchild, ptrl);
		}
		else
		{
			root->rchild = createSortTree(root->rchild, ptrl);
		}
	}
	return root;
}
pNode createFileNode(int firstNum, int lastNum, int webpage, int wordCount, double sim)
{
	pNode ptrl = (pNode)malloc(sizeof(FileNode));
	for (int i = 0; i < MAX_KEYWORD_SIZE; i++)
		ptrl->keyWordCnt[i] = 0;
	ptrl->firstNum = firstNum;
	ptrl->lastNum = lastNum;
	ptrl->lchild = ptrl->rchild = NULL;
	ptrl->wordCount = wordCount;
	ptrl->sim = sim;
	ptrl->webpage = webpage;
	return ptrl;

}
void readArticles()
{
	pNode tempPtrl = NULL;
	int len = 0, webpage = 1, firstNum = 0, lastNum = 0, preLoc = -1, kbD = 0;
	char* buf = (char*)malloc(sizeof(char) * MAX_READ_SIZE);
	FILE* articleFile = fopen("article.txt", "r");
	fscanf(articleFile, "%d-%d", &firstNum, &lastNum);
	fileInfo = createFileNode(firstNum, lastNum, webpage++, 0, 0);
	tempPtrl = fileInfo;
	while ((len = fread(buf, sizeof(char), MAX_READ_SIZE, articleFile)) != 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (isalpha(buf[i]))
			{
				if (preLoc == -1)
					preLoc = i;
				buf[i] = tolower(buf[i]);
			}
			else if (!isalpha(buf[i]) && preLoc != -1)
			{
				//找到一个单词
				buf[i] = '\0';
				if (searchHash(dictionary, buf + preLoc, 2) != -1)
					tempPtrl->wordCount++;
				if ((kbD = searchHash(keywords, buf + preLoc, 3)) != -1)
				{
					tempPtrl->keyWordCnt[kbD]++;
					if (tempPtrl->keyWordCnt[kbD] == 1)
						keyShowCount[kbD]++;
				}
				preLoc = -1;
			}
			if (buf[i] == '\f')
			{
				//下一个文档
				i += 3;//windows和 linux不同 2 3
				firstNum = 0; lastNum = 0;
				while (isdigit(buf[i]))
					firstNum = firstNum * 10 + buf[i++] - '0';
				i++;//逃脱 - 
				while (isdigit(buf[i]))
					lastNum = lastNum * 10 + buf[i++] - '0';
				tempPtrl->rchild = createFileNode(firstNum, lastNum, webpage++, 0, 0);
				tempPtrl = tempPtrl->rchild;
				i--;
			}

		}
	}

	nodeCount = webpage - 1;
	fclose(articleFile);
}
unsigned int kbDHash(char* tempStr, int mode)
{
	//mode 1 为算弃用词S
	unsigned int seed = 131;
	unsigned int tempKbD = 0;
	unsigned int tempSize = (mode == 1) ? MAX_STOPWORD_SIZE : (mode == 2 ? MAX_DICTIONARY_SIZE : MAX_KEYWORD_SIZE);
	for (int i = 0; i < strlen(tempStr); i++)
	{
		tempKbD = tempKbD * seed + tempStr[i];
	}

	return (tempKbD & 0x7fffffff) % tempSize;
}
void createNode(char* buf, pHash ptrl)
{
	if (ptrl->anotion == NULL)
	{
		ptrl->anotion = (char**)malloc(sizeof(char*) * MAX_TRASH_SIZE);
		ptrl->anotionSize = 0;
		ptrl->word = buf;
	}
	else
	{
		ptrl->anotion[ptrl->anotionSize++] = buf;
	}
}
void readDictionaryWords()
{
	int len = 0, preLoc = 0, kbD = 0;
	dicbuf = (char*)malloc(sizeof(char) * MAX_DICTIONARY_SIZE * MAX_MAT_SIZE);
	FILE* dictionaryFile = fopen("dictionary.txt", "r");
	len = fread(dicbuf, sizeof(char), MAX_DICTIONARY_SIZE * MAX_MAT_SIZE, dictionaryFile);
	dicbuf[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		if (dicbuf[i] == '\r')
		{
			dicbuf[i] = '\0';
			if (searchHash(stopwords, dicbuf + preLoc, 1) == -1)
			{
				kbD = kbDHash(dicbuf + preLoc, 2);
				createNode(dicbuf + preLoc, &dictionary[kbD]);
			}
			preLoc = i + 2;
		}
	}
	fclose(dictionaryFile);
}
void readKeyWords(int argc, char** argv)
{
	int kbD = 0;
	rankCount = atoi(argv[1]);
	for (int i = 2; i < argc; i++)
	{
		if (searchHash(dictionary, argv[i], 2) != -1)
		{
			kbD = kbDHash(argv[i], 3);
			keyWordIndex[keyWordCount++] = kbD;
			createNode(argv[i], &keywords[kbD]);
		}
	}
}
int searchHash(nHash ptrl[], char* str, int mode)
{//1为找到
	int kbD = kbDHash(str, mode);
	if (ptrl[kbD].word == NULL)
		return -1;
	else if (strcmp(ptrl[kbD].word, str) == 0)
		return kbD;
	else
		for (int i = 0; i < ptrl[kbD].anotionSize; i++)
			if (strcmp(ptrl[kbD].anotion[i], str) == 0)
				return kbD;
	return -1;
}
void readStopWords()
{
	int len = 0, preLoc = 0, kbD = 0;
	stopbuf = (char*)malloc(sizeof(char) * 100000);
	FILE* stopWordFile = fopen("stopwords.txt", "r");
	len = fread(stopbuf, sizeof(char), 100000, stopWordFile);
	stopbuf[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		if (stopbuf[i] == '\r')
		{
			stopbuf[i] = '\0';
			kbD = kbDHash(stopbuf + preLoc, 1);
			createNode(stopbuf + preLoc, &stopwords[kbD]);
			preLoc = i + 2;
		}
	}
	fclose(stopWordFile);
}

