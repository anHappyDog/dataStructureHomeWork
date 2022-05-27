#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Node Lnode;
typedef struct Node* List;
struct Node {

	int zhishu;
	int xishu;
	List next;

};
List createNode(int x, int y)
{
	List ptrl = (List)malloc(sizeof(Lnode));
	ptrl->xishu = x;
	ptrl->zhishu = y;
	ptrl->next = NULL;
	return ptrl;
}
int size(List ptrl)
{
	int num = 0;
	List temp = ptrl;
	while (temp)
	{
		num++;
		temp = temp->next;
	}
	return num;

}
List returnLastNode(List ptrl)
{
	List temp = ptrl;
	if (temp == NULL)
		return NULL;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}
List readNum(char inputString[])
{
	int x, y;
	int choice = 0;
	int num = 0;
	int iffu = 1;
	List ptrl = NULL, temp = NULL;
	for (int i = 0; i < strlen(inputString); i++)
	{
		if (isdigit(inputString[i]))
		{
			num = num * 10 + inputString[i] - '0';
		}
		else if(inputString[i] !='-')
		{
			if (choice == 0)
			{
				choice = 1;
				x = num *iffu;
				num = 0;
				iffu = 1;
			}
			else
			{
				y = num*iffu;
				iffu = 1;
				num = 0;
				choice = 0;
				if (ptrl == NULL)
				{
					ptrl = createNode(x, y);
					temp = ptrl;
				}
				else
				{
					List  node = createNode(x, y);
					temp->next = node;
					temp = temp->next;
				}
			}
		}
		else if (inputString[i] == '-')
		{
			iffu = -1;
		}
	}
	if (ptrl == NULL)
	{
		ptrl = createNode(x, num*iffu);
		temp = ptrl;
	}
	else
	{
	List  node = createNode(x, num*iffu);
	
	temp->next = node;
	temp = temp->next;
	}
	
	return ptrl;
}
List FindZhishu(List ptrl, int x)
{
	List temp = ptrl;
	while (temp)
	{
		if (temp->zhishu == x)
		{
			return temp;
		}
		temp = temp->next;
	}

	return NULL;

}
List returnPrePtrl(List ptrl, List temp1)
{
	List temp = ptrl;
	if (temp == NULL)
		return NULL;
	while (temp)
	{
		if (temp->next == temp1)
			return temp;
		temp = temp->next;
	}
	return NULL;
}
List multi(List ptrl1, List ptrl2)
{
	List ptrl = NULL;
	List temp1 = ptrl1, temp2 = ptrl2;
	while (temp1 != NULL)
	{
		temp2 = ptrl2;
		while (temp2 != NULL)
		{
			if (ptrl == NULL)
			{
				ptrl = createNode(temp1->xishu * temp2->xishu, temp1->zhishu + temp2->zhishu);
			}
			else
			{
				List findPtrl = FindZhishu(ptrl, temp1->zhishu + temp2->zhishu);
				if (findPtrl != NULL)
				{
					findPtrl->xishu += temp1->xishu * temp2->xishu;
					if (findPtrl->xishu == 0)
					{
						List PrePtrl = returnPrePtrl(ptrl, findPtrl);
						List destr = findPtrl;
						PrePtrl->next = destr->next;
						free(destr);
					}
				}
				else
				{
					List node = createNode(temp1->xishu * temp2->xishu, temp1->zhishu + temp2->zhishu);
					returnLastNode(ptrl)->next = node;
				}

			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
	return ptrl;

}
List Bubble(List ptrl)
{
	List temp = ptrl;
	int num = size(ptrl);
	for (int i = 0; i < num - 1; i++)
	{
		temp = ptrl;
		for (int j = 0; j < num - 1 - i; j++)
		{
			if (temp->next->zhishu > temp->zhishu)
			{
				temp->next->zhishu ^= temp->zhishu;
				 temp->zhishu^= temp->next->zhishu;
				temp->next->zhishu ^= temp->zhishu;
				temp->next->xishu ^= temp->xishu;
				temp->xishu ^= temp->next->xishu;
				temp->next->xishu ^= temp->xishu;
			}

			temp = temp->next;
		}
	}


	return ptrl;
}
int main()
{
	char inputString[1000];
	gets(inputString);
	List ptrl1 = readNum(inputString);
	gets(inputString);
	List ptrl2 = readNum(inputString);
	List ptrl3 = multi(ptrl1, ptrl2);
	List temp = ptrl1;
	/*while (temp)
	{
		printf("%d %d ", temp->xishu, temp->zhishu);
		temp = temp->next;
	}
	printf("\n");
	temp = ptrl2;
	while (temp)
	{
		printf("%d %d ", temp->xishu, temp->zhishu);
		temp = temp->next;
	}
	printf("\n");*/
	ptrl3 = Bubble(ptrl3);
	temp = ptrl3;
	while (temp)
	{
		printf("%d %d ", temp->xishu, temp->zhishu);
		temp = temp->next;
	}

	return 0;
}
