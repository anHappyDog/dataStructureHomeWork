#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct node Node;
typedef struct node* List;
struct node {
	int val;
	char word[100];
	List next;
};
List Create(char wor[])
{
	List ptrl = (List)malloc(sizeof(Node));
	ptrl->val = 1;
	strcpy(ptrl->word, wor);
	ptrl->next = NULL;
	return ptrl;
}
int size(List ptrl)
{
	int count = 0;
	List temp = ptrl;
	while (temp)
	{
		count++;
		temp = temp->next;

	}
	return count;

}
List Bubble(List ptrl)
{
	int count = size(ptrl);
	List temp = ptrl, temp1 = NULL;
	for (int i = 0; i < count-1; i++)
	{
		temp = ptrl;
		for (int j = 0; j < count - i - 1; j++)
		{
			if (strcmp(temp->word, temp->next->word) < 0)
			{
				temp->val ^= temp->next->val;
				temp->next->val ^= temp->val;
				temp->val ^= temp->next->val;
				char tt[100];
				strcpy(tt, temp->word);
				strcpy(temp->word, temp->next->word);
				strcpy(temp->next->word, tt);
			}
		}

	}
	/*while (temp->next != NULL)
	{
		temp1 = temp->next;
		while (temp1->next != NULL)
		{
			if (strcmp(temp1->word, temp1->next->word) > 0)
			{
				temp1->val ^= temp1->next->val;
				temp1->next->val ^= temp1->val;
				temp1->val ^= temp1->next->val;
				char tt[100];
				strcpy(tt, temp->word);
				strcpy(temp->word, temp->next->word);
				strcpy(temp->next->word, tt);
			}
			temp1 = temp1->next;
		}
		temp = temp->next;
	}*/
	
	return ptrl;
}
int main()
{
	int i = 0, index = 0;
	int top1 = -1;
	char temp[100];
	char c;
	char FileChar[10000];
	int top = 0;
	FILE* fp = NULL;
	List ptrl = NULL, tempx = NULL;
	fp = fopen("article.txt", "r");
	if (fp == NULL)
	{
		printf("打开文件失败");
		return -1;
	}
	while ((c = fgetc(fp)) != EOF)
	{
		FileChar[top++] = c;
	}
	FileChar[top] = '\0';

	while (i < strlen(FileChar))
	{
		index = 0;
		while (i < strlen(FileChar) && !isalpha(FileChar[i]))
		{
			i++;
		}
		if (i < strlen(FileChar) && isalpha(FileChar[i]))
		{

			top1 = 0;
			while (i < strlen(FileChar) && isalpha(FileChar[i]))
			{
				temp[top1++] = tolower(FileChar[i++]);
			}
			temp[top1] = '\0';
			if (ptrl == NULL)
			{
				ptrl = Create(temp);
			}
			else
			{
				tempx = ptrl;
				while (tempx != NULL)
				{
					if (strcmp(tempx->word, temp) == 0)
					{
						tempx->val++;
						index = 1;
						break;
					}
					tempx = tempx->next;
				}
				if (index == 0)
				{
					List tempxx = Create(temp);
					if (strcmp(ptrl->word, temp) > 0)
					{
						tempxx->next = ptrl;
						ptrl = tempxx;
					}
					else
					{
						List preP = ptrl;
						tempx = ptrl->next;
						while (tempx != NULL && strcmp(tempx->word, temp) < 0)
						{
							preP = tempx;
							tempx = tempx->next;
						}



						preP->next = tempxx;
						tempxx->next = tempx;
					}
					


				}
			}



		}

		i++;
	}
	
	//ptrl = Bubble(ptrl);
	tempx = ptrl;
	while (tempx)
	{

		printf("%s %d\n", tempx->word, tempx->val);
		tempx = tempx->next;
	}
	fclose(fp);
	return 0;
}
