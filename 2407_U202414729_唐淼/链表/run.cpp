#include"def.h"

LinkList L=NULL;;
LISTS Lists;

int main(void){
    int mode=0;
    show1();
    while(1){
        scanf("%d",&mode);
        switch (mode)
        {
        case 1:
            main1(L);    //单线性表操作
            break;
        case 2:
            main2(Lists);    //多线性表管理
            break;
        case 0:     // 退出系统
            printf("感谢使用系统，再见!\n");
            return 0;    
        default:
            printf("无效的选择，请重新输入!\n");
        }
        show1();
    }
}

int main1(LinkList &L){       //单个线性表操作系统
    ElemType e=0;
    int op=1,i=0;
    status flag=0;
    while(op){
        show2();
        scanf("%d",&op);
        switch(op){
            case 1: //创建线性表
                if(InitList(L)==OK) printf("线性表创建成功！\n");
                else printf("线性表创建失败！\n");
                getchar();getchar();    //清除输入列多余的换行符及其他字符
                break;
            case 2: //销毁线性表   
                if(DestroyList(L)==OK) printf("线性表销毁成功！\n");  
                else printf("线性表销毁失败！");
                getchar();getchar();
                break;
            case 3: //清空线性表
                flag==ClearList(L);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else if(flag==OK) printf("线性表清空成功！\n");     
                getchar();getchar();
                break;
            case 4:  //判断线性表是否为空
                flag=ListEmpty(L);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else if(flag==TRUE) printf("线性表为空！\n");
                else printf("线性表不为空！\n") ;
                getchar();getchar();
                break;
            case 5: //获得线性表长度
                flag=ListLength(L);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else printf("线性表长度为%d!\n",flag);     
                getchar();getchar();
                break;
            case 6:  //获得指定位置线性表元素
                printf("请输入你所要获得的元素位置：");
                scanf("%d",&i);
                flag=GetElem(L,i,e);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else {                    
                    while(flag==ERROR){
                        printf("请输入合法的位置\n");
                        printf("请重新输入你要获得的元素位置：");
                        scanf("%d",&i);                      
                    }
                    printf("第%d个数据元素为%d\n",i,e);
                }
                getchar();getchar();
                break;
            case 7: //定位指定元素
                printf("请输入你要查找的元素！\n");
                scanf("%d",&e); 
                flag=LocateElem(L,e);  
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else if(flag)  printf("元素%d在第%d个位置\n",e,flag);
                else printf("未查找到该元素%d\n",e);                  
                getchar();getchar();
                break;
            case 8:{ //获得指定元素前驱
                ElemType pre;
                pre=0;
                printf("请输入你要查找前驱的元素：");
                scanf("%d",&e);
                flag=PriorElem(L,e,pre);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else if(flag) printf("%d的前驱为%d",e,pre);
                else printf("未找到前驱！\n");
                getchar();getchar();
                break;
            }
            case 9:{ //获得指定元素后继
                ElemType next;
                next=0;
                printf("请输入你要查找后继的元素：");
                scanf("%d",&e);
                flag=NextElem(L,e,next);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else if(flag) printf("%d的后继为%d",e,next);
                else printf("未找到后继！\n"); 
                getchar();getchar();
                break;
            }
            case 10:  //插入元素
                printf("请输入你要插入的元素以及要插入的位置！");
                scanf(" %d %d",&e,&i);
                flag=ListInsert(L,i,e);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else if(flag==OK) printf("ListInsert功能实现成功！");
                else printf("ListInsert功能实现失败！");
                getchar();getchar();
                break;
            case 11:  //删除指定位置元素  
                printf("请输入你要删除的元素位置！");
                scanf(" %d",&i);
                flag=ListDelete(L,i,e);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else if(flag==OK) 
                printf("ListDelete功能实现成功！\n删除的元素为%d!\n",e);
                else printf("ListDelete功能实现失败！");
                getchar();getchar();
                break;
            case 12:  //遍历线性表  
                if(!L) printf("线性表是空表！\n");
                else printf("线性表内容如下：\n");
                ListTraverse(L);
                getchar();getchar();
                break;
            case 13:  //翻转线性表
                flag=ReverseList(L);
                if(flag==INFEASIBLE) printf("线性表不存在！\n");
                else printf("线性表反转成功！\n");
                getchar();getchar();
                break;
            case 14: //删除倒数第i个位置的元素
                printf("请输入你要删除的倒数第i个结点！\n");
                scanf("%d",&i);
                flag=RemoveNthFromEnd(L,i,e);
                if(flag==INFEASIBLE) printf("线性表不存在或线性表为空！\n");
                else printf("RemoveNthFromEnd功能实现成功！\n删除的元素为%d!\n",e);
                getchar();getchar();
                break;
            case 15:  //线性表排序
                if(SortList(L)==INFEASIBLE) printf("线性表不存在或线性表为空！\n");
                else printf("SortList功能已实现！");
                getchar();getchar();
                break;
            case 16:{  //将线性表保存到文件
                printf("请输入文件名：");
                char filename[200];
                scanf("%s",filename);
                flag=SaveList(L,filename);
                if(flag==INFEASIBLE)
                printf("仅能对空表或者不存在的线性表进行写文件操作！ \n");
                else if(flag==OK)
                printf("写入完毕！\n"); 
                getchar();getchar();
                break;
            }
            case 17:{   //读取文件保存到线性表
                printf("请输入文件名：");
                char filename[200];
                scanf("%s",filename);
                flag=LoadList(L,filename);
                if(flag==INFEASIBLE)
                printf("不能对已存在的线性表进行读文件操作！ \n");
                else if(flag==OK)
                printf("读入完毕！\n"); 
                getchar();getchar();
                break;
            }
            case 0: //结束系统
                break;
        }//end of switch
    }//end of while
    printf("感谢使用本系统，再见！\n");
    return 0;
}//end of main()

