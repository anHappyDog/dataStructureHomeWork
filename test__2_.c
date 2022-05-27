#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
/*
#define MAX_WORD_SIZE 128//���������
#define MAX_TRASH_SIZE 32//�ڽӱ����Ԫ�ظ���
#define MAX_STOPWORD_SIZE 300000//���ôʵ���������
#define MAX_DICTIONARY_SIZE 30000000//�ֵ䵥��������
#define MAX_KEYWORD_SIZE 1024 //���ؼ��ʸ���
*/
#define MAX_WORD_SIZE 35//���������
#define MAX_TRASH_SIZE 4//�ڽӱ����Ԫ�ظ���
#define MAX_STOPWORD_SIZE 1000//���ôʵ���������
#define MAX_DICTIONARY_SIZE 800000//�ֵ䵥��������
#define MAX_KEYWORD_SIZE 64 //���ؼ��ʸ���


typedef struct node {

	char word[MAX_WORD_SIZE];
	char anotion[MAX_TRASH_SIZE][MAX_WORD_SIZE];
	int anotionCount[MAX_TRASH_SIZE];
	int anotionSize;


}Node, * PNode;
typedef struct hash {
	PNode head;

}Hash, * PHash;
typedef struct fileNode fNOde, * filePnode;
struct fileNode {
	int firstNum;
	int lastNum;
	int webpage;
	int allWordCount;
	int keyWordCount[MAX_KEYWORD_SIZE];
	double sim;
	filePnode next;
};

