#define _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"
void SetPos(short x, short y)
{
	COORD pos = { x,y };
	//获取标准输出的句柄（用来标识不同设备的数值）
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置标准输出设备上光标的数值为pos
	SetConsoleCursorPosition(hOutput, pos);
}
void WelcomeToGame()
{
	SetPos(50, 20);
	printf("-----贪吃蛇游戏-----");
	SetPos(50, 30);
	system("pause");
	system("cls");
	SetPos(30, 25);
	printf("⽤ ↑ . ↓ . ← . → 分别控制蛇的移动， F3为加速，F4为减速\n");
	SetPos(30, 27);
	printf("加速将能得到更⾼的分数。\n");
	SetPos(50, 30);
	system("pause");
	system("cls");
}
void CreatMap()
{
	int i = 0;
	SetPos(0, 0);
	for (i = 0; i < 80; i += 2)
	{
		wprintf(L"%c", WALL);
	}
	SetPos(0, 40);
	for (i = 0; i < 80; i += 2)
	{
		wprintf(L"%c", WALL);
	}
	for (i = 1; i < 40; i++)
	{
		SetPos(0, i);
		wprintf(L"%c", WALL);
	}
	for (i = 1; i < 40; i++)
	{
		SetPos(78, i);
		wprintf(L"%c", WALL);
	}
}
void InitSnake(pSnake ps)//链表
{
	pSnakeNode cur = NULL;
	int i = 0;
	//创建蛇身节点坐标，并初始化节点
	//采用头插法
	//假定初始蛇有五个节点
	for (int i = 0; i < 5; i++)
	{
		//创建蛇身的节点
		cur = (pSnakeNode)malloc(sizeof(SnakeNode));
		if (cur == NULL)
		{
			perror("InitSnake():malloc()");
			return;
		}
		cur->next = NULL;
		cur->x = POS_X + i * 2;
		cur->y = POS_Y;
		//头插法
		if (ps->_pSnake == NULL)
		{
			ps->_pSnake = cur;
		}
		else
		{
			cur->next = ps->_pSnake;
			ps->_pSnake = cur;
		}
	}
	//打印蛇的身体
	cur = ps->_pSnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}

	//初始化贪吃蛇数据
	ps->_SleepTime = 150;
	ps->_Socre = 0;
	ps->_Status = FINE;
	ps->_foodweight = 10;
	ps->_Dir = RIGHT;
}
void CreatFood(pSnake ps)
{
	int x = 0;
	int y = 0;
	int count = 10;
	again:
		//产生的x坐标应该是2的倍数
		do
		{
			x = rand() % 76 + 2;
			y = rand() % 39 + 1;
		} while (x % 2 != 0);
		pSnakeNode cur = ps->_pSnake;//获取指向蛇头的指针
		//食物产生的位置不能和蛇身冲突
		while (cur)
		{
			if (cur->x == x && cur->y == y)
			{
				goto again;
			}
			cur = cur->next;
		}
		pSnakeNode pFood = (pSnakeNode)malloc(sizeof(SnakeNode));//创建食物
		if (pFood == NULL)
		{
			perror("pFood");
			return;
		}
		else
		{
			pFood->x = x;
			pFood->y = y;
			SetPos(pFood->x, pFood->y);
			wprintf(L"%c", FOOD);
			ps->_pFood = pFood;
		}
}