int main2(LISTS &Lists) {    //多线性表管理系统
    extern LinkList L;
    Lists.head=NULL;
    Lists.tail=Lists.head;
    Lists.length=0;
    int choice=1;
    char name[30];
    int elem, pos, index;

    while (choice) {
        show3();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // 添加新线性表
                printf("请输入线性表名称: ");
                scanf("%s", name);
                if (AddList(Lists, name))
                printf("线性表 %s 添加成功!\n", name);
                else
                printf("添加失败!\n");
                getchar();getchar();
                break;
                
            case 2: // 删除线性表
                printf("请输入要删除的线性表名称: ");
                scanf("%s", name);
                if (RemoveList(Lists, name)==OK){
                    printf("线性表 %s 删除成功!\n", name);
                } else {
                    printf("删除失败，未找到该线性表!\n");
                }
                getchar();getchar();
                break;
                
            case 3: // 查找线性表
                printf("请输入要查找的线性表名称: ");
                scanf("%s", name);
                index = LocateList(Lists, name);
                if (index) {
                    printf("成功找到线性表%s，线性表在第%d个位置！\n",name,index);

                } else {
                    printf("未找到线性表 %s\n", name);
                }
                getchar();getchar();
                break;
                
            case 4: // 操作单个线性表
                displayAllLists(Lists);
                printf("请输入想要单独操作的线性表逻辑序号：");
                int num;
                scanf("%d", &num);
                if (num < 0 || num > Lists.length)
                    printf("序号不合法！\n");
                else
                {
                    ListNode *p=Lists.head;
                    for(int pos=1;pos<num&&p!=NULL;pos++)
                    p=p->next;
                    L=p->List.L;
                    main1(L);
                }  
                L=NULL;
                getchar();getchar();
                break;  

            case 0: // 退出系统
                break;    
                           
            default:
                printf("无效的选择，请重新输入!\n");
                break;
        }
    }
    printf("感谢使用系统，再见!\n");
    return 0;
}