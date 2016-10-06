 // algo4-1.cpp ʵ���㷨4.6��4.7��4.8�ĳ���
 #include"c1.h"
 #include"c4-1.h"
 #include"bo4-1.cpp"

 void get_next(SString T,int next[])
 { // ��ģʽ��T��next����ֵ����������next���㷨4.7
   int i=1,j=0;
   next[1]=0;
   while(i<T[0])
     if(j==0||T[i]==T[j])
     {
       ++i;
       ++j;
       next[i]=j;
     }
     else
       j=next[j];
 }

 void get_nextval(SString T,int nextval[])
 { // ��ģʽ��T��next��������ֵ����������nextval���㷨4.8
   int i=1,j=0;
   nextval[1]=0;
   while(i<T[0])
     if(j==0||T[i]==T[j])
     {
       ++i;
       ++j;
       if(T[i]!=T[j])
         nextval[i]=j;
       else
         nextval[i]=nextval[j];
     }
     else
       j=nextval[j];
 }

 int Index_KMP(SString S,SString T,int pos,int next[])
 { // ����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�KMP�㷨��
   // ���У�T�ǿգ�1��pos��StrLength(S)���㷨4.6
   int i=pos,j=1;
   while(i<=S[0]&&j<=T[0])
     if(j==0||S[i]==T[j]) // �����ȽϺ���ַ�
     {
       ++i;
       ++j;
     }
     else // ģʽ�������ƶ�
       j=next[j];
   if(j>T[0]) // ƥ��ɹ�
     return i-T[0];
   else
     return 0;
 }

 int main()
 {
   int i,*p;
   SString s1,s2; // �Խ̿����㷨4.8֮�ϵ�����Ϊ��
   StrAssign(s1,"aaabaaaab");
   printf("����Ϊ: ");
   StrPrint(s1);
   StrAssign(s2,"aaaab");
   printf("�Ӵ�Ϊ: ");
   StrPrint(s2);
   p=(int*)malloc((StrLength(s2)+1)*sizeof(int)); // ����s2��next����ռ�
   get_next(s2,p); // �����㷨4.7�����next���飬����p��
   printf("�Ӵ���next����Ϊ: ");
   for(i=1;i<=StrLength(s2);i++)
     printf("%d ",*(p+i));
   printf("\n");
   i=Index_KMP(s1,s2,1,p); // �����㷨4.6��ô�s2��s1���״�ƥ���λ��i
   if(i)
     printf("�������Ӵ��ڵ�%d���ַ����״�ƥ��\n",i);
   else
     printf("�������Ӵ�ƥ�䲻�ɹ�\n");
   get_nextval(s2,p); // �����㷨4.8�����next���飬����p��
   printf("�Ӵ���nextval����Ϊ: ");
   for(i=1;i<=StrLength(s2);i++)
     printf("%d ",*(p+i));
   printf("\n");
   printf("�������Ӵ��ڵ�%d���ַ����״�ƥ��\n",Index_KMP(s1,s2,1,p));
 }