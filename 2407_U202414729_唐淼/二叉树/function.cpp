#include"def.h"

// -----------------------------------------------------------------
//                          单二叉树操作部分
// -----------------------------------------------------------------
int tot=0;
unordered_map<int, int> hashb;

void createinit()
{
    tot = 0;
    hashb.clear();
}

status CreateBiTree(BiTree &T,TElemType definition[])
{
// 创建二叉树，根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，如果有相同的关键字，返回ERROR
// 每个结点对应一个整型的关键字和一个字符串，当关键字为0时，表示空子树，为-1表示输入结束；
    if (definition[tot].key == 0 || definition[tot].key == -1)
    {
        ++tot;
        return OK;
    }

    if (hashb[definition[tot].key] != 0)
    return ERROR;
    hashb[definition[tot].key] = 1;

    T = (BiTree)malloc(sizeof(BiTNode));
    if (!T)
    return overflow;
    T->data = definition[tot];
    T->lchild = T->rchild = NULL;
    ++tot;

    if (CreateBiTree(T->lchild, definition) == ERROR)
    return ERROR;

    if (CreateBiTree(T->rchild, definition) == ERROR)
    return ERROR;

    return OK;
}

void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

status DestroyBiTree(BiTree &T)
{
// 销毁二叉树，并删除所有结点，释放结点空间
    if (T == NULL)
        return OK;

    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);

    free(T);
    T = NULL;
    return OK;
}

status ClearBiTree(BiTree &T)
{
// 清空二叉树，只是将二叉树清空了，是空树，但是在内存中还存在空间，只是值不确定。
    if(T==NULL)
    return OK;
     
    if (T == NULL)
        return OK;

    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);

    T->data.key = 0;
    T->data.others[0] = '\0';
    return OK;
}

status BiTreeEmpty(BiTree T)
{
// 判定空二叉树：函数名称是；初始条件是二叉树T存在；操作结果是若T为空二叉树则返回TRUE，否则返回FALSE；
    if (T == NULL)
        return TRUE;

    if (BiTreeEmpty(T->lchild) == FALSE)
        return FALSE;
    if (BiTreeEmpty(T->rchild) == FALSE)
        return FALSE;

    if (T->data.key == 0)
        return TRUE;
    else
        return FALSE;
}

int BiTreeDepth(BiTree T)
{
// 求二叉树深度
    if(T==NULL)
    return 0;
    int ldep=BiTreeDepth(T->lchild);
    int rdep=BiTreeDepth(T->rchild);
    return (ldep>rdep?ldep:rdep)+1; 
}

BiTNode *LocateNode(BiTree T, KeyType e)
// 查找结点
{
    if (T == NULL)
        return NULL;

    if (T->data.key == e)
        return T;

    BiTree p1 = LocateNode(T->lchild, e);
    BiTree p2 = LocateNode(T->rchild, e);

    if (p1 != NULL)
        return p1;
    if (p2 != NULL)
        return p2;
    return NULL;
}

