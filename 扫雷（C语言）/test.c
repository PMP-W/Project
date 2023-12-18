#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void menu()
{

	printf("********************\n");
	printf("********************\n");
	printf("**** 1.开始游戏 ****\n");
	printf("**** 0.退出游戏 ****\n");
	printf("********************\n");
	printf("********************\n");

}
void game()
{
	char mine[ROWS][COLS];//存放布置雷的信息
	char show[ROWS][COLS];//存放排查出的雷的信息
	//初始化棋盘
	//1. mine数组开始全是‘0’
	//2. show数组开始全是‘*’
	Initboard(mine, ROWS, COLS, '0');
	Initboard(show, ROWS, COLS, '*');
	//打印棋盘
	Displayboard(show, ROW, COL);
	//布置雷
	Setmine(mine, ROW, COL);
	//排查雷
    Findmine(mine,show,ROW,COL);
}
int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("------扫雷游戏------\n");
		printf("请输入：");
		scanf("%d", &input);
		
	    switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf( "退出游戏\n" );
			break;
		default:
			break;
		}
		printf("------扫雷游戏------\n");
	} while (input);

	return 0;
}