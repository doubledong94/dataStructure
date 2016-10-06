 // bo3-7.cpp ˳���ѭ������(�洢�ṹ��c3-5.h����)�Ļ�������(9��)
 void InitQueue(SqQueue1 &Q)
 { // ����һ���ն���Q
   if(!(Q.base=(QElemType*)malloc(QUEUE_INIT_SIZE*sizeof(QElemType))))
     exit(ERROR); // �洢����ʧ��
   Q.rear=0; // �ն��У�βָ��Ϊ0
   Q.queuesize=QUEUE_INIT_SIZE; // ��ʼ�洢����
 }

 void DestroyQueue(SqQueue1 &Q)
 { // ���ٶ���Q��Q���ٴ���
   free(Q.base); // �ͷŴ洢�ռ�
   Q.base=NULL;
   Q.rear=Q.queuesize=0;
 }

 void ClearQueue(SqQueue1 &Q)
 { // ��Q��Ϊ�ն���
   Q.rear=0;
 }

 Status QueueEmpty(SqQueue1 Q)
 { // ������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
   if(Q.rear==0)
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(SqQueue1 Q)
 { // ����Q��Ԫ�ظ����������еĳ���
   return Q.rear;
 }

 Status GetHead(SqQueue1 Q,QElemType &e)
 { // �����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
   if(Q.rear)
   {
     e=*Q.base;
     return OK;
   }
   else
     return ERROR;
 }

 void EnQueue(SqQueue1 &Q,QElemType e)
 { // ����Ԫ��eΪQ���µĶ�βԪ��
   if(Q.rear==Q.queuesize) // ��ǰ�洢�ռ�����
   { // ���ӷ���
     Q.base=(QElemType*)realloc(Q.base,(Q.queuesize+QUEUE_INCREMENT)*sizeof(QElemType));
     if(!Q.base) // ����ʧ��
       exit(ERROR);
     Q.queuesize+=QUEUE_INCREMENT; // ���Ӵ洢����
   }
   Q.base[Q.rear++]=e; // �����Ԫ�أ���βָ��+1
 }

 Status DeQueue(SqQueue1 &Q,QElemType &e)
 { // �����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
   int i;
   if(Q.rear) // ���в���
   {
     e=*Q.base;
     for(i=1;i<Q.rear;i++)
       Q.base[i-1]=Q.base[i]; // ����ǰ�ƶ���Ԫ��
     Q.rear--; // βָ��ǰ��
     return OK;
   }
   else
     return ERROR;
 }

 void QueueTraverse(SqQueue1 Q,void(*vi)(QElemType))
 { // �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()
   int i;
   for(i=0;i<Q.rear;i++)
     vi(Q.base[i]);
   printf("\n");
 }