#include<stdio.h>
#include<string.h>
#include<ctype.h>

int client_queue[256];
int rear = 0, front = 0;
int main()
{
	int n = 0, new_client = 0, wait_client = 0;
	int  total_client = 0,corridor = 3;
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&new_client);
		total_client += new_client;
		wait_client += new_client;
		while ((wait_client / corridor >= 7)&&(corridor < 5))
			corridor++;
		front += (wait_client >= corridor)?corridor:wait_client;
		for (int i = front; i < total_client; i++)
		{
			client_queue[i]++;
		}
		if (wait_client >= corridor)
			wait_client -= corridor;
		else
			wait_client = 0;
		while ((wait_client / corridor < 7)&&(corridor > 3))
			corridor--;
	}
	while (wait_client > 0)
	{
		front += (wait_client >= corridor) ? corridor : wait_client;
		if (wait_client >= corridor)
			wait_client -= corridor;
		else
			wait_client = 0;
		for (int i = front; i < total_client; i++)
		{
			client_queue[i]++;
		}
		while ((wait_client / corridor < 7) && (corridor > 3))
			corridor--;

	}
	for (int i = 0; i < total_client; i++)
		printf("%d : %d\n",i + 1,client_queue[i]);
	return 0;
}
