#define _CRT_SECURE_NO_WARNINGS 1
#include"Seqlist.h"
#include"contact.h"

//void SLtest()
//{
//	SL sl;
//	SLInit(&sl);
//	//˳���ľ������
//	SLPushBack(&sl, 1);
//	SLPushBack(&sl, 2);
//	SLPushBack(&sl, 3);
//	SLPushBack(&sl, 4);//1 2 3 4
//	SLPrint(&sl);
//	////ͷ��
//	SLPushFront(&sl, 5);
//	SLPushFront(&sl, 6);
//	SLPushFront(&sl, 7);//7 6 5 1 2 3 4
//	SLPrint(&sl);
//	//βɾ
//	SLPopBack(&sl);
//	SLPrint(&sl);//7 6 5 1 2 3
//	SLPopBack(&sl);
//	SLPrint(&sl);//7 6 5 1 2
//
//	//ͷɾ
//	SLPopFront(&sl);
//	SLPrint(&sl);//6 5 1 2
//	//SLDestroy(&sl);
//}

void contact_test()
{
	contact con;
	ContactInit(&con);
	//��ͨѶ¼��������
	ContactAdd(&con);
	ContactAdd(&con);
	Contactshow(&con);
	//ɾ������
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