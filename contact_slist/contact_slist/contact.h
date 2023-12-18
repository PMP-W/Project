#pragma once
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
//创建保存联系人数据的结构
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


//通讯录的初始化和销毁
void ContactDestory(CInfo** pcon);

CInfo* FindByName(CInfo** pcon);
//添加联系人
void ContactAdd(CInfo** pcon);
//删除联系人
void ContactDel(CInfo** pcon);
//修改联系人
void Contactrevsie(CInfo** pcon);
// 查看通讯录
void Contactshow(CInfo* pcon);
//查找联系人
void ContactFind(CInfo* pcon);
