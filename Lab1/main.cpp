/* Linear Table On Sequence Structure */
#include <cstdio>
#include <malloc.h>
#include <windows.h>
using namespace std;
/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE (-1)
#define OVERFLOW (-2)

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
    ElemType * elem;
    int length;
    int listSize;
}SqList;
/*
 * Function:        InitList
 * Description:     初始化顺序表
 * Calls:           malloc
 * Input:
 *  - SqList &L     顺序表的引用
 * Return:
 *  - status        OK|INFEASTABLE|OVERFLOW
 * Output:          None
 */
status InitList(SqList&L);
/*
 * Function:        DestroyList
 * Description:     销毁顺序表
 * Calls:           free
 * Input:
 *  - SqList &L     顺序表的引用
 * Return:
 *  - status        OK|INFEASTABLE
 * Output:          None
 */
status DestroyList(SqList&L);
/*
 * Function:        ClearList
 * Description:     清空顺序表
 * Calls:           None
 * Input:
 *  - SqList &L     顺序表的引用
 * Return:
 *  - status        OK|INFEASTABLE
 * Output:          None
 */
status ClearList(SqList&L);
/*
 * Function:        ListEmpty
 * Description:     顺序表判空
 * Calls:           None
 * Input:
 *  - SqList L      顺序表
 * Return:
 *  - status        TRUE|FALSE|INFEASTABLE
 * Output:          None
 */
