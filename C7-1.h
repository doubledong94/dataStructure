 // c7-1.h ͼ������(�ڽӾ���)�洢��ʾ
 #define INFINITY INT_MAX // ���������ֵ�����
 #define MAX_VERTEX_NUM 8 // ��󶥵����
 enum GraphKind{DG,DN,UDG,UDN}; // {����ͼ,������,����ͼ,������}
 typedef struct
 {
   VRType adj; // �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ
   InfoType *info; // �û������Ϣ��ָ��(����)
 }ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // ��ά����
 struct MGraph
 {
   VertexType vexs[MAX_VERTEX_NUM]; // ��������
   AdjMatrix arcs; // �ڽӾ���
   int vexnum,arcnum; // ͼ�ĵ�ǰ�������ͻ���
   GraphKind kind; // ͼ�������־
 };