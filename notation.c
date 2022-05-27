#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{	
	int dotindex = -1,firstnum = -1,i = 0;
	char input[100];
	char answer[120];
	int distance = 0,top = 0;
	scanf("%s",input);
	while (i < strlen(input))
	{
		if (firstnum == -1&&input[i] > '0' && input[i] <= '9')
		{
			firstnum = i;
		}
		else if (input[i] == '.')
		{
			
				dotindex = i;
			
			if(firstnum != -1)
			{

				distance = dotindex - firstnum - 1;
				break;
			}
		}
		i++;
	}	
	if (dotindex < firstnum)
		distance = dotindex - firstnum ;
	else
		distance = dotindex - firstnum -1;
	if (distance == 0)
	{
		for (int i = 0; i < strlen(input);i++)
		{
			answer[top++] = input[i];
		}
	}
	else
	{
		
		for (int i = firstnum;i < strlen(input);i++)
		{
			if (i == firstnum + 1)
			{
				answer[top++] = '.';
			}
			if (input[i] == '.')
				continue;
			answer[top++] = input[i];
		}

	}
	
	answer[top++] = 'e';
	int xx = sprintf(answer+top,"%d",distance);
	top = xx + top;
	/*if (distance == 0)
	{
		answer[top++] = '0';
	}
	else 
	{
		if (distance < 0)
		{
			answer[top++] = '-';
			distance = -distance;
		}
		while (distance)
		{
			answer[top++] = '0' + distance % 10;
			distance /= 10;
		}
	}
	*/
	answer[top] = '\0';
	
	printf("%s",answer);
}
