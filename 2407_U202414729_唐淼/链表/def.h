#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
// #define OVERFLOW -2

typedef int status;
typedef int ElemType; // 数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

typedef struct LNode
{ // 单链表（链式结构）结点的定义
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

typedef struct ListNode
{ // 线性表的管理表定义
	struct
	{
		char name[20];
		LinkList L;
	}List;
	struct ListNode *next;
} ListsNode;

typedef struct {
    ListNode *head;              // 链表头指针
	ListNode *tail;              //链表尾指针
	int length;
} LISTS;


void show1(void);
void show2(void);
void show3(void);
int main1(LinkList &L);
int main2(LISTS &Lists);
status InitList(LinkList &L); 
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType& e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType& pre);
status NextElem(LinkList L,ElemType e,ElemType& next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status ReverseList(LinkList L);
status RemoveNthFromEnd(LinkList L,int i,ElemType &e);
status SortList(LinkList &L);
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L, char FileName[]);
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
void displayAllLists(LISTS Lists);
int main1(LinkList &L);
int main2(void);