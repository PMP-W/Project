#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>//������ý���豸�ӿ�
#pragma comment(lib,"winmm.lib")//���ؾ�̬��
//12*12
#define ROW 12 //�� 
#define COL 12 //��
//9*9
#define ROWE 9 //�� 
#define COLE 9 //��
#define MINENUM 12 //�׵����� 
#define MINENUME 9 //�׵����� 
#define SIZE 50 //ͼƬ��С 


void InitMap();
void GameDraw();
void Judefinal();
void ShowMap();
void ResultShow();//���չʾ

void InitMapE();
void GameDrawE();
void JudefinalE();
void ShowMapE();
void ResultShowE();//���չʾ