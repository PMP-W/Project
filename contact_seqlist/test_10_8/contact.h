#define _CRT_SECURE_NO_WARNINGS 1
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
}CInfo;

//通讯录的底层时通过顺序表来实现的
typedef struct Seqlist contact;

//通讯录的初始化和销毁
void ContactInit(contact* pcon);
void ContactDestory(contact* pcon);

//添加联系人
void ContactAdd(contact* pcon);
//删除联系人
void ContactDel(contact* pcon);
//修改联系人
void Contactrevsie(contact* pcon);
// 查看通讯录
void Contactshow(contact* pcon);
//查找联系人
void ContactFind(contact* pcon);
