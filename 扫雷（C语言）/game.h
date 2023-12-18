#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>

#define EASY_COUNT 10
#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2
//初始化棋盘
void Initboard(char board[ROWS][COLS],int rows,int cols,char set);
//打印棋盘
void Displayboard(char board[ROWS][COLS],int row,int col);

//布置雷
void Setmine(char board[ROWS][COLS], int row, int col);
//排查雷
void Findmine(char mine[ROWS][COLS],char show[ROWS][COLS],int row ,int col);
