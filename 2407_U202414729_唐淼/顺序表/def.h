#include <bits/stdc++.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int status;
typedef int ElemType; // 数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{ // 顺序表（顺序结构）的定义
    ElemType *elem;
    int length;
    int listsize;
} SqList;
typedef struct
{ // 线性表的管理表定义
    struct
    {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
} LISTS;

int main1(SqList &L);
int main2(LISTS &Lists);
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList&L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType& pre);
status NextElem(SqList L,ElemType e,ElemType& next);
status ListInsert(SqList&L,int i,ElemType e);
status ListDelete(SqList&L,int i,ElemType& e);
status ListTraverse(SqList L);
status MaxSubArray(SqList L);
status SubArrayNum(SqList L,int k);
status SortList(SqList &L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L, char FileName[]);
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
void show3(void);
void displayAllLists(LISTS Lists);
void show1(void);
void show2(void);