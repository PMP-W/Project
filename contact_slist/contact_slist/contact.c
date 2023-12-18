#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"

void ContactDestory(CInfo** pcon)
{
	printf("清空通讯录\n\n");
	Sleep(100000);
	assert(pcon);
	assert(*pcon);
	CInfo* pcur = *pcon;
	while (pcur->next != NULL)
	{
		CInfo* del = pcur->next;
		free(pcur);
		pcur = del;
	}
	printf("通讯录为空!\n");
}
CInfo* FindByName(CInfo** pcon)
{
	assert(pcon);
	char name[20] = {'\0'};
	scanf("%s", name);
	CInfo* pcur = *pcon;
	while (pcur)
	{
		if (strcmp(pcur->name, name) == 0)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	return NULL;
}
//添加联系人
void ContactAdd(CInfo** pcon)
{
	assert(pcon);
	CInfo* node = (CInfo*)malloc(sizeof(CInfo));
	printf("请输入联系人姓名：\n");
	scanf("%s", &node->name);
	printf("请输入联系人性别：\n");
	scanf("%s", &node->sex);
	printf("请输入联系人年龄：\n");
	scanf("%d", &node->age);
	printf("请输入联系人电话：\n");
	scanf("%s", &node->tel);
	printf("请输入联系人地址：\n");
	scanf("%s", &node->addr);
	if (*pcon == NULL)
	{
		*pcon = node;
		node->next = NULL;
		return;
	}
	CInfo* pcur = *pcon;
	while (pcur->next != NULL)
	{
		pcur = pcur->next;
	}
	pcur->next = node;
	node->next = NULL;
}
//删除联系人
void ContactDel(CInfo** pcon)
{
	assert(pcon);
	assert(*pcon);
	printf("输入要删除的联系人的姓名：\n");
	CInfo* pos = FindByName(pcon);
	assert(pos);
	if (*pcon == pos)
	{
		*pcon = pos->next;
		free(pos);
		return;
	}
	CInfo* prev = *pcon;
	while (prev->next != pos)
	{
		prev = prev->next;
	}
	prev->next = pos->next;
	free(pos);
	pos = NULL;
}
//修改联系人
void Contactrevsie(CInfo** pcon)
{
	assert(pcon);
	assert(*pcon);
	printf("输入要修改的联系人的姓名：\n");
	CInfo* node = FindByName(pcon);
	if (node == NULL)
	{
		printf("联系人不存在！\n");
		return;
	}
	printf("请输入联系人姓名：\n");
	scanf("%s", &node->name);
	printf("请输入联系人性别：\n");
	scanf("%s", &node->sex);
	printf("请输入联系人年龄：\n");
	scanf("%d", &node->age);
	printf("请输入联系人电话：\n");
	scanf("%s", &node->tel);
	printf("请输入联系人地址：\n");
	scanf("%s", &node->addr);



}
// 查看通讯录
void Contactshow(CInfo* pcon)
{
	//打印通讯录所有的数据
	//先打印表头
	printf("******************通讯录*****************************\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "姓名", "性别", "年龄", "电话", "住址");
	CInfo* pcur = pcon;
	while (pcur != NULL)
	{
		printf("%-10s %-10s %-10d %-10s %-10s\n",
			pcur->name,
			pcur->sex,
			pcur->age,
			pcur->tel,
			pcur->addr);
		pcur = pcur->next;
	}
	printf("******************************************************\n");
}
//查找联系人
void ContactFind(CInfo** pcon)
{
	assert(pcon);
	assert(*pcon);
	printf("输入要查找的联系人的姓名：\n");
	CInfo* pos = FindByName(pcon);
	if (pos == NULL)
	{
		printf("未找到!\n");
		return;
	}
	printf("找到了！\n");
	printf("--------------------------------------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "姓名", "性别", "年龄", "电话", "住址");
	printf("%-10s %-10s %-10d %-10s %-10s\n",
		pos->name,
		pos->sex,
		pos->age,
		pos->tel,
		pos->addr);
	printf("--------------------------------------------------------\n");
}
