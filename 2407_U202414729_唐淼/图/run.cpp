#include "def.h"

ALGraph G;
GRAPHLISTS Lists;
unordered_set<string> namehash; // 用于防止多图管理时出现两个相同的图树名

void operator1(ALGraph &G)
{
    int op2;
    show2(G);
    scanf("%d", &op2);
    printf("\n");

    while (op2 != 20)
    {
        if (op2 == 0)
        {
            printf("%s", "感谢使用本系统 ");
            exit(0);
        }
        else if (op2 == 1)
        {
            if (G.vexnum != 0)
                printf("图已存在，请勿重复创建\n");
            else
            {
                // 创建图
                printf("开始创建!\n");
                VertexType V[30];
                KeyType VR[100][2];
                printf("依次输入顶点的关键字以及值：\n");
                int i = 0, ii;
                do
                {
                    scanf("%d%s", &V[i].key, V[i].others);
                } while (V[i++].key != -1);
                i = 0;
                printf("依次输入边：\n");
                do
                {
                    scanf("%d%d", &VR[i][0], &VR[i][1]);
                } while (VR[i++][0] != -1);
                status j = CreateCraph(G, V, VR);
                if (j == ERROR)
                    printf("关键字重复，创建失败\n");
                else if (j == overflow)
                    printf("内存溢出，创建失败 \n");
                else
                    printf("创建成功！\n");
            }
        }
        else if (op2 == 17)
        {
            if (G.vexnum != 0)
                printf("图已存在，请勿重复创建\n");
            else
            {
                printf("请输入文件名：");
                char filename[200];
                scanf("%s", filename);
                status j = LoadGraph(G, filename);
                if (j == ERROR)
                    printf("文件打开失败！ \n");
                else if (j == OK)
                    printf("读入完毕！ \n");
            }
        }
        else
        {
            // 现在对于所有操作来说图都应该存在，所以一次性判断图是否不存在
            if (G.vexnum == 0)
            {
                printf("不能对不存在的图进行操作！ \n");
            }
            else if (op2 == 2)
            {

                DestroyGraph(G);
                printf("销毁成功！\n");
            }
            else if (op2 == 3)
            {
                printf("想要获得哪个关键字对应的顶点位序：");
                KeyType e;
                scanf("%d", &e);
                int j = LocateVex(G, e);
                if (j == -1)
                    printf("找不到该顶点 \n");
                else
                    printf("这个顶点的位序是：%d\n", j);
            }
            else if (op2 == 4)
            {
                printf("输入想要赋值的顶点关键字以及赋予的值：");
                KeyType e;
                VertexType value;
                scanf("%d %d %s", &e, &value.key, &value.others);
                status j = PutVex(G, e, value);
                if (j == ERROR)
                    printf("没有找到想要赋值的顶点 \n");
                else if (j == ERROR2)
                    printf("赋值的关键字不唯一，赋值失败  \n");
                else
                    printf("赋值成功！\n");
            }
            else if (op2 == 5)
            {
                printf("想要获得哪个位序的顶点对应的第一邻接点：");
                int e;
                scanf("%d", &e);

                int j = FirstAdjVex(G, G.vertices[e].data.key);
                if (j == -1)
                    printf("不存在第一邻接点 \n");
                else
                    printf("第一邻接点是：%d\n", j);
            }

            else if (op2 == 6)
            {
                printf("想要获得哪个位序的顶点对应位序顶点的下一邻接点：");
                int v, w;
                scanf("%d %d", &v, &w);

                int j = NextAdjVex(G, G.vertices[v].data.key, G.vertices[w].data.key);
                if (j == -1)
                    printf("不存在下一邻接点 \n");
                else
                    printf("下一邻接点是：%d\n", j);
            }
            else if (op2 == 7)
            {
                printf("输入插入顶点的值：");
                VertexType e;
                scanf("%d %s", &e.key, &e.others);
                status j = InsertVex(G, e);
                if (j == ERROR2)
                    printf("内存溢出，插入失败 \n");
                else if (j == ERROR)
                    printf("插入节点的关键字不唯一，插入失败   \n");
                else
                    printf("插入成功！\n");
            }
            else if (op2 == 8)
            {
                printf("输入想要删除的顶点的关键字：");
                KeyType e;
                scanf("%d", &e);
                status j = DeleteVex(G, e);
                if (j == ERROR)
                    printf("图只有一个顶点，不能删除！\n");
                else if (j == ERROR2)
                    printf("找不到要删除的顶点 \n");
                else
                    printf("删除成功 ");
            }
            else if (op2 == 9)
            {
                printf("输入想要插入的弧（输入2个顶点的关键字）：");
                KeyType a, b;
                scanf("%d %d", &a, &b);
                status j = InsertArc(G, a, b);
                if (j == ERROR)
                    printf("找不到对应关键字的顶点 \n");
                else if (j == ERROR2)
                    printf("插入的边已存在，插入失败  \n");
                else
                    printf("插入成功！\n");
            }
            else if (op2 == 10)
            {
                printf("输入想要删除的弧（输入2个顶点的关键字）：");
                KeyType a, b;
                scanf("%d %d", &a, &b);
                status j = DeleteArc(G, a, b);
                if (j == ERROR)
                    printf("找不到对应关键字的顶点 \n");
                else if (j == ERROR2)
                    printf("不存在要删除的边，\n");
                else
                    printf("删除成功！\n");
            }
            else if (op2 == 11)
            {
                printf("图深度优先搜索遍历结果如下:\n");
                DFSTraverse(G, visit);
            }
            else if (op2 == 12)
            {
                printf("图广度优先搜索遍历结果如下:\n");
                BFSTraverse(G, visit);
            }
            else if (op2 == 13)
            {
                printf("请输入起始顶点v的关键字和最大距离k:");
                KeyType e;
                int k;
                scanf("%d %d", &e, &k);
                if (LocateVex(G, e) == -1)
                    printf("这个起始顶点不存在！\n");
                else
                {
                    vector<VertexType> ans = VerticesSetLessThanK(G, e, k);
                    printf("顶点v距离小于k的顶点集合如下：");
                    for (VertexType i : ans)
                        printf("%d %s ", i.key, i.others);
                    printf("\n");
                }
            }
            else if (op2 == 14)
            {
                printf("请输入起始顶点v和终止顶点的关键字:");
                KeyType a, b;
                int k;
                scanf("%d %d", &a, &b);
                status j = ShortestPathLength(G, a, b);
                if (j == -1)
                    printf("顶点不存在！\n");
                else if (j == -2)
                    printf("路径不存在！\n");
                else
                    printf("顶点%d与顶点%d的最短路径的长度是%d\n", a, b, j);
            }
            else if (op2 == 15)
            {
                printf("图G的所有连通分量的个数是%d\n", ConnectedComponentsNums(G));
            }
            else if (op2 == 16)
            {
                printf("请输入文件名：");
                char filename[200];
                scanf("%s", filename);
                status j = SaveGraph(G, filename);
                if (j == ERROR)
                    printf("文件打开失败！ \n");
                else if (j == OK)
                    printf("写入完毕！ \n");
            }
        }
        getchar(); // 读取掉输入去残留的换行符
        getchar(); // 使结果在屏幕上保持一段时间
        show2(G);
        scanf("%d", &op2);
        printf("\n");
    }
    return;
}

