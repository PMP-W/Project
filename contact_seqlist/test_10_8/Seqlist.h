#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>

//��̬˳���
typedef struct ContactInfo SLDataType;
typedef struct Seqlist
{
	SLDataType* a;
	int size;//˳�������Ч���ݵĸ���
	int cap;//˳���ǰ�Ŀռ��С
}SL;
//��˳�����г�ʼ��
void SLInit(SL* s1);
void SLDestory(SL* ps);

//ͷ��/β�� ����/ɾ��
void SLPushBack(SL* ps,SLDataType x);//β������
void SLPushFront(SL* ps, SLDataType x);//ͷ������
void SLPopBack(SL* ps);//β��ɾ��
void SLPopFront(SL* ps);//ͷ��ɾ��
void SLErase(SL* ps,int pos);//ɾ��ָ��λ�õ�����
void SLInsert(SL* ps,int pos,SLDataType x);//��ָ��λ�ò�������

void SLPrint(SL* ps);//��ӡ
bool SLIsEmpty(SL* ps);//����˳����Ƿ��

bool SLFind(SL* ps, SLDataType x);
