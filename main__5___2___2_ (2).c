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
#define MAX_MAT_SIZE 8 //单词数组的大小
#define MAX_READ_SIZE 3000000 //一次最多读取的article
#define MAX_FILE_SIZE 20000
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
};


nHash dictionary[MAX_DICTIONARY_SIZE];
nHash stopwords[MAX_STOPWORD_SIZE];
nHash keywords[MAX_KEYWORD_SIZE];
int rankCount = 0;//需要个数
int keyWordIndex[MAX_KEYWORD_SIZE], keyWordCount = 0, nodeCount = 0;
char* stopbuf = NULL, * dicbuf = NULL;
double keyShowCount[MAX_KEYWORD_SIZE];
FileNode fileinfo[MAX_FILE_SIZE];

void readStopWords();
void readDictionaryWords();
void readKeyWords(int argc, char** argv);
void readArticles();
void calResult();
int cmp(const void* a, const void* b);

int main(int argc, char** argv)
{
	readStopWords();
	readDictionaryWords();
	readKeyWords(argc, argv);
	readArticles();
	calResult();
	return 0;
}

void calResult()
{
	FILE* resultFile = fopen("results.txt", "w");
	for (register int i = 0; i < keyWordCount; ++i)
	{
		if (keyShowCount[keyWordIndex[i]] > 0)
			keyShowCount[keyWordIndex[i]] = log10((double)nodeCount / keyShowCount[keyWordIndex[i]]);
	}
	for (register int i = 0; i < nodeCount; ++i)
	{
		for (register int j = 0; j < keyWordCount; ++j)
			fileinfo[i].sim += fileinfo[i].keyWordCnt[keyWordIndex[j]] * 100.0 / fileinfo[i].wordCount * keyShowCount[keyWordIndex[j]];
	}
	qsort(fileinfo, nodeCount, sizeof(FileNode), cmp);
	for (register int i = 0; i < nodeCount && i < rankCount; ++i)
	{
		if (fileinfo[i].sim < 1e-6)
			break;
		if (i < 5 && i < nodeCount)
			printf("%.6f %d %d-%d\n", fileinfo[i].sim, fileinfo[i].webpage, fileinfo[i].firstNum, fileinfo[i].lastNum);
		fprintf(resultFile, "%.6f %d %d-%d\n", fileinfo[i].sim, fileinfo[i].webpage, fileinfo[i].firstNum, fileinfo[i].lastNum);
	}
	fclose(resultFile);
}
int cmp(const void* a, const void* b)
{
	pNode aa = (pNode)a, bb = (pNode)b;
	if (fabs(aa->sim - bb->sim) > 1e-6)
		return (bb->sim > aa->sim) ? 1 : -1;
	else
		return aa->webpage - bb->webpage;
}
void readArticles()
{
	register unsigned int kbd2 = 0, kbd3 = 0;
	 int len = 0, webpage = 0, firstNum = 0, lastNum = 0, preLoc = -1, index = 0;
	char* buf = (char*)malloc(sizeof(char) * MAX_READ_SIZE);
	FILE* articleFile = fopen("article.txt", "r");
	fscanf(articleFile, "%d-%d", &firstNum, &lastNum);
	fileinfo[webpage].firstNum = firstNum; fileinfo[webpage].lastNum = lastNum;
	fileinfo[webpage].webpage = webpage + 1;
	while ((len = fread(buf, sizeof(char), MAX_READ_SIZE, articleFile)) != 0)
	{
		for (register int i = 0; i < len; ++i)
		{

			if ('a' <= buf[i] && buf[i] <= 'z' || buf[i] >= 'A' && buf[i] <= 'Z')
			{
				if (preLoc == -1)
					preLoc = i;
				if (buf[i] >= 'A' && buf[i] <= 'Z')
					buf[i] = buf[i] - 'A' + 'a';
				kbd2 = kbd2 * 131 + buf[i];
			}
			else if ( preLoc != -1)
			{
				//找到一个单词
				buf[i] = '\0';
				kbd3 = (kbd2 & 0x7fffffff) % MAX_KEYWORD_SIZE;
				kbd2 = (kbd2 & 0x7fffffff) % MAX_DICTIONARY_SIZE;

				//检查字典
				if (dictionary[kbd2].word == NULL)
					index = 0;
				else if (strcmp(dictionary[kbd2].word, buf + preLoc) == 0)
					index = 1;
				else
				{
					for (int j = 0; j < dictionary[kbd2].anotionSize; ++j)
					{
						if (strcmp(dictionary[kbd2].anotion[j], buf + preLoc) == 0)
						{
							index = 1;
							break;
						}
					}
				}
				if (index == 1)
				{
					++fileinfo[webpage].wordCount;
					index = 0;
					if (keywords[kbd3].word == NULL)
						index = 0;
					else if (strcmp(keywords[kbd3].word, buf + preLoc) == 0)
						index = 1;
					else
					{
						//j++
						for (int j = 0; j < keywords[kbd3].anotionSize; ++j)
						{
							if (strcmp(keywords[kbd3].anotion[j], buf + preLoc) == 0)
							{
								index = 1;
								break;
							}
						}
					}
					if (index == 1)
					{
						fileinfo[webpage].keyWordCnt[kbd3]++;
						if (fileinfo[webpage].keyWordCnt[kbd3] == 1)
							keyShowCount[kbd3]++;
					}
				}
				preLoc = -1;
				index = kbd2 = kbd3 = 0;
			}
			else if (buf[i] == '\f')
			{
				//下一个文档
				i += 3;//windows和 linux不同 2 3
				firstNum = 0; lastNum = 0; webpage++;
				while ('0' <= buf[i] && buf[i] <= '9')
					firstNum = firstNum * 10 + buf[i++] - '0';
				i++;//逃脱 - 
				while ('0' <= buf[i] && buf[i] <= '9')
					lastNum = lastNum * 10 + buf[i++] - '0';
				fileinfo[webpage].firstNum = firstNum; fileinfo[webpage].lastNum = lastNum;
				fileinfo[webpage].webpage = webpage + 1;
				++i;
			}
		}
	}
	nodeCount = webpage + 1;
	fclose(articleFile);
}
void readDictionaryWords()
{
	register unsigned int kbd1 = 0, kbd2 = 0;
	int len = 0, preLoc = 0, index = 0;
	dicbuf = (char*)malloc(sizeof(char) * MAX_DICTIONARY_SIZE * MAX_MAT_SIZE);
	FILE* dictionaryFile = fopen("dictionary.txt", "r");
	len = fread(dicbuf, sizeof(char), MAX_DICTIONARY_SIZE * MAX_MAT_SIZE, dictionaryFile);
	dicbuf[len] = '\0';
	for (register int i = 0; i < len; i++)
	{
		if ('a' <= dicbuf[i] && dicbuf[i] <= 'z')
		{
			kbd1 = kbd1 * 131 + dicbuf[i];
		}
		else if (dicbuf[i] == '\r')
		{
			kbd2 = (kbd1 & 0x7fffffff) % MAX_DICTIONARY_SIZE;
			kbd1 = (kbd1 & 0x7fffffff) % MAX_STOPWORD_SIZE;
			dicbuf[i] = '\0';
			if (stopwords[kbd1].word == NULL)
				index = 0;
			else if (strcmp(stopwords[kbd1].word, dicbuf + preLoc) == 0)
				index = 1;
			else
				for (int i = 0; i < stopwords[kbd1].anotionSize; i++)
				{
					if (strcmp(stopwords[kbd1].anotion[i], dicbuf + preLoc) == 0)
					{
						index = 1;
						break;
					}
				}
			if (index == 0)
			{
				if (dictionary[kbd2].word == NULL)
				{
					dictionary[kbd2].word = dicbuf + preLoc;
				}
				else
				{
					if (dictionary[kbd2].anotion == NULL)
						dictionary[kbd2].anotion = (char**)malloc(sizeof(char*) * MAX_TRASH_SIZE);
					dictionary[kbd2].anotion[dictionary[kbd2].anotionSize++] = dicbuf + preLoc;
				}



			}
			preLoc = i + 2;
			index = kbd2 = kbd1 = 0;
		}
	}
	fclose(dictionaryFile);
}
void readKeyWords(int argc, char** argv)
{
	register unsigned int kbd2 = 0, kbd3 = 0, index = 0;
	rankCount = atoi(argv[1]);
	for (int i = 2; i < argc; ++i)
	{
		kbd3 = kbd2 = 0;
		for (int j = 0; j < strlen(argv[i]); ++j)
			kbd2 = kbd2 * 131 + argv[i][j];
		kbd3 = (kbd2 & 0x7fffffff) % MAX_KEYWORD_SIZE;
		kbd2 = (kbd2 & 0x7fffffff) % MAX_DICTIONARY_SIZE;
		if (dictionary[kbd2].word == NULL)
			index = 0;
		else if (strcmp(dictionary[kbd2].word, argv[i]) == 0)
			index = 1;
		else
		{
			for (int j = 0; j < dictionary[kbd2].anotionSize; ++j)
				if (strcmp(dictionary[kbd2].anotion[j], argv[i]) == 0)
				{
					index = 1;
					break;
				}
		}
		if (index == 1)
		{
			index = 0;
			keyWordIndex[keyWordCount++] = kbd3;
			if (keywords[kbd3].word == NULL)
				keywords[kbd3].word = argv[i];
			else
			{
				if (keywords[kbd3].anotion == NULL)
					keywords[kbd3].anotion = (char**)malloc(sizeof(char*) * MAX_TRASH_SIZE);
				keywords[kbd3].anotion[keywords[kbd3].anotionSize++] = argv[i];
			}

		}
	}
}
void readStopWords()
{
	register unsigned int kbd = 0;
	int len = 0, preLoc = 0;
	stopbuf = (char*)malloc(sizeof(char) * 100000);
	FILE* stopWordFile = fopen("stopwords.txt", "r");
	len = fread(stopbuf, sizeof(char), 100000, stopWordFile);
	for (register int i = 0; i < len; ++i)
	{
		if ('a' <= stopbuf[i] && stopbuf[i] <= 'z')
		{
			kbd = kbd * 131 + stopbuf[i];
		}
		else if (stopbuf[i] == '\r')
		{
			stopbuf[i] = '\0';
			kbd = (kbd & 0x7fffffff) % MAX_STOPWORD_SIZE;
			if (stopwords[kbd].word == NULL)
			{
				stopwords[kbd].word = stopbuf + preLoc;
			}
			else
			{
				if (stopwords[kbd].anotion == NULL)
					stopwords[kbd].anotion = (char**)malloc(sizeof(char*) * MAX_TRASH_SIZE);
				stopwords[kbd].anotion[stopwords[kbd].anotionSize++] = stopbuf + preLoc;
			}
			preLoc = i + 2; kbd = 0;
		}
	}
	fclose(stopWordFile);
}