//int keyWordSize = 0;
//char keyWord[MAX_KEYWORD_SIZE][MAX_WORD_SIZE];
int keyWordNum = 0, finalNodeCount = 0;
int keyWordCount[MAX_KEYWORD_SIZE];
double fileKeyShowCount[MAX_KEYWORD_SIZE] = { 0 };
int nodeCount = 0;
int topShowNum = 0;
filePnode lNode = NULL;
PHash readStopWordFromFile(PHash stopWordList);
PHash readDictionaryWordFromFile(PHash stopWordList, PHash dictionaryWordHash);
PHash createHash(int mode);//1���ô�
unsigned int kbDHash(char tempStr[], int mode);
PHash insertNodeToHash(PHash wordHash, char word[], int mode);
int searchNodeFromHash(PHash wordHash, char word[], int mode);
PNode createNode(char word[]);
void turnWordTolower(char word[]);
PHash orderProcess(PHash dictionaryHash, int argc, char** argv);
filePnode nodeInital(filePnode ptrl, int firstNum, int lastNum, int webpage, double sim);
filePnode readArticlesFromFile(PHash dictionaryHash, PHash keyWordHash);
filePnode answerCalulate(filePnode fileContent);
filePnode answerInsert(filePnode ptrl, filePnode tempPtrl);
void answerShow(filePnode finalPtrl);
int main(int argc, char** argv)
{
	filePnode fileContent = NULL, finalAnswer = NULL;
	PHash stopWordHash = NULL, dictionaryWordHash = NULL, keyWordHash = NULL;

	stopWordHash = createHash(1);
	dictionaryWordHash = createHash(2);

	stopWordHash = readStopWordFromFile(stopWordHash);
	dictionaryWordHash = readDictionaryWordFromFile(stopWordHash, dictionaryWordHash);
	keyWordHash = orderProcess(dictionaryWordHash, argc, argv);
	fileContent = readArticlesFromFile(dictionaryWordHash, keyWordHash);
	finalAnswer = answerCalulate(fileContent);
	answerShow(finalAnswer);
	/*printf("%d\n",searchNodeFromHash(stopWordHash,"a", 1));*/
	//scanf("%s",tempStr);
	//printf("%d\n",searchNodeFromHash(dictionaryWordHash,tempStr,2));
	return 0;
}
//��ʾ�洢����
void answerShow(filePnode finalPtrl)
{
	filePnode temp = finalPtrl;
	FILE* resultsFile = fopen("results.txt", "w");
	if (resultsFile == NULL)
	{
		printf("open results.txt error");
		return;
	}
	for (int i = 0; i < (5 > nodeCount ? nodeCount : 5); i++)
	{
		if (temp->sim == 0)
			break;
		printf("%.6f %d %d-%d\n", temp->sim, temp->webpage, temp->firstNum, temp->lastNum);
		temp = temp->next;
	}
	temp = finalPtrl;
	for (int i = 0; i < nodeCount && i < topShowNum; i++)
	{
		if (temp->sim == 0)
			break;
		fprintf(resultsFile, "%.6f %d %d-%d\n", temp->sim, temp->webpage, temp->firstNum, temp->lastNum);
		temp = temp->next;
	}
	fclose(resultsFile);
}
//�������ս��
filePnode answerCalulate(filePnode fileContent)
{
	int test = 0;
	double sim = 0;
	filePnode finalAnswer = NULL, tempPtrl = fileContent, temp = NULL;
	for (int i = 0; i < keyWordNum; i++)
	{
		if (fileKeyShowCount[keyWordCount[i]] > 0)
		{
			fileKeyShowCount[keyWordCount[i]] = log10(nodeCount / fileKeyShowCount[keyWordCount[i]]);
		}
	}
	while (tempPtrl != NULL)
	{
		test++;
		for (int i = 0; i < keyWordNum; i++)
		{
			sim += ((double)(tempPtrl->keyWordCount[keyWordCount[i]]) / tempPtrl->allWordCount * 100) * fileKeyShowCount[keyWordCount[i]];
		}
		tempPtrl->sim = sim;
		temp = tempPtrl;
		tempPtrl = tempPtrl->next;
		finalAnswer = answerInsert(finalAnswer, temp);
		sim = 0;
	}

	return finalAnswer;
}
//����simʱ�������մ�
filePnode answerInsert(filePnode ptrl, filePnode tempPtrl)
{
	filePnode temp = ptrl;
	if (ptrl == NULL)
	{
		tempPtrl->next = NULL;
		lNode = tempPtrl;
		finalNodeCount++;
		return tempPtrl;
	}
	if (ptrl->sim < tempPtrl->sim)
	{
		tempPtrl->next = ptrl;
		finalNodeCount++;
		return tempPtrl;
	}
	if (finalNodeCount >= topShowNum)
	{
		if (lNode->sim >= tempPtrl->sim)
		{
			return ptrl;
		}
		else
		{
			while (temp->next != NULL && temp->next->sim >= tempPtrl->sim)
				temp = temp->next;
			tempPtrl->next = temp->next;
			temp->next = tempPtrl;
			finalNodeCount++;
			return ptrl;
		}
	}
	else
	{
		if (lNode->sim >= tempPtrl->sim)
		{
			lNode->next = tempPtrl;
			tempPtrl->next = NULL;
			lNode = lNode->next;
			finalNodeCount;
			return ptrl;
		}
		else
		{
			while (temp->next != NULL && temp->next->sim >= tempPtrl->sim)
				temp = temp->next;
			tempPtrl->next = temp->next;
			temp->next = tempPtrl;
			finalNodeCount++;
			return ptrl;
		}
	}

}
//���ı��ж�ȡ���ʴ�������
filePnode readArticlesFromFile(PHash dictionaryHash, PHash keyWordHash)
{
	int webPage = 1;
	filePnode ptrl = NULL, lastNode = NULL, temp = NULL;
	int firstNum = 0, lastNum = 0;
	int tempChr = 0, tempWordTop = 0, tempIndex = 0;
	char tempWord[MAX_WORD_SIZE];
	FILE* articleFile = fopen("article.txt", "r");
	if (articleFile == NULL)
	{
		printf("open articleFile error,return");
		return NULL;
	}
	fscanf(articleFile, "%d-%d", &firstNum, &lastNum);
	ptrl = nodeInital(ptrl, firstNum, lastNum, webPage, 0);
	webPage++;
	lastNode = ptrl;
	nodeCount++;
	while (!feof(articleFile))
	{
		tempChr = fgetc(articleFile);
		//(tempChr = fgetc(articleFile)) != EOF
		tempChr = tolower(tempChr);
		if (isalpha(tempChr))
		{
			tempIndex = 1;
			tempWord[tempWordTop++] = tempChr;
		}
		else if (tempIndex == 1 && !isalpha(tempChr))
		{


			tempWord[tempWordTop] = '\0';
			tempWordTop = 0;
			if (searchNodeFromHash(dictionaryHash, tempWord, 2) == 0)
			{
				lastNode->allWordCount++;
			}
			tempIndex = 0;
			if (searchNodeFromHash(keyWordHash, tempWord, 3) == 0)
			{
				tempIndex = kbDHash(tempWord, 3);
				//fileKeyShowCount[tempIndex]++;
				lastNode->keyWordCount[tempIndex]++;
				tempIndex = 0;
			}
		}
		else if (tempChr == '\f')
		{
			tempChr = fgetc(articleFile);
			tempChr = fgetc(articleFile);
			for (int i = 0; i < keyWordNum; i++)
			{
				if (lastNode->keyWordCount[keyWordCount[i]] > 0)
				{
					fileKeyShowCount[keyWordCount[i]]++;
				}
			}
			fscanf(articleFile, "%d-%d", &firstNum, &lastNum);
			temp = nodeInital(temp, firstNum, lastNum, webPage, 0);

			webPage++;
			lastNode->next = temp;
			lastNode = lastNode->next;
			nodeCount++;
		}

	}
	for (int i = 0; i < keyWordNum; i++)
	{
		if (lastNode->keyWordCount[keyWordCount[i]] > 0)
		{
			fileKeyShowCount[keyWordCount[i]]++;
		}
	}
	fclose(articleFile);
	return ptrl;
}
//��ʼ���ļ����ݽڵ�
filePnode nodeInital(filePnode ptrl, int firstNum, int lastNum, int webPage, double sim)
{
	ptrl = (filePnode)malloc(sizeof(fNOde));
	ptrl->allWordCount = 0;
	ptrl->firstNum = firstNum;
	ptrl->lastNum = lastNum;
	memset(ptrl->keyWordCount, 0, sizeof(ptrl->keyWordCount));
	ptrl->sim = sim;
	ptrl->webpage = webPage;
	ptrl->next = NULL;
	return ptrl;
}

