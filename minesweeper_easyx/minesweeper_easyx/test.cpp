#define _CRT_SECURE_NO_WARNINGS 1
#include"minesweeper.h"
#include<time.h>
extern char str1[100];
extern char _str1[100];
extern char str[100];
extern char _str[100];
extern clock_t _start;
extern clock_t _end;
extern clock_t start, end;
extern int counte;
void menu()
{
	initgraph(1200, 740);
	setbkcolor(WHITE);
	cleardevice();//
	//设置背景图片
	IMAGE img,img1,img2,img3,imgw;//定义一个对象
	//加载图片
	loadimage(&img, "./1234.png");
	loadimage(&img1, "./difficulty.png");
	loadimage(&img2, "./3_3.png");
	loadimage(&img3, "./9_9.png");
	loadimage(&imgw, "./word.png");
	putimage(0, 0, &img);
	mciSendString("open ./坤.mp3 alias B", 0, 0, 0);
	mciSendString("play B", 0, 0, 0);
	putimage(735, 150, &img1);
	putimage(600, 287, &img2);//9*9
	putimage(880, 290, &img3);//12*12
	putimage(700, 50, &imgw);
	MOUSEMSG m;
	setbkmode(TRANSPARENT);
	mciSendString("close B", 0, 0, 0);
	while (1) {
		m = GetMouseMsg();
		//9*9
		if (m.x >= 600 && m.x <= 600+195 && m.y >= 287 && m.y <= 287+170) {
			if (m.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				cleardevice();
				initgraph(ROWE * SIZE+180, COLE * SIZE, 0);
				InitMapE();
				setbkcolor(RGB(255,128,255));
				cleardevice();
				ShowMapE();
				BeginBatchDraw();//双缓冲批量绘图，防止屏闪
				IMAGE img;
				loadimage(&img, "./坤.jpg");
				mciSendString("open ./search.wav alias search", 0, 0, 0);
				mciSendString("play search", 0, 0, 0);
				start = clock();
				while (1)
				{
					end = clock();
					float t = (end - start)/CLOCKS_PER_SEC;
					sprintf(str1, "时间：%.0f s", t);
					sprintf(_str1, "篮球：%d", MINENUME);
					settextcolor(RED);
					settextstyle(20, 0, "hooge 05_54");
					GameDrawE();
					putimage(COLE*SIZE,0,&img);
					setfillcolor(RGB(128, 255, 255));
					setbkmode(TRANSPARENT);
					fillrectangle(COLE * SIZE, 200, COLE * SIZE + 199, 260);
					outtextxy(COLE * SIZE+16, 205,str1 );
					outtextxy(COLE * SIZE+16, 230,_str1 );
					FlushBatchDraw();
					JudefinalE();
				}
				EndBatchDraw();
				break;
			}
		}
		//12*12
		if (m.x >= 880 && m.x <= 880 + 195 && m.y >= 290 && m.y <= 290 + 170)
		{
			if (m.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				cleardevice();
				initgraph(ROW * SIZE+180, COL * SIZE, 0);
				InitMap();
				setbkcolor(RGB(255, 128, 255));
				cleardevice();
				ShowMap();
				BeginBatchDraw();//双缓冲批量绘图，防止屏闪
				IMAGE img;
				loadimage(&img, "./坤.jpg");
				mciSendString("open ./search.wav alias search", 0, 0, 0);
				mciSendString("play search", 0, 0, 0);
				_start = clock();
				while (1)
				{
					_end = clock();
					float t = (_end - _start) / CLOCKS_PER_SEC;
					sprintf(str, "时间：%.0f s", t);
					sprintf(_str, "篮球：%d", MINENUME);
					settextcolor(RED);
					settextstyle(20, 0, "hooge 05_54");
					GameDraw();
					putimage(COL * SIZE, 0, &img);
					setfillcolor(RGB(128, 255, 255));
					setbkmode(TRANSPARENT);
					fillrectangle(COL * SIZE, 200, COL * SIZE + 199, 260);
					outtextxy(COL * SIZE + 16, 205, str);
					outtextxy(COL * SIZE + 16, 230, _str);
					FlushBatchDraw();
					Judefinal();
				}
				EndBatchDraw();
				break;
			}
		}
	}
}
int main()
{
	menu();
	getchar();
	return 0;
}