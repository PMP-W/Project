#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>

//动态顺序表
typedef struct ContactInfo SLDataType;
typedef struct Seqlist
{
	SLDataType* a;
	int size;//顺序表中有效数据的个数
	int cap;//顺序表当前的空间大小
}SL;
//对顺序表进行初始化
void SLInit(SL* s1);
void SLDestory(SL* ps);

//头部/尾部 插入/删除
void SLPushBack(SL* ps,SLDataType x);//尾部插入
void SLPushFront(SL* ps, SLDataType x);//头部插入
void SLPopBack(SL* ps);//尾部删除
void SLPopFront(SL* ps);//头部删除
void SLErase(SL* ps,int pos);//删除指定位置的数据
void SLInsert(SL* ps,int pos,SLDataType x);//在指定位置插入数据

void SLPrint(SL* ps);//打印
bool SLIsEmpty(SL* ps);//检验顺序表是否空

bool SLFind(SL* ps, SLDataType x);
