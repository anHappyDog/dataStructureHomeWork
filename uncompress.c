#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_HAFUMAN_SIZE 128
#define MAX_CHR_SIZE 128
#define MAX_FILENAME_SIZE 128
typedef struct node Node, * Pnode;
struct node {
	char chr;
	Pnode lchild, rchild;

};


int chrCount = 0;//字符个数
int chrLocate[MAX_CHR_SIZE];//字符下标
//int sortedChrLocate[MAX_CHR_SIZE];//排序后（长度从大到小）的数组下标
char haffumanCode[MAX_CHR_SIZE][MAX_FILENAME_SIZE];//哈夫曼编码
char sRc[MAX_FILENAME_SIZE], oBj[MAX_FILENAME_SIZE];//读文件和写文件

void getFileExt(char tempFileName[], char fileExt[]);
int  orderProcess(int argc, char** argv);
void readHaffumanCodeFromSrc(FILE* srcFile);
Pnode createHaffmanTree(Pnode root);
void readContentToFile(Pnode root, FILE* srcFile);
void bubbleSortForChrLocate();
void copyNameToObj(char fileName[], int mode);

//test 前序
void preOrder(Pnode ptrl);

int main(int argc, char** argv)
{
	Pnode root = NULL;
	FILE* srcFile = NULL;
	if (orderProcess(argc, argv) == -1)
	{
		return -1;
	}
	srcFile = fopen(sRc, "rb");
	if (srcFile == NULL)
	{
		printf("open src file error");
		return -1;
	}
	readHaffumanCodeFromSrc(srcFile);
	bubbleSortForChrLocate();
	root = createHaffmanTree(root);
	//preOrder(root);
	readContentToFile(root, srcFile);
	fclose(srcFile);
	return 0;
}
void preOrder(Pnode ptrl)
{
	if (ptrl != NULL)
	{
		if (ptrl->chr >= 0)
			printf("%c\n", ptrl->chr);
		preOrder(ptrl->lchild);
		preOrder(ptrl->rchild);
	}


}

