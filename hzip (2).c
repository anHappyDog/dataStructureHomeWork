#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_FILENAME_SIZE 512
#define MAX_HAFFMAN_SIZE 64

typedef struct BTree* BTnode;
typedef struct Forest forest;
struct BTree {
	char c;
	int weight;
	BTnode lchild, rchild;

};
struct Forest {
	BTnode tree;
};


char Src[MAX_FILENAME_SIZE], Obj[MAX_FILENAME_SIZE];
int AscWeight[128] = { 0 };
char haffamanCode[128][MAX_HAFFMAN_SIZE];
unsigned char chrCount = 0;

void writeFinalToObjFile();
int inputOrderProcess(int argc, char** argv);
void readChrFromFile();
BTnode createNode(char c, int weight);
void bubbleSortForFoest(forest tempForest[], int forestTop);
void createChildTree(forest tempForest[], int* forestTop);
BTnode createHaffmanTree();
void createHaffmanCode(BTnode root);
void usedForCreateHaffmanCode(BTnode root, char tempStr[]);
int main(int argc, char** argv)
{
	BTnode root = NULL;
	if (inputOrderProcess(argc, argv) == -1)
		return -1;
	readChrFromFile();
	root = createHaffmanTree();
	createHaffmanCode(root);
	writeFinalToObjFile();
	return 0;
}


