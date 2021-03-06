 // bo9-6.cpp 动态查找表(Trie键树)的基本操作，包括算法9.16
 void InitDSTable(TrieTree &T)
 { // 操作结果：构造一个空的Trie键树T
   T=NULL;
 }

 void DestroyDSTable(TrieTree &T)
 { // 初始条件：Trie树T存在。操作结果：销毁Trie树T
   int i;
   if(T) // 非空树
   {
     for(i=0;i<LENGTH;i++)
       if(T->kind==BRANCH&&T->bh.ptr[i]) // 第i个结点不空
         if(T->bh.ptr[i]->kind==BRANCH) // 是子树
           DestroyDSTable(T->bh.ptr[i]);
         else // 是叶子
         {
           free(T->bh.ptr[i]);
           T->bh.ptr[i]=NULL;
         }
     free(T); // 释放根结点
     T=NULL; // 空指针赋0
   }
 }

 int ord(char c)
 {
   c=toupper(c);
   if(c>='A'&&c<='Z')
     return c-'A'+1; // 英文字母返回其在字母表中的序号
   else
     return 0; // 其余字符返回0
 }

 Record *SearchTrie(TrieTree T,KeysType K)
 { // 在键树T中查找关键字等于K的记录。算法9.16
   TrieTree p;
   int i;
   for(p=T,i=0;p&&p->kind==BRANCH&&i<K.num;p=p->bh.ptr[ord(K.ch[i])],++i);
   // 对K的每个字符逐个查找，*p为分支结点，ord()求字符在字母表中序号
   if(p&&p->kind==LEAF&&p->lf.K.num==K.num&&EQ(p->lf.K.ch,K.ch)) // 查找成功
     return p->lf.infoptr;
   else // 查找不成功
     return NULL;
 }

 void InsertTrie(TrieTree &T,Record *r)
 { // 初始条件：Trie键树T存在，r为待插入的数据元素的指针
   // 操作结果：若T中不存在其关键字等于(*r).key.ch的数据元素，则按关键字顺序插r到T中
   TrieTree p,q,ap;
   int i=0,j;
   KeysType K1,K=r->key;
   if(!T) // 空树
   {
     T=(TrieTree)malloc(sizeof(TrieNode));
     T->kind=BRANCH;
     for(i=0;i<LENGTH;i++) // 指针量赋初值NULL
       T->bh.ptr[i]=NULL;
     p=T->bh.ptr[ord(K.ch[0])]=(TrieTree)malloc(sizeof(TrieNode));
     p->kind=LEAF;
     p->lf.K=K;
     p->lf.infoptr=r;
   }
   else // 非空树
   {
     for(p=T,i=0;p&&p->kind==BRANCH&&i<K.num;++i)
     {
       q=p;
       p=p->bh.ptr[ord(K.ch[i])];
     }
     i--;
     if(p&&p->kind==LEAF&&p->lf.K.num==K.num&&EQ(p->lf.K.ch,K.ch)) // T中存在该关键字
       return;
     else // T中不存在该关键字，插入之
       if(!p) // 分支空
       {
	 p=q->bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
	 p->kind=LEAF;
	 p->lf.K=K;
	 p->lf.infoptr=r;
       }
       else if(p->kind==LEAF) // 有不完全相同的叶子
       {
         K1=p->lf.K;
         do
         {
           ap=q->bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
           ap->kind=BRANCH;
           for(j=0;j<LENGTH;j++) // 指针量赋初值NULL
             ap->bh.ptr[j]=NULL;
	   q=ap;
           i++;
         }while(ord(K.ch[i])==ord(K1.ch[i]));
         q->bh.ptr[ord(K1.ch[i])]=p;
         p=q->bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
         p->kind=LEAF;
         p->lf.K=K;
         p->lf.infoptr=r;
       }
   }
 }

 void TraverseDSTable(TrieTree T,void(*Vi)(Record*))
 { // 初始条件：Trie键树T存在，Vi是对记录指针操作的应用函数
   // 操作结果：按关键字的顺序输出关键字及其对应的记录
   TrieTree p;
   int i;
   if(T)
     for(i=0;i<LENGTH;i++)
     {
       p=T->bh.ptr[i];
       if(p&&p->kind==LEAF)
         Vi(p->lf.infoptr);
       else if(p&&p->kind==BRANCH)
         TraverseDSTable(p,Vi);
     }
 }
