#include "def.h"

void show1(void){   //总体菜单
    printf("===============单线性表操作系统菜单================\n");
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
        printf("    	  4. ListEmpty      13. ReverseList\n");
        printf("    	  5. ListLength     14. RemoveNthFromEnd\n");
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

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L)    //判断线性表是否存在
    return INFEASIBLE;
    L=(LinkList)malloc(sizeof(LNode));    //创造首结点
    L->next=NULL;      //初始化首结点的指针域
    return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *temp;
    while(L){    //遍历释放所有结点
        temp = L->next;
        free(L);
        L=temp;
    }
    return OK;
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *p,*q=L->next;
    while(q){    //遍历释放除首结点以外的所有结点
        p=q;    
        q=q->next;
        free(p);
    }
    L->next=NULL;  //更新首结点的指针域
    return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    if(L->next==NULL)    //判断线性表是否为空，及是否存在元素结点
    return TRUE;
    return FALSE;
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    int length=0;
    LNode *temp=L->next;
    while(temp){    //遍历计算元素结点数量
        length++;
        temp=temp->next;
    }
    return length;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    if(i<1)
    return ERROR;
    LNode *temp=L;
    for(int j=1;j<=i;j++){    //沿线性表移动到第i个元素结点
        temp=temp->next;
        if(!temp)
        return ERROR;
    }
    e=temp->data;    //将第i个元素结点的值赋值给e
    return OK;
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    int loc=0;
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *temp=L->next;
    while(temp){    //遍历线性表
        loc++;
        if(temp->data==e)    //判断结点的值域的值是否为e
        return loc;
        temp=temp->next;  //若不是，继续遍历
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *Pre=L->next;
    if(!Pre||Pre->data==e)    //判断线性表是否为空或e是否为首元素
    return ERROR;
    LNode *temp=Pre->next;
    while(temp){     //遍历查找e
        if(temp->data==e){
            pre=Pre->data;    //将前驱赋值给pre
            return OK;
        }
        else{
            Pre=temp;
            temp=temp->next;
        }
    }
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *cur=L->next;
    while(cur){     //遍历查找元素e
        if(cur->data==e){ 
            if(cur->next==NULL)
            break;
            next=cur->next->data;    //将后继的值赋给next
            return OK;
        }
        cur=cur->next;
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    if(i<1)    //判断i是否合法
    return ERROR;
    LNode *pre=L;
    LNode *temp=(LNode *)malloc(sizeof(LNode));
    if (!temp) 
    return ERROR;
    for(int j=1;j<i;j++){    //移动到指定位置
        if(pre->next==NULL)    //判断位置是否合法
        return ERROR;
        pre=pre->next;
    }
    temp->data=e;    //更新插入结点的值域
    temp->next=pre->next;     //插入结点
    pre->next=temp;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *temp=L;
    LNode *cur=temp->next;
    if(i<1)
    return ERROR;
    for(int j=1;j<i;j++){     //遍历移动到第i个元素结点
        if(temp->next==NULL||cur->next==NULL)    //判断i是否合法
        return ERROR;
        temp=cur;    
        cur=cur->next;
    }
    e=cur->data;    //将第i个元素结点的值赋值给e
    temp->next=cur->next;    //删除第i个元素结点
    free(cur);    //释放原来第i个元素结点的空间
    return OK;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *temp=L->next;
    while(temp){    //遍历线性表
        printf("%d",temp->data);
        if(L->next)
        printf(" ");
        temp=temp->next;
    }
    return OK;
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{ 
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    FILE *fq=fopen(FileName,"w");    //打开文件
    if(!fq)    //判断文件是否打开成功
    return ERROR;
    LNode *temp=L->next;
    while(temp){
        fprintf(fq,"%d ",temp->data);    //遍历线性表并将内容输出到文件中
        temp=temp->next;
    }
    fclose(fq);    //关闭文件
    return OK;
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L)    //判断线性表是否存在
    return INFEASIBLE;
    FILE *fq=fopen(FileName,"r");    //打开文件
    if(!fq)     //判断文件是否打开成功
    return ERROR;
    L=(LinkList)malloc(sizeof(LNode));    //创建线性表
    L->next=NULL;
    LNode *temp=L;
    ElemType e=0;
    while(fscanf(fq,"%d",&e)==1){      //读取文件并赋值给线性表
        temp->next=(LNode *)malloc(sizeof(LNode));
        temp->next->next=NULL;
        temp->next->data=e;
        temp=temp->next;
    }
    fclose(fq);
    return OK;
}

status ReverseList(LinkList L){
//如果线性表不存在，返回INFEASIBLE；否则翻转线性表
    if(!L)    //判断线性表是否存在
    return INFEASIBLE;
    LNode *pre=NULL;    //保存前一个结点
    LNode *cur=L->next;    //保存当前结点
    LNode *next=NULL;    //保存下一个结点
    while(cur){
        next=cur->next;    //保存下一个结点
        cur->next=pre;    //翻转当前节点与前一个结点
        pre=cur;    //顺着线性表向后移动
        cur=next;
    }
    L->next=pre;    //更新首元素结点
    return OK;
}

status RemoveNthFromEnd(LinkList L,int i,ElemType &e){
    status length=ListLength(L);    //获得线性表长度
    if(!L||!length)    //判断线性表是否存在以及是否为空
    return INFEASIBLE;
    if(i>length||i<1)    //判断i是否合法
    return ERROR;
    i=length-i+1;    //获得要删除元素的正向位置
    ListDelete(L,i,e);
    return OK;
}

status SortList(LinkList &L){
    if(L==NULL||L->next==NULL)    //判断线性表是否存在以及是否为空
    return INFEASIBLE;
    int flag=FALSE;    //线性表是否排序完成的标志
    status length=ListLength(L);  //获得线性表长度
    while(!flag){    //冒泡排序
        LNode *p1=L->next;
        LNode *p2=p1->next;
        flag=TRUE;
        for(int i=0;i<length-1&&p1&&p2;i++){
            if(p1->data>p2->data){
                int temp=p1->data;
                p1->data=p2->data;
                p2->data=temp;
                flag=FALSE;
            }
            p1=p2;
            p2=p2->next;
        }
        length--;
    }
    return OK;
}

status AddList(LISTS &Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{   
    ListNode *p=Lists.head;
    while (p!=NULL) {    //判断线性表是否已存在
        if (strcmp(p->List.name, ListName) == 0)
        return ERROR;
        p=p->next;
    }
    LinkList NewList=NULL;    //创建新线性表
    if(InitList(NewList)!=OK)
    return ERROR;
    ListNode *NewNode=(ListNode *)malloc(sizeof(ListNode));   //创建新线性表结点
    if(!NewNode)
    return ERROR;
    NewNode->List.L = NewList;
    strcpy(NewNode->List.name, ListName);
    if(!Lists.head){    
        Lists.head=NewNode;
        Lists.tail=NewNode;       
    }
    else{
        Lists.tail->next=NewNode;
        Lists.tail=NewNode;
    }
    Lists.length++;
    return OK;
}

int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回在多线性表中的位置，否则返回0
{
    ListNode *p=Lists.head;
    int pos=1;
    while (p!=NULL) {    //遍历查找线性表
        if (strcmp(p->List.name, ListName) == 0)
        return pos;
        p=p->next;
        pos++;
    }
    return ERROR;
}

status RemoveList(LISTS &Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    ListNode *prev = NULL;
    ListNode *curr = Lists.head;
    
    while (curr != NULL) {
        if (strcmp(curr->List.name, ListName) == 0) {
            // 找到要删除的节点
            DestroyList(curr->List.L);  // 销毁线性表           
            if (prev == NULL) {       // 从链表中删除节点
                // 删除的是头节点
                Lists.head = curr->next;
            } else {
                prev->next = curr->next;
            }           
            free(curr);  // 释放节点内存
            Lists.length--;
            return OK;
        }
        prev = curr;
        curr = curr->next;
    }
    return ERROR;
}

void displayAllLists(LISTS Lists) {    //展示所有线性表
    printf("当前线性表有：\n");
    int i=1;    
    ListNode *p=Lists.head;
    while (p!=NULL) {    //遍历线性表
        printf("%d:%s\n",i++,p->List.name);
        p=p->next;
    }
}