#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
#include"Seqlist.h"

//ͨѶ¼��ʼ��
void ContactInit(contact* pcon)
{
	SLInit(pcon);
}
//ͨѶ¼����
void ContactDestory(contact* pcon)
{
	SLDestory(pcon);
}

//�����ϵ��
void ContactAdd(contact* pcon)
{
	//������Ҫ��ȡ����Ϣ����CInfo�ṹ����Ҫ�������
	CInfo info;
	printf("��������ϵ��������\n");
	scanf("%s", info.name);
	printf("��������ϵ���Ա�\n");
	scanf("%s", info.sex);
	printf("��������ϵ�����䣺\n");
	scanf("%d", &info.age);
	printf("��������ϵ�˵绰��\n");
	scanf("%s", info.tel);
	printf("��������ϵ�˵�ַ��\n");
	scanf("%s", info.addr);

	//��ͨѶ¼��˳����в�������
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
//ɾ��ָ����ϵ��
void ContactDel(contact* pcon)
{
	//ǿ��Ҫ���û�ͨ����ϰ�˵�����������
	printf("������Ҫɾ������ϵ�����ƣ�\n");
	char name[NAME_MAX];
	scanf("%s", name);
	int findindex = FindByName(pcon, name);
	if (findindex < 0)
	{
		printf("��ϵ�˲����ڣ�");
		return;
	}
	SLErase(pcon, findindex);
}

//�鿴ͨѶ¼
void Contactshow(contact* pcon)
{
	//��ӡͨѶ¼���е�����
	//�ȴ�ӡ��ͷ
	printf("******************ͨѶ¼*****************************\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "����","�Ա�","����","�绰","סַ");
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
//����ָ����ϵ��
void ContactFind(contact* pcon)
{
	//����Ҫ���ҵ���ϵ�˵�����

	char name[NAME_MAX];
	printf("������Ҫ���ҵ���ϵ�˵�������\n");
	scanf("%s", name);
	int pos = FindByName(pcon, name);
	if (pos < 0)
	{
		printf("δ�ҵ���ϵ�ˣ�\n");
		return;
	}
	printf("�ҵ��ˣ�\n");
	printf("--------------------------------------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "����", "�Ա�", "����", "�绰", "סַ");
	printf("%-10s %-10s %-10d %-10s %-10s\n",
		pcon->a[pos].name,
		pcon->a[pos].sex,
		pcon->a[pos].age,
		pcon->a[pos].tel,
		pcon->a[pos].addr);
	printf("--------------------------------------------------------\n");

}
//�޸���ϵ��
void Contactrevsie(contact* pcon)
{
	char name[NAME_MAX];
	printf("������Ҫ�޸ĵ��û������ƣ�\n");
	scanf("%s", name);
	int pos = FindByName(pcon, name);
	if (pos < 0)
	{
		printf("���û������ڣ�\n");
		return;
	}

}