//游戏开始，完成游戏的初始化
void GameStart(pSnake ps)
{
	//设置控制台窗口大小
	system("mode con cols=125 lines=50");
	//设置控制台窗口名称
	system("title 贪吃蛇");
	//鼠标光标的隐藏
	//获取标准输出的句柄（用来标识不同设备的数值）
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);//获取控制台光标的信息
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo);//设置控制台光标的信息

	//打印欢迎界面
	WelcomeToGame();
	//打印地图
	CreatMap();
	//初始化蛇身
	InitSnake(ps);
	//创建第一个食物
	CreatFood(ps);
}
//打印提示信息
void PrintHelpInfo()
{
	SetPos(83, 15);
	printf("① 不能穿墙，不能咬到自己\n");
	SetPos(83, 16);
	printf("② ⽤↑.↓.←.→ 分别控制蛇的移动.");
	SetPos(83, 17);
	printf("③ F3 为加速，F4 为减速\n");
	SetPos(83, 18);
	printf("④ ESC ：退出游戏.  space：暂停游戏.");
}
//psn 是下一个节点的地址
//ps 是维护蛇的指针
int NextIsFood(pSnakeNode psn, pSnake ps)
{
	return ((psn->x == ps->_pFood->x) && psn->y == ps->_pFood->y);
}
void pause()
{
	while (1)
	{
		Sleep(300);
		if (KEY_PRESS(VK_SPACE))
			break;
	}
}
void EatFood(pSnakeNode psn, pSnake ps)
{
	//头插法
	psn->next = ps->_pSnake;
	ps->_pSnake = psn;
	//打印蛇
	pSnakeNode cur = ps->_pSnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%c", BODY);
		cur = cur->next;
	}
	ps->_Socre += ps->_foodweight;
	//释放食物节点
	free(ps->_pFood);
	//创建新的食物
	CreatFood(ps);
}
void NoFood(pSnakeNode psn, pSnake ps)
{
	//头插法
	psn->next = ps->_pSnake;
	ps->_pSnake = psn;
	//打印蛇
	pSnakeNode cur = ps->_pSnake;
	while (cur->next->next)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%c", BODY);
		cur = cur->next;
	}
	//最后一个位置打印空格，然后释放节点
	SetPos(cur->next->x, cur->next->y);
	printf("  ");
	free(cur->next);
	cur->next = NULL;
}
int killByWall(pSnake ps)
{
	if (ps->_pSnake->x == 0
		|| ps->_pSnake->x == 80
		|| ps->_pSnake->y == 0
		|| ps->_pSnake->y == 40)
	{
		ps->_Status = KILL_BY_WALL;
		return 1;
	}
	return 0;
}
int killBySelf(pSnake ps)
{
	pSnakeNode cur = ps->_pSnake->next;
	while (cur)
	{
		if ((ps->_pSnake->x == cur->x) && (ps->_pSnake->y) == cur->y)
		{
			ps->_Status = KILL_BY_SELF;
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

//蛇身移动
void SnakeMove(pSnake ps)
{
	//创建下一个节点
	pSnakeNode pNextNode = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pNextNode == NULL)
	{
		perror("SnakeMove:");
		return;
	}
	//确定下一个节点的坐标，下一个节点的坐标根据蛇头的坐标和方向确定
	switch (ps->_Dir)
	{
	case UP:
	{
		pNextNode->x = ps->_pSnake->x;
		pNextNode->y = ps->_pSnake->y - 1;
	}
		break;
	case DOWM:
	{
		pNextNode->x = ps->_pSnake->x;
		pNextNode->y = ps->_pSnake->y + 1;
	}
		break;
	case LEFT:
	{
		pNextNode->x = ps->_pSnake->x-2;
		pNextNode->y = ps->_pSnake->y;
	}
		break;
	case RIGHT:
	{
		pNextNode->x = ps->_pSnake->x+2;
		pNextNode->y = ps->_pSnake->y;
	}
		break;
	}
	//如果下一个位置是食物
	if (NextIsFood(pNextNode, ps))
	{
		EatFood(pNextNode, ps);
	}
	//如果下一个位置不是食物
	else
	{
		NoFood(pNextNode, ps);
	}
	killByWall(ps);
	killBySelf(ps);
}

void GameRun(pSnake ps)
{
	//在右侧打印提示信息
	PrintHelpInfo();
	do
	{
		SetPos(83, 15);
		printf("得分：%d", ps->_Socre);
		printf("当前每个食物的分数：%d", ps->_foodweight);
		if (KEY_PRESS(VK_UP) && ps->_Dir != DOWM)
		{
			ps->_Dir = UP;
		}
		if (KEY_PRESS(VK_DOWN) && ps->_Dir != UP)
		{
			ps->_Dir = DOWM;
		}
		if (KEY_PRESS(VK_LEFT) && ps->_Dir != RIGHT)
		{
			ps->_Dir = LEFT;
		}
		if (KEY_PRESS(VK_RIGHT) && ps->_Dir != LEFT)
		{
			ps->_Dir = RIGHT;
		}
		if (KEY_PRESS(VK_SPACE))
		{
			pause();
		}
		if (KEY_PRESS(VK_ESCAPE))
		{
			ps->_Status = END_NORMAL;
			break;
		}
		if (KEY_PRESS(VK_F3))
		{
			if (ps->_SleepTime > 10)
			{
				ps->_SleepTime -= 20;
				ps->_foodweight += 5;
			}
		}
		if (KEY_PRESS(VK_F4))
		{
			if (ps->_SleepTime < 350)
			{
				ps->_SleepTime += 30;
				ps->_foodweight -= 5;
			}
			if (ps->_SleepTime == 350)
			{
				ps->_foodweight = 1;
			}
		}
		Sleep(ps->_SleepTime);
		SnakeMove(ps);
	} while (ps->_Status == FINE);
}
void GameEnd(pSnake ps)
{
	pSnakeNode cur = ps->_pSnake;
	SetPos(25, 16);
	switch (ps->_Status)
	{
	case END_NORMAL:
		printf("退出游戏");
		break;
	case KILL_BY_SELF:
		printf("你不小心撞到自己了，游戏结束!");
		break;
	case KILL_BY_WALL:
		printf("你撞到墙壁了！！！");
		break;
	}
	//释放蛇身节点
	while (cur)
	{
		pSnakeNode del = cur;
		cur = cur->next;
		free(del);
	}
}