void operator2(GRAPHLISTS &Lists)
{
    InitGraphLists(Lists);
    show3();
    int op3;
    scanf("%d", &op3);
    printf("\n");

    while (1)
    {
        if (op3 == 0)
        {
            printf("%s", "感谢使用本系统 ");
            exit(0);
        }
        else if (op3 == 1)
        {
            printf("请输入新建图名：");
            char name[200];
            scanf("%s", name);
            string sname = name;
            if (namehash.count(sname) != 0)
                printf("名称已存在，创建失败！\n");
            else
            {
                status j = AddGraph(Lists, name);
                if (j == OK)
                    printf("创建成功！\n");
                else
                    printf("内存溢出，创建失败！\n");
                namehash.insert(sname);
            }
        }
        else if (op3 == 2)
        {
            printf("请输入想要移除的图名：");
            char name[200];
            scanf("%s", name);
            string sname = name;
            if (namehash.count(sname) == 0)
                printf("找不到该名称的图，移除失败！\n");
            else
            {
                status j = RemoveGraph(Lists, name);
                if (j == OK)
                    printf("移除成功！\n");
                else
                    printf("移除失败\n");
                namehash.erase(sname);
            }
        }
        else if (op3 == 3)
        {
            printf("请输入想要查询的图名：");
            char name[200];
            scanf("%s", name);
            status j = LocateGraph(Lists, name);
            if (j == 0)
                printf("图名不存在！\n");
            else
                printf("%s的逻辑序号是%d\n", name, j);
        }
        else if (op3 == 4)
        {   
            Traverse(Lists);
            printf("请输入想要单独操作的图逻辑序号：");
            int num;
            scanf("%d", &num);
            if (num < 0 || num > Lists.length)
                printf("序号不合法！\n");
            else
    {
        // 如果图不存在则创建
        if (Lists.elem[num - 1].G == NULL)
        {
            Lists.elem[num - 1].G = (ALGraph*)malloc(sizeof(ALGraph));
            Lists.elem[num - 1].G->vexnum = Lists.elem[num - 1].G->arcnum = 0;
        }
        
        // 操作图
        operator1(*Lists.elem[num - 1].G);
    }
        }
        getchar();
        getchar();
        show3();
        scanf("%d", &op3);
        printf("\n");
    }
}

int main()
{
    int op1;
    show1();
    scanf("%d", &op1);
    G.vexnum = G.arcnum = 0;
    while (op1)
    {
        switch (op1)
        {
        case 1:
            operator1(G);
            break;

        case 2:
            operator2(Lists);
            break;

        case 0:
            printf("%s", "感谢使用本系统 ");
            return 0;
        }
        show1();
        scanf("%d", &op1);
    }
}