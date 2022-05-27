#include<stdio.h>
#include<string.h>
#include<ctype.h>


char fuhao_stack[128];
double shuzi_stack[128];
int fuhao_top = -1;
int shuzi_top = -1;
void func_t(char fh);
void computeNum(char fh);
void readNum(char[]);

int main()
{
	char inputStr[256];
	gets(inputStr);
	readNum(inputStr);


	return 0;
}
void readNum(char inputStr[])
{
	int if_shuzi = 0;
	int temp_num = 0;
	for (int i = 0; i < strlen(inputStr); i++)
	{
		while (inputStr[i] == ' ')
			i++;
		if (isdigit(inputStr[i]))
		{
			if_shuzi = 1;
			temp_num = temp_num * 10 + inputStr[i] - '0';
		}
		else if (inputStr[i] == '=')
		{
			if (if_shuzi)
			{
				shuzi_stack[++shuzi_top] = temp_num;
				temp_num = 0;
				if_shuzi = 0;
			}
			break;
		}
		else if (inputStr[i] == '('|| inputStr[i] == ')')
		{
			if (inputStr[i] == '(')
			{
				fuhao_stack[++fuhao_top] = '(';
			}
			else
			{
				while (fuhao_stack[fuhao_top] != '(')
				{
					if (if_shuzi)
					{
						shuzi_stack[++shuzi_top] = temp_num;
						temp_num = 0;
						if_shuzi = 0;
					}
					computeNum(fuhao_stack[fuhao_top--]);
				}
				fuhao_top--;
			}
		}
		else if(inputStr[i] !='('&&inputStr[i]!=')')
		{
			if (if_shuzi)
			{
				shuzi_stack[++shuzi_top] = temp_num;
				temp_num = 0;
				if_shuzi = 0;
			}
			while (inputStr[i] == ' ')
				i++;
			func_t(inputStr[i]);
			
		}
	}
	while (fuhao_top > -1)
	{
		computeNum(fuhao_stack[fuhao_top--]);
	}
	printf("%.2f\n",shuzi_stack[0]);
}
void func_t(char fh)
{
	if (fuhao_top == -1)
	{
		fuhao_stack[++fuhao_top] = fh;
		return;
	}

	if (fh == '+' || fh == '-')
	{
		while (fuhao_top > -1 && fuhao_stack[fuhao_top] != '(')
		{
			computeNum(fuhao_stack[fuhao_top--]);
		}
		fuhao_stack[++fuhao_top] = fh;
	}
	else if (fh == '*' || fh == '/')
	{

		while (fuhao_top > -1 && fuhao_stack[fuhao_top] != '(' && (fuhao_stack[fuhao_top] == '*' || fuhao_stack[fuhao_top] == '/'))
			computeNum(fuhao_stack[fuhao_top--]);
		fuhao_stack[++fuhao_top] = fh;

	}
	else if (fh == '(')
		fuhao_stack[++fuhao_top] = fh;
	else if (fh == ')')
	{
		while (fuhao_stack[fuhao_top] != '(')
		{
			computeNum(fuhao_stack[fuhao_top--]);
		}
		fuhao_top--;
	}
}
void computeNum(char fh)
{
	double tem_num1, tem_num2;
	tem_num1 = shuzi_stack[shuzi_top--];
	tem_num2 = shuzi_stack[shuzi_top--];
	if (fh == '+')
		shuzi_stack[++shuzi_top] = tem_num1 + tem_num2;
	else if (fh == '-')
		shuzi_stack[++shuzi_top] = tem_num2 - tem_num1;
	else if (fh == '*')
		shuzi_stack[++shuzi_top] = tem_num2 * tem_num1;
	else if (fh == '/')
		shuzi_stack[++shuzi_top] = tem_num2 / tem_num1;
}


