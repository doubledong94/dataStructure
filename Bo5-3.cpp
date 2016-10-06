 // bo5-3.cpp ���߼�����ϡ�����(�洢�ṹ��c5-3.h����)�Ļ�������(8��),�����㷨5.3
 Status CreateSMatrix(RLSMatrix &M)
 { // ����ϡ�����M
   int i,j;
   Triple T;
   Status k;
   printf("��������������,����,����Ԫ������");
   scanf("%d,%d,%d",&M.mu,&M.nu,&M.tu);
   if(M.tu>MAX_SIZE||M.mu>MAX_RC)
     return ERROR;
   M.data[0].i=0; // Ϊ���±Ƚ���׼��
   for(i=1;i<=M.tu;i++)
   {
     do
     {
       printf("�밴����˳�������%d������Ԫ�����ڵ���(1��%d),��(1��%d),Ԫ��ֵ:",i,M.mu,M.nu);
       scanf("%d,%d,%d",&T.i,&T.j,&T.e);
       k=0;
       if(T.i<1||T.i>M.mu||T.j<1||T.j>M.nu) // �С��г�����Χ
         k=1;
       if(T.i<M.data[i-1].i||T.i==M.data[i-1].i&&T.j<=M.data[i-1].j) // û�а�˳���������Ԫ��
         k=1;
     }while(k); // ������������������
     M.data[i]=T;
   }
   for(i=1;i<=M.mu;i++) // ��rpos[]����ֵ0
     M.rpos[i]=0;
   for(i=1;i<=M.tu;i++) // ����ÿ�з���Ԫ����������rpos[]
     M.rpos[M.data[i].i]++;
   for(i=M.mu;i>=1;i--) // ����rpos[]
   {
     M.rpos[i]=1; // ����ֵ1
     for(j=i-1;j>=1;j--)
       M.rpos[i]+=M.rpos[j];
   }
   return OK;
 }

 void DestroySMatrix(RLSMatrix &M)
 { // ����ϡ�����M(ʹMΪ0��0��0������Ԫ�صľ���)
   M.mu=M.nu=M.tu=0;
 }

 void PrintSMatrix(RLSMatrix M)
 { // ���ϡ�����M
   int i;
   printf("%d��%d��%d������Ԫ�ء�\n",M.mu,M.nu,M.tu);
   printf("��  ��  Ԫ��ֵ\n");
   for(i=1;i<=M.tu;i++)
     printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
   for(i=1;i<=M.mu;i++)
     printf("��%d�еĵ�һ������Ԫ���Ǳ������%d��Ԫ��\n",i,M.rpos[i]);
 }

 void PrintSMatrix1(RLSMatrix M)
 { // ��������ʽ���M
   int i,j,k=1;
   Triple *p=M.data;
   p++; // pָ���1������Ԫ��
   for(i=1;i<=M.mu;i++)
   {
     for(j=1;j<=M.nu;j++)
       if(k<=M.tu&&p->i==i&&p->j==j) // pָ�����Ԫ����p��ָԪ��Ϊ��ǰ����Ԫ��
       {
         printf("%3d",p->e); // ���p��ָԪ�ص�ֵ
         p++; // pָ����һ��Ԫ��
         k++; // ������+1
       }
       else // p��ָԪ�ز��ǵ�ǰ����Ԫ��
         printf("%3d",0); // ���0
     printf("\n");
   }
 }

 void CopySMatrix(RLSMatrix M,RLSMatrix &T)
 { // ��ϡ�����M���Ƶõ�T
   T=M;
 }

 Status AddSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
 { // ��ϡ�����ĺ�Q=M+N
   int k,p,q,tm,tn;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   Q.mu=M.mu; // Q��������
   Q.nu=M.nu; // Q��������
   Q.tu=0; // Q�������Ԫ������ֵ
   for(k=1;k<=M.mu;++k) // ����ÿһ�У�kָʾ�к�
   {
     Q.rpos[k]=Q.tu+1; // Q�����k�еĵ�1��Ԫ�ص�λ��
     p=M.rpos[k]; // pָʾM�����k�е�ǰԪ�ص����
     q=N.rpos[k]; // qָʾN�����k�е�ǰԪ�ص����
     if(k==M.mu) // �����һ��
     {
       tm=M.tu+1; // tm��tn�ֱ���p��q���Ͻ�
       tn=N.tu+1;
     }
     else
     {
       tm=M.rpos[k+1];
       tn=N.rpos[k+1];
     }
     while(p<tm&&q<tn) // M��N������е�k��Ԫ��δ����
       if(M.data[p].j==N.data[q].j) // M����ǰԪ�ص���=N����ǰԪ�ص���
       {
	 if(M.data[p].e+N.data[q].e!=0) // �Ͳ�Ϊ0������Q
	 {
	   Q.data[++Q.tu]=M.data[p];
	   Q.data[Q.tu].e+=N.data[q].e;
	 }
	 p++;
	 q++;
       }
       else if(M.data[p].j<N.data[q].j) // M����ǰԪ�ص���<N����ǰԪ�ص���
	 Q.data[++Q.tu]=M.data[p++]; // ��M�ĵ�ǰֵ����Q
       else // M����ǰԪ�ص���>N����ǰԪ�ص���
         Q.data[++Q.tu]=N.data[q++]; // ��N�ĵ�ǰֵ����Q
     while(p<tm) // M�����е�k�е�Ԫ��δ����
       Q.data[++Q.tu]=M.data[p++]; // ��M�ĵ�ǰֵ����Q
     while(q<tn) // N������k�е�Ԫ��δ����
       Q.data[++Q.tu]=N.data[q++]; // ��N�ĵ�ǰֵ����Q
   }
   if(Q.tu>MAX_SIZE)
     return ERROR;
   else
     return OK;
 }

 Status SubtSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
 { // ��ϡ�����Ĳ�Q=M-N
   int i;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   for(i=1;i<=N.tu;++i) // ����N��ÿһԪ�أ���ֵ����-1
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q); // Q=M+(-N)
   return OK;
 }

 Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
 { // ��ϡ�����˻�Q=M��N���㷨5.3��
   int arow,brow,p,q,ccol,ctemp[MAX_RC+1],t,tp;
   if(M.nu!=N.mu) // ����M������Ӧ�;���N���������
     return ERROR;
   Q.mu=M.mu; // Q��ʼ��
   Q.nu=N.nu;
   Q.tu=0;
   if(M.tu*N.tu==0) // M��N������һ���������
     return ERROR;
   for(arow=1;arow<=M.mu;++arow)
   { // ��M�ĵ�һ�п�ʼ�������һ�У�arow��M�ĵ�ǰ��
     for(ccol=1;ccol<=Q.nu;++ccol)
       ctemp[ccol]=0; // Q�ĵ�ǰ�еĸ���Ԫ���ۼ�������
     Q.rpos[arow]=Q.tu+1; // Q��ǰ�еĵ�1��Ԫ��λ����1�����1��Ԫ��֮��
     if(arow<M.mu)
       tp=M.rpos[arow+1];
     else
       tp=M.tu+1; // �����1�����
     for(p=M.rpos[arow];p<tp;++p)
     { // ��M��ǰ����ÿһ������Ԫ
       brow=M.data[p].j; // �ҵ���ӦԪ��N�е��к�(M��ǰԪ���к�)
       if(brow<N.mu)
         t=N.rpos[brow+1];
       else
         t=N.tu+1; // �����1�����
       for(q=N.rpos[brow];q<t;++q)
       {
         ccol=N.data[q].j; // �˻�Ԫ����Q���к�
         ctemp[ccol]+=M.data[p].e*N.data[q].e;
       }
     } // ���Q�е�arow�еķ���Ԫ
     for(ccol=1;ccol<=Q.nu;++ccol) // ѹ���洢���з���Ԫ
       if(ctemp[ccol]!=0)
       {
         if(++Q.tu>MAX_SIZE)
           return ERROR;
         Q.data[Q.tu].i=arow;
         Q.data[Q.tu].j=ccol;
         Q.data[Q.tu].e=ctemp[ccol];
       }
   }
   return OK;
 }

 void TransposeSMatrix(RLSMatrix M,RLSMatrix &T)
 { // ��ϡ�����M��ת�þ���T
   int p,q,t,col,*num;
   num=(int *)malloc((M.nu+1)*sizeof(int));
   T.mu=M.nu;
   T.nu=M.mu;
   T.tu=M.tu;
   if(T.tu)
   {
     for(col=1;col<=M.nu;++col)
       num[col]=0;  // ���ֵ
     for(t=1;t<=M.tu;++t) // ��M��ÿһ�з���Ԫ����
       ++num[M.data[t].j];
     T.rpos[1]=1;
     for(col=2;col<=M.nu;++col) // ��M�е�col�е�һ������Ԫ��T.data�е����
       T.rpos[col]=T.rpos[col-1]+num[col-1];
     for(col=1;col<=M.nu;++col)
       num[col]=T.rpos[col];
     for(p=1;p<=M.tu;++p)
     {
       col=M.data[p].j;
       q=num[col];
       T.data[q].i=M.data[p].j;
       T.data[q].j=M.data[p].i;
       T.data[q].e=M.data[p].e;
       ++num[col];
     }
   }
   free(num);
 }