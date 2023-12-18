#define _CRT_SECURE_NO_WARNINGS 1
#include"Seqlist.h"
#include"contact.h"

//void SLtest()
//{
//	SL sl;
//	SLInit(&sl);
//	//顺序表的具体操作
//	SLPushBack(&sl, 1);
//	SLPushBack(&sl, 2);
//	SLPushBack(&sl, 3);
//	SLPushBack(&sl, 4);//1 2 3 4
//	SLPrint(&sl);
//	////头插
//	SLPushFront(&sl, 5);
//	SLPushFront(&sl, 6);
//	SLPushFront(&sl, 7);//7 6 5 1 2 3 4
//	SLPrint(&sl);
//	//尾删
//	SLPopBack(&sl);
//	SLPrint(&sl);//7 6 5 1 2 3
//	SLPopBack(&sl);
//	SLPrint(&sl);//7 6 5 1 2
//
//	//头删
//	SLPopFront(&sl);
//	SLPrint(&sl);//6 5 1 2
//	//SLDestroy(&sl);
//}

void contact_test()
{
	contact con;
	ContactInit(&con);
	//往通讯录插入数据
	ContactAdd(&con);
	ContactAdd(&con);
	Contactshow(&con);
	//删除数据
	ContactDel(&con);
	Contactshow(&con);


	ContactFind(&con);


	ContactDestory(&con);
}
int main()
{
	contact_test();
	return 0;
}