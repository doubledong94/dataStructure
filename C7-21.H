 // c7-21.h ͼ���ڽӱ��洢��ʾ(�뵥�����ı������ͽ�����ϵ)
 #define MAX_VERTEX_NUM 20
 enum GraphKind{DG,DN,UDG,UDN}; // {����ͼ,������,����ͼ,������}
 struct ElemType // ��
 {
   int adjvex; // �û���ָ��Ķ����λ��
   InfoType *info; // ����Ȩֵָ��
 };

 struct ArcNode // ��
 {
   ElemType data; // ��ָ������Ĳ��ֶ�����ElemType
   ArcNode *nextarc; // ָ����һ������ָ��
 }; // �����

 typedef struct
 {
   VertexType data; // ������Ϣ
   ArcNode *firstarc; // ��һ�������ĵ�ַ,ָ���һ�������ö���Ļ���ָ��
 }VNode,AdjList[MAX_VERTEX_NUM]; // ͷ���

 struct ALGraph
 {
   AdjList vertices;
   int vexnum,arcnum; // ͼ�ĵ�ǰ�������ͻ���
   GraphKind kind; // ͼ�������־
 };
 #define LNode ArcNode // �ӣ����嵥�����Ľ��������ͼ�ı���������
 #define next nextarc // �ӣ����嵥��������ָ�����Ǳ����ָ����һ������ָ����
 typedef ArcNode *LinkList; // �ӣ�����ָ����������ָ����ָ��ͼ�ı�����ָ��