status ListEmpty(SqList L);
/*
 * Function:        ListEmpty
 * Description:     顺序表判空
 * Calls:           None
 * Input:
 *  - SqList L      顺序表
 * Return:
 *  - status        TRUE|FALSE|INFEASTABLE
 * Output:          None
 */
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType&e);
status LocateElem(SqList L,ElemType e); //简化过
status PriorElem(SqList L,ElemType cur,ElemType&pre_e);
status NextElem(SqList L,ElemType cur,ElemType&next_e);
status ListInsert(SqList&L,int i,ElemType e);
status ListDelete(SqList&L,int i,ElemType&e);
status ListTraverse(SqList L);  //简化过
/*--------------------------------------------*/
int main(){
    SqList L;int op=1;
    L.elem=nullptr;
    while(op){
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("    -------------------------------------------------\n");
        printf("    	  1. InitList           7. LocateElem\n");
        printf("    	  2. DestroyList        8. PriorElem\n");
        printf("    	  3. ClearList          9. NextElem \n");
        printf("    	  4. ListEmpty          10. ListInsert\n");
        printf("    	  5. ListLength         11. ListDelete\n");
        printf("    	  6. GetElem            12. ListTraverse\n");
        printf("    	  0. Exit\n");
        printf("    -------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                switch (InitList(L)) {
                    case OK:printf("线性表创建成功！\n");break;
                    case OVERFLOW:printf("线性表创建失败！\n");break;
                    case INFEASTABLE:printf("线性表已存在！\n");break;
                }
                getchar();getchar();
                break;
            case 2:
                // printf("\n----DestroyList功能待实现！\n");
                switch (DestroyList(L)) {
                    case OK:printf("线性表销毁成功！\n");break;
                    case INFEASTABLE:printf("线性表未初始化！\n");break;
                }
                getchar();getchar();
                break;
            case 3:
                // printf("\n----ClearList功能待实现！\n");
                switch (ClearList(L)) {
                    case OK:printf("线性表清空成功！\n");break;
                }
                getchar();getchar();
                break;
            case 4:
                printf("\n----ListEmpty功能待实现！\n");
                getchar();getchar();
                break;
            case 5:
                printf("\n----ListLength功能待实现！\n");
                getchar();getchar();
                break;
            case 6:
                printf("\n----GetElem功能待实现！\n");
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
                if(!ListTraverse(L)) printf("线性表是空表！\n");
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    Sleep(2500);
    return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
status InitList(SqList&L){

    if(L.elem)return INFEASTABLE;
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem) return OVERFLOW;
    L.length=0;
    L.listSize=LIST_INIT_SIZE;
    return OK;
}
status DestroyList(SqList&L){
    if(L.elem){
        free(L.elem);
        L.elem= nullptr;
        L.length= 0;
        L.listSize= 0;
        return OK;
    }else return INFEASTABLE;
}
status ClearList(SqList&L){
    if(L.elem){
        L.length=0;return OK;
    } else return INFEASTABLE;
}
status ListEmpty(SqList L){
    if(L.elem){
        return L.length?FALSE:TRUE;
    } else return INFEASTABLE;
}
int ListLength(SqList L){
    if(L.elem){
        return L.length;
    } else return INFEASTABLE;
}
status GetElem(SqList L,int i,ElemType&e){
    if (L.elem){
        if (i<=0||i>L.length)return ERROR;
        else{
            e=L.elem[i-1];
            return OK;
        }
    } else return INFEASTABLE;
}
status LocateElem(SqList L,ElemType e){
    if(L.elem){
        for (int i=1; i <= L.length; i++){
            if(L.elem[i-1]==e)return i;
        }
        return ERROR;
    } else return INFEASTABLE;
}
status PriorElem(SqList L,ElemType cur,ElemType&pre_e){
    if(L.elem){
        for (int i=2; i <= L.length; i++){
            if(L.elem[i-1]==cur){
                pre_e=L.elem[i-2];
                return OK;
            }
        }
        return ERROR;
    } else return INFEASTABLE;
}
status NextElem(SqList L,ElemType cur,ElemType&next_e){
    if(L.elem){
        for (int i=1; i < L.length; i++){
            if(L.elem[i-1]==cur){
                next_e=L.elem[i];
                return OK;
            }
        }
        return ERROR;
    } else return INFEASTABLE;
}
status ListInsert(SqList&L,int i,ElemType e){
    if (L.elem){
        if(i>L.length+1||i<=0)return ERROR;
        if(L.length==L.listSize){
            auto *new_base=(ElemType*) realloc(L.elem,(L.listSize=L.listSize+LISTINCREMENT)*sizeof(ElemType));
            if (new_base)L.elem=new_base;
            else return OVERFLOW;
        }
        for (int p=L.length;p>=i;p--)
            L.elem[p]=L.elem[p-1];
        L.elem[i-1]=e;
        L.length++;
        return OK;
    } else return INFEASTABLE;
}
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；
// 当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListDelete(SqList&L,int i,ElemType&e){
    if (L.elem){
        if (i<=0||i>L.length)return ERROR;
        e=L.elem[i-1];
        for (int j = i; j < L.length; j++) {
            L.elem[j-1]=L.elem[j];
        }
        L.length--;
        return OK;
    } else return INFEASTABLE;
}
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
status ListTraverse(SqList L){
    int i;
    printf("\n---------------all elements -------------------\n");
    for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
    printf("\n------------------ end ------------------------\n");
    return L.length;
}
status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(!L.elem)return INFEASTABLE;
    FILE*pWrite= fopen(FileName, "w");
    if (pWrite){
        for (int i = 0; i < L.length; i++) {
            fprintf(pWrite, "%d ", L.elem[i]);
        }
        fclose(pWrite);
        return OK;
    } else return ERROR;
}
status  LoadList(SqList&L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L.elem)return INFEASTABLE;
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem) return OVERFLOW;
    L.length=0;
    L.listSize=LIST_INIT_SIZE;
    FILE*pRead= fopen(FileName, "r");
    if (pRead){
        for (int i = 0; !feof(pRead); L.length=i++) {
            if(L.length==L.listSize){
                auto *new_base=(ElemType*) realloc(L.elem,(L.listSize=L.listSize+LISTINCREMENT)*sizeof(ElemType));
                if (new_base)L.elem=new_base;
                else return OVERFLOW;
            }
            fscanf(pRead, "%d", L.elem + i);
        }
        fclose(pRead);
        return OK;
    } else return ERROR;
}