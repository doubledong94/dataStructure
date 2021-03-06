 // algo8-3.cpp 实现算法8.3的程序
 #include"c1.h"
 typedef char AtomType; // 定义原子类型为字符型
 #include"c8-3.h"
 #include"bo5-5.cpp"

 void MarkList(GList GL) // 算法8.3改
 { // 遍历非空广义表GL(GL!=NULL且GL->mark不定)，对表中所有未加标志的结点加标志
   GList q,p=GL,t=NULL; // t指示p的母表
   Status finished=FALSE;
   if(GL==NULL)
     return;
   while(!finished)
   {
     while(p->mark!=1)
     {
       p->mark=1; // MarkHead(p)的细化
       q=p->ptr.hp; // q指向*p的表头
       if(q&&q->mark!=1)
	 if(q->tag==0)
	   q->mark=1; // ATOM，表头为原子结点
         else
         { // 继续遍历子表
           p->ptr.hp=t;
           p->tag=ATOM;
           t=p;
           p=q;
         }
     } // 完成对表头的标志
     q=p->ptr.tp; // q指向*p的表尾
     if(q&&q->mark!=1)
     { // 继续遍历表尾
       p->ptr.tp=t;
       t=p;
       p=q;
     }
     else // BackTrack(finished)的细化
     {
       while(t&&t->tag==1) // LIST，表结点，从表尾回溯
       {
	 q=t;
	 t=q->ptr.tp;
	 q->ptr.tp=p;
	 p=q;
       }
       if(!t)
         finished=TRUE; // 结束
       else
       { // 从表头回溯
         q=t;
	 t=q->ptr.hp;
	 q->ptr.hp=p;
	 p=q;
	 p->tag=LIST;
       } // 继续遍历表尾
     }
   }
 }

 void Traverse_GL(GList L,void(*v)(GList))
 { // 利用递归算法遍历广义表L，由bo5-5.cpp改
   if(L) // L不空
     if(L->tag==ATOM) // L为单原子
       v(L);
     else // L为广义表
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
   printf("请输入广义表l(书写形式：空表:(),单原子:a,其它:(a,(b),c)):\n");
   gets(p);
   StrAssign(t,p);
   CreateGList(l,t); // 在bo5-5.cpp中
   MarkList(l); // 加标志
   Traverse_GL(l,visit);
 }
