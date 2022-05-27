#include<stdio.h>
#include<string.h>
#include<ctype.h>
char* Mystrstr(const char*,const char*);
int main()
{
	int strCount = 0, top = 0;
	FILE* fp;
	char temp[1024], input[124], output[124];
	char str[200][1024];
	scanf("%s", input, 124);
	scanf("%s", output, 124);
	fp = fopen("filein.txt", "r");
	if (fp == NULL)
	{
		printf("´ò¿ªÊ§°Ü");
		return -1;
	}
	while (fgets(str[strCount++], 1024, fp) != EOF)
	{
		if (feof(fp))
			break;
	}
	fclose(fp);
	for (int i = 0; i < strCount; i++)
	{
		top = 0;
		int x = 0, tem = 0;
		char* p;
		while (x < strlen(str[i]))
		{

			if (tem > -1)
			{
				p = Mystrstr(str[i] + x, input);

tem = p - str[i];
			}
			if (p == NULL)
			{
				for (x; x < strlen(str[i]); x++)
				{
					temp[top++] = str[i][x];

				}
				break;
			}
			else
			{
				for (x; x < tem; x++)
				{
					temp[top++] = str[i][x];
				}
				for (int j = x; j < x + strlen(output); j++)
				{
					temp[top++] = output[j - x];
				}
				x += strlen(input);
			}

		}
		temp[top] = '\0';
		strcpy(str[i], temp);
	}

	fp = fopen("fileout.txt", "w");
	for (int i = 0; i < strCount; i++)
	{
		fputs(str[i], fp);

	}

	fclose(fp);
	return 0;
}
char* Mystrstr(const char* dsc, const char* out)
{
	int j;
	for (int i = 0; i < strlen(dsc); i++)
	{
		if (i + strlen(out) <= strlen(dsc) && tolower(out[0]) == tolower(dsc[i]))
		{
			for (j = 0; j < strlen(out) && tolower(dsc[i + j]) == tolower(out[j]); j++);
			if (out[j] == '\0')
				return dsc + i;
		}
	}
	return NULL;
}
