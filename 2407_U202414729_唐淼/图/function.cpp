#include "def.h"

status check(VertexType V[], KeyType VR[][2])
{
    int k = 0;
    int flag[100] = {};
    // 先检查V是否正确
    while (V[k].key != -1)
    {
        if (flag[V[k].key] != 0)
            return ERROR; // 关键字重复
        else
            flag[V[k].key] = 1;
        ++k;
    }

    // 检查V数组
    if (k == 0 || k > MAX_VERTEX_NUM)
        return 0;

    // 在检查VR数组是否正确（不能存在环，顶点必须存在）
    k = 0;
    while (VR[k][0] != -1)
    {
        if (VR[k][0] == VR[k][1])
            return ERROR;
        if (flag[VR[k][0]] == 0 || flag[VR[k][1]] == 0)
            return ERROR;
        ++k;
    }
    return OK;
}

status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    if (check(V, VR) == ERROR)
        return ERROR;
    int k = 0;
    int flag[100] = {};

    // 先对V数组进行处理
    G.arcnum = 0, G.vexnum = 0;
    while (V[k].key != -1)
    {
        flag[V[k].key] = k;
        ++G.vexnum;
        G.vertices[k].data.key = V[k].key;
        strcpy(G.vertices[k].data.others, V[k].others);
        G.vertices[k].firstarc = NULL;
        k++;
    }

    // 对边进行处理
    k = 0;
    while (VR[k][0] != -1)
    {
        ++G.arcnum;
        ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode));
        ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));
        p1->adjvex = flag[VR[k][1]];
        p2->adjvex = flag[VR[k][0]];
        // 头插法
        p1->nextarc = G.vertices[flag[VR[k][0]]].firstarc;
        p2->nextarc = G.vertices[flag[VR[k][1]]].firstarc;
        G.vertices[flag[VR[k][0]]].firstarc = p1;
        G.vertices[flag[VR[k][1]]].firstarc = p2;
        ++k;
    }
    G.kind = UDG;
    return OK;
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    for (int i = 0; i < G.arcnum; ++i)
    {
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
        G.vertices[i].firstarc = NULL;
    }
    G.arcnum = G.vexnum = 0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u)
// 根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    for (int i = 0; i < G.vexnum; ++i)
        if (G.vertices[i].data.key == u)
            return i;
    return -1;
}

status PutVex(ALGraph &G, KeyType u, VertexType value)
// 根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
// 如果查找失败或关键字不唯一，返回ERROR
{
    int index = -1;
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.vertices[i].data.key == value.key)
            return ERROR2;
        if (G.vertices[i].data.key == u)
            index = i;
    }
    if (index == -1)
        return ERROR;
    G.vertices[index].data = value;
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u)
// 根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int i = -1;
    for (i = 0; i < G.vexnum; ++i)
    {
        if (G.vertices[i].data.key == u)
            break;
    }
    if (i == G.vexnum)
        return -1;
    return G.vertices[i].firstarc->adjvex;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
// v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    int i, j;
    for (i = 0; i < G.vexnum; ++i)
        if (G.vertices[i].data.key == v)
            break;
    for (j = 0; j < G.vexnum; ++j)
        if (G.vertices[j].data.key == w)
            break;
    if (i == G.vexnum || j == G.vexnum)
        return -1; // v||w 不存在
    ArcNode *p = G.vertices[i].firstarc;
    while (p)
    {
        if (p->adjvex == j)
            break;
        p = p->nextarc;
    }
    return p->nextarc == NULL ? -1 : p->nextarc->adjvex;
}

status check2(ALGraph &G, KeyType u)
{
    for (int i = 0; i < G.vexnum; ++i)
        if (G.vertices[i].data.key == u)
            return ERROR;
    return OK;
}

status InsertVex(ALGraph &G, VertexType v)
// 在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    if (check2(G, v.key) == ERROR)
        return ERROR;
    if (G.vexnum == MAX_VERTEX_NUM)
        return ERROR2;
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    ++G.vexnum;
    return OK;
}

