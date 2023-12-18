#define _CRT_SECURE_NO_WARNINGS 1
#include"minesweeper.h"

bool FLAGE; //������ʾ�Ƿ��˳�
int mape[ROWE][COLE]; //�����������Ԫ��
int counte=MINENUME; //�����ж����и����Ƿ񶼵���
int count_me; //�ҵ��׵ĸ���
char str1[100];
char _str1[100];
clock_t start, end;
IMAGE imge[12];  //����������ͼƬ
void Setminee()
{
	//����10����
	//�������
	//����-1��ʾ
	int cnt = 0;//��¼�����˶��ٸ���
	while (cnt < MINENUME)//num����
	{
		int r = rand() % ROWE;//��  <=row
		int c = rand() % COLE;//��  <=col

		if (mape[r][c] == 0)//���������ظ�
		{
			mape[r][c] = -1;
			cnt++;
		}
	}
}

//��Χ����
void Getminecounte()
{
	//�����ھŹ���Χ�����в����׵ĸ��� ++1
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			if (mape[i][j] == -1)//�ҵ���
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if ((m >= 0 && n >= 0 && m < ROWE && n < COLE) && mape[m][n] != -1)//����Խ��Ͷ���++1
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
	//�������
	srand((unsigned int)time(NULL));

	FLAGE = true;
	counte = 0;
	count_me = 0;

	//��ʼ��
	//0��ʾ���ף���ʱ��û������
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			mape[i][j] = 0;
		}
	}
	Setminee();
	Getminecounte();
	////��������
	//initgraph(ROW * SIZE, COL * SIZE);
	//����ͼƬ
	loadimage(&imge[0], "./0.jpg", SIZE, SIZE);//����
	loadimage(&imge[1], "./1.jpg", SIZE, SIZE);//����1-8
	loadimage(&imge[2], "./2.jpg", SIZE, SIZE);
	loadimage(&imge[3], "./3.jpg", SIZE, SIZE);
	loadimage(&imge[4], "./4.jpg", SIZE, SIZE);
	loadimage(&imge[5], "./5.jpg", SIZE, SIZE);
	loadimage(&imge[6], "./6.jpg", SIZE, SIZE);
	loadimage(&imge[7], "./7.jpg", SIZE, SIZE);
	loadimage(&imge[8], ".//8.jpg", SIZE, SIZE);
	loadimage(&imge[9], "./����.png", SIZE, SIZE);//��
	loadimage(&imge[10], "./10.jpg", SIZE, SIZE);//�ڸ�
	loadimage(&imge[11], "./11.jpg", SIZE, SIZE);//��־��
	//�տ�ʼ����ȫ������
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



//ͼ�񻯳���
void GameDrawE()
{
	cleardevice();//���ͼ��
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			if (mape[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &imge[9]);//��
			}
			else if (mape[i][j] >= 0 && mape[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &imge[mape[i][j]]);//����
			}
			else if (mape[i][j] >= 19 && mape[i][j] <= 28)
			{
				putimage(j * SIZE, i * SIZE, &imge[10]);//����
			}
			else if (mape[i][j] > 30)
			{
				putimage(j * SIZE, i * SIZE, &imge[11]);//���
			}
		}
	}
}

//��������չ����Χ�ĸ���
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
					mape[i][j]>8)//����Խ��
				{
					mape[i][j] -= 20;//����
					counte++;//�㿪�ĸ�����
					OpenAroundE(i, j);
				}
			}
		}
	}
}

int MouseE()
{
	if (MouseHit())//�ж��Ƿ��������Ϣ
	{
		MOUSEMSG msg = GetMouseMsg();//��ȡ�������
		int row = msg.y / SIZE;//ת��Ϊ�����±�
		int col = msg.x / SIZE;
		switch (msg.uMsg)//�ж������Ϣ������
		{
		case WM_LBUTTONDOWN://���
			if (mape[row][col] > 8)//���ܶ��Ѿ�չ����������в���
			{
				mciSendString("close click", 0, 0, 0);
				mciSendString("open ./click.wav alias click", 0, 0, 0);
				mciSendString("play click", 0, 0, 0);

				mape[row][col] -= 20;
				counte++;
				OpenAroundE(row, col);
			}

			break;
		case WM_RBUTTONDOWN://�Ҽ������
			if (mape[row][col] > 8 && mape[row][col] <= 28)
			{
				mciSendString("close rclick", 0, 0, 0);
				mciSendString("open ./rightClick.wav alias rclick", 0, 0, 0);
				mciSendString("play rclick", 0, 0, 0);
				mape[row][col] += 20;
			}
			else if (mape[row][col] > 28)
			{
				mape[row][col] -= 20;//�Ѿ���ǹ���
			}
			break;
		}
		return mape[row][col];
	}
}

void ResultShowE()
{
	cleardevice();//���ͼ��
	for (int i = 0; i < ROWE; i++)
	{
		for (int j = 0; j < COLE; j++)
		{
			if (mape[i][j] >= 19&&mape[i][j]<39)//δ�������
				mape[i][j] -= 20;
			if (mape[i][j] >= 39)//�ѱ������
				mape[i][j] -= 40;
			if (mape[i][j] == -1)
			{
				putimage(j * SIZE, i * SIZE, &imge[9]);//��
			}
			if (mape[i][j] >= 0 && mape[i][j] <= 8)
			{
				putimage(j * SIZE, i * SIZE, &imge[mape[i][j]]);//����
			}
		}
	}
}
void JudefinalE()
{
	HWND hwnd = GetHWnd();
	if (MouseE() == -1)//�㵽��
	{
		mciSendString("close search", 0, 0, 0);

		mciSendString("open ./search.wav alias search", 0, 0, 0);
		mciSendString("play search", 0, 0, 0);
		//���öԻ���
		int isy = MessageBox(hwnd, "����̫���ˣ��ȵ����ˣ��뿴���𣿣���", "��ʾ", MB_YESNO);
		if (IDYES == isy)
		{
			ResultShowE();//չʾ���
			IMAGE img;
			loadimage(&img, "./��.jpg");
			putimage(COLE * SIZE, 0, &img);
			setbkmode(TRANSPARENT);
			fillrectangle(COLE * SIZE, 200, COLE * SIZE + 199, 260);
			outtextxy(COLE * SIZE + 16, 205, str1);
			outtextxy(COLE * SIZE + 16, 230, _str1);
			FlushBatchDraw();
			Sleep(1000);
			int r = MessageBox(hwnd, "С�˼��������𣿣���", "��ʾ", MB_YESNO);
			if (IDYES == r)
			{
				InitMapE();
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
				InitMapE();
				counte = 0;
			}
		}
		mciSendString("close BGM", 0, 0, 0);//�ر�����
	}
	if (counte == ROWE * COLE - MINENUME)
	{
		int isy = MessageBox(GetHWnd(), "���죬���ȻӮ�ˣ�������", "��ʾ", MB_YESNO);
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



