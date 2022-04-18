#include <cstdio>
#include <malloc.h>
#include <cstring>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //数据元素类型定义
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
typedef struct {  //线性表的集合类型定义
    struct {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
} LISTS;
LISTS Lists;      //线性表集合的定义Lists
int usingList = 0;
status InitList(LinkList & L);
status DestroyList(LinkList & L);
status ClearList(LinkList&L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType& e);
int LocateElem(LinkList L,ElemType e); //简化过
status PriorElem(LinkList L,ElemType e,ElemType &pre_e);
status NextElem(LinkList,ElemType e,ElemType&next_e);
status ListInsert(LinkList&L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType& e);
status ListTraverse(LinkList L);
status sortList(LinkList L);
LNode *mergeSortList(LNode *head);
LNode *merge(LNode *head1, LNode *head2);
status reverseList(LinkList L);
status RemoveNthFromEnd(LinkList L,int n,ElemType&e);
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList &L, char FileName[]);
status AddList(LISTS &lists, const char ListName[]);
status RemoveList(LISTS &lists, char ListName[]);
int LocateList(LISTS lists, const char ListName[]);
int main(){
    int op=1,tmp;
    ElemType e;
    char filename[100],s[30];
    for (auto &i: Lists.elem) {
        i.L = nullptr;
    }
    Lists.length = 1;
    strcpy(Lists.elem[usingList].name, "Default");
    while(op){
        system("cls");
        printf("\n\n");
        printf("    ╔════════════════════════════════════════════════╗\n");
        printf("    ║               %d-%-10s                     ║\n", usingList, Lists.elem[usingList].name);
        printf("    ╟────────────────────────────────────────────────╢\n");
        printf("    ║     1. InitList           2. DestroyList       ║\n");
        printf("    ║     3. ClearList          4. ListEmpty         ║\n");
        printf("    ║     5. ListLength         6. GetElem           ║\n");
        printf("    ║     7. LocateElem         8. PriorElem         ║\n");
        printf("    ║     9. NextElem           10. ListInsert       ║\n");
        printf("    ║     11. ListDelete        12. ListTraverse     ║\n");
        printf("    ║     13. sortList          14. reverseList      ║\n");
        printf("    ║     15. SaveList          16. LoadList         ║\n");
        printf("    ║     17. AddList           18. RemoveList       ║\n");
        printf("    ║     19. ChangeList        20. LocateList       ║\n");
        printf("    ║     21. RemoveNthFromEnd  0. Exit              ║\n");
        printf("    ╚════════════════════════════════════════════════╝\n");
        printf("    请选择你的操作[0~20]:");
        scanf_s("%d",&op);
        switch(op){
            case 1:
                //printf("\n----IntiList功能待实现！\n");
                switch (InitList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("链表创建成功！\n");break;
                    case OVERFLOW:
                        printf("内存分配失败！\n");break;
                    case INFEASIBLE:
                        printf("链表已存在！\n");break;
                }
                getchar();getchar();
                break;
            case 2:
                // printf("\n----DestroyList功能待实现！\n");
                switch (DestroyList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("链表销毁成功！\n");break;
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                }
                getchar();getchar();
                break;
            case 3:
                // printf("\n----ClearList功能待实现！\n");
                switch (ClearList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("链表清空成功！\n");break;
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                }
                getchar();getchar();
                break;
            case 4:
                // printf("\n----ListEmpty功能待实现！\n");
                switch (ListEmpty(Lists.elem[usingList].L)) {
                    case TRUE:
                        printf("链表为空。\n");break;
                    case FALSE:
                        printf("链表不为空。\n");break;
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                }
                getchar();getchar();
                break;
            case 5:
                // printf("\n----ListLength功能待实现！\n");
                if ((tmp=ListLength(Lists.elem[usingList].L))==INFEASIBLE) printf("链表未初始化！\n");
                else printf("链表长度为%d。\n",tmp);
                getchar();getchar();
                break;
            case 6:
                // printf("\n----GetElem功能待实现！\n");
                printf("请输入元素位序:\n");
                scanf("%d",&tmp);
                switch (GetElem(Lists.elem[usingList].L,tmp,e)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                    case ERROR:
                        printf("位序%d非法！\n",tmp);break;
                    case OK:
                        printf("位序为%d的元素为%d。\n",tmp,e);break;
                }
                getchar();getchar();
                break;
            case 7:
                // printf("\n----LocateElem功能待实现！\n");
                printf("请输入元素:\n");
                scanf("%d",&e);
                switch (tmp=LocateElem(Lists.elem[usingList].L,e)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                    case ERROR:
                        printf("元素%d不存在！\n",e);break;
                    default:
                        printf("元素%d的位序为%d。\n",e,tmp);break;
                }
                getchar();getchar();
                break;
            case 8:
                // printf("\n----PriorElem功能待实现！\n");
                printf("请输入当前元素:\n");
                scanf("%d",&e);
                switch (PriorElem(Lists.elem[usingList].L,e,e)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                    case ERROR:
                        printf("元素%d前驱不存在！\n",e);break;
                    case OK:
                        printf("前驱为%d。\n",e);break;
                }
                getchar();getchar();
                break;
            case 9:
                // printf("\n----NextElem功能待实现！\n");
                printf("请输入当前元素:\n");
                scanf("%d",&e);
                switch (NextElem(Lists.elem[usingList].L,e,e)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                    case ERROR:
                        printf("元素%d后继不存在！\n",e);break;
                    case OK:
                        printf("后继为%d。\n",e);break;
                }
                getchar();getchar();
                break;
            case 10:
                // printf("\n----ListInsert功能待实现！\n");
                printf("请输入位序:\n");
                scanf("%d",&tmp);
                printf("请输入元素:\n");
                scanf("%d",&e);
                switch (ListInsert(Lists.elem[usingList].L,tmp,e)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                    case ERROR:
                        printf("位序%d非法！\n",tmp);break;
                    case OK:
                        printf("元素%d插入成功！\n",e);break;
                    case OVERFLOW:
                        printf("内存分配失败！\n");break;
                }
                getchar();getchar();
                break;
            case 11:
                // printf("\n----ListDelete功能待实现！\n");
                printf("请输入位序:\n");
                scanf("%d",&tmp);
                switch (ListDelete(Lists.elem[usingList].L,tmp,e)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                    case ERROR:
                        printf("位序%d非法！\n",tmp);break;
                    case OK:
                        printf("%d号元素%d删除成功！\n",tmp,e);break;
                }
                getchar();getchar();
                break;
            case 12:
                //printf("\n----ListTrabverse功能待实现！\n");
                switch (ListTraverse(Lists.elem[usingList].L)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");
                        break;
                    case ERROR:
                        printf("链表为空！\n");
                        break;
                }
                getchar();getchar();
                break;
            case 13:
                if (sortList(Lists.elem[usingList].L) == OK) {
                    printf("排序成功！\n");
                } else {
                    printf("链表未初始化！\n");
                }
                getchar();
                getchar();
                break;
            case 14:
                switch (reverseList(Lists.elem[usingList].L)) {
                    case INFEASIBLE:
                        printf("链表未初始化！\n");
                        break;
                    case OK:
                        printf("翻转成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 15:
                printf("请输入文件路径:\n");
                scanf("%s", filename);
                switch (SaveList(Lists.elem[usingList].L, filename)) {
                    case ERROR:
                        printf("文件打开失败！\n");
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                    case OK:
                        printf("保存成功！\n");
                        break;
                }
                getchar();getchar();
                break;
            case 16:
                printf("请输入文件路径:\n");
                scanf("%s", filename);
                switch (LoadList(Lists.elem[usingList].L, filename)) {
                    case ERROR:
                        printf("文件打开失败！\n");
                        break;
                    case INFEASIBLE:
                        printf("线性表已存在！\n");
                        break;
                    case OVERFLOW:
                        printf("内存分配失败！\n");
                        break;
                    case OK:
                        printf("加载成功！\n");
                        break;
                }
                getchar();getchar();
                break;
            case 17:
                printf("请输入要创建的表名:\n");
                scanf_s("%s", s);
                switch (AddList(Lists, s)) {
                    case OK:
                        printf("创建成功！\n");
                        break;
                    case OVERFLOW:
                        printf("当前表过多！\n");
                        break;
                    case ERROR:
                        printf("表已存在！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 18:
                printf("请输入要删除的表名:\n");
                scanf_s("%s", s);
                if (RemoveList(Lists, s) == ERROR)printf("删除失败！\n");
                else printf("删除成功！\n");
                getchar();
                getchar();
                break;
            case 19:
                printf("请输入要使用的表名:\n");
                scanf_s("%s", s);
                tmp = LocateList(Lists, s);
                if (tmp) {
                    usingList = tmp - 1;
                    printf("改变使用表成功！\n当前表:%d-%s\n", usingList, Lists.elem[usingList].name);
                } else {
                    printf("表不存在！\n");
                }
                getchar();
                getchar();
                break;

            case 20:
                printf("请输入表名:\n");
                scanf_s("%s", s);
                tmp = LocateList(Lists, s);
                if (!tmp) {
                    printf("%s表不存在！\n", s);
                } else {
                    printf("%s是第%d个表。\n", s, tmp - 1);
                }
                getchar();
                getchar();
                break;
            case 21:
                printf("请输入结点的倒数序号:\n");
                scanf_s("%d",&tmp);
                switch (RemoveNthFromEnd(Lists.elem[usingList].L, tmp,e)) {
                    case ERROR:
                        printf("序号%d非法！\n",tmp);break;
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                    case OK:
                        printf("倒数第%d个结点%d删除成功！\n",tmp,e);break;
                }
                getchar();
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    getchar();
    getchar();
    return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
status InitList(LinkList & L){
    if(L)return INFEASIBLE;
    L=(LNode*)malloc(sizeof(LNode));
    if(!L)return OVERFLOW;
    L->data=0;
    L->next=nullptr;
    return OK;
}
status DestroyList(LinkList & L){
    if(!L)return INFEASIBLE;
    LNode*p=L,*q;
    while (p){
        q=p->next;
        free(p);
        p=q;
    }
    L=nullptr;
    return OK;
}
status ClearList(LinkList&L){
    if(!L)return INFEASIBLE;
    LNode*p=L->next,*q;
    while (p){
        q=p->next;
        free(p);
        p=q;
    }
    L->next=nullptr;
    return OK;
}
status ListEmpty(LinkList L){
    if(!L)return INFEASIBLE;
    if(L->next)return FALSE;
    return TRUE;
}
int ListLength(LinkList L){
    if(!L)return INFEASIBLE;
    int len=0;
    LNode *p=L->next;
    while (p){
        len++;
        p=p->next;
    }
    return len;
}
status GetElem(LinkList L,int i,ElemType &e){
    if(!L)return INFEASIBLE;
    if(i<=0)return ERROR;
    LNode *p=L;
    for (int j = 0; j < i; j++) {
        if(!p)return ERROR;
        p=p->next;
    }
    e=p->data;
    return OK;
}
int LocateElem(LinkList L,ElemType e){
    if(!L)return INFEASIBLE;
    LNode *p=L->next;
    int i=ERROR,j=1;
    while (p){
        if(p->data==e){
            i=j;
            break;
        }
        p=p->next;j++;
    }
    return i;
}
status PriorElem(LinkList L,ElemType e,ElemType &pre){
    if(!L)return INFEASIBLE;
    LNode *p=L->next;
    if(!p)return ERROR;
    int i=ERROR,j=1;
    while (p->next){
        if(p->next->data==e){
            i=OK;
            pre=p->data;
            break;
        }
        p=p->next;j++;
    }
    return i;
}
status NextElem(LinkList L,ElemType e,ElemType &next){
    if(!L)return INFEASIBLE;
    LNode *p=L->next;
    if(!p)return ERROR;
    int i=ERROR;
    while (p->next){
        if(p->data==e){
            i=OK;
            next=p->next->data;
            break;
        }
        p=p->next;
    }
    return i;
}
status ListInsert(LinkList &L,int i,ElemType e){
    if(!L)return INFEASIBLE;
    if(i<=0)return ERROR;
    LNode *p=L;
    for (int j = 0; j < i-1; j++) {
        p=p->next;
        if(!p)return ERROR;
    }
    auto *newNode=(LNode*)malloc(sizeof(LNode));
    if(!newNode)return OVERFLOW;
    newNode->next=p->next;
    newNode->data=e;
    p->next=newNode;
    return OK;
}
status ListDelete(LinkList &L,int i,ElemType &e){
    if(!L)return INFEASIBLE;
    if(i<=0||!L->next)return ERROR;
    LNode *p=L;
    for (int j = 0; j < i-1; j++) {
        p=p->next;
        if(!p->next)return ERROR;
    }
    e=p->next->data;
    LNode *q=p->next;
    p->next=q->next;
    free(q);
    return OK;
}
status ListTraverse(LinkList L){
    if(!L)return INFEASIBLE;
    if(!L->next)return ERROR;
    printf("\n-----------------All Elem----------------\n");
    LNode *p=L->next;
    while (p){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n-------------------End-------------------\n");
    return OK;
}
status sortList(LinkList L) {
    if(!L)return INFEASIBLE;
    mergeSortList(L);
    return OK;
}
LNode *mergeSortList(LNode *head) {
    if(head == nullptr || head->next == nullptr)return head;
    else{
        //快慢指针找到中间节点
        LNode *fast = head,*slow = head;
        while(fast->next != nullptr && fast->next->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = nullptr;
        fast = mergeSortList(head);//前半段排序
        slow = mergeSortList(slow);//后半段排序
        return merge(fast,slow);
    }

}
LNode *merge(LNode *head1, LNode *head2){
    if(head1 == nullptr)return head2;
    if(head2 == nullptr)return head1;
    LNode *res , *p ;
    if(head1->data < head2->data)
    {res = head1; head1 = head1->next;}
    else{res = head2; head2 = head2->next;}
    p = res;
    while(head1 != nullptr && head2 != nullptr){
        if(head1->data < head2->data){
            p->next = head1;
            head1 = head1->next;
        }
        else{
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if(head1 != nullptr)p->next = head1;
    else if(head2 != nullptr)p->next = head2;
    return res;
}
status reverseList(LinkList L){
    if(!L)return INFEASIBLE;
    if(!L->next||!L->next->next)return OK;
    LNode *p=L->next,*q= nullptr,*m=L->next,*n=L->next->next;
    while (p->next)p=p->next;
    L->next=p;
    while (n!=p){
        m->next=q;
        q=m;m=n;n=n->next;
    }
    n->next=m;
    m->next=q;
    return OK;
}
status SaveList(LinkList L,char FileName[]){
    if(!L)return INFEASIBLE;
    FILE *pw= fopen(FileName,"wb");
    if(!pw)return ERROR;
    LNode *p=L->next;
    while (p){
        fwrite(&p->data,sizeof(int),1,pw);
        p=p->next;
    }
    fclose(pw);
    return OK;
}

status LoadList(LinkList &L,char FileName[]){
    if(L)return INFEASIBLE;
    FILE *pr= fopen(FileName,"rb");
    if(!pr)return ERROR;
    L=(LNode*)malloc(sizeof(LNode));
    if(!L)return OVERFLOW;
    L->data=0;
    L->next=nullptr;
    LNode *p=L;
    while (true){
        auto*newNode=(LNode*)malloc(sizeof(LNode));
        if(!newNode)return OVERFLOW;
        if(!fread(&(newNode->data),sizeof(int),1,pr))break;
        newNode->next=p->next;
        p->next=newNode;
        p=newNode;
    }
    fclose(pr);
    return OK;
}
status AddList(LISTS &lists, const char ListName[]) {
    if (lists.length >= 10)return OVERFLOW;
    if (LocateList(lists, ListName)) return ERROR;
    int i = 0;
    while ((((lists.elem)[lists.length]).name[i] = ListName[i]))i++;
    ((lists.elem)[lists.length]).L = nullptr;
    lists.length++;
    return OK;
}

status RemoveList(LISTS &lists, char ListName[]) {
    int i = LocateList(lists, ListName);
    if (!i) {
        printf("该表不存在！\n");
        return ERROR;
    }
    if (i == usingList + 1) {
        printf("不能删除当前表！\n");
        return ERROR;
    }
    i--;
    if (usingList >= i)usingList--;
    DestroyList(lists.elem[i].L);
    for (; i < lists.length; i++) {
        int j = 0;
        while ((lists.elem[i].name[j] = lists.elem[i + 1].name[j]))j++;
        DestroyList(lists.elem[i].L);
        lists.elem[i].L = lists.elem[i + 1].L;
    }
    lists.length--;
    return OK;

}

int LocateList(LISTS lists, const char ListName[]) {
    for (int i = 0; i < lists.length; i++) {
        if (strcmp(lists.elem[i].name, ListName) != 0)continue;
        return i + 1;
    }
    return 0;
}
status RemoveNthFromEnd(LinkList L,int n,ElemType&e){
    if(!L)return INFEASIBLE;
    if(n<=0)return ERROR;
    LNode *p=L,*q=L;
    for (int i = 0; i < n; i++) {
        q=q->next;
        if(!q)return ERROR;
    }
    q=q->next;
    while (q){
        p=p->next;
        q=q->next;
    }
    q=p->next;
    p->next=p->next->next;
    e=q->data;
    free(q);
    return OK;
}