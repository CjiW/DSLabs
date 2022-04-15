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
        printf("    ║     13. SaveList          14. LoadList         ║\n");
        printf("    ║     15. sortList          16. AddList          ║\n");
        printf("    ║     17. RemoveList        18. ChangeList       ║\n");
        printf("    ║     19. LocateList        0. Exit              ║\n");
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
                    case OK:
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
                        printf("链表未初始化！\n");break;
                    case ERROR:
                        printf("链表为空！\n");break;
                }
                getchar();getchar();
                break;
            case 13:
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
            case 14:
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
            case 16:
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
            case 17:
                printf("请输入要删除的表名:\n");
                scanf_s("%s", s);
                if (RemoveList(Lists, s) == ERROR)printf("删除失败！\n");
                else printf("删除成功！\n");
                getchar();
                getchar();
                break;
            case 18:
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

            case 19:
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
        fread(&(newNode->data),sizeof(int),1,pr);
        if(!newNode->data)break;
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