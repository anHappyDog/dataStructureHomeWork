#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{	
	char s[100];
	int queue[50];
	int finalnum;
	int tempNum,temp,top = 0,index,i=0;
	gets(s);
	while(i <strlen(s))
	{
		if (s[i] == ' ')
			i++;
		else if (isdigit(s[i]))
		{
			tempNum = s[i] - '0';
			i++;
			while (i <strlen(s)&&isdigit(s[i]))
			{
				tempNum = tempNum * 10 + s[i] - '0';
				i++;
			}
			/*while (i < strlen(s) && s[i] == ' ')
				i++;
			if (i < strlen(s) && s[i] != '/' && s[i] != '*')
			{
				queue[top++] = tempNum;
				queue[top++] = s[i];
			}
			else if (i < strlen(s) && (s[i] == '/' || s[i] == '*'))
			{

			}*/
		}
		else if (s[i] == '+' || s[i] == '-')
		{
			queue[top++] = tempNum;
			queue[top++] = s[i];
			i++;
		}
		else if (s[i] == '*' || s[i] == '/')
		{
			index = s[i] == '*' ? 1 : 0;//1Îª³É
			temp = tempNum;
			i++;
			while (s[i] == ' ')
				i++;
			if (isdigit(s[i]))
			{
				tempNum = s[i] - '0';
				i++;
				while (i < strlen(s) && isdigit(s[i]))
				{
					tempNum = tempNum * 10 + s[i] - '0';
					i++;
				}
				if (index == 1)
					tempNum = tempNum * temp;
				else
					tempNum = temp / tempNum;
			}
			
		}
		 if (s[i] == '=')
		{
			queue[top++] = tempNum;
			i++;
		}
	}
	finalnum = queue[0];
	for (int j = 1; j < top;j++)
	{
		if (queue[j] == '+')
		{
			finalnum += queue[j + 1];
			j++;
		}
		else if (queue[j] == '-')
		{
			finalnum -= queue[j + 1];
			j++;
		}
	}
	printf("%d",finalnum);
}


