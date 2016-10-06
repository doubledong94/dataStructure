 // bo2-7.cpp ����ʽ(�洢�ṹ��c2-6.h����)�Ļ����������㷨2.22��2.23��(8��)
 #include"c2-5.h"
 #include"bo2-6.cpp"
 typedef LinkList polynomial;
 #define DestroyPolyn DestroyList // ��bo2-6.cpp�еĺ���ͬ�岻ͬ��
 #define PolynLength ListLength // ��bo2-6.cpp�еĺ���ͬ�岻ͬ��

 void OrderInsertMerge(LinkList &L,ElemType e,int(* compare)(term,term))
 { // �������ж�����compare()��Լ������ֵΪe�Ľ������ϲ�����������L���ʵ�λ��
   Position q,s;
   if(LocateElem(L,e,q,compare)) // L�д��ڸ�ָ����
   {
     q->data.coef+=e.coef; // �ı䵱ǰ���ϵ����ֵ
     if(!q->data.coef) // ϵ��Ϊ0
     { // ɾ������ʽL�е�ǰ���
       s=PriorPos(L,q); // sΪ��ǰ����ǰ��
       if(!s) // q��ǰ��
         s=L.head;
       DelFirst(L,s,q);
       FreeNode(q);
     }
   }
   else // ���ɸ�ָ�����������
   {
     MakeNode(s,e); // ���ɽ��
     InsFirst(L,q,s);
   }
 }

 int cmp(term a,term b) // CreatPolyn()��ʵ��
 { // ��a��ָ��ֵ<��=��>b��ָ��ֵ���ֱ𷵻�-1��0��+1
   if(a.expn==b.expn)
     return 0;
   else
     return (a.expn-b.expn)/abs(a.expn-b.expn);
 }

 void CreatPolyn(polynomial &P,int m) // �㷨2.22
 { // ����m���ϵ����ָ����������ʾһԪ����ʽ����������P
   Position q,s;
   term e;
   int i;
   InitList(P);
   printf("����������%d��ϵ����ָ����\n",m);
   for(i=1;i<=m;++i)
   { // ��������m��������(�ɰ�����˳��)
     scanf("%f,%d",&e.coef,&e.expn);
     if(!LocateElem(P,e,q,cmp)) // ��ǰ�����в����ڸ�ָ���cmp��ʵ��
     {
       MakeNode(s,e); // ���ɽ�㲢��������
       InsFirst(P,q,s);
	 }
   }
 }

 void PrintPolyn(polynomial P)
 { // ��ӡ���һԪ����ʽP
   Link q;
   q=P.head->next; // qָ���1�����
   printf("  ϵ��    ָ��\n");
   while(q)
   {
     printf("%f  %d\n",q->data.coef,q->data.expn);
     q=q->next;
   }
 }

 void AddPolyn(polynomial &Pa,polynomial &Pb) // �㷨2.23
 { // ����ʽ�ӷ���Pa=Pa+Pb��������һԪ����ʽPb
   Position ha,hb,qa,qb;
   term a,b;
   ha=GetHead(Pa);
   hb=GetHead(Pb); // ha��hb�ֱ�ָ��Pa��Pb��ͷ���
   qa=NextPos(ha);
   qb=NextPos(hb); // qa��qb�ֱ�ָ��Pa��Pb�е�ǰ���(��Ϊ��1�����)
   while(!ListEmpty(Pa)&&!ListEmpty(Pb)&&qa)
   { // Pa��Pb���ǿ���haûָ��β���(qa!=0)
     a=GetCurElem(qa);
     b=GetCurElem(qb); // a��bΪ�����е�ǰ�Ƚ�Ԫ��
     switch(cmp(a,b))
     {
       case -1:ha=qa; // ����ʽPa�е�ǰ����ָ��ֵС
               qa=NextPos(ha); // ha��qa�������1�����
               break;
       case 0: qa->data.coef+=qb->data.coef; // ���ߵ�ָ��ֵ��ȣ��޸�Pa��ǰ����ϵ��ֵ
               if(qa->data.coef==0) // ɾ������ʽPa�е�ǰ���
               {
                 DelFirst(Pa,ha,qa);
		 FreeNode(qa);
               }
               else
                 ha=qa;
               DelFirst(Pb,hb,qb);
               FreeNode(qb);
               qb=NextPos(hb);
               qa=NextPos(ha);
               break;
       case 1: DelFirst(Pb,hb,qb); // ����ʽPb�е�ǰ����ָ��ֵС
               InsFirst(Pa,ha,qb);
               ha=ha->next;
               qb=NextPos(hb);
     }
   }
   if(!ListEmpty(Pb))
   {
     Pb.tail=hb;
     Append(Pa,qb); // ����Pb��ʣ����
   }
   DestroyPolyn(Pb); // ����Pb
 }

 void AddPolyn1(polynomial &Pa,polynomial &Pb)
 { // ��һ�ֶ���ʽ�ӷ����㷨��Pa=Pa+Pb��������һԪ����ʽPb
   Position qb;
   term b;
   qb=GetHead(Pb); // qbָ��Pb��ͷ���
   qb=qb->next; // qbָ��Pb�ĵ�1�����
   while(qb)
   {
     b=GetCurElem(qb);
     OrderInsertMerge(Pa,b,cmp);
     qb=qb->next;
   }
   DestroyPolyn(Pb); // ����Pb
 }

 void Opposite(polynomial Pa)
 { // һԪ����ʽPaϵ��ȡ��
   Position p;
   p=Pa.head;
   while(p->next)
   {
     p=p->next;
     p->data.coef*=-1;
   }
 }

 void SubtractPolyn(polynomial &Pa,polynomial &Pb)
 { // ����ʽ������Pa=Pa-Pb��������һԪ����ʽPb
   Opposite(Pb);
   AddPolyn(Pa,Pb);
 }

 void MultiplyPolyn(polynomial &Pa,polynomial &Pb)
 { // ����ʽ�˷���Pa=Pa��Pb��������һԪ����ʽPb
   polynomial Pc;
   Position qa,qb;
   term a,b,c;
   InitList(Pc);
   qa=GetHead(Pa);
   qa=qa->next;
   while(qa)
   {
     a=GetCurElem(qa);
     qb=GetHead(Pb);
     qb=qb->next;
     while(qb)
     {
       b=GetCurElem(qb);
       c.coef=a.coef*b.coef;
       c.expn=a.expn+b.expn;
       OrderInsertMerge(Pc,c,cmp);
       qb=qb->next;
     }
     qa=qa->next;
   }
   DestroyPolyn(Pb); // ����Pb
   ClearList(Pa); // ��Pa����Ϊ�ձ�
   Pa.head=Pc.head;
   Pa.tail=Pc.tail;
   Pa.len=Pc.len;
 }