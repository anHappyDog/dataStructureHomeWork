#include<stdio.h>
#include<string.h>
int record[11];
int visit[11];

void dfs(int start,int num);
int main()
{
	int num;
	scanf("%d",&num);
	memset(record,0,sizeof(record));
	memset(record,0,sizeof(record));
	dfs(0,num);

}
void dfs(int start,int num)
{
	if (start >= num)
	{
		for (int i = 1;i <= num;i++)
		{

			printf("%d",record[i]);
			if (i < num)
				printf(" ");
		}
		printf("\n");
	}
	else
	{
		for (int i = 1; i <= num;i++)
		{
			if (visit[i] == 0)
			{
				visit[i] = 1;
				record[start + 1] = i;
				dfs(start + 1,num);
				visit[i] = 0;
			}

		}
	}

}



