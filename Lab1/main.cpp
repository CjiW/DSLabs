/* Linear Table On Sequence Structure */
#include <cstdio>
#include <malloc.h>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //顺序表（顺序结构）的定义
    ElemType *elem;
    int length;
    int listSize;
} SqList;

/*
 * Function:        InitList
 * Description:     初始化顺序表
 * Calls:           malloc
 * Input:
 *  - SqList &L     顺序表的引用
 * Return:
 *  - status        OK|INFEASIBLE|OVERFLOW
 * Output:          None
 */
status InitList(SqList &L);

/*
 * Function:        DestroyList
 * Description:     销毁顺序表
 * Calls:           free
 * Input:
 *  - SqList &L     顺序表的引用
 * Return:
 *  - status        OK|INFEASIBLE
 * Output:          None
 */
status DestroyList(SqList &L);

/*
 * Function:        ClearList
 * Description:     清空顺序表
 * Calls:           None
 * Input:
 *  - SqList &L     顺序表的引用
 * Return:
 *  - status        OK|INFEASIBLE
 * Output:          None
 */
status ClearList(SqList &L);

/*
 * Function:        ListEmpty
 * Description:     顺序表判空
 * Calls:           None
 * Input:
 *  - SqList L      顺序表
 * Return:
 *  - status        TRUE|FALSE|INFEASIBLE
 * Output:          None
 */
status ListEmpty(SqList L);

/*
 * Function:        ListLength
 * Description:     获取顺序表长度
 * Calls:           None
 * Input:
 *  - SqList L      顺序表
 * Return:
 *  - int           长度|INFEASIBLE
 * Output:          None
 */
int ListLength(SqList L);

/*
 * Function:        GetElem
 * Description:     获取顺序表特定位置元素
 * Calls:           None
 * Input:
 *  - SqList L      顺序表
 *  - int i         指定位置
 *  - ElemType &e   返回元素的引用
 * Return:
 *  - status        OK|ERROR|INFEASIBLE
 * Output:          None
 */
status GetElem(SqList L, int i, ElemType &e);

/*
 * Function:        LocateElem
 * Description:     获取顺序表中元素位置
 * Calls:           None
 * Input:
 *  - SqList L      顺序表
 *  - ElemType e    指定元素
 * Return:
 *  - int           位置|ERROR|INFEASIBLE
 * Output:          None
 */
int LocateElem(SqList L, ElemType e); //简化过
/*
 * Function:         PriorElem
 * Description:      获取顺序表元素的前驱
 * Calls:            None
 * Input:
 *  - SqList L       顺序表
 *  - ElemType cur   当前元素
 *  - ElemType&pre_e 前驱元素的引用
 * Return:
 *  - status         OK|ERROR|INFEASIBLE
 * Output:           None
 */
status PriorElem(SqList L, ElemType cur, ElemType &pre_e);

/*
 * Function:          NextElem
 * Description:       获取顺序表元素的后继
 * Calls:             None
 * Input:
 *  - SqList L        顺序表
 *  - ElemType cur    当前元素
 *  - ElemType&next_e 后继元素的引用
 * Return:
 *  - status          OK|ERROR|INFEASIBLE
 * Output:            None
 */
status NextElem(SqList L, ElemType cur, ElemType &next_e);

/*
 * Function:        ListInsert
 * Description:     插入元素到指定位置
 * Calls:           realloc
 * Input:
 *  - SqList &L     顺序表引用
 *  - int i         插入位置
 *  - ElemType e    插入元素
 * Return:
 *  - status        OK|ERROR|INFEASIBLE|OVERFLOW
 * Output:          None
 */
status ListInsert(SqList &L, int i, ElemType e);

/*
 * Function:        ListDelete
 * Description:     删除特定位置元素
 * Calls:           None
 * Input:
 *  - SqList &L     顺序表引用
 *  - int i         指定位置
 *  - ElemType &e   删除元素的引用
 * Return:
 *  - status        OK|ERROR|INFEASIBLE
 * Output:          None
 */
status ListDelete(SqList &L, int i, ElemType &e);

/*
 * Function:        ListTraverse
 * Description:     遍历并打印顺序表
 * Calls:           printf
 * Input:
 *  - SqList L      顺序表
 * Return:
 *  - status        OK|INFEASIBLE
 * Output:          顺序表元素，以空格分隔
 */
status ListTraverse(SqList L);

/*
 * Function:          SaveList
 * Description:       存储顺序表
 * Calls:             fopen, fwrite, fclose
 * Input:
 *  - SqList L        顺序表
 *  - char FileName[] 文件路径
 * Return:
 *  - status          OK|ERROR|INFEASIBLE
 * Output:            None
 */
status SaveList(SqList L, char FileName[]);

