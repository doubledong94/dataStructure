 // algo7-6.cpp ʵ���㷨7.15�ĳ��򡣵Ͻ�˹�����㷨��ʵ��
 #include"c1.h"
 #define MAX_NAME 5 // �����ַ�������󳤶�+1
 #define MAX_INFO 20 // �����Ϣ�ַ�������󳤶�+1
 typedef int VRType;
 typedef char InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h" // �ڽӾ���洢��ʾ
 #include"bo7-1.cpp" // �ڽӾ���洢��ʾ�Ļ�������
 typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // ·�����󣬶�ά����
 typedef int ShortPathTable[MAX_VERTEX_NUM]; // ��̾������һά����

 void ShortestPath_DIJ(MGraph G,int v0,PathMatrix P,ShortPathTable D)
 { // ��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����
   // D[v]����P[v][w]ΪTRUE����w�Ǵ�v0��v��ǰ������·���ϵĶ��㡣
   // final[v]ΪTRUE���ҽ���v��S�����Ѿ���ô�v0��v�����·�� �㷨7.15
   int v,w,i,j,min;
   Status final[MAX_VERTEX_NUM]; // ��������Ϊ���ʾ�ö��㵽v0����̾������������ֵΪ��
   for(v=0;v<G.vexnum;++v)
   {
     final[v]=FALSE; // ���ֵ
     D[v]=G.arcs[v0][v].adj; // D[]���v0��v����̾��룬��ֵΪv0��v��ֱ�Ӿ���
     for(w=0;w<G.vexnum;++w)
       P[v][w]=FALSE; // ��P[][]��ֵΪFALSE��û��·��
     if(D[v]<INFINITY) // v0��v��ֱ��·��
       P[v][v0]=P[v][v]=TRUE; // һά����p[v][]��ʾԴ��v0��v���·��ͨ���Ķ���
   }
   D[v0]=0; // v0��v0����Ϊ0
   final[v0]=TRUE; // v0���㲢��S��
   for(i=1;i<G.vexnum;++i) // ����G.vexnum-1������
   { // ��ʼ��ѭ����ÿ�����v0��ĳ������v�����·��������v����S��
     min=INFINITY; // ��ǰ��֪��v0�����������룬���ֵΪ��
     for(w=0;w<G.vexnum;++w) // �����ж�����
       if(!final[w]&&D[w]<min) //��S��֮��Ķ���������v0����Ķ��㣬�����丳��v�����븳��min
       {
	 v=w;
	 min=D[w];
       }
     final[v]=TRUE; // ��v����S��
     for(w=0;w<G.vexnum;++w) // �����²���Ķ��㣬���²���S���Ķ��㵽v0�ľ����·������
       if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+G.arcs[v][w].adj<D[w]))
       { // w������S����v0��v��w�ľ��룼Ŀǰv0��w�ľ���
         D[w]=min+G.arcs[v][w].adj; // ����D[w]
	 for(j=0;j<G.vexnum;++j) // �޸�P[w]��v0��w�����Ķ������v0��v�����Ķ����ټ��϶���w
	   P[w][j]=P[v][j];
	 P[w][w]=TRUE;
       }
   }
 }

 int main()
 {
   int i,j;
   MGraph g;
   PathMatrix p; // ��ά���飬·������
   ShortPathTable d; // һά���飬��̾����
   CreateDN(g); // ����������g
   Display(g); // ���������g
   ShortestPath_DIJ(g,0,p,d);//��g��λ��Ϊ0�Ķ���ΪԴ�㣬���䵽������������̾��롣����d��
   printf("���·������p[i][j]����:\n");
   for(i=0;i<g.vexnum;++i)
   {
     for(j=0;j<g.vexnum;++j)
       printf("%2d",p[i][j]);
     printf("\n");
   }
   printf("%s������������·������Ϊ��\n",g.vexs[0]);
   for(i=0;i<g.vexnum;++i)
     if(i!=0)
       printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
 }