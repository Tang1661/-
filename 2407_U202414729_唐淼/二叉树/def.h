#include "stdio.h"
#include "stdlib.h"
#include <bits/stdc++.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define ERROR2 -3
#define INFEASIBLE -1
#define overflow -2
#define init_size 50

typedef int status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    char others[20];
} TElemType; // 二叉树结点类型定义

typedef struct BiTNode
{ // 二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
    int pos;
    TElemType data;
} DEF;

typedef struct
{
    char name[30];
    BiTNode *T;
} TreeEntry;

typedef struct
{
    TreeEntry *elem; // 改为动态数组指针
    int length;      // 当前实际存储了多少个二叉树
    int listsize;    // 当前已分配的容量
} LISTS;

void visit(BiTree T);
void createinit(void);
status CreateBiTree(BiTree &T,TElemType definition[]);
status DestroyBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
status ClearBiTree(BiTree &T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
BiTree FindFather(BiTree T,KeyType e);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
int MaxPathSum(BiTree T);
BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
void InvertTree(BiTree T);
void save(BiTree T,FILE *fp);
status SaveBiTree(BiTree T, char FileName[]);
void load(BiTree &T,FILE *fp);
status LoadBiTree(BiTree &T, char FileName[]);
void InitLists(LISTS &Lists);
status Addtree(LISTS &Lists, char *name);
status Removetree(LISTS &Lists, char *name);
int Locatetree(LISTS &Lists, char *name);
void TraversLists(LISTS Lists);
void show1();
void show2(BiTree T);
void show3();