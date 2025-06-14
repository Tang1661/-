#include"def.h"
#include"string.h"
status InitList(SqList& L)
{
    if(L.elem)     //判断线性表是否存在
    return INFEASIBLE;      
    else{
        L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));   
        //为创建的线性表分配存储空间
        L.listsize=LIST_INIT_SIZE;
        L.length=0;
        //更新listsize,length
        return OK;
    }
}

status DestroyList(SqList& L)
{
    if(L.elem){     //若线性表存在则销毁线性表
        free(L.elem);   //释放线性表空间
        L.elem=NULL;    //使线性表未初始化
        L.listsize=0;
        L.length=0;
        return OK;
    }
    return INFEASIBLE;
}

status ClearList(SqList& L)
{
    if(L.elem==NULL)     
    return INFEASIBLE;  //若线性表不存在，则返回INFEASIBLE
    else{  
    L.length=0;
    L.listsize=LIST_INIT_SIZE;      //清空线性表
    return OK;
    }
}

status ListEmpty(SqList L)
{
    if(L.elem==NULL)      //判断表是否存在
    return INFEASIBLE;
    else if(L.length==0)  //判断表是否为空
    return TRUE;
    return FALSE;
}

status ListLength(SqList L)
{
    if(L.elem==NULL)     //若表不存在则返回INFEASIBLE
    return INFEASIBLE;
    return L.length;     //返回表的长度
}

status GetElem(SqList L,int i,ElemType &e)
{
    if(L.elem==NULL)     //判断表是否存在
    return INFEASIBLE;
    if(i<1||i>L.length)  //判断i是否合法
    return ERROR;
    e=L.elem[i-1];       //获得第i个元素
    return OK;
}

int LocateElem(SqList L,ElemType e)
{
    if(L.elem==NULL)     //判断线性表是否存在
    return INFEASIBLE;
    int i;
    for(i=0;i<L.length;i++){   //遍历线性表查找e
        if(L.elem[i]==e)
        return i+1;
    }
    return ERROR;    //找到指定元素e
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
{
    if(L.elem==NULL)     //判断线性表是否存在
    return INFEASIBLE;
    int i;
    for(i=0;i<L.length;i++){   //遍历查找指定元素e
        if(L.elem[i]==e)
        break;
    }
    if(i<L.length&&i>0){    //若找到e，则将e的前驱赋值给pre
    pre=L.elem[i-1];
    return OK;
    }
    return ERROR;
}

status NextElem(SqList L,ElemType e,ElemType &next)
{
    if(L.elem==NULL)    //判断线性表是否存在
    return INFEASIBLE;
    int i;
    for(i=0;i<L.length;i++){  //遍历查找指定元素e
        if(e==L.elem[i])
        break;
    }
    if(i<L.length-1){     ////若找到e，则将e的后继赋值给next
        next=L.elem[i+1];
        return OK;
    }
    return ERROR;
}

status ListInsert(SqList &L,int i,ElemType e)
{
    if(L.elem==NULL)    //判断线性表是否存在
    return INFEASIBLE;
    if(i>L.length+1||i<1)    //判断i是否合法
    return ERROR;
    if(L.length>=L.listsize){      //若线性表已满，则为线性表扩容
        ElemType *newelem;
        newelem=(ElemType *)malloc(sizeof(ElemType)*(L.listsize+LISTINCREMENT));
        //分配新的存储空间
        if (!newelem) {
            return OVERFLOW;  // 内存不足
        }
        for(int j=0;j<L.length;j++){    //复制原来的线性表
            newelem[j]=L.elem[j];
        }
        free(L.elem);
        L.elem=newelem;    //替换线性表
        L.listsize+=LISTINCREMENT;    //更新线性表可用长度
    }
    for(int j=L.length;j>=i;j--){   //将线性表中指定位置及之后的元素向后挪一位
        L.elem[j]=L.elem[j-1];
    }
    L.elem[i-1]=e;    //插入指定元素到指定位置
    L.length+=1;      //更新线性表长度
    return OK;
}

status ListDelete(SqList &L,int i,ElemType &e)
{
    if (L.elem==NULL)      //判断线性表是否存在
    return INFEASIBLE;
    if(i<1||i>L.length)    //判断i是否合法
    return ERROR;
    e=L.elem[i-1];         //获得删除的第i个元素
    for(int j=i-1;j<L.length-1;j++){    //将第i个位置后面的元素向前移一位
        L.elem[j]=L.elem[j+1];
    }
    L.length-=1;
    return OK;
}

status ListTraverse(SqList L)
{
    if(L.elem==NULL)     //判断线性表是否存在
    return INFEASIBLE;
    for(int i=0;i<L.length;i++){     //遍历线性表
        printf("%d",L.elem[i]);
        if(i<L.length-1)    //输出空格
        printf(" ");
    }
    return OK;
}

status MaxSubArray(SqList L)
{
    if(L.elem==NULL)    //判断线性表是否为空
    return INFEASIBLE;
    ElemType psum = L.elem[0], msum = L.elem[0];
    for (int i = 1; i < L.length; ++i)    //寻找最大子数组和
    {
        psum = max(L.elem[i], psum + L.elem[i]);
        msum = max(msum, psum);
    }
    return msum;
}

status SubArrayNum(SqList L,int k){
    if(L.elem==NULL||L.length==0)   //判断线性表是否存在以及是否为空
    return INFEASIBLE;
    int count=0;    
    for(int start=0;start<L.length;start++){  //寻找和为k的子数组
        int sum=0;
        for(int end=start;end<L.length;end++){
            sum+=L.elem[end];
            if(sum==k)
            count++;
        }
    }
    return count;
}

status SortList(SqList &L){
    if(L.elem==NULL)    //判断线性表是否为空
    return INFEASIBLE; 
    for(int j=0;j<L.length-1;j++){     //冒泡排序
        for(int k=j+1;k<L.length;k++){
            if(L.elem[j]>L.elem[k]){
                ElemType mid=L.elem[j];
                L.elem[j]=L.elem[k];
                L.elem[k]=mid;
            }
        }
    }
    return OK;
}

status AddList(LISTS &Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    Lists.elem[Lists.length].L.elem = NULL; // 头歌里面一开始不是NULL，要人为设为空
    InitList(Lists.elem[Lists.length].L);
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.length++;
    return 1;
}

status RemoveList(LISTS &Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    for (int i = 0; i < Lists.length; ++i)
        if (strcmp(Lists.elem[i].name, ListName) == 0)    //遍历寻找线性表
        {
            DestroyList(Lists.elem[i].L);    //销毁线性表
            for (int k = i; k < Lists.length - 1; ++k)
            //将销毁的线性表后面的线性表前移一位
            {
                SqList &pre = Lists.elem[k].L, &now = Lists.elem[k + 1].L;
                pre.elem = NULL; // 要认为定义为NULL才能init
                InitList(pre);

                strcpy(Lists.elem[k].name, Lists.elem[k + 1].name);
                for (int x = 0; x < now.length; ++x)
                    ListInsert(pre, x + 1, now.elem[x]);
                pre.length = now.length, pre.listsize = now.listsize;
            }
            Lists.length--;     //线性表数量减一
            return OK;
        }
    return ERROR;
}

int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for (int i = 0; i < Lists.length; ++i)
        if (strcmp(Lists.elem[i].name, ListName) == 0)     //遍历查找线性表
            return i + 1;
    return 0;
}

