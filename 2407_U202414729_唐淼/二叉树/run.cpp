#include"def.h"
BiTree T;
LISTS Lists;
unordered_set<string> namehash; // 用于防止多二叉树管理时出现两个相同的二叉树树名

void operator1(BiTree &T)
{
    int op2;
    show2(T);
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
            if (T != NULL)
                printf("二叉树已存在，请勿重复创建\n");
            else
            {
                // 创建二叉树
                TElemType definition[100];
                int i = 0;
                do
                {
                    scanf("%d%s", &definition[i].key, definition[i].others);
                } while (definition[i++].key != -1);
                createinit();
                status j = CreateBiTree(T, definition);
                if (j == ERROR)
                    printf("关键字重复，创建失败\n");
                else if (j == overflow)
                    printf("内存溢出，创建失败\n");
                else
                    printf("创建成功！\n");
            }
        }
        else if (op2 == 16)
        {
            if (T != NULL)
                printf("二叉树已存在，请勿重复创建\n");
            else
            {
                printf("请输入文件名：");
                char filename[200];
                scanf("%s", filename);
                status j = LoadBiTree(T, filename);
                if (j == ERROR)
                    printf("文件打开失败！ \n");
                else if (j == OK)
                    printf("读入完毕！ \n");
            }
        }
        else
        {
            // 现在对于所有操作来说二叉树都应该存在，所以一次性判断二叉树是否不存在
            if (T == NULL)
            {
                printf("不能对不存在的二叉树进行操作！ \n");
            }
            else if (op2 == 2)
            {

                DestroyBiTree(T);
                printf("销毁成功！ \n");
            }
            else if (op2 == 3)
            {
                ClearBiTree(T);
                printf("清空成功！ \n");
            }
            else if (op2 == 4)
            {
                status j = BiTreeEmpty(T);
                if (j == TRUE)
                    printf("二叉树是空哒！ \n");
                else if (j == FALSE)
                    printf("二叉树不是空的！\n");
            }
            else if (op2 == 5)
            {
                int j = BiTreeDepth(T);
                printf("二叉树的深度是%d\n", j);
            }
            else if (op2 == 6)
            {
                printf("想要获得哪个关键字对应的结点：");
                KeyType e;
                scanf("%d", &e);
                BiTNode *j = LocateNode(T, e);
                if (j == NULL)
                    printf("找不到该节点 \n");
                else
                    printf("这个节点是：%d %s\n", j->data.key, j->data.others);
            }
            else if (op2 == 7)
            {
                printf("输入想要赋值的节点关键字以及赋予的值：");
                KeyType e;
                TElemType value;
                scanf("%d %d %s", &e, &value.key, &value.others);
                status j = Assign(T, e, value);
                if (j == ERROR)
                    printf("没有找到想要赋值的节点 \n");
                else if (j == ERROR2)
                    printf("赋值的关键字不唯一，赋值失败  \n");
                else
                    printf("赋值成功！\n");
            }
            else if (op2 == 8)
            {
                printf("想要获得哪个关键字对应结点的兄弟节点：");
                KeyType e;
                scanf("%d", &e);

                // 先判断这个点自己在不在
                BiTNode *i = LocateNode(T, e);
                if (i == NULL)
                    printf("找不到对应关键字的节点 \n");
                else
                {
                    // 找兄弟节点
                    BiTNode *j = GetSibling(T, e);
                    if (j == NULL)
                        printf("该兄弟节点不存在 \n");
                    else
                        printf("这个节点的兄弟节点是：%d %s\n", j->data.key, j->data.others);
                }
            }
            else if (op2 == 9)
            {
                printf("依次输入被插入的节点关键字，插入方向，插入的节点值：");
                KeyType e;
                int LR;
                TElemType c;
                scanf("%d %d %d %s", &e, &LR, &c.key, &c.others);
                status j = InsertNode(T, e, LR, c);
                if (j == overflow)
                    printf("内存溢出，插入失败 \n");
                else if (j == ERROR)
                    printf("没有找到被插入的节点 \n");
                else if (j == ERROR2)
                    printf("插入节点的关键字不唯一，插入失败  \n");
                else
                    printf("插入成功！\n");
            }
            else if (op2 == 10)
            {
                printf("输入想要删除的节点的关键字：");
                KeyType e;
                scanf("%d", &e);
                status j = DeleteNode(T, e);
                if (j == ERROR)
                    printf("找不到要删除的节点 \n");
                else
                    printf("删除成功 ");
            }
            else if (op2 == 11)
            {
                printf("二叉树先序遍历结果如下:\n");
                PreOrderTraverse(T, visit);
            }
            else if (op2 == 12)
            {
                printf("二叉树中序遍历结果如下:\n");
                InOrderTraverse(T, visit);
            }
            else if (op2 == 13)
            {
                printf("二叉树后序遍历结果如下:\n");
                PostOrderTraverse(T, visit);
            }
            else if (op2 == 14)
            {
                printf("二叉树按层遍历结果如下:\n");
                LevelOrderTraverse(T, visit);
            }
            else if (op2 == 15)
            {
                printf("请输入文件名：");
                char filename[200];
                scanf("%s", filename);
                status j = SaveBiTree(T, filename);
                if (j == ERROR)
                    printf("文件打开失败！ \n");
                else if (j == OK)
                    printf("写入完毕！ \n");
            }
            else if (op2 == 17)
            {
                printf("最长路径为%d\n", MaxPathSum(T));
            }
            else if (op2 == 18)
            {
                printf("请输入想要寻找最近公共祖先的2个节点的关键字:");
                KeyType e1, e2;
                scanf("%d %d", &e1, &e2);
                BiTNode *p = LowestCommonAncestor(T, e1, e2);
                if (p == NULL)
                    printf("没有最近的公共祖先\n");
                else
                    printf("最近的公共祖先是%d %s\n", p->data.key, p->data.others);
            }
            else if (op2 == 19)
            {
                InvertTree(T);
                printf("翻转成功！\n");
            }
        }
        getchar(); // 读取掉输入去残留的换行符
        getchar(); // 使结果在屏幕上保持一段时间
        show2(T);
        scanf("%d", &op2);
        printf("\n");
    }
    return;
}

