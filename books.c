#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct book Book;
struct book {
	char name[51];
	char author[21];
	char press[31];
	char date[11];
};
void FuncOne();
void FuncTwo();
void FuncZero();
void FuncThree();
void PreWork();
int cmp(const void* a, const void* b);
Book books[500];
int top = 0;
int main()
{
	int choice;
	PreWork();
	qsort(books, top, sizeof(books[0]), cmp);
	while (1)
	{ 
		 scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			FuncOne();
			break;
		case 2:
			FuncTwo();
			break;
		case 3:
			FuncThree();
			break;
		case 0:
			FuncZero();
			return 0;
			break;
		}
	}
	return 0;
}

void FuncThree()
{
	char temp[120];
	char ff[120];
	scanf("%s",ff);
	for (int i = 0; i < top; i++)
	{
		if (strstr(books[i].name, ff) != NULL)
		{
			strcpy(temp,books[top-1].name);
			strcpy(books[top - 1].name,books[i].name);
			strcpy(books[i ].name,temp);

			strcpy(temp, books[top - 1].author);
			strcpy(books[top - 1].author, books[i].author);
			strcpy(books[i ].author, temp);

			strcpy(temp, books[top - 1].press);
			strcpy(books[top - 1].press, books[i].press);
			strcpy(books[i].press, temp);
			
			strcpy(temp, books[top - 1].date);
			strcpy(books[top - 1].date, books[i].date);
			strcpy(books[i].date, temp);
			top--;
			i--;
		}
	}
	qsort(books, top, sizeof(books[0]), cmp);
}
void FuncOne()
{
	char temp[120];
	scanf( "%s %s %s %s", books[top].name, books[top].author, books[top].press, books[top].date);
	top++;
	qsort(books,top,sizeof(books[0]),cmp);
	
}

void FuncTwo()
{
	char temp[120];
	char output[120];
	scanf("%s",temp);
	for (int i = 0; i < top; i++)
	{
		if (strstr(books[i].name,temp) != NULL)
		{
			sprintf(output, "%-50s%-20s%-30s%-10s", books[i].name, books[i].author, books[i].press, books[i].date);
			printf("%s\n", output);
		}
	}

}
void FuncZero()
{
	FILE* fp;
	char temp[120];
	fp = fopen("ordered.txt", "w");
	if (fp == NULL)
	{
		printf("´ò¿ªÊ§°Ü");
		return ;
	}
	for (int i = 0; i < top; i++)
	{
		sprintf(temp, "%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].press, books[i].date);
		
		fputs(temp,fp);

	}
	fclose(fp);
}
void PreWork()
{
	FILE* fp;
	char temp[120];
	fp = fopen("books.txt", "r");
	while (fgets(temp, 120, fp)!=NULL)
	{
		sscanf(temp, "%s %s %s %s", books[top].name, books[top].author, books[top].press, books[top].date);
		top++;
	}
	fclose(fp);
}
int cmp(const void* a, const void* b)
{
	Book* aa = (Book*)a;
	Book* bb = (Book*)b;
	return strcmp(aa->name,bb->name);

}
