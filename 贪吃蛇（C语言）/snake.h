#pragma once
#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
#include<locale.h>
#include<time.h>

//检测某一个键是否被按过，判断GetAsyncKeyState的返回值的最低位是否为1
#define KEY_PRESS(VK) ((GetAsyncKeyState(VK)&0x1)?1:0)
//设置墙体
#define WALL L'□'
//设置蛇身节点
#define BODY L'●'
//设置事物
#define FOOD L'★'
//蛇的初始位置
#define POS_X 24
#define POS_Y 5



//蛇身节点的信息
typedef struct SnakeNode
{
	int x;//横坐标（向左为正）
	int y;//纵坐标（向下为正）
	struct SnakeNode* next;
}SnakeNode ,*pSnakeNode;
enum DIRECTION//蛇头的方向，默认是向右
{
	UP = 1,
	DOWM,
	LEFT,
	RIGHT
};
enum GAME_STATUS //游戏状态
{
	FINE,//游戏正常运行
	KILL_BY_WALL,//蛇撞墙
	KILL_BY_SELF,//蛇撞到自己
	END_NORMAL//游戏正常结束
};
//整条蛇
typedef struct Snake
{
	pSnakeNode _pSnake;//维护整条蛇的指针
	pSnakeNode _pFood;//维护食物的指针
	enum DIRECTION _Dir;//蛇头的方向，默认是向右
	enum GAME_STATUS _Status;//游戏状态
	int _Socre;//游戏当前获得的分数
	int _foodweight;//每个食物当前的分数
	int _SleepTime;//每走一步休息的时间，即蛇的速度
}Snake,*pSnake;

//设置光标位置
void SetPos(short x, short y);
//游戏开始，完成游戏的初始化
void WelcomeToGame();
void CreatMap();
//初始化蛇身
void InitSnake(pSnake ps);
void CreatFood(pSnake ps);
void CreatFood(pSnake ps);
void GameStart(pSnake ps);
//游戏运行
void PrintHelpInfo();
int NextIsFood(pSnakeNode psn, pSnake ps);
void pause();
int killByWall(pSnake ps);
int killBySelf(pSnake ps);
void EatFood(pSnakeNode psn, pSnake ps);
void SnakeMove(pSnake ps);
void GameRun(pSnake ps);
//游戏结束
void GameEnd(pSnake ps);