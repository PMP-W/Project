#pragma once
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
//����������ϵ�����ݵĽṹ
#define NAME_MAX 100
#define SEX_MAX 10
#define TEL_MAX 15
#define ADDR_MAX 100

typedef struct ContactInfo
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tel[TEL_MAX];
	char addr[ADDR_MAX];
	struct ContactInfo* next;
}CInfo;


//ͨѶ¼�ĳ�ʼ��������
void ContactDestory(CInfo** pcon);

CInfo* FindByName(CInfo** pcon);
//�����ϵ��
void ContactAdd(CInfo** pcon);
//ɾ����ϵ��
void ContactDel(CInfo** pcon);
//�޸���ϵ��
void Contactrevsie(CInfo** pcon);
// �鿴ͨѶ¼
void Contactshow(CInfo* pcon);
//������ϵ��
void ContactFind(CInfo* pcon);
