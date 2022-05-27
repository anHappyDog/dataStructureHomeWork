#include<stdio.h>
#include<string.h>
#include<ctype.h>


char kuohaostr[201];
int index = 0;
int shuzi_stack[201];
char my_stack[201];
int top = -1;
void ReadText(FILE* fp);
void popStack();
void pushStack(char chr, int line);
int ifEmpty();
int main()
{
	FILE* fp;
	fp = fopen("example.c", "r");
	if (fp == NULL)
	{
		printf("打开文件失败");
		return -1;
	}
	ReadText(fp);
	fclose(fp);
	return 0;
}
int ifEmpty()
{
	return top == -1;
}
void pushStack(char chr,int line)
{
	my_stack[++top] = chr;
	shuzi_stack[top] = line;
}
void popStack()
{
	top--;
}
void ReadText(FILE* fp)
{
	int line = 0;
	int ifzhushi2 = 0, ifzifuchuan = 0;
	char tempStr[128];
	while (fgets(tempStr, 128, fp))
	{
		line++;
		for (int i = 0; i < strlen(tempStr); i++)
		{
			if (tempStr[i] == '"')
			{
				ifzifuchuan = (ifzifuchuan == 1) ? 0 : 1;
			}
			if (i + 1 < strlen(tempStr) && tempStr[i] == '/' && tempStr[i + 1] == '/')
			{
				break;
			}
			else if (i + 1 < strlen(tempStr) && tempStr[i] == '/' && tempStr[i + 1] == '*')
			{
				ifzhushi2 = 1;
			}
			else if (ifzhushi2 == 1 && i + 1 < strlen(tempStr) && tempStr[i] == '*' && tempStr[i + 1] == '/')
			{
				ifzhushi2 = 0;
			}
			if (ifzhushi2 == 0 && ifzifuchuan == 0)
			{
				if (tempStr[i] == '(')
				{
					pushStack(tempStr[i],line);
					kuohaostr[index++] = tempStr[i];
				}
				else if (tempStr[i] == '{')
				{
					if (!ifEmpty()&&my_stack[top] =='(')
					{
						printf("without maching '%c' at line %d\n",my_stack[top], shuzi_stack[top]);
						return;
					}
					else
					{
						pushStack(tempStr[i], line);
						kuohaostr[index++] = tempStr[i];
					}
				}
				else if (tempStr[i] == ')')
				{
					if (ifEmpty() || !ifEmpty() && my_stack[top] != '(')
					{
						printf("without maching '%c' at line %d\n", tempStr[i], line);
						return;
					}
					popStack();
					kuohaostr[index++] = tempStr[i];
				}
				else if (tempStr[i] == '}')
				{
					if (ifEmpty() || !ifEmpty() && my_stack[top] != '{')
					{
						printf("without maching '%c' at line %d\n", tempStr[i], line);
						return;
					}
					popStack();
					kuohaostr[index++] = tempStr[i];
				}
			}
		}
	}
	if (!ifEmpty())
	{
		printf("without maching '%c' at line %d\n",my_stack[0], shuzi_stack[0]);
		return;
	}
	kuohaostr[index] = '\0';
	printf("%s\n", kuohaostr);

}
