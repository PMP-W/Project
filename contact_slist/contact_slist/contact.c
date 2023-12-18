#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"

void ContactDestory(CInfo** pcon)
{
	printf("���ͨѶ¼\n\n");
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
	printf("ͨѶ¼Ϊ��!\n");
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
//�����ϵ��
void ContactAdd(CInfo** pcon)
{
	assert(pcon);
	CInfo* node = (CInfo*)malloc(sizeof(CInfo));
	printf("��������ϵ��������\n");
	scanf("%s", &node->name);
	printf("��������ϵ���Ա�\n");
	scanf("%s", &node->sex);
	printf("��������ϵ�����䣺\n");
	scanf("%d", &node->age);
	printf("��������ϵ�˵绰��\n");
	scanf("%s", &node->tel);
	printf("��������ϵ�˵�ַ��\n");
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
//ɾ����ϵ��
void ContactDel(CInfo** pcon)
{
	assert(pcon);
	assert(*pcon);
	printf("����Ҫɾ������ϵ�˵�������\n");
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
//�޸���ϵ��
void Contactrevsie(CInfo** pcon)
{
	assert(pcon);
	assert(*pcon);
	printf("����Ҫ�޸ĵ���ϵ�˵�������\n");
	CInfo* node = FindByName(pcon);
	if (node == NULL)
	{
		printf("��ϵ�˲����ڣ�\n");
		return;
	}
	printf("��������ϵ��������\n");
	scanf("%s", &node->name);
	printf("��������ϵ���Ա�\n");
	scanf("%s", &node->sex);
	printf("��������ϵ�����䣺\n");
	scanf("%d", &node->age);
	printf("��������ϵ�˵绰��\n");
	scanf("%s", &node->tel);
	printf("��������ϵ�˵�ַ��\n");
	scanf("%s", &node->addr);



}
// �鿴ͨѶ¼
void Contactshow(CInfo* pcon)
{
	//��ӡͨѶ¼���е�����
	//�ȴ�ӡ��ͷ
	printf("******************ͨѶ¼*****************************\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "����", "�Ա�", "����", "�绰", "סַ");
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
//������ϵ��
void ContactFind(CInfo** pcon)
{
	assert(pcon);
	assert(*pcon);
	printf("����Ҫ���ҵ���ϵ�˵�������\n");
	CInfo* pos = FindByName(pcon);
	if (pos == NULL)
	{
		printf("δ�ҵ�!\n");
		return;
	}
	printf("�ҵ��ˣ�\n");
	printf("--------------------------------------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "����", "�Ա�", "����", "�绰", "סַ");
	printf("%-10s %-10s %-10d %-10s %-10s\n",
		pos->name,
		pos->sex,
		pos->age,
		pos->tel,
		pos->addr);
	printf("--------------------------------------------------------\n");
}
