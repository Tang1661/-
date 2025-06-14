#include <bits/stdc++.h>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define overflow -2
#define ERROR2 -3
#define MAX_VERTEX_NUM 20
#define init_size 10

typedef int status;
typedef int KeyType;

typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;

typedef struct
{
    KeyType key;
    char others[20];
} VertexType; // 顶点类型定义

typedef struct ArcNode
{                            // 表结点类型定义
    int adjvex;              // 顶点位置编号
    struct ArcNode *nextarc; // 下一个表结点指针
} ArcNode;
typedef struct VNode
{                      // 头结点及其数组类型定义
    VertexType data;   // 顶点信息
    ArcNode *firstarc; // 指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{                       // 邻接表的类型定义
    AdjList vertices;   // 头结点数组
    int vexnum, arcnum; // 顶点数、弧数
    GraphKind kind;     // 图的类型
} ALGraph;

typedef struct
{
    char name[30]; // 图的名称
    ALGraph *G;    // 指向图的指针
} GraphEntry;

typedef struct
{
    GraphEntry *elem; // 动态数组，存储多个图
    int length;       // 当前存储的图个数
    int listsize;     // 当前分配的总容量
} GRAPHLISTS;

status check(VertexType V[], KeyType VR[][2]);
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph &G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status check2(ALGraph &G, KeyType u);
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KeyType v);
status InsertArc(ALGraph &G, KeyType v, KeyType w);
status DeleteArc(ALGraph &G, KeyType v, KeyType w);
void visit(VertexType v);
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
vector<int> dijkstra(ALGraph &G, KeyType v);
vector<VertexType> VerticesSetLessThanK(ALGraph &G, KeyType v, int k);
int ShortestPathLength(ALGraph &G, KeyType v, KeyType w);
int ConnectedComponentsNums(ALGraph &G);
void PrintGraph(ALGraph &G);
void InitGraphLists(GRAPHLISTS &Lists);
status AddGraph(GRAPHLISTS &Lists, char *name);
status RemoveGraph(GRAPHLISTS &Lists, char *name);
int LocateGraph(GRAPHLISTS &Lists, char *name);
void show1();
void show2(ALGraph G);
void show3();
void Traverse(GRAPHLISTS Lists);