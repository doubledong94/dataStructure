 // main7-4.cpp ����bo7-4.cpp��������
 #include"c1.h"
 #define MAX_NAME 3 // �����ַ�������󳤶�+1
 typedef int InfoType; // Ȩֵ����
 typedef char VertexType[MAX_NAME]; // �ַ�������
 #include"c7-4.h"
 #include"bo7-4.cpp"
 void visit(VertexType v)
 {
   printf("%s ",v);
 }

 int main()
 {
   int k,n;
   AMLGraph g;
   VertexType v1,v2;
   CreateGraph(g);
   Display(g);
   printf("�޸Ķ����ֵ��������ԭֵ ��ֵ: ");
   scanf("%s%s",v1,v2);
   PutVex(g,v1,v2);
   printf("�����¶��㣬�����붥���ֵ: ");
   scanf("%s",v1);
   InsertVex(g,v1);
   printf("�������¶����йصıߣ����������: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("��������һ�����ֵ: ");
     scanf("%s",v2);
     InsertArc(g,v1,v2);
   }
   Display(g);
   printf("ɾ��һ���ߣ��������ɾ���ߵ�������(�Կո���Ϊ���)��");
   scanf("%s%s",v1,v2);
   DeleteArc(g,v1,v2);
   Display(g);
   printf("ɾ�����㼰��صıߣ������붥���ֵ: ");
   scanf("%s",v1);
   DeleteVex(g,v1);
   Display(g);
   printf("������������Ľ��:\n");
   DFSTraverse(g,visit);
   printf("������������Ľ��:\n");
   BFSTraverse(g,visit);
   DestroyGraph(g);
 }