status DeleteVex(ALGraph &G, KeyType v)
// 在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    if (G.vexnum == 1)
        return ERROR;
    int pos = LocateVex(G, v);
    if (pos == -1)
        return ERROR2;

    // 删除与该顶点相连的边，同时删除邻接点中的反向边
    ArcNode *p = G.vertices[pos].firstarc;
    while (p)
    {
        int adj = p->adjvex;

        // 删除 adj 顶点中的 pos 节点
        ArcNode **q = &G.vertices[adj].firstarc;
        while (*q)
        {
            if ((*q)->adjvex == pos)
            {
                ArcNode *toDelete = *q;
                *q = (*q)->nextarc; // 这里可以直接修改q的值，让它指向下一个边
                free(toDelete);
                break;
            }
            q = &(*q)->nextarc; // 这里修改q的赋值，但是不会改变G中边数组
        }

        ArcNode *temp = p;
        p = p->nextarc;
        free(temp);
        --G.arcnum;
    }
    G.vertices[pos].firstarc = NULL;

    // 将顶点数组中 pos 之后的元素前移，顶点信息和邻接表指针一起移动
    for (int i = pos; i < G.vexnum - 1; ++i)
        G.vertices[i] = G.vertices[i + 1];
    G.vertices[G.vexnum - 1].firstarc = NULL;
    --G.vexnum;

    // 更新所有边中 adjvex 的索引（由于顶点数组下标变化）
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc)
        {
            if (p->adjvex > pos)
                p->adjvex--;
        }
    }

    return OK;
}

status InsertArc(ALGraph &G, KeyType v, KeyType w)
// 在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    int posv = LocateVex(G, v), posw = LocateVex(G, w);
    if (posv == -1 || posw == -1)
        return ERROR;

    // 检查v-w是否已经存在
    ArcNode *p = G.vertices[posv].firstarc;
    while (p)
    {
        if (p->adjvex == posw)
            return ERROR2;
        p = p->nextarc;
    }

    // 加边
    ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode)), *p2 = (ArcNode *)malloc(sizeof(ArcNode));
    p1->adjvex = posw, p2->adjvex = posv;
    p1->nextarc = G.vertices[posv].firstarc, p2->nextarc = G.vertices[posw].firstarc;
    G.vertices[posv].firstarc = p1, G.vertices[posw].firstarc = p2;
    ++G.arcnum;
    return OK;
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
// 在图G中删除弧<v,w>，若是无向图则同时删除<w,v>，成功返回OK，否则返回ERROR
{
    int posv = LocateVex(G, v), posw = LocateVex(G, w);
    if (posv == -1 || posw == -1)
        return ERROR;

    // 删除<v,w>
    int flag = 0;
    ArcNode **p = &G.vertices[posv].firstarc;
    while (*p)
    {
        if ((*p)->adjvex == posw)
        {
            ArcNode *temp = (*p);
            (*p) = (*p)->nextarc;
            free(temp);
            flag = 1;
            break;
        }
        p = &(*p)->nextarc;
    }
    if (!flag)
        return ERROR2; // 没有这条边

    // 如果是无向图，还要删除<w,v>
    if (G.kind == UDG || G.kind == UDN)
    {
        p = &G.vertices[posw].firstarc;
        while (*p)
        {
            if ((*p)->adjvex == posv)
            {
                ArcNode *temp = (*p);
                (*p) = (*p)->nextarc;
                free(temp);
                flag = 1;
                break;
            }
            p = &(*p)->nextarc;
        }
    }

    --G.arcnum;
    return OK;
}

