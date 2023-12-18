#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>//包含多媒体设备接口
#pragma comment(lib,"winmm.lib")//加载静态库
//12*12
#define ROW 12 //行 
#define COL 12 //列
//9*9
#define ROWE 9 //行 
#define COLE 9 //列
#define MINENUM 12 //雷的数量 
#define MINENUME 9 //雷的数量 
#define SIZE 50 //图片大小 


void InitMap();
void GameDraw();
void Judefinal();
void ShowMap();
void ResultShow();//结果展示

void InitMapE();
void GameDrawE();
void JudefinalE();
void ShowMapE();
void ResultShowE();//结果展示