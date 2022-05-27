#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	int hash[26],top = 0,answer_top =0;
	char key[60];
	char final_key[60];
	char encrypt[1024];
	char answer[1024];
	FILE* fp;
	scanf("%s",key);
	memset(hash,0,sizeof(hash));
	fp = fopen("encrypt.txt","r");
	if (fp == NULL)
	{
		printf("´ò¿ªÊ§°Ü\n");
		return -1;
	}
	fgets(encrypt,1024,fp);
	for (int i = 0; i < strlen(key); i++)
	{
		if (islower(key[i]) && hash[key[i] - 'a'] == 0)
		{
			hash[key[i] - 'a'] = 1;
			final_key[top++] = key[i];
		}
		else if (!islower(key[i]))
		{
			final_key[top++] = key[i];
		}
	}
	for (int i = 25; i >= 0; i--)
	{
		if (hash[i] == 0)
		{
			final_key[top++] = i + 'a';
		}

	}
	final_key[top] = '\0';
	for (int i = 0; i < strlen(encrypt); i++)
	{
		if (islower(encrypt[i]))
		{
			answer[answer_top++] = final_key[encrypt[i] - 'a'];
		}
		else
		{
			answer[answer_top++] = encrypt[i];
		}

	}
	answer[answer_top] = '\0';
	fclose(fp);
	fp = fopen("output.txt","w");
	fputs(answer,fp);
	fclose(fp);
	return 0;
}
