 // func7-1.cpp algo7-4.cpp��algo7-5.cppҪ����
 void FindInDegree(ALGraph G,int indegree[])
 { // �󶥵����ȣ��㷨7.12��7.13����
   int i;
   ArcNode *p;
   for(i=0;i<G.vexnum;i++)
     indegree[i]=0; // ����ֵ
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       indegree[p->data.adjvex]++;
       p=p->nextarc;
     }
   }
 }