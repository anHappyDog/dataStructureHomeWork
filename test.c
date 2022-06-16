#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define _for(i,a,b) for(register int i = (a); i< (b);++i)
#define MAX_READ_SIZE 6400000
#define MAX_STO_SIZE 4000
#define MAX_KEY_SIZE 64
#define MAX_NODE_SIZE 2000000
#define MAX_FILE_SIZE 20000
typedef struct trie Trie, * pTrie;
typedef struct filenode fileNode, * pNode;
struct trie {
	int iskey, isdic, issto, num;
	pTrie next[26];
};
struct filenode {

	double sim;
	int webpage, firstnum, lastnum;
	double keyfileshowCount[MAX_KEY_SIZE];
};
int len, usednodeCount = -1, rankCount, keyCount, fileCount;
double keyshowCount[MAX_KEY_SIZE];
char buf[MAX_READ_SIZE];
pTrie utrie = NULL, tempptrl = NULL;
Trie node[MAX_NODE_SIZE];
fileNode  fileinfo[MAX_FILE_SIZE];

void dic();
void sto();
void arc();
void key(int argc, char** argv);
void cal();
void show();
int cmp(const void* a, const void* b);
int main(int argc, char** argv)
{
	sto();
	dic();
	key(argc, argv);
	arc();
	cal();
	show();
	return 0;
}
void show()
{
	FILE* resfile = fopen("results.txt", "w");

	_for(i, 0, rankCount)
	{
		if (fileinfo[i].sim < 1e-6)
			break;
		if (i < 5 && i < fileCount)
			printf("%.6f %d %d-%d\n", fileinfo[i].sim, fileinfo[i].webpage, fileinfo[i].firstnum, fileinfo[i].lastnum);
		if (i < fileCount)
			fprintf(resfile, "%.6f %d %d-%d\n", fileinfo[i].sim, fileinfo[i].webpage, fileinfo[i].firstnum, fileinfo[i].lastnum);
	}

	fclose(resfile);
}
void cal()
{
	_for(i, 0, keyCount)
		if (keyshowCount[i] > 0)
			keyshowCount[i] = log10(fileCount / keyshowCount[i]);
	_for(i, 0, fileCount)
		_for(j, 0, keyCount)
		fileinfo[i].sim += fileinfo[i].keyfileshowCount[j] * keyshowCount[j];
	qsort(fileinfo, fileCount, sizeof(fileNode), cmp);
}
int cmp(const void* a, const void* b)
{
	pNode aa = (pNode)a, bb = (pNode)b;
	if (aa->sim - bb->sim > 1e-6)
		return -1;
	else if (aa->sim - bb->sim < -1e-6)
		return 1;
	else
		return aa->webpage - bb->webpage;
}
void arc()
{
	int firstnum = 0, lastnum = 0;
	register unsigned char x = 0;
	register unsigned int wordCount = 0;
	tempptrl = utrie;
	FILE* arcfile = fopen("article.txt", "r");
	fscanf(arcfile, "%d-%d", &firstnum, &lastnum);
	fileinfo[fileCount].webpage = fileCount + 1;
	fileinfo[fileCount].firstnum = firstnum; fileinfo[fileCount].lastnum = lastnum;
	firstnum = lastnum = 0;
	while ((len = fread(buf, sizeof(char), MAX_READ_SIZE, arcfile)) != 0)
	{
		_for(i, 0, len)
		{
			if (('a' <= buf[i] && buf[i] <= 'z') || ('A' <= buf[i] && buf[i] <= 'Z'))
			{
				if ('A' <= buf[i] && buf[i] <= 'Z')
					x = buf[i] - 'A';
				else
					x = buf[i] - 'a';
				if (tempptrl != NULL)
					tempptrl = tempptrl->next[x];
			}
			else if (buf[i] != '\f')
			{
				if (tempptrl != NULL && tempptrl->isdic == 1)
				{
					++wordCount;
					if (tempptrl->iskey == 1)
					{
						if (++fileinfo[fileCount].keyfileshowCount[tempptrl->num] == 1)
							++keyshowCount[tempptrl->num];
					}
				}
				tempptrl = utrie;
			}
			else if (buf[i] == '\f')
			{
				_for(j, 0, keyCount)
					fileinfo[fileCount].keyfileshowCount[j] = fileinfo[fileCount].keyfileshowCount[j] / wordCount * 100;
				i += 3;//linux Ϊ3
				while ('0' <= buf[i] && buf[i] <= '9')
				{
					firstnum = firstnum * 10 + buf[i] - '0';
					++i;
				}
				++i;
				while ('0' <= buf[i] && buf[i] <= '9')
				{
					lastnum = lastnum * 10 + buf[i] - '0';
					++i;
				}
				++fileCount;
				fileinfo[fileCount].webpage = fileCount + 1;
				fileinfo[fileCount].firstnum = firstnum; fileinfo[fileCount].lastnum = lastnum;
				firstnum = lastnum = 0;
				wordCount = 0;
			}
		}
	}
	_for(j, 0, keyCount)
		fileinfo[fileCount].keyfileshowCount[j] = fileinfo[fileCount].keyfileshowCount[j] / wordCount * 100;
	++fileCount;
	fclose(arcfile);
}
void key(int argc, char** argv)
{
	register unsigned char x = 0;
	tempptrl = utrie;
	keyCount = argc - 2;
	rankCount = atoi(argv[1]);
	_for(i, 2, argc)
	{
		_for(j, 0, strlen(argv[i]))
		{
			x = argv[i][j] - 'a';
			if (tempptrl->next[x] == NULL)
				tempptrl->next[x] = &node[++usednodeCount];
			tempptrl = tempptrl->next[x];
		}
		if (tempptrl->isdic == 1)
		{
			tempptrl->num = i - 2;
			tempptrl->iskey = 1;
		}
		tempptrl = utrie;
	}
}
void dic()
{
	register unsigned char x = 0;
	tempptrl = utrie;
	FILE* dicfile = fopen("dictionary.txt", "r");
	len = fread(buf, sizeof(char), MAX_READ_SIZE, dicfile);
	_for(i, 0, len)
	{
		if ('a' <= buf[i] && buf[i] <= 'z')
		{
			x = buf[i] - 'a';
			if (tempptrl->next[x] == NULL)
				tempptrl->next[x] = &node[++usednodeCount];
			tempptrl = tempptrl->next[x];
		}
		else if (buf[i] == '\r')
		{
			if (tempptrl->issto != 1)
				tempptrl->isdic = 1;
			tempptrl = utrie;
			++i;
		}
	}
	fclose(dicfile);
}
void sto()
{
	register unsigned char x = 0;
	FILE* stofile = fopen("stopwords.txt", "r");
	utrie = &node[++usednodeCount];
	tempptrl = utrie;
	len = fread(buf, sizeof(char), MAX_STO_SIZE, stofile);
	_for(i, 0, len)
	{
		if ('a' <= buf[i] && buf[i] <= 'z')
		{
			x = buf[i] - 'a';
			if (tempptrl->next[x] == NULL)
				tempptrl->next[x] = &node[++usednodeCount];
			tempptrl = tempptrl->next[x];
		}
		else if (buf[i] == '\r')
		{
			tempptrl->issto = 1;
			tempptrl = utrie;
			++i;
		}
	}
	fclose(stofile);
}