void show1(void){   //总体菜单
    printf("===============线性表操作系统菜单================\n");
    printf("-------------------------------------------------\n");
    printf("    1. 单线性表操作       2.多线性表管理\n");
    printf("    0. 离开系统\n");
    printf("-------------------------------------------------\n");
    printf("ps:本系统在执行完一个功能后要再随便输出个字符才能再次显示菜单！\n");
    printf("    请选择你的操作[0~2]:");
}

void show2(void){    //单线性表操作菜单
    printf("\n\n");
        printf("===============单线性表操作系统菜单================\n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       10. ListInsert\n");
        printf("    	  2. DestroyList    11. ListDelete\n");
        printf("    	  3. ClearList      12. ListTraverse\n");
        printf("    	  4. ListEmpty      13. MaxSubArray\n");
        printf("    	  5. ListLength     14. SubArrayNum\n");
        printf("    	  6. GetElem        15. SortList\n");
        printf("    	  7. LocateElem     16. SaveList\n");
        printf("    	  8. PriorElem      17. LoadList\n");
        printf("    	  9. NextElem        0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("ps:本系统在执行完一个功能后要再随便输出个字符才能再次显示菜单！\n");
        printf("    请选择你的操作[0~17]:");
}

void show3() {    //多线性表管理菜单
    printf("\n========== 多线性表管理系统菜单 ==========\n");
    printf("1. 添加新线性表         3. 查找线性表\n");
    printf("2. 删除线性表           4. 操作单个线性表\n");
    printf("0. 退出系统\n");
    printf("===================================\n");
    printf("ps:本系统在执行完一个功能后要再随便输出个字符才能再次显示菜单！\n");
    printf("请选择操作[0-4]: ");
}

void displayAllLists(LISTS Lists) {
    printf("\n当前所有线性表:\n");
    for (int i = 0; i < Lists.length; i++) {
        printf("%d. %s: ", i+1, Lists.elem[i].name);
        ListTraverse(Lists.elem[i].L);
        printf("\n");
    }
}

status LoadList(SqList &L, char FileName[])
{
    if (L.elem)    //判断线性表是否存在
        return INFEASIBLE;
    FILE *fq = fopen(FileName, "r");    //打开文件
    if (!fq)    //判断文件是否打开成功
        return INFEASIBLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    L.length = 0, L.listsize = LIST_INIT_SIZE;

    while (fscanf(fq, "%d", &L.elem[L.length]) == 1)    // 逐个读取整数
    {
        L.length++;
        if (L.length >= L.listsize)
        { // 如果数组满了，扩展数组
            L.elem = (ElemType *)realloc(L.elem, (L.length + LISTINCREMENT) * sizeof(ElemType));
            L.listsize += LISTINCREMENT;
        }
    }
    fclose(fq);
    return OK;
}

status SaveList(SqList L, char FileName[])
{
    if (!L.elem)    //判断线性表是否存在
        return INFEASIBLE;
    FILE *fq = fopen(FileName, "w");    //打开文件并判断是否打开成功
    if (!fq)
        return INFEASIBLE;
    for (int i = 0; i < L.length; ++i)    //逐个输入字符
        fprintf(fq, "%d ", L.elem[i]);
    fclose(fq);
    return OK;
}