#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
#include"Seqlist.h"

//通讯录初始化
void ContactInit(contact* pcon)
{
	SLInit(pcon);
}
//通讯录销毁
void ContactDestory(contact* pcon)
{
	SLDestory(pcon);
}

//添加联系人
void ContactAdd(contact* pcon)
{
	//接下来要获取的信息都是CInfo结构体里要求的数据
	CInfo info;
	printf("请输入联系人姓名：\n");
	scanf("%s", info.name);
	printf("请输入联系人性别：\n");
	scanf("%s", info.sex);
	printf("请输入联系人年龄：\n");
	scanf("%d", &info.age);
	printf("请输入联系人电话：\n");
	scanf("%s", info.tel);
	printf("请输入联系人地址：\n");
	scanf("%s", info.addr);

	//往通讯录（顺序表）中插入数据
	SLPushBack(pcon, info);
	
}
int FindByName(contact* pcon, char name[])
{
	for (int i = 0; i < pcon->size; i++)
	{
		if (strcmp(pcon->a[i].name, name) == 0)
			return i;
	}
	return -1;
}
//删除指定联系人
void ContactDel(contact* pcon)
{
	//强制要求用户通过练习人的名称来查找
	printf("请输入要删除的联系人名称：\n");
	char name[NAME_MAX];
	scanf("%s", name);
	int findindex = FindByName(pcon, name);
	if (findindex < 0)
	{
		printf("联系人不存在！");
		return;
	}
	SLErase(pcon, findindex);
}

//查看通讯录
void Contactshow(contact* pcon)
{
	//打印通讯录所有的数据
	//先打印表头
	printf("******************通讯录*****************************\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "姓名","性别","年龄","电话","住址");
	for (int i = 0; i < pcon->size; i++)
	{
		printf("%-10s %-10s %-10d %-10s %-10s\n", 
			pcon->a[i].name, 
			pcon->a[i].sex, 
			pcon->a[i].age, 
			pcon->a[i].tel, 
			pcon->a[i].addr);
	}
	printf("******************************************************\n");

}
//查找指定联系人
void ContactFind(contact* pcon)
{
	//输入要查找的联系人的姓名

	char name[NAME_MAX];
	printf("请输入要查找的联系人的姓名：\n");
	scanf("%s", name);
	int pos = FindByName(pcon, name);
	if (pos < 0)
	{
		printf("未找到联系人！\n");
		return;
	}
	printf("找到了！\n");
	printf("--------------------------------------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "姓名", "性别", "年龄", "电话", "住址");
	printf("%-10s %-10s %-10d %-10s %-10s\n",
		pcon->a[pos].name,
		pcon->a[pos].sex,
		pcon->a[pos].age,
		pcon->a[pos].tel,
		pcon->a[pos].addr);
	printf("--------------------------------------------------------\n");

}
//修改联系人
void Contactrevsie(contact* pcon)
{
	char name[NAME_MAX];
	printf("请输入要修改的用户的名称：\n");
	scanf("%s", name);
	int pos = FindByName(pcon, name);
	if (pos < 0)
	{
		printf("此用户不存在！\n");
		return;
	}

}
