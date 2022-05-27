#include<stdio.h>
#include<string.h>

typedef struct people People;
struct people {

	char name[30];
	char tel[20];
	int showCount;
};
People peoples[100];
int cmp(const void* a, const void* b)
{
	People* aa = (People*)a;
	People* bb = (People*)b;
	/*if (strcmp(aa->name, bb->name) > 0)
		return 1;
	else
		return -1;*/
	return strcmp(aa->name,bb->name);
}


int main()
{
	int sign = 0;
	char temp_name[30], temp_tel[30];
	
	int num = 0,top = 0;
	scanf("%d",&num);
	for (int i = 0; i < num; i++)
	{
		sign = 0;
		scanf("%s",temp_name);
		scanf("%s",temp_tel);
		if (i != 0)
		{
			for (int j = 0; j < top; j++)
			{
				if (peoples[j].showCount == -1)
				{
					continue;
				}
				if (strcmp(temp_name, peoples[j].name) == 0)
				{
					if (strcmp(temp_tel, peoples[j].tel) == 0)
					{
						sign = 1;
					}
					else
					{
		
						sign = 2;
						peoples[j].showCount++;
						sprintf(peoples[top].name,"%s_%d",temp_name,peoples[j].showCount);
						sprintf(peoples[top].tel, "%s", temp_tel);
						peoples[top].showCount = -1;
						top++;
					}
				}
			}
		}
		if (sign == 0)
		{
			strcpy(peoples[top].name, temp_name);
			strcpy(peoples[top].tel,temp_tel);
			peoples[top].showCount = 0;
			top++;
		}
	}
	qsort(peoples,top,sizeof(peoples[0]),cmp);
	for (int i = 0; i < top; i++)
	{
		printf("%s %s\n",peoples[i].name,peoples[i].tel);
	}
	return 0;
}
