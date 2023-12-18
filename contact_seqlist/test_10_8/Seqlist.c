#define _CRT_SECURE_NO_WARNINGS 1
#include"Seqlist.h"
#include"contact.h"
void SLInit(SL* ps)
{
	ps->a = NULL;
	ps->size = 0;
	ps->cap = 0;

}
void SLDestory(SL* ps)
{
	if (ps->a)
		free(ps->a);
	ps->a = NULL;
	ps->size = ps->cap = 0;
}

void SLcheckCapacity(SL* ps)
{
	if (ps->size == ps->cap)
	{
		//�ռ䲻�������������
		//��Ҫ����
		int newcapscity = ps->cap == 0 ? 4 : 2 * ps->cap;
		//ʹ��realloc����ռ�
		//�ռ��������ʧ�ܣ���Ҫ����һ����ʱ���������򣬿��ܻᣬ�ͷ�ԭ��������ڴ棬���ԭ�е�����
		SLDataType* tmp = (SLDataType*)realloc(ps->a, newcapscity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			perror("realloc");
			return ;//���������󣬷���һ����0��״̬��
		}
		ps->a = tmp;
		ps->cap = newcapscity;
	}
}
//ͷ��/β�� ����/ɾ��
void SLPushBack(SL* ps, SLDataType x)//β������
{
	//ʹ��ָ��ǰ���ж�ָ���Ƿ�Ϊ��
	assert(ps);
	//��͵ķ�ʽ
	//if(ps->a==NULL)
	//1.�ռ��㹻��ֱ��β��
	//�ռ䲻�㣬����
	SLcheckCapacity(ps);
	//ֱ�Ӳ�������
	ps->a[ps->size++] = x;
}
void SLPushFront(SL* ps, SLDataType x)//ͷ������
{
	assert(ps);
	//�жϿռ��Ƿ��㹻������������
	SLcheckCapacity(ps);
	//�ռ��㹻����ʷ���ݺ���һλ
	for (size_t i = ps->size; i > 0; i--)
	{
		ps->a[i] = ps->a[i - 1];
	}
	ps->a[0] = x;
	ps->size++;
}
void SLPopBack(SL* ps)//β��ɾ��
{
	//�ж�˳����Ƿ�Ϊ��
	assert(ps);
	//assert(!SLIsEmpty(ps));
	ps->size--;
}
void SLPopFront(SL* ps)//ͷ��ɾ��
{
	for (size_t i = 1; i<ps->size; i++)
	{
		ps->a[i - 1] = ps->a[i];
	}
	ps->size--;
}
//void SLPrint(SL* ps)//��ӡ
//{
//	for (size_t i = 0; i < ps->size; i++)
//	{
//		printf("%d ", ps->a[i]);
//	}
//	printf("\n");
//}
bool SLIsEmpty(SL* ps)//����˳����Ƿ��
{
	assert(ps);
	return ps->size == 0;
}

void SLErase(SL* ps,int pos)//ɾ��ָ��λ�õ�����
{
	assert(ps);
	assert(!SLIsEmpty(ps));
	assert(pos >= 0 && pos <= ps->size - 1);

	//ɾ��(����)
	for (int i = pos; i <= ps->size-1; i++)
	{
		ps->a[i] = ps->a[i+1];
	}
	ps->size--;
}
void SLInsert(SL* ps, int pos, SLDataType x)//��ָ��λ�ò�������
{
	assert(ps);
	assert(pos >= 0 && pos <= ps->size);
	SLcheckCapacity(ps);

	//����
	for (int i = ps->size; i > pos; i--)
	{
		ps->a[i] = ps->a[i-1];
	}
	ps->a[pos] = x;
	ps->size++;
}
//bool SLFind(SL* ps, SLDataType x) {
//	assert(ps);
//	for (int i = 0; i < ps->size; i++)
//	{
//		if (strcmp(ps->a[i].name, x)==0) {
//			//�ҵ���
//			return true;
//		}
//	}
//	return false;
//}