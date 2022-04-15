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
typedef int ElemType; //����Ԫ�����Ͷ���
typedef int ElemType;
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
typedef struct {  //���Ա�ļ������Ͷ���
    struct {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
} LISTS;
LISTS Lists;      //���Ա��ϵĶ���Lists
int usingList = 0;
status InitList(LinkList & L);
status DestroyList(LinkList & L);
status ClearList(LinkList&L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType& e);
int LocateElem(LinkList L,ElemType e); //�򻯹�
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
        printf("    �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        printf("    �U               %d-%-10s                     �U\n", usingList, Lists.elem[usingList].name);
        printf("    �c�������������������������������������������������������������������������������������������������f\n");
        printf("    �U     1. InitList           2. DestroyList       �U\n");
        printf("    �U     3. ClearList          4. ListEmpty         �U\n");
        printf("    �U     5. ListLength         6. GetElem           �U\n");
        printf("    �U     7. LocateElem         8. PriorElem         �U\n");
        printf("    �U     9. NextElem           10. ListInsert       �U\n");
        printf("    �U     11. ListDelete        12. ListTraverse     �U\n");
        printf("    �U     13. SaveList          14. LoadList         �U\n");
        printf("    �U     15. sortList          16. AddList          �U\n");
        printf("    �U     17. RemoveList        18. ChangeList       �U\n");
        printf("    �U     19. LocateList        0. Exit              �U\n");
        printf("    �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        printf("    ��ѡ����Ĳ���[0~20]:");
        scanf_s("%d",&op);
        switch(op){
            case 1:
                //printf("\n----IntiList���ܴ�ʵ�֣�\n");
                switch (InitList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("�������ɹ���\n");break;
                    case OVERFLOW:
                        printf("�ڴ����ʧ�ܣ�\n");break;
                    case INFEASIBLE:
                        printf("�����Ѵ��ڣ�\n");break;
                }
                getchar();getchar();
                break;
            case 2:
                // printf("\n----DestroyList���ܴ�ʵ�֣�\n");
                switch (DestroyList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("�������ٳɹ���\n");break;
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                }
                getchar();getchar();
                break;
            case 3:
                // printf("\n----ClearList���ܴ�ʵ�֣�\n");
                switch (ClearList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("������ճɹ���\n");break;
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                }
                getchar();getchar();
                break;
            case 4:
                // printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
                switch (ListEmpty(Lists.elem[usingList].L)) {
                    case TRUE:
                        printf("����Ϊ�ա�\n");break;
                    case FALSE:
                        printf("����Ϊ�ա�\n");break;
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                }
                getchar();getchar();
                break;
            case 5:
                // printf("\n----ListLength���ܴ�ʵ�֣�\n");
                if ((tmp=ListLength(Lists.elem[usingList].L))==INFEASIBLE) printf("����δ��ʼ����\n");
                else printf("������Ϊ%d��\n",tmp);
                getchar();getchar();
                break;
            case 6:
                // printf("\n----GetElem���ܴ�ʵ�֣�\n");
                printf("������Ԫ��λ��:\n");
                scanf("%d",&tmp);
                switch (GetElem(Lists.elem[usingList].L,tmp,e)) {
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                    case ERROR:
                        printf("λ��%d�Ƿ���\n",tmp);break;
                    case OK:
                        printf("λ��Ϊ%d��Ԫ��Ϊ%d��\n",tmp,e);break;
                }
                getchar();getchar();
                break;
            case 7:
                // printf("\n----LocateElem���ܴ�ʵ�֣�\n");
                printf("������Ԫ��:\n");
                scanf("%d",&e);
                switch (tmp=LocateElem(Lists.elem[usingList].L,e)) {
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                    case ERROR:
                        printf("Ԫ��%d�����ڣ�\n",e);break;
                    case OK:
                        printf("Ԫ��%d��λ��Ϊ%d��\n",e,tmp);break;
                }
                getchar();getchar();
                break;
            case 8:
                // printf("\n----PriorElem���ܴ�ʵ�֣�\n");
                printf("�����뵱ǰԪ��:\n");
                scanf("%d",&e);
                switch (PriorElem(Lists.elem[usingList].L,e,e)) {
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                    case ERROR:
                        printf("Ԫ��%dǰ�������ڣ�\n",e);break;
                    case OK:
                        printf("ǰ��Ϊ%d��\n",e);break;
                }
                getchar();getchar();
                break;
            case 9:
                // printf("\n----NextElem���ܴ�ʵ�֣�\n");
                printf("�����뵱ǰԪ��:\n");
                scanf("%d",&e);
                switch (NextElem(Lists.elem[usingList].L,e,e)) {
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                    case ERROR:
                        printf("Ԫ��%d��̲����ڣ�\n",e);break;
                    case OK:
                        printf("���Ϊ%d��\n",e);break;
                }
                getchar();getchar();
                break;
            case 10:
                // printf("\n----ListInsert���ܴ�ʵ�֣�\n");
                printf("������λ��:\n");
                scanf("%d",&tmp);
                printf("������Ԫ��:\n");
                scanf("%d",&e);
                switch (ListInsert(Lists.elem[usingList].L,tmp,e)) {
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                    case ERROR:
                        printf("λ��%d�Ƿ���\n",tmp);break;
                    case OK:
                        printf("Ԫ��%d����ɹ���\n",e);break;
                    case OVERFLOW:
                        printf("�ڴ����ʧ�ܣ�\n");break;
                }
                getchar();getchar();
                break;
            case 11:
                // printf("\n----ListDelete���ܴ�ʵ�֣�\n");
                printf("������λ��:\n");
                scanf("%d",&tmp);
                switch (ListDelete(Lists.elem[usingList].L,tmp,e)) {
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                    case ERROR:
                        printf("λ��%d�Ƿ���\n",tmp);break;
                    case OK:
                        printf("%d��Ԫ��%dɾ���ɹ���\n",tmp,e);break;
                }
                getchar();getchar();
                break;
            case 12:
                //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");
                switch (ListTraverse(Lists.elem[usingList].L)) {
                    case INFEASIBLE:
                        printf("����δ��ʼ����\n");break;
                    case ERROR:
                        printf("����Ϊ�գ�\n");break;
                }
                getchar();getchar();
                break;
            case 13:
                printf("�������ļ�·��:\n");
                scanf("%s", filename);
                switch (SaveList(Lists.elem[usingList].L, filename)) {
                    case ERROR:
                        printf("�ļ���ʧ�ܣ�\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                    case OK:
                        printf("����ɹ���\n");
                        break;
                }
                getchar();getchar();
                break;
            case 14:
                printf("�������ļ�·��:\n");
                scanf("%s", filename);
                switch (LoadList(Lists.elem[usingList].L, filename)) {
                    case ERROR:
                        printf("�ļ���ʧ�ܣ�\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա��Ѵ��ڣ�\n");
                        break;
                    case OVERFLOW:
                        printf("�ڴ����ʧ�ܣ�\n");
                        break;
                    case OK:
                        printf("���سɹ���\n");
                        break;
                }
                getchar();getchar();
                break;
            case 16:
                printf("������Ҫ�����ı���:\n");
                scanf_s("%s", s);
                switch (AddList(Lists, s)) {
                    case OK:
                        printf("�����ɹ���\n");
                        break;
                    case OVERFLOW:
                        printf("��ǰ����࣡\n");
                        break;
                    case ERROR:
                        printf("���Ѵ��ڣ�\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 17:
                printf("������Ҫɾ���ı���:\n");
                scanf_s("%s", s);
                if (RemoveList(Lists, s) == ERROR)printf("ɾ��ʧ�ܣ�\n");
                else printf("ɾ���ɹ���\n");
                getchar();
                getchar();
                break;
            case 18:
                printf("������Ҫʹ�õı���:\n");
                scanf_s("%s", s);
                tmp = LocateList(Lists, s);
                if (tmp) {
                    usingList = tmp - 1;
                    printf("�ı�ʹ�ñ�ɹ���\n��ǰ��:%d-%s\n", usingList, Lists.elem[usingList].name);
                } else {
                    printf("�����ڣ�\n");
                }
                getchar();
                getchar();
                break;

            case 19:
                printf("���������:\n");
                scanf_s("%s", s);
                tmp = LocateList(Lists, s);
                if (!tmp) {
                    printf("%s�����ڣ�\n", s);
                } else {
                    printf("%s�ǵ�%d����\n", s, tmp - 1);
                }
                getchar();
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
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
        printf("�ñ����ڣ�\n");
        return ERROR;
    }
    if (i == usingList + 1) {
        printf("����ɾ����ǰ��\n");
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