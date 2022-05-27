#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct point {
	int x;
	int y;


}Point;


typedef struct line{
	Point p1;
	Point p2;
}Line ,*LINE;

int cmp(const void* a, const void* b)
{
	LINE aa = (LINE)a;
	LINE bb = (LINE)b;
	if (aa->p1.x == bb->p1.x)
	{
		return aa->p2.x - bb->p2.x;
	}
	return aa->p1.x - bb->p1.x;
}


int main()
{
	int Max = -1,X = 0,Y = 0,leftx,lefty,maxX=0,maxY=0,count = 1;
	int N;
	LINE ptrl;
	scanf("%d",&N);
	ptrl = (LINE)malloc(sizeof(Line) * N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d %d %d",&ptrl[i].p1.x, &ptrl[i].p1.y, &ptrl[i].p2.x, &ptrl[i].p2.y);
	}
	qsort(ptrl,N,sizeof(Line),cmp);
	for (int i = 0; i < N; i++)
	{
		X = ptrl[i].p1.x;
		Y = ptrl[i].p1.y;
		leftx = ptrl[i].p2.x;
		lefty = ptrl[i].p2.y;
		count = 1;
		for (int j = i + 1; j < N; j++)
		{
			if (ptrl[j].p1.x == leftx && ptrl[j].p1.y == lefty)
			{
				leftx = ptrl[j].p2.x;
				lefty = ptrl[j].p2.y;
				count++;
			}

			if (count > Max)
			{
				Max = count;
				maxX = X;
				maxY = Y;
			}
		}
	}
	printf("%d %d %d",Max,maxX,maxY);
	return 0;
}
