#define _CRT_SECURE_NO_WARNINGS 1
#include"minesweeper.h"

bool FLAG; //������ʾ�Ƿ��˳�
int map[ROW][COL]; //�����������Ԫ��
int count; //�����ж����и����Ƿ񶼵���
int count_m; //�ҵ��׵ĸ���
clock_t _start;
clock_t _end;
float time_l;
char str[100];
char _str[100];
IMAGE img[12];  //����������ͼƬ
void Setmine()
{
	//����10����
	//�������
	//����-1��ʾ
	int cnt = 0;//��¼�����˶��ٸ���
	while (cnt < MINENUM)//num����
	{
		int r = rand() % ROW;//��  <=row
		int c = rand() % COL;//��  <=col

		if (map[r][c] == 0)//���������ظ�
		{
			map[r][c] = -1;
			cnt++;
		}
	}
}

//��Χ����
void Getminecount()
{
	//�����ھŹ���Χ�����в����׵ĸ��� ++1
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)//�ҵ���
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if ((m >= 0 && n >= 0 && m < ROW && n < COL) && map[m][n] != -1)//����Խ��Ͷ���++1
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
	//�������
	srand((unsigned int)time(NULL));

	FLAG = true;
	count = 0;
	count_m = 0;

	//��ʼ��
	//0��ʾ���ף���ʱ��û������
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] = 0;
		}
	}
	Setmine();
	Getminecount();
	////��������
	//initgraph(ROW * SIZE, COL * SIZE);
	//����ͼƬ
	loadimage(&img[0], "./0.jpg", SIZE, SIZE);//����
	loadimage(&img[1], "./1.jpg", SIZE, SIZE);//����1-8
	loadimage(&img[2], "./2.jpg", SIZE, SIZE);
	loadimage(&img[3], "./3.jpg", SIZE, SIZE);
	loadimage(&img[4], "./4.jpg", SIZE, SIZE);
	loadimage(&img[5], "./5.jpg", SIZE, SIZE);
	loadimage(&img[6], "./6.jpg", SIZE, SIZE);
	loadimage(&img[7], "./7.jpg", SIZE, SIZE);
	loadimage(&img[8], ".//8.jpg", SIZE, SIZE);
	loadimage(&img[9], "./����.png", SIZE, SIZE);//��
	loadimage(&img[10], "./10.jpg", SIZE, SIZE);//�ڸ�
	loadimage(&img[11], "./11.jpg", SIZE, SIZE);//��־��
	//�տ�ʼ����ȫ������
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


//ͼ�񻯳���
void GameDraw()
{
	cleardevice();//���ͼ��
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &img[9]);//��
			}
			else if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &img[map[i][j]]);//����
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * SIZE, i * SIZE, &img[10]);//����
			}
			else if (map[i][j] > 30)
			{
				putimage(j * SIZE, i * SIZE, &img[11]);//���
			}
		}
	}
}

//��������չ����Χ�ĸ���
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
					map[i][j]>8)//����Խ��
				{
					map[i][j] -= 20;//����
					count++;//�㿪�ĸ�����
					OpenAround(i, j);
				}
			}
		}
	}
}

int Mouse()
{
	if (MouseHit())//�ж��Ƿ��������Ϣ
	{
		MOUSEMSG msg = GetMouseMsg();//��ȡ�������
		int row = msg.y/SIZE;//ת��Ϊ�����±�
		int col = msg.x/SIZE;
		switch (msg.uMsg)//�ж������Ϣ������
		{
			case WM_LBUTTONDOWN://���
			if (map[row][col] > 8)//���ܶ��Ѿ�չ����������в���
			{
				mciSendString("close click", 0, 0, 0);
				mciSendString("open ./click.wav alias click", 0, 0, 0);
				mciSendString("play click", 0, 0, 0);

				map[row][col] -= 20;
				count++;
				OpenAround(row, col);
			}
			
			break;
			case WM_RBUTTONDOWN://�Ҽ������
				if (map[row][col] > 8 && map[row][col] <= 28)
				{
					mciSendString("close rclick", 0, 0, 0);
					mciSendString("open ./rightClick.wav alias rclick", 0, 0, 0);
					mciSendString("play rclick", 0, 0, 0);
					map[row][col] += 20;
				}
				else if (map[row][col] > 28)
				{
					map[row][col] -= 20;//�Ѿ���ǹ���
				}
				break;
		}
		return map[row][col];
	}
}

void ResultShow()
{
	cleardevice();//���ͼ��
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] >= 19 && map[i][j] < 39)//δ�������
				map[i][j] -= 20;
			if (map[i][j] >= 39)//�ѱ������
				map[i][j] -= 40;
			if (map[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &img[9]);//��
			}
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &img[map[i][j]]);//����
			}
		}
	}
}
void Judefinal()
{
	HWND hwnd = GetHWnd();
	if (Mouse() == -1)//�㵽��
	{
		//���öԻ���
		mciSendString("open ./search.wav alias search", 0, 0, 0);
		mciSendString("play search", 0, 0, 0);
		int isy = MessageBox(hwnd, "����̫���ˣ��ȵ����ˣ��뿴���𣿣���", "��ʾ", MB_YESNO);
		if (IDYES == isy)
		{
			ResultShow();//չʾ���
			IMAGE img;
			loadimage(&img, "./��.jpg");
			putimage(COL * SIZE, 0, &img);
			setbkmode(TRANSPARENT);
			fillrectangle(COL * SIZE, 200, COL * SIZE + 199, 260);
			outtextxy(COL * SIZE + 16, 205, str);
			outtextxy(COL * SIZE + 16, 230, _str);
			FlushBatchDraw();
			Sleep(1000);
			int r = MessageBox(hwnd, "С�˼��������𣿣���", "��ʾ", MB_YESNO);
			if (IDYES == r)
			{
				InitMap();
			}
			else
				exit(1);
		}
		else
		{
			int r = MessageBox(hwnd, "ȷ���������𣿣���", "��ʾ", MB_YESNO);
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
		mciSendString("close BGM", 0, 0, 0);//�ر�����
	}
	if (count == ROW * COL - MINENUM)
	{
		int isy = MessageBox(GetHWnd(), "���죬���ȻӮ�ˣ�������", "��ʾ", MB_YESNO);
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



