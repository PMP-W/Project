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
		//空间不足以再添加数据
		//需要扩容
		int newcapscity = ps->cap == 0 ? 4 : 2 * ps->cap;
		//使用realloc申请空间
		//空间可能申请失败，需要创建一个临时变量，否则，可能会，释放原来申请的内存，清除原有的数据
		SLDataType* tmp = (SLDataType*)realloc(ps->a, newcapscity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			perror("realloc");
			return ;//程序发生错误，返回一个非0的状态码
		}
		ps->a = tmp;
		ps->cap = newcapscity;
	}
}
//头部/尾部 插入/删除
void SLPushBack(SL* ps, SLDataType x)//尾部插入
{
	//使用指针前，判断指针是否为空
	assert(ps);
	//柔和的方式
	//if(ps->a==NULL)
	//1.空间足够，直接尾插
	//空间不足，扩容
	SLcheckCapacity(ps);
	//直接插入数据
	ps->a[ps->size++] = x;
}
void SLPushFront(SL* ps, SLDataType x)//头部插入
{
	assert(ps);
	//判断空间是否足够，不够则扩容
	SLcheckCapacity(ps);
	//空间足够，历史数据后移一位
	for (size_t i = ps->size; i > 0; i--)
	{
		ps->a[i] = ps->a[i - 1];
	}
	ps->a[0] = x;
	ps->size++;
}
void SLPopBack(SL* ps)//尾部删除
{
	//判断顺序表是否为空
	assert(ps);
	//assert(!SLIsEmpty(ps));
	ps->size--;
}
void SLPopFront(SL* ps)//头部删除
{
	for (size_t i = 1; i<ps->size; i++)
	{
		ps->a[i - 1] = ps->a[i];
	}
	ps->size--;
}
//void SLPrint(SL* ps)//打印
//{
//	for (size_t i = 0; i < ps->size; i++)
//	{
//		printf("%d ", ps->a[i]);
//	}
//	printf("\n");
//}
bool SLIsEmpty(SL* ps)//检验顺序表是否空
{
	assert(ps);
	return ps->size == 0;
}

void SLErase(SL* ps,int pos)//删除指定位置的数据
{
	assert(ps);
	assert(!SLIsEmpty(ps));
	assert(pos >= 0 && pos <= ps->size - 1);

	//删除(覆盖)
	for (int i = pos; i <= ps->size-1; i++)
	{
		ps->a[i] = ps->a[i+1];
	}
	ps->size--;
}
void SLInsert(SL* ps, int pos, SLDataType x)//在指定位置插入数据
{
	assert(ps);
	assert(pos >= 0 && pos <= ps->size);
	SLcheckCapacity(ps);

	//插入
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
//			//找到了
//			return true;
//		}
//	}
//	return false;
//}