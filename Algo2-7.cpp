 // algo2-7.cpp �̿�����ͼ2.10��̬����ʾ��
 // ��1������λ����[0].cur�С���Աcur��ֵΪ0��������β
 #include"c1.h"
 #define N 6 // �ַ�������
 typedef char ElemType[N];
 #include"c2-3.h"

 int main()
 {
   SLinkList s={{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0}}; // �̿�����ͼ2.10(a)��״̬
   int i;
   i=s[0].cur; // iָʾ��1������λ��
   while(i)
   { // ����̿�����ͼ2.10(a)��״̬
     printf("%s ",s[i].data); // ��������ĵ�ǰֵ
     i=s[i].cur; // �ҵ���һ��
   }
   printf("\n");
   s[4].cur=9; // ���̿�����ͼ2.10(b)�޸�(��"LI"֮�����"SHI")
   s[9].cur=5;
   strcpy(s[9].data,"SHI");
   s[6].cur=8; // ɾ��"ZHENG"
   i=s[0].cur; // iָʾ��1������λ��
   while(i)
   { // ����̿�����ͼ2.10(b)��״̬
     printf("%s ",s[i].data); // ��������ĵ�ǰֵ
     i=s[i].cur; // �ҵ���һ��
   }
   printf("\n");
 }