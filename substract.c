#include<stdio.h>
#include<string.h>
#include<ctype.h>
void TurnNum(char num1[],char num2[],int*top1,int*top2);
void InputNum(char inputNum[], char num[],int* top);
void Calculate(char num1[], char num2[],char num[],int top1,int top2,int *top3);
int main()
{
	char inputNumOne[100],inputNumTwo[100],NumOne[100],NumTwo[100],num[100],finnalnum[100];
	int top1 = 0, top2 = 0, top3 = 0,sign = -1;
	scanf("%s",inputNumOne);
	scanf("%s",inputNumTwo);
	InputNum(inputNumOne,NumOne,&top1);
	InputNum(inputNumTwo, NumTwo, &top2);
	if (top1 < top2)
	{
		num[top3++] = '-';
		TurnNum(NumOne,NumTwo,&top1,&top2);
	}
	Calculate(NumOne, NumTwo, num, top1, top2, &top3);
	/*else if (top1 == top2)
	{

	}
	else
	{

	}*/
	num[top3] = '\0';
	top3 = 0;
	InputNum(num,finnalnum,&top3);
	if (top3 == 0)
	{
		finnalnum[top3++] = '0';
	}
	finnalnum[top3] = '\0';
	printf("%s",finnalnum);

	return 0;
}
void Calculate(char num1[], char num2[], char num[], int top1, int top2, int* top3)
{
	for (int i = 0;i < top1 - top2;i++)
	{
		num[(*top3)++] = num1[i];
	}
	for (int i = top1 - top2; i < top1;i++)
	{
		if(num1[i] >= num2[i - top1 + top2])
			num[(*top3)++] = num1[i] - num2[i - top1 + top2] + '0';

		if(num1[i] < num2[i - top1 + top2])
		{
			int temp = (*top3);
			num[(*top3)++] = num1[i] - num2[i - top1 + top2] + '0';
			int lasttemp = temp + 1;
			do {
				temp--;
				if (temp == 0 && num[temp] == '0')
				{
					(*top3) = 0;
					num[(*top3)++] = '-';
					TurnNum(num1, num2, &top1, &top2);
					Calculate(num1,num2,num,top1,top2,top3);
					return;
				}
				lasttemp = temp + 1;
				num[lasttemp] += 10;
				num[temp] -= 1;
			
			} while (num[temp] < '0');
			
			/*if (temp > 0)
			{
				if (num[temp] > 0)
				{
					num[temp] -= 1;
					num[*(top3)++] = num1[i] - num2[i - top1 + top2] + '0' + 10;

				}
			}*/
		}
	}

}
void TurnNum(char num1[], char num2[], int* top1, int* top2)
{
	char temp[100];
	strcpy(temp,num1);
	strcpy(num1,num2);
	strcpy(num2,temp);
	*top1 ^= *top2;
	*top2 ^= *top1;
	*top1 ^= *top2;

}
void InputNum(char inputNum[], char num[], int* top)
{
	int sign = -1;
	for (int i = 0; i < strlen(inputNum);i++)
	{
		if (inputNum[i] == '-')
			num[(*top)++] = '-';
		if (sign == -1 && inputNum[i] == '0')
			continue;
		else if (sign == -1 && inputNum[i] > '0')
		{
			sign = 1;
			num[(*top)++] = inputNum[i];
		}
		else if (sign == 1)
		{
			num[(*top)++] = inputNum[i];
		}
	}
	num[*top] = '\0';
}
//#include<stdio.h>
//#include<string.h>
//#include<ctype.h>
//int main()
//{
//	int sign = 0;//1ÎªÕý
//	char beijian[100];
//	char s1[100], s2[100], top1 = 0, top2 = 0, top3 = 0;
//	char jian[100];
//	char answer[100];
//	int i = 0, index = -1;
//	scanf("%s", beijian);
//	scanf("%s", jian);
//	while (i < strlen(beijian))
//	{
//		if (index == -1 && beijian[i] == '0')
//			continue;
//		else if (index == -1 && beijian[i] > '0')
//		{
//			index = 1;
//			s1[top1++] = beijian[i];
//		}
//		else if (index == 1)
//		{
//			s1[top1++] = beijian[i];
//		}
//		i++;
//	}
//	s1[top1] = '\0';
//	index = -1;i = 0;
//	while (i < strlen(jian))
//	{
//		if (index == -1 && jian[i] == '0')
//			continue;
//		else if (index == -1 && jian[i] > '0')
//		{
//			index = 1;
//			s2[top2++] = jian[i];
//		}
//		else if (index == 1)
//		{
//			s2[top2++] = jian[i];
//		}
//		i++;
//	}
//	s2[top2] = '\0';
//	if (top1 < top2)
//	{
//		int tt = top1;
//		top1 = top2;
//		top2 = tt;
//		char s3[120];
//		strcpy(s3, s1);
//		memset(s1, 0, sizeof(s1));
//		strcpy(s1, s2);
//		memset(s2, 0, sizeof(s2));
//		strcpy(s2, s3);
//		answer[top3++] = '-';
//		/*for (int j = 0;j < top2 - top1;j++)
//		{
//			answer[top3++] = s2[j];
//		}
//		for (int j = top2 - top1;j < top2;j++)
//		{
//			if (s2[j] >= s1[j - top2 + top1])
//			{
//				answer[top3++] = s2[j] - s1[j - top2 + top1] + '0';
//			}
//			else
//			{
//				int temp = top3 - 1;
//				answer[top3++] = s2[j] + 10 - s1[j - top2 + top1] + '0';
//				answer[temp]--;
//				while (answer[temp] < '0')
//				{
//					answer[temp] += 10;
//					answer[temp - 1] -= 1;
//					temp--;
//				}
//
//			}
//
//		}
//		*/
//	}
//	if (top1 == top2)
//	{
//		int biaoji = -1;
//		for (int j = 0; j < top1;j++)
//		{
//			sign = 1;
//			if (s1[j] > s2[j])
//			{
//				biaoji = 1;
//				answer[top3++] = s1[j] - s2[j] + '\0';
//			}
//			else if (s1[j] == s2[j])
//			{
//				if (biaoji == -1)
//					continue;
//				else if (biaoji == 1)
//				{
//					answer[top3++] = '0';
//
//				}
//			}
//			else
//			{
//
//				answer[top3++] = s1[j] - s2[j] + 10 + '0';
//				if (top3 - 1 == 0)
//				{
//					char s3[120];
//					memset(answer, 0, sizeof(answer));
//					top3 = 0;
//					strcpy(s3, s1);
//					memset(s1, 0, sizeof(s1));
//					strcpy(s1, s2);
//					memset(s2, 0, sizeof(s2));
//					strcpy(s2, s3);
//					answer[top3++] = '-';
//					sign = 0;
//					break;
//				}
//				else
//				{
//					int temp = top3 - 2;
//					if (sign == 0)
//						break;
//					while (answer[temp] < '0')
//					{
//						if (temp == 0 && answer[temp] == '0')
//						{
//							char s3[120];
//							memset(answer, 0, sizeof(answer));
//							top3 = 0;
//							strcpy(s3, s1);
//							memset(s1, 0, sizeof(s1));
//							strcpy(s1, s2);
//							memset(s2, 0, sizeof(s2));
//							strcpy(s2, s3);
//							answer[top3++] = '-';
//							sign = 0;
//							break;
//						}
//						/*for (int j = 0;j < top1 - top2;j++)
//						{
//							answer[top3++] = s1[j];
//						}
//						for (int j = top1 - top2;j < top1;j++)
//						{
//							if (s1[j] >= s2[j - top1 + top2])
//							{
//								answer[top3++] = s1[j] - s2[j - top1 + top2] + '0';
//							}
//							else
//							{
//								int temp = top3 - 1;
//								answer[top3++] = s1[j] + 10 - s2[j - top1 + top2] + '0';
//								answer[temp]--;
//								while (answer[temp] < '0')
//								{
//									answer[temp] += 10;
//									answer[temp - 1] -= 1;
//									temp--;
//								}
//
//							}
//
//						}
//						answer[top3] = '\0';
//						printf("%s", answer);
//						return 0;
//					}*/
//						answer[temp +1] += 10;
//						answer[temp ] -= 1;
//						temp--;
//
//					}
//				}
//			}
//
//		}
//		if (sign == 0)
//		{
//			for (int j = 0;j < top1 - top2;j++)
//			{
//				answer[top3++] = s1[j];
//			}
//			for (int j = top1 - top2;j < top1;j++)
//			{
//				if (s1[j] >= s2[j - top1 + top2])
//				{
//					answer[top3++] = s1[j] - s2[j - top1 + top2] + '0';
//				}
//				else
//				{
//					int temp = top3 - 1;
//					answer[top3++] = s1[j] + 10 - s2[j - top1 + top2] + '0';
//					answer[temp]--;
//					while (answer[temp] < '0')
//					{
//						answer[temp] += 10;
//						answer[temp - 1] -= 1;
//						temp--;
//					}
//
//				}
//
//			}
//		}
//		int x = top3,bb = -1;
//		top3 = 0;
//	
//			for (int j = 0;j < x;j++)
//			{
//				if (answer[j] == '-')
//					answer[top3++] = '-';
//				else if (answer[j] == '0' && bb == -1)
//				{
//					continue;
//				}
//				else if (answer[j] > '0' && bb == -1)
//				{
//					answer[top3++] = answer[j];
//					bb = 1;
//				}
//			}
//	
//		answer[top3] = '\0';
//		printf("%s", answer);
//	}
//}
