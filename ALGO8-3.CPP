 // algo8-3.cpp ʵ���㷨8.3�ĳ���
 #include"c1.h"
 typedef char AtomType; // ����ԭ������Ϊ�ַ���
 #include"c8-3.h"
 #include"bo5-5.cpp"

 void MarkList(GList GL) // �㷨8.3��
 { // �����ǿչ����GL(GL!=NULL��GL->mark����)���Ա�������δ�ӱ�־�Ľ��ӱ�־
   GList q,p=GL,t=NULL; // tָʾp��ĸ��
   Status finished=FALSE;
   if(GL==NULL)
     return;
   while(!finished)
   {
     while(p->mark!=1)
     {
       p->mark=1; // MarkHead(p)��ϸ��
       q=p->ptr.hp; // qָ��*p�ı�ͷ
       if(q&&q->mark!=1)
	 if(q->tag==0)
	   q->mark=1; // ATOM����ͷΪԭ�ӽ��
         else
         { // ���������ӱ�
           p->ptr.hp=t;
           p->tag=ATOM;
           t=p;
           p=q;
         }
     } // ��ɶԱ�ͷ�ı�־
     q=p->ptr.tp; // qָ��*p�ı�β
     if(q&&q->mark!=1)
     { // ����������β
       p->ptr.tp=t;
       t=p;
       p=q;
     }
     else // BackTrack(finished)��ϸ��
     {
       while(t&&t->tag==1) // LIST������㣬�ӱ�β����
       {
	 q=t;
	 t=q->ptr.tp;
	 q->ptr.tp=p;
	 p=q;
       }
       if(!t)
         finished=TRUE; // ����
       else
       { // �ӱ�ͷ����
         q=t;
	 t=q->ptr.hp;
	 q->ptr.hp=p;
	 p=q;
	 p->tag=LIST;
       } // ����������β
     }
   }
 }

 void Traverse_GL(GList L,void(*v)(GList))
 { // ���õݹ��㷨���������L����bo5-5.cpp��
   if(L) // L����
     if(L->tag==ATOM) // LΪ��ԭ��
       v(L);
     else // LΪ�����
     {
       v(L);
       Traverse_GL(L->ptr.hp,v);
       Traverse_GL(L->ptr.tp,v);
     }
 }

 void visit(GList p)
 {
   if(p->tag==ATOM)
     printf("mark=%d %c\n",p->mark,p->atom);
   else
     printf("mark=%d list\n",p->mark);
 }

 int main()
 {
   char p[80];
   SString t;
   GList l;
   printf("����������l(��д��ʽ���ձ�:(),��ԭ��:a,����:(a,(b),c)):\n");
   gets(p);
   StrAssign(t,p);
   CreateGList(l,t); // ��bo5-5.cpp��
   MarkList(l); // �ӱ�־
   Traverse_GL(l,visit);
 }