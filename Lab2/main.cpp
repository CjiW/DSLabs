#include <cstdio>
#include <malloc.h>

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

status InitList(LinkList & L);
status DestroyList(LinkList & L);
status ClearList(LinkList&L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType& e);
int LocateElem(LinkList L,ElemType e); //简化过
status PriorElem(LinkList L,ElemType cur,ElemType &pre_e);
status NextElem(LinkList,ElemType cur,ElemType&next_e);
status ListInsert(LinkList&L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType& e);
status ListTraverse(LinkList L);
int main(){
    LinkList L;  int op=1,tmp;
    char filename[100];
    while(op){
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       7. LocateElem\n");
        printf("    	  2. DestroyList8. PriorElem\n");
        printf("    	  3. ClearList       9. NextElem \n");
        printf("    	  4. ListEmpty     10. ListInsert\n");
        printf("    	  5. ListLength     11. ListDelete\n");
        printf("    	  6. GetElem       12. ListTraverse\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                //printf("\n----IntiList功能待实现！\n");
                switch (InitList(L)) {
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
                switch (DestroyList(L)) {
                    case OK:
                        printf("链表销毁成功！\n");break;
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                }
                getchar();getchar();
                break;
            case 3:
                // printf("\n----ClearList功能待实现！\n");
                switch (ClearList(L)) {
                    case OK:
                        printf("链表清空成功！\n");break;
                    case INFEASIBLE:
                        printf("链表未初始化！\n");break;
                }
                getchar();getchar();
                break;
            case 4:
                // printf("\n----ListEmpty功能待实现！\n");
                switch (ListEmpty(L)) {
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
                if ((tmp=ListLength(L))==INFEASIBLE) printf("链表未初始化！\n");
                else printf("链表长度为%d。\n",tmp);
                getchar();getchar();
                break;
            case 6:
                // printf("\n----GetElem功能待实现！\n");
                printf("");//TODO
                // switch (GetElem()) {
                //
                // }
                getchar();getchar();
                break;
            case 7:
                printf("\n----LocateElem功能待实现！\n");
                getchar();getchar();
                break;
            case 8:
                printf("\n----PriorElem功能待实现！\n");
                getchar();getchar();
                break;
            case 9:
                printf("\n----NextElem功能待实现！\n");
                getchar();getchar();
                break;
            case 10:
                printf("\n----ListInsert功能待实现！\n");
                getchar();getchar();
                break;
            case 11:
                printf("\n----ListDelete功能待实现！\n");
                getchar();getchar();
                break;
            case 12:
                //printf("\n----ListTrabverse功能待实现！\n");
                ListTraverse(L);
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
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
    LNode *p=L->next;
    while (p){
        printf("%d ",p->data);
        p=p->next;
    }
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