//��������������в���
int inputOrderProcess(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("Usage: hzip.exe [-u] <filename>\n");
		return -1;
	}
	else if (argc > 2 && strcmp(argv[1], "-u") != 0)
	{
		printf("Usage: hzip.exe [-u] <filename>\n");
		return -1;
	}
	//�������������
	else if (argc > 1 && strstr(argv[argc - 1], "txt") == NULL)
	{
		printf("File extension error!\n");
		return -1;
	}

	//��ѹ��������
	strcpy(Src, argv[1]);
	for (int i = 0; i < strlen(Src); i++)
	{
		if (Src[i] != '.')
			Obj[i] = Src[i];
		else
		{
			Obj[i] = '.'; Obj[i + 1] = 'h'; Obj[i + 2] = 'z';
			Obj[i + 3] = 'i'; Obj[i + 4] = 'p';
			Obj[i + 5] = '\0';
			break;
		}
	}
	return 1;
}
//��һ�ζ�ȡ�ļ����Ȩ��
void readChrFromFile()
{
	char tempChr;
	FILE* srcFile = fopen(Src, "r");
	if (srcFile == NULL)
	{
		printf("open file error");
		return;
	}
	while (!feof(srcFile))
	{
		tempChr = fgetc(srcFile);
		AscWeight[tempChr]++;
	}
	AscWeight[0] = 1;
	fclose(srcFile);
}
//�����ڵ�
BTnode createNode(char c, int weight)
{
	BTnode ptrl = (BTnode)malloc(sizeof(struct BTree));
	ptrl->c = c;
	ptrl->weight = weight;
	ptrl->lchild = NULL; ptrl->rchild = NULL;
	return ptrl;
}
//���ڵ�һ������
void bubbleSortForFoest(forest tempForest[], int forestTop)
{
	int flag = 0;
	BTnode temp = NULL;
	for (int i = 0; i <= forestTop - 1; i++)
	{
		flag = 0;
		for (int j = 0; j <= forestTop - i - 1; j++)
		{
			if (tempForest[j].tree->weight > tempForest[j + 1].tree->weight)
			{
				temp = tempForest[j].tree;
				tempForest[j].tree = tempForest[j + 1].tree;
				tempForest[j + 1].tree = temp;
				flag = 1;
			}
			else if (tempForest[j].tree->weight == tempForest[j + 1].tree->weight && tempForest[j].tree->c > tempForest[j + 1].tree->c)
			{
				temp = tempForest[j].tree;
				tempForest[j].tree = tempForest[j + 1].tree;
				tempForest[j + 1].tree = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			return;
	}
}
//�������������ڲ�����������
void createChildTree(forest tempForest[], int* forestTop)
{
	int s = 2;
	BTnode tempPtrl = (BTnode)malloc(sizeof(struct BTree));
	tempPtrl->lchild = tempForest[0].tree;
	tempPtrl->rchild = tempForest[1].tree;
	tempPtrl->weight = tempForest[0].tree->weight + tempForest[1].tree->weight;
	if (*forestTop == 1)
	{
		tempForest[0].tree = tempPtrl;
		(*forestTop)--;
		return;
	}
	else if (*forestTop > 1)
	{
		if (tempPtrl->weight < tempForest[2].tree->weight)
		{
			tempForest[1].tree = tempPtrl;
		}
		else if (tempPtrl->weight >= tempForest[*forestTop].tree->weight)
		{
			for (int i = 0; i < *forestTop; i++)
			{
				tempForest[i] = tempForest[i + 1];
			}
			tempForest[*forestTop].tree = tempPtrl;

		}
		else
		{
			while (tempPtrl->weight >= tempForest[s].tree->weight)
				s++;
			for (int i = 1; i < s - 1; i++)
				tempForest[i] = tempForest[i + 1];
			tempForest[s - 1].tree = tempPtrl;
		}
	}
	for (int i = 0; i < *forestTop; i++)
		tempForest[i] = tempForest[i + 1];
	(*forestTop)--;
}
//������������
BTnode createHaffmanTree()
{
	int forestTop = -1;
	forest tempForest[128];
	BTnode tempPtrl = NULL;
	for (int i = 0; i < 128; i++)
	{
		if (AscWeight[i] > 0)
		{
			tempPtrl = createNode(i, AscWeight[i]);
			tempForest[++forestTop].tree = tempPtrl;
			chrCount++;
		}
	}
	bubbleSortForFoest(tempForest, forestTop);
	do {
		createChildTree(tempForest, &forestTop);
	} while (forestTop > 0);
	return tempForest[0].tree;
}
//��������������
void usedForCreateHaffmanCode(BTnode root, char tempStr[])//ʵ�ִ���
{
	char temp[MAX_HAFFMAN_SIZE];
	strcpy(temp, tempStr);
	if (root->lchild == NULL && root->rchild == NULL)
	{
		strcpy(haffamanCode[root->c], temp);
	}
	else
	{

		temp[strlen(tempStr) + 1] = '\0';
		if (root->lchild != NULL)
		{
			temp[strlen(tempStr)] = '0';
			usedForCreateHaffmanCode(root->lchild, temp);
		}
		if (root->rchild != NULL)
		{
			temp[strlen(tempStr)] = '1';
			usedForCreateHaffmanCode(root->rchild, temp);
		}

	}

}
//�˿ڣ�����Ϊ�˺ÿ�
void createHaffmanCode(BTnode root)
{
	char tempStr[32] = "";
	usedForCreateHaffmanCode(root, tempStr);
}
//���haffman����,��һ����
void outputHaffmanCode(FILE* objFile, int i)
{
	int aIndex = 0;//����λ��
	unsigned char temp = 0;
	for (int j = 0; j < strlen(haffamanCode[i]); j++)
	{
		temp = (temp << 1) | (haffamanCode[i][j] - '0');
		if ((aIndex + 1) % 8 == 0)
		{
			fputc(temp, objFile);
			aIndex = 0;
			temp = 0;
		}
		else
		{
			aIndex++;
		}
	}
	if (temp != 0 || aIndex != 0)
	{
		temp <<= (8 - aIndex);
		fputc(temp, objFile);
		aIndex = 0;
		temp = 0;
	}
}
//�����һ���֣�����������
void writeFirstFinalToObjFile(FILE* objFile)
{
	unsigned char temp = 0;
	fputc(chrCount, objFile);
	for (int i = 0; i < 128; i++)
	{
		if (AscWeight[i] > 0)
		{
			fputc((unsigned char)i, objFile);
			fputc((unsigned char)strlen(haffamanCode[i]), objFile);
			outputHaffmanCode(objFile, i);
		}
	}
}
void writeSecondFinalToObjFile(FILE* objFile)
{
	int ifeof = 0;
	int aIndex = 0;//����λ��
	unsigned char temp = 0;
	char tempChr;
	FILE* txtFile = fopen(Src, "r");
	if (txtFile == NULL)
	{
		printf("open file error");
		return;
	}
	while (1)
	{
		tempChr = fgetc(txtFile);
		//outputHaffmanCode(objFile, tempChr);
		if (tempChr == EOF)
		{
			tempChr = 0;
			ifeof = 1;
		}
		for (int j = 0; j < strlen(haffamanCode[tempChr]); j++)
		{
			temp = (temp << 1) | (haffamanCode[tempChr][j] - '0');
			if ((aIndex + 1) % 8 == 0)
			{
				fputc(temp, objFile);
				aIndex = 0;
				temp = 0;
			}
			else
			{
				aIndex++;
			}
		}
		if (ifeof == 1)
			break;
	}
	if (aIndex != 0)
	{
		temp <<= (8 - aIndex);
		fputc(temp, objFile);
		aIndex = 0;
		temp = 0;
	}
	fclose(txtFile);
}
//������
void writeFinalToObjFile()
{
	FILE* objFile = fopen(Obj, "w");
	if (objFile == NULL)
	{
		printf("open file error");
		return;
	}
	writeFirstFinalToObjFile(objFile);
	writeSecondFinalToObjFile(objFile);
	fclose(objFile);
}