void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
// 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int vis[30] = {}, stk[100], top = -1;

    for (int i = 0; i < G.vexnum; ++i)
    {
        if (!vis[i])
            stk[++top] = i;

        while (top != -1)
        {
            int v = stk[top--];
            if (!vis[v])
            {
                visit(G.vertices[v].data);
                vis[v] = 1;

                ArcNode *p = G.vertices[v].firstarc;
                while (p)
                {
                    if (!vis[p->adjvex])
                    {
                        stk[++top] = p->adjvex;
                        break;
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    return OK;
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
// 对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int que[1000], top = -1, down = -1, vis[30] = {};

    for (int i = 0; i < G.vexnum; ++i)
    {
        if (!vis[i])
            que[++top] = i;
        while (down != top)
        {
            int v = que[++down];
            if (!vis[v])
            {
                visit(G.vertices[v].data);
                vis[v] = 1;

                ArcNode *p = G.vertices[v].firstarc;
                while (p)
                {
                    if (!vis[p->adjvex])
                        que[++top] = p->adjvex;
                    p = p->nextarc;
                }
            }
        }
    }
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
// 将图的数据写入到文件FileName中
{
    FILE *fp = fopen(FileName, "w");
    if (!fp)
        return ERROR;

    // 保存图的基本信息
    fprintf(fp, "%d %d %d\n", G.vexnum, G.arcnum, G.kind);

    // 保存所有顶点
    for (int i = 0; i < G.vexnum; ++i)
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);

    // 写边
    for (int i = 0; i < G.vexnum; ++i)
    {
        ArcNode *stack[100]; // 假设某个顶点最多100条边
        int top = 0;
        ArcNode *p = G.vertices[i].firstarc;

        // 用数组模拟栈存储边
        while (p)
        {
            stack[top++] = p;
            p = p->nextarc;
        }

        // 逆序写出
        while (top > 0)
        {
            ArcNode *q = stack[--top];
            fprintf(fp, "%d %d\n", i, q->adjvex);
        }
    }

    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
// 读入文件FileName的图数据，创建图的邻接表
{
    FILE *fp = fopen(FileName, "r");
    if (!fp)
        return ERROR;

    fscanf(fp, "%d %d %d\n", &G.vexnum, &G.arcnum, &G.kind);

    // 读取顶点
    for (int i = 0; i < G.vexnum; ++i)
    {
        fscanf(fp, "%d %s\n", &G.vertices[i].data.key, &G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
    }

    // 读入边
    int u, v;
    while (fscanf(fp, "%d %d\n", &u, &v) == 2)
    {
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = v;
        p->nextarc = G.vertices[u].firstarc;
        G.vertices[u].firstarc = p;
    }

    fclose(fp);
    return OK;
}

vector<int> dijkstra(ALGraph &G, KeyType v)
{
    int start = LocateVex(G, v);
    vector<int> vis(G.vexnum, 0); // 记录这个点访问过没有
    vector<int> d(G.vexnum, 1e9); // 记录到v点的距离
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({d[start] = 0, start});

    while (!pq.empty())
    {
        int w = pq.top().first, x = pq.top().second;
        pq.pop();
        if (vis[x])
            continue;
        vis[x] = true;

        ArcNode *p = G.vertices[x].firstarc;
        while (p)
        {
            int y = p->adjvex;
            if (d[x] + 1 < d[y])
            {
                pq.push({d[y] = d[x] + 1, y});
            }
            p = p->nextarc;
        }
    }

    return d;
}

vector<VertexType> VerticesSetLessThanK(ALGraph &G, KeyType v, int k)
// 操作结果是返回与顶点v距离小于k的顶点集合；
{
    vector<VertexType> ans;

    vector<int> d = dijkstra(G, v);
    for (int i = 0; i < d.size(); ++i)
        if (d[i] < k)
            ans.push_back(G.vertices[i].data);

    return ans;
}

int ShortestPathLength(ALGraph &G, KeyType v, KeyType w)
// 初始条件是图G存在；操作结果是返回顶点v与顶点w的最短路径的长度
{
    int pos1 = LocateVex(G, v), pos2 = LocateVex(G, w);
    if (pos1 == -1 || pos2 == -1)
        return -1;
    vector<int> d = dijkstra(G, v);
    return d[pos2] == (int)1e9 ? -2 : d[pos2];
}

void DFS(ALGraph &G, int u, vector<int> &vis)
// 从顶点 u 开始深度优先搜索，标记访问的顶点
{
    vis[u] = 1;
    ArcNode *p = G.vertices[u].firstarc;
    while (p)
    {
        int v = p->adjvex;
        if (!vis[v])
            DFS(G, v, vis);
        p = p->nextarc;
    }
}

int ConnectedComponentsNums(ALGraph &G)
// 操作结果：返回图G的所有连通分量的个数（仅适用于无向图）
{
    if (G.kind != UDG && G.kind != UDN)
    {
        printf( "该函数仅适用于无向图。" );
        return -1;
    }

    vector<int> vis(G.vexnum, 0); // 访问标记
    int cnt = 0;

    for (int i = 0; i < G.vexnum; ++i)
    {
        if (!vis[i])
        {
            ++cnt;
            DFS(G, i, vis);
        }
    }

    return cnt;
}

void PrintGraph(ALGraph &G)
{
    printf("-----------------------------------------------\n");
    printf("顶点数: %d, 边数: %d\n", G.vexnum, G.arcnum);
    printf("图类型: ");
    switch (G.kind)
    {
    case DG:
        printf("有向图\n");
        break;
    case DN:
        printf("有向网\n");
        break;
    case UDG:
        printf("无向图\n");
        break;
    case UDN:
        printf("无向网\n");
        break;
    default:
        printf("未知类型\n");
        break;
    }

    for (int i = 0; i < G.vexnum; ++i)
    {
        printf("[%d]%d, \"%s\"", i, G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            printf(" --> %d", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
    printf("-----------------------------------------------\n");
    printf("\n");
}

void InitGraphLists(GRAPHLISTS &Lists)
{
    Lists.elem = (GraphEntry *)malloc(init_size * sizeof(GraphEntry));
    Lists.length = 0;
    Lists.listsize = init_size;
}

// 添加图
status AddGraph(GRAPHLISTS &Lists, char *name)
{
    if (Lists.length == Lists.listsize)
    {
        // 扩容
        GraphEntry *newelem = (GraphEntry *)realloc(Lists.elem, (Lists.listsize + init_size) * sizeof(GraphEntry));
        if (!newelem)
            return overflow;

        Lists.elem = newelem;
        Lists.listsize += init_size;
    }

    // 初始化空图指针
    Lists.elem[Lists.length].G = NULL;
    strcpy(Lists.elem[Lists.length].name, name);
    ++Lists.length;
    return OK;
}

// 删除图
status RemoveGraph(GRAPHLISTS &Lists, char *name)
{
    for (int i = 0; i < Lists.length; ++i)
    {
        if (strcmp(Lists.elem[i].name, name) == 0)
        {
            // 释放图结构内存（需要你自己实现 DestroyGraph）
            if (Lists.elem[i].G){
                DestroyGraph(*Lists.elem[i].G);
                free(Lists.elem[i].G);
            }
            // 元素前移
            for (int j = i; j < Lists.length - 1; ++j)
                Lists.elem[j] = Lists.elem[j + 1];

            --Lists.length;
            return OK;
        }
    }
    return ERROR; // 未找到
}

// 查找图，成功返回逻辑序号（从1开始），失败返回0
int LocateGraph(GRAPHLISTS &Lists, char *name)
{
    for (int i = 0; i < Lists.length; ++i)
        if (strcmp(Lists.elem[i].name, name) == 0)
            return i + 1;
    return 0;
}

void show1()
{
    printf("\n");
    printf("     Menu for Linear Table Type On Sequence Structure \n");
    printf("-----------------------------------------------------------\n");
    printf("                   请选择你要操作的类型：\n");
    printf("           1. 单图              2.多图 \n");
    printf("           0. 退出 \n");
    printf("-----------------------------------------------------------\n");
    printf("                   请选择你的操作[0~2]:");
}

void show2(ALGraph G)
{
    // system("cls");
    printf("\n");
    printf("      Menu for Linear Table On Sequence Structure         \n");
    printf("----------------------------------------------------------\n");
    printf("    	  1. CreateCraph         2. DestroyGraph         \n");
    printf("    	  3. LocateVex           4. PutVex           \n");
    printf("    	  5. FirstAdjVex         6. NextAdjVex                \n");
    printf("    	  7. InsertVex           8. DeleteVex            \n");
    printf("    	  9. InsertArc           10.DeleteArc            \n");
    printf("    	  11. DFSTraverse        12.BFSTraverse       \n");
    printf("    	  13. VerticesSetLessThanK                \n");
    printf("    	  14. ShortestPathLength                  \n");
    printf("    	  15. ConnectedComponentsNums                 \n");
    printf("    	  16. SaveGraph          17.LoadGraph          \n");
    printf("    	  0.  Exit                20.change type \n");
    printf("ps:本系统在执行完一个功能后要再随便输出个字符才能再次显示菜单欧\n");
    printf("-----------------------------------------------------------\n");
    printf("图实时预览:\n");
    if (G.vexnum == 0)
        printf("图不存在 \n");
    else
        PrintGraph(G);
    printf("\n            请选择你的操作[0~20]:");
}

void show3()
{
    printf("\n");
    printf("         Menu for Linear Table On Sequence Structure        \n");
    printf("---------------------------------------------------------- \n");
    printf("    	  1. AddGraph         2. RemoveGraph                \n");
    printf("    	  3. LocateGraph      4. operator single Graph     \n");
    printf("    	  0. Exit             \n");
    printf("ps:本系统在执行完一个功能后要再随便输出个字符才能再次显示菜单欧\n");
    printf("-----------------------------------------------------------\n");
    printf("\n            请选择你的操作[0~4]:");
}

void Traverse(GRAPHLISTS Lists){
    for(int i=0;i<Lists.length;i++){
        printf("%d.%s\n",i+1,Lists.elem[i].name);
    }
}