//�������������
PHash orderProcess(PHash dictionaryHash, int argc, char** argv)
{
	int x = 0;
	unsigned int kbD = 0;
	PNode tempNode = NULL;
	PHash ptrl = NULL;
	if (argc - 2 > MAX_KEYWORD_SIZE)
		return NULL;
	topShowNum = atoi(argv[1]);
	ptrl = createHash(3);
	for (int i = 2; i < argc; i++)
	{
		if (searchNodeFromHash(dictionaryHash, argv[i], 2) == 0)
		{
			kbD = kbDHash(argv[i], 3);
			keyWordCount[keyWordNum++] = kbD;
			ptrl = insertNodeToHash(ptrl, argv[i], 3);
		}
	}
	return ptrl;
}
//����NODE�ڵ�
PNode createNode(char word[])
{
	PNode ptrl = (PNode)malloc(sizeof(Node));
	strcpy(ptrl->word, word);
	ptrl->anotionSize = 0;
	return ptrl;
}
//��hash�в���ڵ�
PHash insertNodeToHash(PHash wordHash, char word[], int mode)
{
	unsigned int kbD;
	PNode temp = NULL;
	kbD = kbDHash(word, mode);

	if (wordHash[kbD].head == NULL)
	{
		temp = createNode(word);
		wordHash[kbD].head = temp;
		return wordHash;
	}
	else if (strcmp(wordHash[kbD].head->word, word) != 0)
	{
		temp = wordHash[kbD].head;
		if (temp->anotionSize == MAX_TRASH_SIZE)
		{
			printf("�õ�ַ���ڽӱ����ˣ�����ԭ��ϣ");
			return wordHash;
		}
		strcpy(temp->anotion[temp->anotionSize++], word);
		return wordHash;
	}
	else
	{
		return wordHash;
	}

}
//�����ϣ��ַ
unsigned int kbDHash(char tempStr[], int mode)
{
	//mode 1 Ϊ�����ô�S
	unsigned int seed = 131;
	unsigned int tempKbD = 0;
	unsigned int tempSize = (mode == 1) ? MAX_STOPWORD_SIZE : (mode == 2 ? MAX_DICTIONARY_SIZE : MAX_KEYWORD_SIZE);
	for (int i = 0; i < strlen(tempStr); i++)
	{
		tempKbD = tempKbD * seed + tempStr[i];
	}

	return (tempKbD & 0x7fffffff) % tempSize;
}
//��hash�в���word
int searchNodeFromHash(PHash wordHash, char word[], int mode)
{
	unsigned int kbD = kbDHash(word, mode);
	if (wordHash[kbD].head == NULL)
	{
		return 1;
	}
	else
	{
		if (strcmp(wordHash[kbD].head->word, word) == 0)
			return 0;
		else
		{
			for (int i = 0; i < wordHash[kbD].head->anotionSize; i++)
			{
				if (strcmp(wordHash[kbD].head->anotion[i], word) == 0)
					return 0;
			}
		}
	}
	return 1;
}
//��ʼ��hash
PHash createHash(int mode)
{
	if (mode == 1)//���ô�
	{
		PHash WordHash = (PHash)malloc(sizeof(Hash) * MAX_STOPWORD_SIZE);
		for (int i = 0; i < MAX_STOPWORD_SIZE; i++)
			WordHash[i].head = NULL;
		return WordHash;
	}
	else if (mode == 2)
	{
		PHash WordHash = (PHash)malloc(sizeof(Hash) * MAX_DICTIONARY_SIZE);
		for (int i = 0; i < MAX_DICTIONARY_SIZE; i++)
			WordHash[i].head = NULL;
		return WordHash;
	}
	else if (mode == 3)
	{
		PHash WordHash = (PHash)malloc(sizeof(Hash) * MAX_KEYWORD_SIZE);
		for (int i = 0; i < MAX_KEYWORD_SIZE; i++)
			WordHash[i].head = NULL;
		return WordHash;

	}
}
//��stopwords
PHash readStopWordFromFile(PHash stopWordList)
{
	char tempStr[MAX_WORD_SIZE];
	FILE* stopWordFile = fopen("stopwords.txt", "r");
	if (stopWordFile == NULL)
	{
		printf("open stopWordFile error");
		return;
	}
	while (fscanf(stopWordFile, "%s", tempStr) != EOF)
	{
		stopWordList = insertNodeToHash(stopWordList, tempStr, 1);
	}
	fclose(stopWordFile);
	return stopWordList;
}
//��dictionary
PHash readDictionaryWordFromFile(PHash stopWordList, PHash dictionaryWordHash)
{
	char tempStr[MAX_WORD_SIZE];
	FILE* dictionaryFile = fopen("dictionary.txt", "r");
	if (dictionaryFile == NULL)
	{
		printf("open dictionaryfile error");
		return;
	}
	while (fscanf(dictionaryFile, "%s", tempStr) != EOF)
	{
		if (searchNodeFromHash(stopWordList, tempStr, 1) == 1)
		{
			dictionaryWordHash = insertNodeToHash(dictionaryWordHash, tempStr, 2);
		}
	}
	fclose(dictionaryFile);
	return dictionaryWordHash;
}
//������ת��ΪСд
void turnWordTolower(char word[])
{
	for (int i = 0; i < strlen(word); i++)
		word[i] = tolower(word[i]);
}