void copyNameToObj(char fileName[], int mode)
{
	int top = 0;
	while (top < strlen(fileName) && fileName[top] != '.')
	{
		oBj[top] = fileName[top];
		top++;
	}
	if (mode == 1)
	{//压缩

		oBj[top++] = '.';
		oBj[top++] = 'h'; oBj[top++] = 'z';
		oBj[top++] = 'i'; oBj[top++] = 'p';
		oBj[top++] = '\0';
	}
	else if (mode == 2)
	{//解压缩
		oBj[top++] = '.';
		oBj[top++] = 't'; oBj[top++] = 'x';
		oBj[top++] = 't'; oBj[top++] = '\0';
	}

}
void readContentToFile(Pnode root, FILE* srcFile)
{
	int bitCont = 0;
	int tempChr = 0;
	Pnode temp = root;
	FILE* objFile = fopen(oBj, "w");
	while ((tempChr = fgetc(srcFile))!=EOF)
	{
		//fread(&tempChr, sizeof(unsigned char), 1, srcFile);
		//tempChr = fgetc(srcFile);
		
		//(tempChr = fgetc(srcFile)) != EOF
	
		while (bitCont < 8)
		{
			if (temp->chr > -1)
			{
				fputc(temp->chr, objFile);
				temp = root;
			}
			else if (((tempChr & 0X80) >> 7) == 0)
			{
				temp = temp->lchild;
				tempChr <<= 1;
				bitCont++;
			}
			else if (((tempChr & 0X80) >> 7) == 1)
			{
				temp = temp->rchild;
				tempChr <<= 1;
				bitCont++;
			}
		}
		bitCont = 0;
		
	}
	
	fclose(objFile);
}
void bubbleSortForChrLocate()
{
	int flag = 0;
	for (int i = 0; i < chrCount - 1; i++)
	{
		flag = 0;
		for (int j = 0; j < chrCount - i - 1; j++)
		{
			if (strlen(haffumanCode[chrLocate[j]]) < strlen(haffumanCode[chrLocate[j + 1]]))
			{
				chrLocate[j] ^= chrLocate[j + 1];
				chrLocate[j + 1] ^= chrLocate[j];
				chrLocate[j] ^= chrLocate[j + 1];
				flag = 1;
			}
		}
		if (flag == 0)
			return;
	}

}
Pnode createNode(char chr)
{
	Pnode ptrl = (Pnode)malloc(sizeof(Node));
	ptrl->chr = chr;
	ptrl->lchild = ptrl->rchild = NULL;
	return ptrl;
}
Pnode createHaffmanTree(Pnode root)
{
	Pnode temp = NULL;
	root = createNode(-1);
	temp = root;
	for (int i = 0; i < chrCount; i++)
	{
		temp = root;
		for (int j = 0; j < strlen(haffumanCode[chrLocate[i]]); j++)
		{
			if (haffumanCode[chrLocate[i]][j] == '0')
			{
				if (temp->lchild != NULL)
					temp = temp->lchild;
				else
				{
					temp->lchild = createNode(-1);
					temp = temp->lchild;
				}
			}
			else if (haffumanCode[chrLocate[i]][j] == '1')
			{
				if (temp->rchild != NULL)
					temp = temp->rchild;
				else
				{
					temp->rchild = createNode(-1);
					temp = temp->rchild;
				}
			}
		}
		temp->chr = chrLocate[i];
	}
	return root;
}
void readHaffumanCodeFromSrc(FILE* srcFile)
{
	int readChrCount = 0, bitCount = 0;
	unsigned char tempChr = 0, chrLength = 0, tempByte = 0;
	chrCount = fgetc(srcFile);

	while (readChrCount < chrCount)
	{
		//if (readChrCount == 78)
		//	printf("\n");
		/*if (readChrCount == 70)
		{
			printf("\n");
		}*/
		tempChr = fgetc(srcFile);
		chrLength = fgetc(srcFile);
		chrLocate[readChrCount++] = tempChr;
		tempByte = fgetc(srcFile);
		for (bitCount = 0; bitCount < chrLength; bitCount++)
		{
			//printf("%c",tempByte % 2 + '0');
			haffumanCode[tempChr][bitCount] = '0' + ((tempByte & 0X80) >> 7);
			tempByte <<= 1;
			if (((bitCount + 1) % 8 == 0) && bitCount < chrLength - 1)
			{
				tempByte = fgetc(srcFile);
			}
		}
		haffumanCode[tempChr][bitCount] = '\0';
		//printf("%d %s\n", readChrCount, haffumanCode[tempChr]);
	}
}
void getFileExt(char tempFileName[], char fileExt[])
{

	int i = 0, top = 0;
	while (i < strlen(tempFileName) && tempFileName[i] != '.')
		i++;
	i++;
	if (i < strlen(tempFileName))
	{
		while (i < strlen(tempFileName))
			fileExt[top++] = tempFileName[i++];
		fileExt[top] = '\0';
	}
}
int orderProcess(int argc, char** argv)
{
	char fileExt[MAX_FILENAME_SIZE];
	char tempFileName[MAX_FILENAME_SIZE];
	if (argc == 1)
	{
		printf("Usage: hzip.exe [-u] <filename>\n");
		return -1;
	}
	else if (argc == 2)
	{
		getFileExt(argv[1], fileExt);
		if (strcmp(fileExt, "hzip") != 0)
		{
			printf("File extension error!\n");
			return -1;
		}
		else
		{
			strcpy(sRc, argv[1]);
			copyNameToObj(argv[1], 1);
			return 1;
		}

	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-u") != 0)
		{
			printf("Usage: hzip.exe [-u] <filename>\n");
			return -1;
		}
		getFileExt(argv[2], fileExt);
		if (strcmp(fileExt, "hzip") != 0)
		{
			printf("File extension error!\n");
			return -1;
		}
		else
		{
			strcpy(sRc, argv[2]);
			copyNameToObj(argv[2], 2);
			return 1;
		}
	}

}





