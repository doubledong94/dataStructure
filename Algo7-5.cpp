 // algo7-5.cpp ��ؼ�·����ʵ���㷨7.13��7.14�ĳ���
 #include"c1.h"
 #define MAX_NAME 5 // �����ַ�������󳤶�+1
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; // �ַ�������
 #include"c7-21.h"
 #include"bo7-2.cpp"
 #include"func7-1.cpp"

 int ve[MAX_VERTEX_NUM]; // �¼����緢��ʱ�䣬ȫ�ֱ���(�����㷨7.13���㷨7.14)

 typedef int SElemType; // ջԪ������
 #include"c3-1.h" // ˳��ջ�Ĵ洢�ṹ
 #include"bo3-1.cpp" // ˳��ջ�Ļ�������
 Status TopologicalOrder(ALGraph G,SqStack &T)
 { // �㷨7.13 ������G�����ڽӱ��洢�ṹ����������¼������緢��ʱ��ve(ȫ�ֱ���)��TΪ��������
   // ����ջ,SΪ����ȶ���ջ����G�޻�·������ջT����G��һ����������,�Һ���ֵΪOK,����ΪERROR
   int i,k,count=0; // ����ջ����������ֵΪ0
   int indegree[MAX_VERTEX_NUM]; // ������飬��Ÿ����㵱ǰ�����
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree); // �Ը����������indegree[]����func7-1.cpp��
   InitStack(S); // ��ʼ������ȶ���ջS
   printf("�������У�");
   for(i=0;i<G.vexnum;++i) // �����ж���i
     if(!indegree[i]) // �������Ϊ0
       Push(S,i); // ��i������ȶ���ջS
   InitStack(T); // ��ʼ���������ж���ջ
   for(i=0;i<G.vexnum;++i) // ��ʼ��ve[]=0(��Сֵ���ȼٶ�ÿ���¼������������¼�Լ��)
     ve[i]=0;
   while(!StackEmpty(S)) // ������ȶ���ջS����
   {
     Pop(S,i); // ��ջS������������Ķ���j����
     printf("%s ",G.vertices[i].data);
     Push(T,i); // j�Ŷ���������������ջT(ջ��Ԫ��Ϊ��������ĵ�1��Ԫ��)
     ++count; // ����ջT�Ķ������
     for(p=G.vertices[i].firstarc;p;p=p->nextarc)
     { // ��i�Ŷ����ÿ���ڽӵ�
       k=p->data.adjvex; // �����Ϊk
       if(--indegree[k]==0) // k����ȼ�1������Ϊ0����k��ջS
	 Push(S,k);
       if(ve[i]+*(p->data.info)>ve[k]) // *(p->data.info)��<i,k>��Ȩֵ
	 ve[k]=ve[i]+*(p->data.info); // ����k�¼������緢��ʱ��Ҫ����ֱ��ǰ������i�¼���
     }                  // ���緢��ʱ���<i,k>��ȨֵԼ��������i���������򣬹�ve[i]���ٸı�
   }
   if(count<G.vexnum)
   {
     printf("���������л�·\n");
     return ERROR;
   }
   else
     return OK;
 }

 Status CriticalPath(ALGraph G)
 { // �㷨7.14 GΪ�����������G�ĸ���ؼ��
   int vl[MAX_VERTEX_NUM]; // �¼���ٷ���ʱ��
   SqStack T;
   int i,j,k,ee,el,dut;
   ArcNode *p;
   if(!TopologicalOrder(G,T)) // ��������
     return ERROR;
   j=ve[0]; // j�ĳ�ֵ
   for(i=1;i<G.vexnum;i++)
     if(ve[i]>j)
       j=ve[i]; // j=Max(ve[]) ��ɵ�����緢��ʱ��
   for(i=0;i<G.vexnum;i++) // ��ʼ�������¼�����ٷ���ʱ��
     vl[i]=j; // Ϊ��ɵ�����緢��ʱ��(���ֵ)
   while(!StackEmpty(T)) // ������������������vlֵ
     for(Pop(T,j),p=G.vertices[j].firstarc;p;p=p->nextarc)
     { // ����ջT��Ԫ��,����j,pָ��j�ĺ���¼�k,�¼�k����ٷ���ʱ����ȷ��(��Ϊ������������)
       k=p->data.adjvex;
       dut=*(p->data.info); // dut=<j,k>��Ȩֵ
       if(vl[k]-dut<vl[j])
	 vl[j]=vl[k]-dut; // �¼�j����ٷ���ʱ��Ҫ����ֱ�Ӻ���¼�k����ٷ���ʱ��
     }                    // ��<j,k>��ȨֵԼ��������k�����������򣬹�vl[k]���ٸı�
   printf("\ni ve[i] vl[i]\n");
   for(i=0;i<G.vexnum;i++) // ��ʼ�������¼�����ٷ���ʱ��
   {
     printf("%d   %d     %d",i,ve[i],vl[i]);
     if(ve[i]==vl[i])
       printf(" �ؼ�·�������Ķ���");
     printf("\n");
   }
   printf("j   k  Ȩֵ  ee  el\n");
   for(j=0;j<G.vexnum;++j) // ��ee��el�͹ؼ��
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->data.adjvex;
       dut=*(p->data.info); // dut=<j,k>��Ȩֵ
       ee=ve[j]; // ee=�<j,k>�����翪ʼʱ��(��j��)
       el=vl[k]-dut; // el=�<j,k>����ٿ�ʼʱ��(��j��)
       printf("%s��%s %3d %3d %3d ",G.vertices[j].data,G.vertices[k].data,dut,ee,el);
       // ������ߵĲ���
       if(ee==el) // �ǹؼ��
         printf("�ؼ��");
       printf("\n");
     }
   return OK;
 }

 int main()
 {
   ALGraph h;
   printf("��ѡ��������\n");
   CreateGraph(h); // ����������h����bo7-2.cpp��
   Display(h); // ���������h����bo7-2.cpp��
   CriticalPath(h); // ��h�Ĺؼ�·��
 }