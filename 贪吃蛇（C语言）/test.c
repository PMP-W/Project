#define _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"

void test()
{
	srand((unsigned int)time(NULL));
	int ch = 0;
	do
	{
		Snake snake = { 0 };
		GameStart(&snake);
		GameRun(&snake);
		GameEnd(&snake);
		SetPos(25, 17);
		printf("你还敢玩吗？？？（Y/N）：");
		ch = getchar();
		getchar();//清理\n
	} while (ch == 'Y');
	SetPos(85, 42);
}
int main()
{
	setlocale(LC_ALL, "");//设置为本地模式
	test();

	return 0;
}