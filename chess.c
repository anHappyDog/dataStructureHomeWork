#include<stdio.h>


int main()
{
	int chess[19][19];
	int sign, nums = 0;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			scanf("%d", &chess[i][j]);
		}

	}
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			nums = 0;
			sign = chess[i][j];
			if (sign != 0)
			{
				if (i + 3 < 19)
				{
					for (int x = 0; x < 4; x++)
					{
						if (chess[x + i][j] == sign)
							nums++;
					}
					if (nums == 4 && (i > 0 && chess[i - 1][j] == 0 || i + 4 < 19 && chess[i + 4][j] == 0))
					{
						printf("%d:%d,%d\n", sign, i + 1, j + 1);
						return 0;
					}
					nums = 0;
				}
				if (j + 3 < 19)
				{
					for (int x = 0; x < 4; x++)
					{
						if (chess[i][x + j] == sign)
							nums++;
					}
					if (nums == 4 && (j > 0 && chess[i][j - 1] == 0 || j + 4 < 19 && chess[i][j + 4] == 0))
					{
						printf("%d:%d,%d\n", sign, i + 1, j + 1);
						return 0;

					}
					nums = 0;
				}
				if (i + 3 < 19 && j + 3 < 19)
				{
					for (int x = 0; x < 4; x++)
					{
						if (chess[i + x][j + x] == sign)
							nums++;
					}
					if (nums == 4 && (i > 0 && j > 0 && chess[i - 1][j - 1] == 0 || i + 4 < 19 && j + 4 < 19 && chess[i + 4][j + 4] == 0))
					{
						printf("%d:%d,%d\n", sign, i + 1, j + 1);
						return 0;

					}
					nums = 0;

				}
				if (j - 3 >= 0 && i + 3 < 19)
				{
					for (int x = 0; x < 4; x++)
					{
						if (chess[i + x][j - x] == sign)
							nums++;
					}
					if (nums == 4 && (i - 1 >= 0 && j + 1 < 19 && chess[i - 1][j + 1] == 0 || i + 4 < 19 && j - 4 >= 0 && chess[i + 4][j - 4] == 0))
					{
						printf("%d:%d,%d\n", sign, i + 1, j + 1);
						return 0;

					}
					nums = 0;
				}
			}


		}

	}
	printf("NO\n");
	return 0;
}
