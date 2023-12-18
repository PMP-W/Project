#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
//初始化棋盘
void Initboard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	for (i = 0; i < rows; i++)
	{
		int j = 0;
		for (j = 0; j < cols; j++)
		{
			board[i][j]= set;
		}
	}

}
//打印棋盘
void Displayboard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	for (i = 0; i <= row; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		int j = 0;
		for (j = 1	; j < col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
//布置雷
void Setmine(char board[ROWS][COLS], int row, int col)
{
	//布置10个雷
	//随机布置
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}
int Getminecount(char mine[ROWS][COLS], int x, int y)
{
	return (mine[x - 1][y] + mine[x - 1][y - 1] + mine[x][y - 1] + mine[x + 1][y - 1] + mine[x+1][y]+
		mine[x + 1][y + 1] + mine[x][y + 1] + mine[x - 1][y + 1] - 8 * '0');

}
//排查雷
void Findmine(char mine[ROWS][COLS],char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;
	while (win < row * col - EASY_COUNT)
	{
		printf("请输入坐标：");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)//限定的范围可能有bug
		{
			if (mine[x][y] == '1')                  //=和==不要混淆了，混淆后难以发现错误
			{
				printf("游戏失败\n");
				Displayboard(mine, ROW, COL);

				break;
			}
			else
			{
				//此处无雷，统计该处周围有几个雷
				int count = Getminecount(mine, x, y);
				show[x][y] = count + '0';
				Displayboard(show, ROW, COL);
				win++;
			}
		}
		else
		{
			printf("非法输入，请重新输入\n");
		}
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("恭喜你，排雷成功\n");
		Displayboard(mine, ROW, COL);
	}
}



