// algo2-2.cpp ʵ���㷨2.2�ĳ���
#include"c1.h"
typedef int ElemType;
#include"c2-1.h"
#include"bo2-1.cpp"
#include"func2-3.cpp" // ����equal()��comp()��print()��print2()��print1()����
void MergeList(SqList La,SqList Lb,SqList &Lc) // �㷨2.2
{ // ��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����С�
// �鲢La��Lb�õ��µ����Ա�Lc��Lc������Ԫ��Ҳ��ֵ�ǵݼ�����
	int i=1,j=1,k=0;
	int La_len,Lb_len;
	ElemType ai,bj;
	InitList(Lc); // �����ձ�Lc
	La_len=ListLength(La);
	Lb_len=ListLength(Lb);
	while(i<=La_len&&j<=Lb_len) // ��La�ͱ�Lb���ǿ�
	{
		GetElem(La,i,ai);
		GetElem(Lb,j,bj);
		if(ai<=bj)
		{
			ListInsert(Lc,++k,ai);
			++i;
		}
		else
		{
			ListInsert(Lc,++k,bj);
			++j;
		}
	} // ��������whileѭ��ֻ����һ����ִ��
	while(i<=La_len) // ��La�ǿ��ұ�Lb��
	{
		GetElem(La,i++,ai);
		ListInsert(Lc,++k,ai);
	}
	while(j<=Lb_len) // ��Lb�ǿ��ұ�La��
	{
		GetElem(Lb,j++,bj);
		ListInsert(Lc,++k,bj);
	}
}

int main()
{
	SqList La,Lb,Lc;
	int j,a[4]={3,5,8,11},b[7]={2,6,8,9,11,15,20};
	InitList(La); // �����ձ�La
	for(j=1;j<=4;j++) // �ڱ�La�в���4��Ԫ��
		ListInsert(La,j,a[j-1]);
	printf("La= "); // �����La������
	ListTraverse(La,print1);
	InitList(Lb); // �����ձ�Lb
	for(j=1;j<=7;j++) // �ڱ�Lb�в���7��Ԫ��
		ListInsert(Lb,j,b[j-1]);
	printf("Lb= "); // �����Lb������
	ListTraverse(Lb,print1);
	MergeList(La,Lb,Lc);
	printf("Lc= "); // �����Lc������
	ListTraverse(Lc,print1);
	return 0;
}