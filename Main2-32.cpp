 // main2-32.cpp ����func2-2.cpp��bo2-32.cpp��������
 #include"c1.h"
 typedef int ElemType;
 #include"c2-3.h"
 #include"func2-2.cpp" // ���ַ��������õĺ����ڴ��ļ���
 #include"bo2-32.cpp"
 #include"func2-3.cpp" // ����equal()��comp()��print()��print2()��print1()����

 int main()
 {
   int j,k,La,Lb;
   Status i;
   ElemType e,e0;
   SLinkList L;
   InitSpace(L); // ������������
   La=InitList(L); // ��ʼ������La
   Lb=InitList(L); // ��ʼ������Lb
   printf("La���շ�%d(1:�� 0:��) La�ı���=%d\n",ListEmpty(L,La),ListLength(L,La));
   for(j=1;j<=5;j++)
     ListInsert(L,La,1,j);
   printf("�ڿձ�La�ı�ͷ���β���1��5��La=");
   ListTraverse(L,La,print);
   for(j=1;j<=5;j++)
     ListInsert(L,Lb,j,j);
   printf("�ڿձ�Lb�ı�β���β���1��5��Lb=");
   ListTraverse(L,Lb,print);
   printf("La���շ�%d(1:�� 0:��) La�ı���=%d\n",ListEmpty(L,La),ListLength(L,La));
   ClearList(L,La);
   printf("���La��La=");
   ListTraverse(L,La,print);
   printf("La���շ�%d(1:�� 0:��) La�ı���=%d\n",ListEmpty(L,La),ListLength(L,La));
   for(j=2;j<8;j+=5)
   {
     i=GetElem(L,Lb,j,e);
     if(i)
       printf("Lb���ĵ�%d��Ԫ�ص�ֵΪ��%d\n",j,e);
     else
       printf("Lb�������ڵ�%d��Ԫ�أ�\n",j,e);
   }
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,Lb,j);
     if(k)
       printf("Lb����ֵΪ%d��Ԫ���ھ�̬�����е�λ��Ϊ%d\n",j,k);
     else
       printf("Lb����û��ֵΪ%d��Ԫ��\n",j);
   }
   for(j=1;j<=2;j++) // ����ͷ��������
   {
     GetElem(L,Lb,j,e0); // �ѵ�j�����ݸ���e0
     i=PriorElem(L,Lb,e0,e); // ��e0��ǰ��
     if(!i)
       printf("Lb���е�Ԫ��%d��ǰ��\n",e0);
     else
       printf("Lb����Ԫ��%d��ǰ��Ϊ��%d\n",e0,e);
   }
   for(j=ListLength(L,Lb)-1;j<=ListLength(L,Lb);j++) // �����������
   {
     GetElem(L,Lb,j,e0); // �ѵ�j�����ݸ���e0
     i=NextElem(L,Lb,e0,e); // ��e0�ĺ��
     if(!i)
       printf("Lb����Ԫ��%d�޺��\n",e0);
     else
       printf("Lb����Ԫ��%d�ĺ��Ϊ��%d\n",e0,e);
   }
   k=ListLength(L,Lb); // kΪ����
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,Lb,j,e); // ɾ����j������
     if(i)
       printf("Lb���е�%d��Ԫ��Ϊ%d,��ɾ����\n",j,e);
     else
       printf("ɾ��Lb���е�%d��Ԫ��ʧ��(�����ڴ�Ԫ��)��\n",j);
   }
   printf("�������Lb��Ԫ�أ�");
   ListTraverse(L,Lb,print); // ���ζ�Ԫ�ص���print()�����Ԫ�ص�ֵ
 }