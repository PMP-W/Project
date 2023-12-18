#define _CRT_SECURE_NO_WARNINGS 1
#include"minesweeper.h"

bool FLAG; //用来表示是否退出
int map[ROW][COL]; //用来存放所有元素
int count; //用来判断所有格子是否都点完
int count_m; //找到雷的个数
clock_t _start;
clock_t _end;
float time_l;
char str[100];
char _str[100];
IMAGE img[12];  //用来放所有图片
void Setmine()
{
	//布置10个雷
	//随机布置
	//雷用-1表示
	int cnt = 0;//记录生成了多少个雷
	while (cnt < MINENUM)//num个雷
	{
		int r = rand() % ROW;//行  <=row
		int c = rand() % COL;//列  <=col

		if (map[r][c] == 0)//避免生成重复
		{
			map[r][c] = -1;
			cnt++;
		}
	}
}

//周围的雷
void Getminecount()
{
	//雷所在九宫格范围内所有不是雷的格子 ++1
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)//找到雷
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if ((m >= 0 && n >= 0 && m < ROW && n < COL) && map[m][n] != -1)//避免越界和对雷++1
						{
							map[m][n]++;
						}
					}
				}
			}
		}
	}
}
void InitMap()
{
	_start = clock();
	_end = clock();
	mciSendString("open ./start.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM", 0, 0, 0);
	count = 0;
	//随机布雷
	srand((unsigned int)time(NULL));

	FLAG = true;
	count = 0;
	count_m = 0;

	//初始化
	//0表示无雷，此时还没布置雷
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] = 0;
		}
	}
	Setmine();
	Getminecount();
	////创建窗口
	//initgraph(ROW * SIZE, COL * SIZE);
	//加载图片
	loadimage(&img[0], "./0.jpg", SIZE, SIZE);//背景
	loadimage(&img[1], "./1.jpg", SIZE, SIZE);//数字1-8
	loadimage(&img[2], "./2.jpg", SIZE, SIZE);
	loadimage(&img[3], "./3.jpg", SIZE, SIZE);
	loadimage(&img[4], "./4.jpg", SIZE, SIZE);
	loadimage(&img[5], "./5.jpg", SIZE, SIZE);
	loadimage(&img[6], "./6.jpg", SIZE, SIZE);
	loadimage(&img[7], "./7.jpg", SIZE, SIZE);
	loadimage(&img[8], ".//8.jpg", SIZE, SIZE);
	loadimage(&img[9], "./篮球.png", SIZE, SIZE);//雷
	loadimage(&img[10], "./10.jpg", SIZE, SIZE);//遮盖
	loadimage(&img[11], "./11.jpg", SIZE, SIZE);//标志旗
	//刚开始所有全部加密
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] += 20;
		}
	}
}
void ShowMap()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%2d ", map[i][j]);
		}
		printf("\n");
	}
	printf("------------------------------\n");
}


//图像化程序
void GameDraw()
{
	cleardevice();//清空图层
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &img[9]);//雷
			}
			else if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &img[map[i][j]]);//数字
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * SIZE, i * SIZE, &img[10]);//加密
			}
			else if (map[i][j] > 30)
			{
				putimage(j * SIZE, i * SIZE, &img[11]);//标记
			}
		}
	}
}

//鼠标操作，展开周围的格子
void OpenAround(int row,int col)
{
	if (map[row][col] == 0)
	{
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				if (i >= 0 && i < ROW && j >= 0 && j < COL &&
					(map[i][j] == 20 || map[i][j] != 19) &&
					map[i][j]>8)//不能越界
				{
					map[i][j] -= 20;//解密
					count++;//点开的格子数
					OpenAround(i, j);
				}
			}
		}
	}
}

int Mouse()
{
	if (MouseHit())//判断是否有鼠标消息
	{
		MOUSEMSG msg = GetMouseMsg();//获取鼠标坐标
		int row = msg.y/SIZE;//转换为数组下标
		int col = msg.x/SIZE;
		switch (msg.uMsg)//判断鼠标消息的类型
		{
			case WM_LBUTTONDOWN://左键
			if (map[row][col] > 8)//不能对已经展开的区域进行操作
			{
				mciSendString("close click", 0, 0, 0);
				mciSendString("open ./click.wav alias click", 0, 0, 0);
				mciSendString("play click", 0, 0, 0);

				map[row][col] -= 20;
				count++;
				OpenAround(row, col);
			}
			
			break;
			case WM_RBUTTONDOWN://右键，标记
				if (map[row][col] > 8 && map[row][col] <= 28)
				{
					mciSendString("close rclick", 0, 0, 0);
					mciSendString("open ./rightClick.wav alias rclick", 0, 0, 0);
					mciSendString("play rclick", 0, 0, 0);
					map[row][col] += 20;
				}
				else if (map[row][col] > 28)
				{
					map[row][col] -= 20;//已经标记过的
				}
				break;
		}
		return map[row][col];
	}
}

void ResultShow()
{
	cleardevice();//清空图层
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] >= 19 && map[i][j] < 39)//未点击区域
				map[i][j] -= 20;
			if (map[i][j] >= 39)//已标记区域
				map[i][j] -= 40;
			if (map[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &img[9]);//雷
			}
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &img[map[i][j]]);//数字
			}
		}
	}
}
void Judefinal()
{
	HWND hwnd = GetHWnd();
	if (Mouse() == -1)//点到雷
	{
		//设置对话框
		mciSendString("open ./search.wav alias search", 0, 0, 0);
		mciSendString("play search", 0, 0, 0);
		int isy = MessageBox(hwnd, "运气太差了，踩到雷了，想看答案吗？？？", "提示", MB_YESNO);
		if (IDYES == isy)
		{
			ResultShow();//展示结果
			IMAGE img;
			loadimage(&img, "./坤.jpg");
			putimage(COL * SIZE, 0, &img);
			setbkmode(TRANSPARENT);
			fillrectangle(COL * SIZE, 200, COL * SIZE + 199, 260);
			outtextxy(COL * SIZE + 16, 205, str);
			outtextxy(COL * SIZE + 16, 230, _str);
			FlushBatchDraw();
			Sleep(1000);
			int r = MessageBox(hwnd, "小菜鸡，还玩吗？？？", "提示", MB_YESNO);
			if (IDYES == r)
			{
				InitMap();
			}
			else
				exit(1);
		}
		else
		{
			int r = MessageBox(hwnd, "确定不玩了吗？？？", "提示", MB_YESNO);
			if (IDYES == r)
			{
				exit(1);
			}
			else
			{
				InitMap();
				count = 0;
			}
		}
		mciSendString("close BGM", 0, 0, 0);//关闭音乐
	}
	if (count == ROW * COL - MINENUM)
	{
		int isy = MessageBox(GetHWnd(), "逆天，你居然赢了，还玩吗", "提示", MB_YESNO);
		if (IDYES == isy)
		{
			InitMap();
			count = 0;
		}
		else
		{
			exit(1);
		}
		mciSendString("close BGM", 0, 0, 0);
	}
}



