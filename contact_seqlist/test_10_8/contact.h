#define _CRT_SECURE_NO_WARNINGS 1
//����������ϵ�����ݵĽṹ
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

//ͨѶ¼�ĵײ�ʱͨ��˳�����ʵ�ֵ�
typedef struct Seqlist contact;

//ͨѶ¼�ĳ�ʼ��������
void ContactInit(contact* pcon);
void ContactDestory(contact* pcon);

//�����ϵ��
void ContactAdd(contact* pcon);
//ɾ����ϵ��
void ContactDel(contact* pcon);
//�޸���ϵ��
void Contactrevsie(contact* pcon);
// �鿴ͨѶ¼
void Contactshow(contact* pcon);
//������ϵ��
void ContactFind(contact* pcon);
