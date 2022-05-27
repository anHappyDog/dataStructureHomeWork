#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{	
	char s[100];
	char s1[150];
	int i, j=0;
	scanf("%s",s);
	for (i = 0; i < strlen(s);i++)
	{
		if (s[i] == '-')
		{
			if (i < strlen(s) - 1 && i > 0)
			{
				if (isdigit(s[i - 1]) && isdigit(s[i + 1]) || islower(s[i-1])&&islower(s[i +1]) || isupper(s[i-1])&&isupper(s[i +1]))
				{
					for (int x = s[i - 1] + 1;x < s[i+1];x++)
					{
						s1[j++] = x;
					}
				}
				else
				{
					s1[j++] = s[i];
				}
			}
		}
		else
		{
			s1[j++] = s[i];
		}
	}
	s1[j] = '\0';
	printf("%s",s1);

}