status Assign(BiTree &T,KeyType e,TElemType value)
{
// 结点赋值
    BiTree p1=LocateNode(T,e);
    BiTree p2=LocateNode(T,value.key);
    if(p1==NULL||(p2!=NULL&&e!=value.key)){
        return ERROR;
    }
    p1->data=value;
    return OK;
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    if(T==NULL)
    return NULL;

    if(T->rchild&&T->rchild->data.key==e)
    return T->lchild;
    if(T->lchild&&T->lchild->data.key==e)
    return T->rchild;

    BiTNode* pl=GetSibling(T->lchild,e);
    if(pl!=NULL)
    return pl;
    BiTNode* pr=GetSibling(T->rchild,e);
    if(pr!=NULL)
    return pr;

    return NULL;
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点
// 结点e的原有左子树或右子树则为结点c的右子树，返回OK。如果插入失败，返回ERROR。
// 特别地，当LR为-1时，作为根结点插入，原根结点作为c的右子树。
{
    if(LR==-1){
        BiTree root=(BiTree)malloc(sizeof(BiTNode));
        if(!root)
        return overflow;
        root->rchild=T;
        root->lchild==NULL;
        root->data=c;
        T=root;
        return OK;
    }
    // 检验有没有可替换节点
    BiTree pos=LocateNode(T,e);
    if(pos==NULL)
    return ERROR;
    // 保证唯一性
    BiTree pos2=LocateNode(T,c.key);
    if(pos2!=NULL)
    return ERROR;
    BiTree newnode=(BiTree)malloc(sizeof(BiTNode));
    if(!newnode)
    return overflow;
    newnode->data=c;
    newnode->lchild=NULL;
    if(LR==1){
        // 此时插入到右子树
        newnode->rchild=pos->rchild;
        pos->rchild=newnode;
    }
    else if(LR==0){
        // 此时插入到左子树
        newnode->rchild=pos->lchild;
        pos->lchild=newnode;
    }
    return OK;
}

BiTree FindFather(BiTree T,KeyType e){
//查找父亲结点
    if(T==NULL)
    return NULL;
    if(T->data.key==e)
    return T;
    if(T->lchild && T->lchild->data.key == e || T->rchild && T->rchild->data.key == e)
    return T;
BiTree p1=FindFather(T->lchild,e);
BiTree p2=FindFather(T->rchild,e);
if(p1!=NULL)
return p1;
if(p2!=NULL)
return p2;
return NULL;
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点
{
    BiTree p = FindFather(T, e);
    if (p == NULL)
    return ERROR;
    BiTree cur=T;
    int LR=-1;
    // 找到要删除的节点
    if(p->data.key!=e){
        if(p->lchild->data.key==e){
            cur=p->lchild;
            LR=0;
        }
        else{
            cur=p->rchild;
            LR=1;
        }
    }
    // 开始删除节点
    if(cur->lchild==NULL&&cur->rchild==NULL){
        if(LR==-1)
        T=NULL;
        else if(LR==0)
        p->lchild=NULL;
        else if(LR==1)
        p->rchild=NULL;
        free(cur);
    }
    else if(cur->lchild!=NULL&&cur->rchild==NULL){
        // 结点只有一个左子树
        if(LR==-1)
        T=cur->lchild;
        else if(LR==0)
        p->lchild=cur->lchild;
        else if(LR==1)
        p->rchild=cur->lchild;
        free(cur);
    }
    else if(cur->lchild==NULL&&cur->rchild!=NULL){
        // 结点只有一个右子树
        if(LR==-1)
        T=cur->rchild;
        else if(LR==0)
        p->lchild=cur->rchild;
        else if(LR==1)
        p->rchild=cur->rchild;
        free(cur);
    }
    else if(cur->lchild!=NULL&&cur->rchild!=NULL){
        // 结点有两个子树
        BiTree l=cur->lchild;
        BiTree r=cur->rchild;
       if(LR==-1)
        T=cur->lchild;
        else if(LR==0)
        p->lchild=cur->lchild;
        else if(LR==1)
        p->rchild=cur->lchild;
        while(l->rchild!=NULL)
        l=l->rchild;
        l->rchild=r;
        free(cur);    
    }
    return OK;
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    if (T == NULL)
        return ERROR;
    BiTree stack[1000] = {NULL};
    int top = -1;
    stack[++top] = T;
    while (top != -1)
    {
        BiTree cur = stack[top--];
        visit(cur);
        if (cur->rchild)
            stack[++top] = cur->rchild;
        if (cur->lchild)
            stack[++top] = cur->lchild;
    }
    return OK;
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    if (T == NULL)
        return ERROR;
    if (T->lchild)
        InOrderTraverse(T->lchild, visit);
    visit(T);
    if (T->rchild)
        InOrderTraverse(T->rchild, visit);
    return OK;
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    if (T == NULL)
        return ERROR;
    if (T->lchild)
        PostOrderTraverse(T->lchild, visit);
    if (T->rchild)
        PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    if (T == NULL)
        return ERROR;
    BiTree queue[1000] = {NULL};
    int down = 0, top = -1;
    queue[++top] = T;

    while (down <= top)
    {
        BiTree cur = queue[down++];
        visit(cur);
        if (cur->lchild)
            queue[++top] = cur->lchild;
        if (cur->rchild)
            queue[++top] = cur->rchild;
    }
    return OK;
}

int MaxPathSum(BiTree T)
{
// 最大路径和，操作结果是返回根节点到叶子结点的最大路径和；
    if (T == NULL)
        return 0;

    // 递归计算左右子树的最大路径和
    int left = MaxPathSum(T->lchild);
    int right = MaxPathSum(T->rchild);

    // 返回当前节点的 key + 左右子树中较大的路径和
    return T->data.key + (left > right ? left : right);
}


BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
{
// 最近公共祖先，操作结果是该二叉树中e1节点和e2节点的最近公共祖先
    if (T == NULL)
        return NULL;

    // 如果当前节点就是 e1 或 e2，直接返回它
    if (T->data.key == e1 || T->data.key == e2)
        return T;

    // 在左右子树中递归查找
    BiTree left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTree right = LowestCommonAncestor(T->rchild, e1, e2);

    if (left != NULL && right != NULL)
        return T; // 若分别出现在左右子树，当前节点即为最近公共祖先

    return left != NULL ? left : right; // 否则返回非空的那一侧
}


void InvertTree(BiTree T)
{
// 翻转二叉树，操作结果是将T翻转，使其所有节点的左右节点互换；
    if (T == NULL)
        return;

    // 交换当前节点的左右孩子
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;

    // 递归处理左右子树
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}

void save(BiTree T,FILE *fp)
{
//文件存储
    if (T==NULL)
    {
        fprintf(fp, "#\n");
        return;
    }
    fprintf(fp, "%d %s\n",T->data.key, T->data.others);
    save(T->lchild, fp);
    save(T->rchild, fp);
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    FILE *fp = fopen(FileName, "w");
    if (!fp)
    return ERROR;
    save(T, fp);
    fclose(fp);
    return OK;
}

void load(BiTree &T,FILE *fp)
{
    char list[100];
    if(!fgets(list,sizeof(list),fp))
    return;
    if(list[0]=='#'){
        T=NULL;
        return;
    }
    T=(BiTree)malloc(sizeof(BiTNode));
    sscanf(list,"%d %s",&T->data.key,T->data.others);
    load(T->lchild,fp);
    load(T->rchild,fp);
}

status LoadBiTree(BiTree &T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    FILE *fp = fopen(FileName, "r");
    if (!fp)
        return ERROR;
    load(T, fp);
    fclose(fp);
    return OK;
}

// -----------------------------------------------------------------
//                          多线性表管理部分
// -----------------------------------------------------------------

// 创建线性表
void InitLists(LISTS &Lists)
{
    Lists.elem = (TreeEntry *)malloc(init_size * sizeof(TreeEntry));
    Lists.length = 0;
    Lists.listsize = init_size;
}


status Addtree(LISTS &Lists, char *name)
{
// 添加二叉树
    if (Lists.length == Lists.listsize)
    {
        // 扩容
        TreeEntry *newelem = (TreeEntry *)realloc(Lists.elem, (Lists.listsize + init_size) * sizeof(TreeEntry));
        if (!newelem)
            return overflow;
        // 扩容后释放原内存
        for (int i = 0; i < Lists.length; ++i)
            DestroyBiTree(Lists.elem[i].T); // 释放每棵二叉树
        free(Lists.elem);                   // 释放动态数组本身
        Lists.elem = newelem;
        Lists.listsize += init_size;
    }

    // 初始化空树
    Lists.elem[Lists.length].T = NULL;
    strcpy(Lists.elem[Lists.length].name, name);
    ++Lists.length;
    return OK;
}


status Removetree(LISTS &Lists, char *name)
{
// 移除二叉树
    for (int i = 0; i < Lists.length; ++i)
    {
        if (strcmp(Lists.elem[i].name, name) == 0)
        {
            // 释放二叉树内存
            DestroyBiTree(Lists.elem[i].T);

            // 将后面的元素全部向前移动
            for (int j = i; j < Lists.length - 1; ++j)
                Lists.elem[j] = Lists.elem[j + 1];

            --Lists.length;
            return OK;
        }
    }
    // 删除失败
    return ERROR;
}


int Locatetree(LISTS &Lists, char *name)
{
// 在Lists中查找一个名称为name的二叉树，成功返回逻辑序号，否则返回0
    for (int i = 0; i < Lists.length; ++i)
        if (strcmp(Lists.elem[i].name, name) == 0)
            return i + 1;
    return 0;
}

void TraversLists(LISTS Lists){
    for (int i = 0; i <Lists.length; ++i)
    printf("%d: %s\n",i+1,Lists.elem[i].name);
}

void show1()
{
    printf("\n");
    printf("     Menu for Linear Table Type On Sequence Structure \n");
    printf("-----------------------------------------------------------\n");
    printf("                   请选择你要操作的类型：\n");
    printf("           1. 单二叉树          2.多二叉树 \n");
    printf("           0. 退出\n");
    printf("-----------------------------------------------------------\n");
    printf("                   请选择你的操作[0~2]:");
}

void show2(BiTree T)
{
    printf("\n");
    printf("      Menu for Linear Table On Sequence Structure         \n");
    printf("----------------------------------------------------------\n");
    printf("    	  1. CreateBiTree         2. DestroyBiTree         \n");
    printf("    	  3. ClearBiTree          4. BiTreeEmpty           \n");
    printf("    	  5. BiTreeDepth          6. LocateNode                \n");
    printf("    	  7. Assign               8. GetSibling            \n");
    printf("    	  9. InsertNode           10. DeleteNode            \n");
    printf("    	  11. PreOrderTraverse    12.InOrderTraverse       \n");
    printf("    	  13. PostOrderTraverse   14.LevelOrderTraverse    \n");
    printf("    	  15. SaveBiTree          16.LoadBiTree            \n");
    printf("    	  17. MaxPathSum          18.LowestCommonAncestor  \n");
    printf("    	  19. InvertTree          20.Change type          \n");
    printf("    	  0 . Exit                 \n");
    printf("ps:本系统在执行完一个功能后要再随便输出个字符才能再次显示菜单欧\n");
    printf("-----------------------------------------------------------\n");
    printf("二叉树实时预览（这里是按层遍历）:");
    status j = LevelOrderTraverse(T, visit);
    if (j == ERROR)
        printf("二叉树不存在 \n");
    else
        printf("\n");
    printf("\n            请选择你的操作[0~20]:");
}

void show3()
{
    printf("\n");
    printf("         Menu for Linear Table On Sequence Structure        \n");
    printf("---------------------------------------------------------- \n");
    printf("    	  1. Addtree          2. Removetree                \n");
    printf("    	  3. Locatetree       4. operator single tree     \n");
    printf("    	  0.Exit             \n");
    printf("ps:本系统在执行完一个功能后要再随便输出个字符才能再次显示菜单欧\n");
    printf("-----------------------------------------------------------\n");
    printf("\n            请选择你的操作[0~4]:");
}