/*
 * Function:          LoadList
 * Description:       加载顺序表
 * Calls:             fopen, fread, fclose, ListInsert
 * Input:
 *  - SqList &L       顺序表引用
 *  - char FileName[] 文件路径
 * Return:
 *  - status          OK|ERROR|OVERFLOW|INFEASIBLE
 * Output:            None
 */
status LoadList(SqList &L, char FileName[]);

/*--------------------------------------------*/
int main() {
    SqList L;
    int op = 1, tmp;
    ElemType e;
    char filename[128];
    L.elem = nullptr;
    while (op) {
        system("cls");
        printf("\n\n");
        // ╔ ═ ╗ ║ ╚ ╝
        printf("    ╔════════════════════════════════════════════════╗\n");
        printf("    ║  Menu for Linear Table On Sequence Structure   ║\n");
        printf("    ╟────────────────────────────────────────────────╢\n");
        printf("    ║     1. InitList           2. DestroyList       ║\n");
        printf("    ║     3. ClearList          4. ListEmpty         ║\n");
        printf("    ║     5. ListLength         6. GetElem           ║\n");
        printf("    ║     7. LocateElem         8. PriorElem         ║\n");
        printf("    ║     9. NextElem           10. ListInsert       ║\n");
        printf("    ║     11. ListDelete        12. ListTraverse     ║\n");
        printf("    ║     13. SaveList          14. LoadList         ║\n");
        printf("    ║                  0. Exit                       ║\n");
        printf("    ╚════════════════════════════════════════════════╝\n");
        printf("    请选择你的操作[0~12]:");
        scanf_s("%d", &op);
        switch (op) {
            case 1:
                switch (InitList(L)) {
                    case OK:
                        printf("线性表创建成功！\n");
                        break;
                    case OVERFLOW:
                        printf("线性表创建失败！\n");
                        break;
                    case INFEASIBLE:
                        printf("线性表已存在！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 2:
                // printf("\n----DestroyList功能待实现！\n");
                switch (DestroyList(L)) {
                    case OK:
                        printf("线性表销毁成功！\n");
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 3:
                // printf("\n----ClearList功能待实现！\n");
                switch (ClearList(L)) {
                    case OK:
                        printf("线性表清空成功！\n");
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 4:
                // printf("\n----ListEmpty功能待实现！\n");
                switch (ListEmpty(L)) {
                    case TRUE:
                        printf("线性表为空。\n");
                        break;
                    case FALSE:
                        printf("线性表不为空。\n");
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 5:
                // printf("\n----ListLength功能待实现！\n");
                if ((tmp = ListLength(L)) == INFEASIBLE)
                    printf("线性表未初始化！\n");
                else
                    printf("线性表长度为 %d。", tmp);
                getchar();
                getchar();
                break;
            case 6:
                // printf("\n----GetElem功能待实现！\n");
                printf("请输入元素位置:\n");
                scanf_s("%d", &tmp);
                switch (GetElem(L, tmp, e)) {
                    case OK:
                        printf("第%d个元素为%d。\n", tmp, e);
                        break;
                    case ERROR:
                        printf("位置%d非法！\n", tmp);
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 7:
                // printf("\n----LocateElem功能待实现！\n");
                printf("请输入元素值:\n");
                scanf_s("%d", &e);
                switch (tmp = LocateElem(L, e)) {
                    case ERROR:
                        printf("元素%d不存在！\n", e);
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                    default:
                        printf("元素%d位置为%d。\n", e, tmp);
                        break;
                }
                getchar();
                getchar();
                break;
            case 8:
                // printf("\n----PriorElem功能待实现！\n");
                printf("请输入当前元素值:\n");
                scanf_s("%d", &e);
                switch (PriorElem(L, e, e)) {
                    case OK:
                        printf("前驱元素为%d。\n", e);
                        break;
                    case ERROR:
                        printf("元素%d的前驱元素不存在！\n", e);
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 9:
                // printf("\n----NextElem功能待实现！\n");
                printf("请输入当前元素值:\n");
                scanf_s("%d", &e);
                switch (NextElem(L, e, e)) {
                    case OK:
                        printf("后继元素为%d。\n", e);
                        break;
                    case ERROR:
                        printf("元素%d的后继元素不存在！\n", e);
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 10:
                // printf("\n----ListInsert功能待实现！\n");
                printf("请输入位置值:\n");
                scanf_s("%d", &tmp);
                printf("请输入元素值:\n");
                scanf_s("%d", &e);
                switch (ListInsert(L, tmp, e)) {
                    case OK:
                        printf("元素%d插入成功！\n", e);
                        break;
                    case ERROR:
                        printf("位置%d非法！\n", tmp);
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                    case OVERFLOW:
                        printf("内存分配失败！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 11:
                // printf("\n----ListDelete功能待实现！\n");
                printf("请输入位置值:\n");
                scanf_s("%d", &tmp);
                switch (ListDelete(L, tmp, e)) {
                    case OK:
                        printf("第%d个元素%d删除成功！\n", tmp, e);
                        break;
                    case ERROR:
                        printf("位置%d非法！\n", tmp);
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 12:

                if (ListTraverse(L) == INFEASIBLE) {
                    printf("线性表未初始化！\n");
                }
                getchar();
                getchar();
                break;
            case 13:
                printf("请输入文件路径:\n");
                scanf("%s", filename);
                switch (SaveList(L, filename)) {
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
                getchar();
                getchar();
                break;
            case 14:
                printf("请输入文件路径:\n");
                scanf("%s", filename);
                switch (LoadList(L, filename)) {
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
                getchar();
                getchar();
                break;
            case 0:
                break;
            default:;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    getchar();
    getchar();
    return 0;
}//end of main()
/*--------------------------------------------*/
status InitList(SqList &L) {

    if (L.elem)return INFEASIBLE;
    L.elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) return OVERFLOW;
    L.length = 0;
    L.listSize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList &L) {
    if (L.elem) {
        free(L.elem);
        L.elem = nullptr;
        L.length = 0;
        L.listSize = 0;
        return OK;
    } else return INFEASIBLE;
}

status ClearList(SqList &L) {
    if (L.elem) {
        L.length = 0;
        return OK;
    } else return INFEASIBLE;
}

status ListEmpty(SqList L) {
    if (L.elem) {
        return L.length ? FALSE : TRUE;
    } else return INFEASIBLE;
}

int ListLength(SqList L) {
    if (L.elem) {
        return L.length;
    } else return INFEASIBLE;
}

status GetElem(SqList L, int i, ElemType &e) {
    if (L.elem) {
        if (i <= 0 || i > L.length)return ERROR;
        else {
            e = L.elem[i - 1];
            return OK;
        }
    } else return INFEASIBLE;
}

int LocateElem(SqList L, ElemType e) {
    if (L.elem) {
        for (int i = 1; i <= L.length; i++) {
            if (L.elem[i - 1] == e)return i;
        }
        return ERROR;
    } else return INFEASIBLE;
}

status PriorElem(SqList L, ElemType cur, ElemType &pre_e) {
    if (L.elem) {
        for (int i = 2; i <= L.length; i++) {
            if (L.elem[i - 1] == cur) {
                pre_e = L.elem[i - 2];
                return OK;
            }
        }
        return ERROR;
    } else return INFEASIBLE;
}

status NextElem(SqList L, ElemType cur, ElemType &next_e) {
    if (L.elem) {
        for (int i = 1; i < L.length; i++) {
            if (L.elem[i - 1] == cur) {
                next_e = L.elem[i];
                return OK;
            }
        }
        return ERROR;
    } else return INFEASIBLE;
}

status ListInsert(SqList &L, int i, ElemType e) {
    if (L.elem) {
        if (i > L.length + 1 || i <= 0)return ERROR;
        if (L.length == L.listSize) {
            auto *new_base = (ElemType *) realloc(L.elem, (L.listSize = L.listSize + LISTINCREMENT) * sizeof(ElemType));
            if (new_base)L.elem = new_base;
            else return OVERFLOW;
        }
        for (int p = L.length; p >= i; p--)
            L.elem[p] = L.elem[p - 1];
        L.elem[i - 1] = e;
        L.length++;
        return OK;
    } else return INFEASIBLE;
}

status ListDelete(SqList &L, int i, ElemType &e) {
    if (L.elem) {
        if (i <= 0 || i > L.length)return ERROR;
        e = L.elem[i - 1];
        for (int j = i; j < L.length; j++) {
            L.elem[j - 1] = L.elem[j];
        }
        L.length--;
        return OK;
    } else return INFEASIBLE;
}

status ListTraverse(SqList L) {
    if (L.elem) {
        if (!L.length) {
            printf("线性表是空表！\n");
        } else {
            printf("\n-----------------All Elem----------------\n");
            int i;
            for (i = 0; i < L.length; i++) printf("%d ", L.elem[i]);
            printf("\n-------------------End-------------------\n");
        }
        return OK;
    } else return INFEASIBLE;
}

status SaveList(SqList L, char FileName[]) {
    if (!L.elem)return INFEASIBLE;
    FILE *pWrite = fopen(FileName, "w+");
    if (pWrite) {
        fwrite(L.elem, sizeof(ElemType), L.length, pWrite);
        fclose(pWrite);
        return OK;
    } else return ERROR;
}

status LoadList(SqList &L, char FileName[]) {
    ElemType tmp;
    status s;
    s = InitList(L);
    if (s != OK) return s;
    FILE *pRead = fopen(FileName, "r");
    if (pRead) {
        while (s == OK && fread(&tmp, sizeof(ElemType), 1, pRead))
            s = ListInsert(L, L.length + 1, tmp);
        fclose(pRead);
        return s;
    } else return ERROR;
}