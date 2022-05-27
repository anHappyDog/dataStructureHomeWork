#include<stdio.h>
#include<string.h>
#include<ctype.h>


char orders_stack[100][512];
int orders_top = -1;
void string_add(char* s, char* s1, int pos);
void string_delete(char* s, int pos, int n);
void undo_func(char inputStr[]);
void s_scanf(char* temp_string, char* order_stacks);
int main()
{
	char inputStr[512];
	char add_str[512];
	char delete_str[512];
	char orders[512];
	int n,pos,n_char = 0;
	gets(inputStr);
	scanf("%d\n",&n);
	for (int i = 0; i < n; i++)
	{
		gets(orders);
		strcpy(orders_stack[++orders_top], orders);
	}

	while (1)
	{
		gets(orders);
		if (strlen(orders) == 1)
		{
			//undo
			if (orders_top > -1)
			{
				undo_func(inputStr);
			}
		}
		else if (orders[0] == '-')
		{
			printf("%s\n",inputStr);
			return 0;
		}
		else if (orders[0] == '1')
		{
			strcpy(orders_stack[++orders_top],orders);
			sscanf(orders,"1 %d",&pos);
			s_scanf(add_str,orders);
			string_add(inputStr,add_str,pos);
		}
		else if (orders[0] == '2')
		{
			sscanf(orders,"2 %d %d",&pos,&n_char );
			for (int i = pos; (i < pos + n_char) && (i < strlen(inputStr)); i++)
			{
				delete_str[i - pos] = inputStr[i];
			}
			delete_str[pos+ n_char >=strlen(inputStr)? strlen(inputStr) - pos : n_char] = '\0';
			sprintf(add_str,"2 %d %s",pos,delete_str);
			strcpy(orders_stack[++orders_top],add_str);
			string_delete(inputStr,pos,n_char);
		}
		printf("\n");
	}
	
	return 0;
}
void undo_func(char inputStr[])
{
	int pos;
	char temp_string[512];
	if (orders_stack[orders_top][0] == '1')
	{
		sscanf(orders_stack[orders_top],"1 %d",&pos);
		s_scanf(temp_string, orders_stack[orders_top]);
		string_delete(inputStr,pos,strlen(temp_string));
		orders_top--;
	}
	else if (orders_stack[orders_top][0] == '2')
	{
		sscanf(orders_stack[orders_top], "2 %d", &pos);
		s_scanf(temp_string,orders_stack[orders_top]);
		string_add(inputStr,temp_string,pos);
		orders_top--;
	}

}
void s_scanf(char* temp_string,char*order_stacks)
{
	int i = 2;
	for (i; i < strlen(orders_stack); i++)
	{
		if (!isdigit(order_stacks[i]))
			break;
	}
	i += 1;
	strcpy(temp_string,order_stacks + i);

}
void string_add(char* s, char* s1,int pos)
{
	int s_length = strlen(s);
	char temp_string[512];
	strcpy(temp_string,s + pos);

	for (int i = pos; i < pos + strlen(s1); i++)
	{
		s[i] = s1[i - pos];
	}
	for (int i = pos + strlen(s1); i < s_length + pos + strlen(s1); i++)
	{
		s[i] = temp_string[i-pos-strlen(s1)];

	}
	s[s_length + pos + strlen(s1)] = '\0';
}
void string_delete(char* s, int pos,int n)
{
	int i = 0;
	int s_length = strlen(s);
	if (pos + n >= s_length)
	{
		s[pos] = '\0';
	}
	else
	{
		for ( i = pos + n; i < s_length; i++)
		{
			s[i - n] = s[i];
		}
		s[i-n] = '\0';
	}

}

