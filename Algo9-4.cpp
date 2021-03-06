 // algo9-4.cpp 检验bo9-2.cpp的程序
 #include"c1.h"
 #define N 10 // 数据元素个数
 typedef int KeyType; // 设关键字域为整型
 struct ElemType // 数据元素类型
 {
   KeyType key;
   int others;
 };
 #include"c9-7.h"
 #include"bo9-2.cpp"

 void print(ElemType c)
 {
   printf("(%d,%d) ",c.key,c.others);
 }

 int main()
 {
   BiTree dt,p;
   int i;
   KeyType j;
   ElemType r[N]={{45,1},{12,2},{53,3},{3,4},{37,5},{24,6},{100,7},{61,8},{90,9},{78,10}};
   // 以教科书图9.7(a)为例，另加除关键字之外的其他信息
   InitDSTable(dt); // 构造空表
   for(i=0;i<N;i++)
     InsertBST(dt,r[i]); // 依次插入数据元素
   TraverseDSTable(dt,print);
   printf("\n请输入待查找的值: ");
   scanf("%d",&j);
   p=SearchBST(dt,j);
   if(p)
   {
     printf("表中存在此值。");
     DeleteBST(dt,j);
     printf("删除此值后:\n");
     TraverseDSTable(dt,print);
     printf("\n");
   }
   else
     printf("表中不存在此值\n");
   DestroyDSTable(dt);
 }
