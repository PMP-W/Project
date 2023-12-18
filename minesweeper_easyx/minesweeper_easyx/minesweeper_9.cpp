#define _CRT_SECURE_NO_WARNINGS 1
#include"minesweeper.h"

bool FLAGE; //用来表示是否退出
int mape[ROWE][COLE]; //用来存放所有元素
int counte=MINENUME; //用来判断所有格子是否都点完
int count_me; //找到雷的个数
char str1[100];
char _str1[100];
clock_t start, end;
IMAGE imge[12];  //用来放所有图片
void Setminee()
{
	//布置10个雷
	//随机布置
	//雷用-1表示
	int cnt = 0;//记录生成了多少个雷
	while (cnt < MINENUME)//num个雷
	{
		int r = rand() % ROWE;//行  <=row
		int c = rand() % COLE;//列  <=col

		if (mape[r][c] == 0)//避免生成重复
		{
			mape[r][c] = -1;
			cnt++;
		}
	}
}

//周围的雷
void Getminecounte()
{
	//雷所在九宫格范围内所有不是雷的格子 ++1
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			if (mape[i][j] == -1)//找到雷
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if ((m >= 0 && n >= 0 && m < ROWE && n < COLE) && mape[m][n] != -1)//避免越界和对雷++1
						{
							mape[m][n]++;
						}
					}
				}
			}
		}
	}
}
void InitMapE()
{
	start = clock();
	end = clock();
	mciSendString("open ./start.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM", 0, 0, 0);
	counte = 0;
	//随机布雷
	srand((unsigned int)time(NULL));

	FLAGE = true;
	counte = 0;
	count_me = 0;

	//初始化
	//0表示无雷，此时还没布置雷
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			mape[i][j] = 0;
		}
	}
	Setminee();
	Getminecounte();
	////创建窗口
	//initgraph(ROW * SIZE, COL * SIZE);
	//加载图片
	loadimage(&imge[0], "./0.jpg", SIZE, SIZE);//背景
	loadimage(&imge[1], "./1.jpg", SIZE, SIZE);//数字1-8
	loadimage(&imge[2], "./2.jpg", SIZE, SIZE);
	loadimage(&imge[3], "./3.jpg", SIZE, SIZE);
	loadimage(&imge[4], "./4.jpg", SIZE, SIZE);
	loadimage(&imge[5], "./5.jpg", SIZE, SIZE);
	loadimage(&imge[6], "./6.jpg", SIZE, SIZE);
	loadimage(&imge[7], "./7.jpg", SIZE, SIZE);
	loadimage(&imge[8], ".//8.jpg", SIZE, SIZE);
	loadimage(&imge[9], "./篮球.png", SIZE, SIZE);//雷
	loadimage(&imge[10], "./10.jpg", SIZE, SIZE);//遮盖
	loadimage(&imge[11], "./11.jpg", SIZE, SIZE);//标志旗
	//刚开始所有全部加密
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			mape[i][j] += 20;
		}
	}
}
void ShowMapE()
{
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			printf("%2d ", mape[i][j]);
		}
		printf("\n");
	}
	printf("------------------------------\n");
}



//图像化程序
void GameDrawE()
{
	cleardevice();//清空图层
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			if (mape[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &imge[9]);//雷
			}
			else if (mape[i][j] >= 0 && mape[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &imge[mape[i][j]]);//数字
			}
			else if (mape[i][j] >= 19 && mape[i][j] <= 28)
			{
				putimage(j * SIZE, i * SIZE, &imge[10]);//加密
			}
			else if (mape[i][j] > 30)
			{
				putimage(j * SIZE, i * SIZE, &imge[11]);//标记
			}
		}
	}
}

//鼠标操作，展开周围的格子
void OpenAroundE(int row, int col)
{
	if (mape[row][col] == 0)
	{
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				if (i >= 0 && i < ROWE && j >= 0 && j < COLE &&
					(mape[i][j] == 20 || mape[i][j] != 19) &&
					mape[i][j]>8)//不能越界
				{
					mape[i][j] -= 20;//解密
					counte++;//点开的格子数
					OpenAroundE(i, j);
				}
			}
		}
	}
}

int MouseE()
{
	if (MouseHit())//判断是否有鼠标消息
	{
		MOUSEMSG msg = GetMouseMsg();//获取鼠标坐标
		int row = msg.y / SIZE;//转换为数组下标
		int col = msg.x / SIZE;
		switch (msg.uMsg)//判断鼠标消息的类型
		{
		case WM_LBUTTONDOWN://左键
			if (mape[row][col] > 8)//不能对已经展开的区域进行操作
			{
				mciSendString("close click", 0, 0, 0);
				mciSendString("open ./click.wav alias click", 0, 0, 0);
				mciSendString("play click", 0, 0, 0);

				mape[row][col] -= 20;
				counte++;
				OpenAroundE(row, col);
			}

			break;
		case WM_RBUTTONDOWN://右键，标记
			if (mape[row][col] > 8 && mape[row][col] <= 28)
			{
				mciSendString("close rclick", 0, 0, 0);
				mciSendString("open ./rightClick.wav alias rclick", 0, 0, 0);
				mciSendString("play rclick", 0, 0, 0);
				mape[row][col] += 20;
			}
			else if (mape[row][col] > 28)
			{
				mape[row][col] -= 20;//已经标记过的
			}
			break;
		}
		return mape[row][col];
	}
}

void ResultShowE()
{
	cleardevice();//清空图层
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			if (mape[i][j] >= 19&&mape[i][j]<39)//未点击区域
				mape[i][j] -= 20;
			if (mape[i][j] >= 39)//已标记区域
				mape[i][j] -= 40;
			if (mape[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &imge[9]);//雷
			}
			if (mape[i][j] >= 0 && mape[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &imge[mape[i][j]]);//数字
			}
		}
	}
}
void JudefinalE()
{
	HWND hwnd = GetHWnd();
	if (MouseE() == -1)//点到雷
	{
		mciSendString("close search", 0, 0, 0);

		mciSendString("open ./search.wav alias search", 0, 0, 0);
		mciSendString("play search", 0, 0, 0);
		//设置对话框
		int isy = MessageBox(hwnd, "运气太差了，踩到雷了，想看答案吗？？？", "提示", MB_YESNO);
		if (IDYES == isy)
		{
			ResultShowE();//展示结果
			IMAGE img;
			loadimage(&img, "./坤.jpg");
			putimage(COLE * SIZE, 0, &img);
			setbkmode(TRANSPARENT);
			fillrectangle(COLE * SIZE, 200, COLE * SIZE + 199, 260);
			outtextxy(COLE * SIZE + 16, 205, str1);
			outtextxy(COLE * SIZE + 16, 230, _str1);
			FlushBatchDraw();
			Sleep(1000);
			int r = MessageBox(hwnd, "小菜鸡，还玩吗？？？", "提示", MB_YESNO);
			if (IDYES == r)
			{
				InitMapE();
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
				InitMapE();
				counte = 0;
			}
		}
		mciSendString("close BGM", 0, 0, 0);//关闭音乐
	}
	if (counte == ROWE * COLE - MINENUME)
	{
		int isy = MessageBox(GetHWnd(), "逆天，你居然赢了，还玩吗", "提示", MB_YESNO);
		if (IDYES == isy)
		{
			InitMapE();
			counte = 0;
		}
		else
		{
			exit(1);
		}
		mciSendString("close BGM", 0, 0, 0);
	}
}



