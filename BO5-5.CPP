 // bo5-5.cpp �������ͷβ�����洢(�洢�ṹ��c5-5.h����)�Ļ�������(11��),�����㷨5.5,5.6,5.7
 #include"func5-1.cpp" // �㷨5.8
 void InitGList(GList &L)
 { // �����յĹ����L
   L=NULL;
 }

 void CreateGList(GList &L,SString S) // �㷨5.7
 { // ����ͷβ�����洢�ṹ���ɹ��������д��ʽ��S���������L����emp="()"
   SString sub,hsub,emp;
   GList p,q;
   StrAssign(emp,"()"); // �մ�emp="()"
   if(!StrCompare(S,emp)) // S="()"
     L=NULL; // �����ձ�
   else // S���ǿմ�
   {
     if(!(L=(GList)malloc(sizeof(GLNode)))) // �������
       exit(OVERFLOW);
     if(StrLength(S)==1) // SΪ��ԭ�ӣ�ֻ������ڵݹ������
     {
       L->tag=ATOM;
       L->atom=S[1]; // ������ԭ�ӹ����
     }
     else // SΪ��
     {
       L->tag=LIST;
       p=L;
       SubString(sub,S,2,StrLength(S)-2); // ���������(ȥ����1���ַ������1���ַ�)����sub
       do
       { // �ظ���n���ӱ�
         sever(sub,hsub); // ��sub�з������ͷ��hsub
         CreateGList(p->ptr.hp,hsub);
         q=p;
         if(!StrEmpty(sub)) // ��β����
         {
           if(!(p=(GLNode *)malloc(sizeof(GLNode))))
             exit(OVERFLOW);
           p->tag=LIST;
	   q->ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->ptr.tp=NULL;
     }
   }
 }

 void DestroyGList(GList &L)
 { // ���ٹ����L
   GList q1,q2;
   if(L)
   {
     if(L->tag==LIST) // ɾ�������
     {
       q1=L->ptr.hp; // q1ָ���ͷ
       q2=L->ptr.tp; // q2ָ���β
       DestroyGList(q1); // ���ٱ�ͷ
       DestroyGList(q2); // ���ٱ�β
     }
     free(L);
     L=NULL;
   }
 }

 void CopyGList(GList &T,GList L)
 { // ����ͷβ�����洢�ṹ���ɹ����L���Ƶõ������T���㷨5.6
   if(!L) // ���ƿձ�
     T=NULL;
   else
   {
     T=(GList)malloc(sizeof(GLNode)); // �������
     if(!T)
       exit(OVERFLOW);
     T->tag=L->tag;
     if(L->tag==ATOM)
       T->atom=L->atom; // ���Ƶ�ԭ��
     else
     {
       CopyGList(T->ptr.hp,L->ptr.hp); // �ݹ鸴���ӱ�
       CopyGList(T->ptr.tp,L->ptr.tp);
     }
   }
 }

 int GListLength(GList L)
 { // ���ع�����ĳ��ȣ���Ԫ�ظ���
   int len=0;
   while(L)
   {
     L=L->ptr.tp;
     len++;
   }
   return len;
 }

 int GListDepth(GList L)
 { // ����ͷβ�����洢�ṹ��������L����ȡ��㷨5.5
   int max,dep;
   GList pp;
   if(!L)
     return 1; // �ձ����Ϊ1
   if(L->tag==ATOM)
     return 0; // ԭ�����Ϊ0��ֻ������ڵݹ������
   for(max=0,pp=L;pp;pp=pp->ptr.tp)
   {
     dep=GListDepth(pp->ptr.hp); // �ݹ�����pp->ptr.hpΪͷָ����ӱ����
     if(dep>max)
       max=dep;
   }
   return max+1; // �ǿձ�������Ǹ�Ԫ�ص���ȵ����ֵ��1
 }

 Status GListEmpty(GList L)
 { // �ж�������Ƿ�Ϊ��
   if(!L)
     return TRUE;
   else
     return FALSE;
 }

 GList GetHead(GList L)
 { // ���ɹ����L�ı�ͷԪ�أ�����ָ�����Ԫ�ص�ָ��
   GList h,p;
   if(!L) // �ձ��ޱ�ͷ
     return NULL;
   p=L->ptr.hp; // pָ��L�ı�ͷԪ��
   CopyGList(h,p); // ����ͷԪ�ظ��Ƹ�h
   return h;
 }

 GList GetTail(GList L)
 { // �������L�ı�β����Ϊ�����������ָ������¹������ָ��
   GList t;
   if(!L) // �ձ��ޱ�β
     return NULL;
   CopyGList(t,L->ptr.tp); // ��L�ı�β����t
   return t;
 }

 void InsertFirst_GL(GList &L,GList e)
 { // ��ʼ��������������ڡ��������������Ԫ��e(Ҳ�������ӱ�)��Ϊ�����L�ĵ�1Ԫ��(��ͷ)
   GList p=(GList)malloc(sizeof(GLNode)); // �����½��
   if(!p)
     exit(OVERFLOW);
   p->tag=LIST; // ���������Ǳ�
   p->ptr.hp=e; // ��ͷָ��e
   p->ptr.tp=L; // ��βָ��ԭ��L
   L=p; // Lָ���½��
 }

 void DeleteFirst_GL(GList &L,GList &e)
 { // ��ʼ�����������L���ڡ����������ɾ�������L�ĵ�һԪ�أ�����e������ֵ
   GList p=L; // pָ���1�����
   e=L->ptr.hp; // eָ��L�ı�ͷ
   L=L->ptr.tp; // Lָ��ԭL�ı�β
   free(p); // �ͷŵ�1�����
 }

 void Traverse_GL(GList L,void(*v)(AtomType))
 { // ���õݹ��㷨���������L
   if(L) // L����
     if(L->tag==ATOM) // LΪ��ԭ��
       v(L->atom);
     else // LΪ�����
     {
       Traverse_GL(L->ptr.hp,v); // �ݹ����L�ı�ͷ
       Traverse_GL(L->ptr.tp,v); // �ݹ����L�ı�β
     }
 }