void operator2(LISTS &Lists)
{
    InitLists(Lists);
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
            printf("请输入新建二叉树树名：");
            char name[200];
            scanf("%s", name);
            string sname = name;
            if (namehash.count(sname) != 0)
                printf("名称已存在，创建失败！\n");
            else
            {
                status j = Addtree(Lists, name);
                if (j == OK)
                    printf("创建成功！\n");
                else
                    printf("内存溢出，创建失败！\n");
                namehash.insert(sname);
            }
        }
        else if (op3 == 2)
        {
            printf("请输入想要移除的二叉树树名：");
            char name[200];
            scanf("%s", name);
            string sname = name;
            if (namehash.count(sname) == 0)
                printf("找不到该名称的二叉树，移除失败！\n");
            else
            {
                status j = Removetree(Lists, name);
                if (j == OK)
                    printf("移除成功！\n");
                else
                    printf("移除失败\n");
                namehash.erase(sname);
            }
        }
        else if (op3 == 3)
        {
            printf("请输入想要查询的二叉树树名：");
            char name[200];
            scanf("%s", name);
            status j = Locatetree(Lists, name);
            if (j == 0)
                printf("二叉树树名不存在！\n");
            else
                printf("%s的逻辑序号是%d\n", name, j);
        }
        else if (op3 == 4)
        {
            TraversLists(Lists);
            printf("请输入想要单独操作的二叉树逻辑序号：");
            int num;
            scanf("%d", &num);
            if (num < 0 || num > Lists.length)
                printf("序号不合法！\n");
            else
            {
                T = Lists.elem[num - 1].T;
                operator1(T);
                Lists.elem[num - 1].T = T;
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
    T = NULL;
    while (op1)
    {
        switch (op1)
        {
        case 1:
            operator1(T);
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