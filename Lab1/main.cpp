/* Linear Table On Sequence Structure */
#include <cstdio>
#include <malloc.h>
#include <cstring>

using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)

typedef int status;
typedef int ElemType; //数据元素类型定义


typedef struct Node {
    int key;
    int value;
    struct Node *next;
} HashNode;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //顺序表（顺序结构）的定义
    ElemType *elem;
    int length;
    int listSize;
} SqList;
typedef struct {  //线性表的集合类型定义
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
} LISTS;
LISTS Lists;      //线性表集合的定义Lists
int usingList = 0;

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

int MaxSubArray(SqList L);

int SubArrayNum(SqList L, ElemType k);

status sortList(SqList L);

ElemType min(ElemType a, ElemType b);

ElemType max(ElemType a, ElemType b);

int hash(int key, int numsSize);

int containKey(HashNode *hashtable, int key, int numsSize);

int getKey(HashNode *hashtable, int key, int numsSize);

void push(HashNode *hashtable, int key, int numsSize);

status AddList(LISTS &lists, const char ListName[]);

status RemoveList(LISTS &lists, char ListName[]);

int LocateList(LISTS lists, const char ListName[]);

/*--------------------------------------------*/
int main() {
    int op = 1, tmp;
    ElemType e;
    char filename[128], s[30];
    for (auto &i: Lists.elem) {
        i.L.elem = nullptr;
    }
    Lists.length = 1;
    strcpy(Lists.elem[usingList].name, "Default");
    while (op) {
        system("cls");
        printf("\n\n");
        // ╔ ═ ╗ ║ ╚ ╝
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
        printf("    ║     15. MaxSubArray       16. SubArrayNum      ║\n");
        printf("    ║     17. sortList          18. RemoveList       ║\n");
        printf("    ║     19. ChangeList        20. AddList          ║\n");
        printf("    ║     21. LocateList        0. Exit              ║\n");
        printf("    ╚════════════════════════════════════════════════╝\n");
        printf("    请选择你的操作[0~20]:");
        scanf_s("%d", &op);
        switch (op) {
            case 1:
                switch (InitList(Lists.elem[usingList].L)) {
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
                switch (DestroyList(Lists.elem[usingList].L)) {
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
                switch (ClearList(Lists.elem[usingList].L)) {
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
                switch (ListEmpty(Lists.elem[usingList].L)) {
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
                if ((tmp = ListLength(Lists.elem[usingList].L)) == INFEASIBLE)
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
                switch (GetElem(Lists.elem[usingList].L, tmp, e)) {
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
                switch (tmp = LocateElem(Lists.elem[usingList].L, e)) {
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
                switch (PriorElem(Lists.elem[usingList].L, e, e)) {
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
                switch (NextElem(Lists.elem[usingList].L, e, e)) {
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
                switch (ListInsert(Lists.elem[usingList].L, tmp, e)) {
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
                switch (ListDelete(Lists.elem[usingList].L, tmp, e)) {
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

                if (ListTraverse(Lists.elem[usingList].L) == INFEASIBLE) {
                    printf("线性表未初始化！\n");
                }
                getchar();
                getchar();
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
                getchar();
                getchar();
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
                getchar();
                getchar();
                break;
            case 15:
                tmp = MaxSubArray(Lists.elem[usingList].L);
                printf("最大子数组和为%d。\n", tmp);
                getchar();
                getchar();
                break;
            case 16:
                printf("请输入子数组和:\n");
                scanf_s("%d", &e);
                tmp = SubArrayNum(Lists.elem[usingList].L, e);
                printf("和为%d的子数组数为%d。\n", e, tmp);
                getchar();
                getchar();
                break;
            case 17:
                if (sortList(Lists.elem[usingList].L) == OK) {
                    printf("排序成功！\n");
                } else {
                    printf("排序失败！\n");
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
            case 21:
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
    FILE *pWrite = fopen(FileName, "wb+");
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
    FILE *pRead = fopen(FileName, "rb");
    if (pRead) {
        while (s == OK && fread(&tmp, sizeof(ElemType), 1, pRead))
            s = ListInsert(L, L.length + 1, tmp);
        fclose(pRead);
        return s;
    } else return ERROR;
}

int MaxSubArray(SqList L) {
    if (!L.elem)return INFEASIBLE;
    int pre = 0, maxAns = L.elem[0];
    for (int i = 0; i < L.length; i++) {
        pre = max(pre + L.elem[i], L.elem[i]);
        maxAns = max(maxAns, pre);
    }
    return maxAns;
}

status sortList(SqList L) {
    ElemType *a = L.elem;
    auto *b = (ElemType *) malloc(L.length * sizeof(ElemType));
    if (!b)return ERROR;
    int seg, start;
    for (seg = 1; seg < L.length; seg += seg) {
        for (start = 0; start < L.length; start += seg * 2) {
            int low = start, mid = min(start + seg, L.length), high = min(start + seg * 2, L.length);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int *temp = a;
        a = b;
        b = temp;
    }
    if (a != L.elem) {
        int i;
        for (i = 0; i < L.length; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
    return OK;
}

ElemType min(ElemType a, ElemType b) {
    return a > b ? b : a;
}

ElemType max(ElemType a, ElemType b) {
    return a < b ? b : a;
}


int hash(int key, int numsSize) {
    return key & (numsSize - 1);
}

int containKey(HashNode *hashtable, int key, int numsSize) {
    HashNode *head = &hashtable[hash(key, numsSize)];
    HashNode *tail = head->next;
    while (tail) {
        if (tail->key == key) return 1;
        tail = tail->next;
    }
    return 0;
}

int getKey(HashNode *hashtable, int key, int numsSize) {
    HashNode *head = &hashtable[hash(key, numsSize)];
    HashNode *tail = head->next;
    while (tail) {
        if (tail->key == key) return tail->value;
        tail = tail->next;
    }
    return -1;
}

void push(HashNode *hashtable, int key, int numsSize) {
    HashNode *head = &hashtable[hash(key, numsSize)];
    HashNode *tail = head->next;
    while (tail) {
        if (tail->key == key) {
            tail->value++;
            return;
        }
        tail = tail->next;
    }
    auto *q = (HashNode *) malloc(sizeof(HashNode));
    q->key = key;
    q->value = 1;
    q->next = head->next;
    head->next = q;
}

int SubArrayNum(SqList L, int k) {
    auto *hashtable = (HashNode *) malloc(sizeof(HashNode) * L.length);
    memset(hashtable, 0, sizeof(HashNode) * L.length);
    push(hashtable, 0, L.length);
    int pre = 0, cnt = 0;
    for (int i = 0; i < L.length; i++) {
        pre += L.elem[i];
        if (containKey(hashtable, pre - k, L.length))
            cnt += getKey(hashtable, pre - k, L.length);
        push(hashtable, pre, L.length);
    }
    return cnt;
}

status AddList(LISTS &lists, const char ListName[]) {
    if (lists.length >= 10)return OVERFLOW;
    if (LocateList(lists, ListName)) return ERROR;
    int i = 0;
    while ((((lists.elem)[lists.length]).name[i] = ListName[i]))i++;
    ((lists.elem)[lists.length]).L.elem = nullptr;
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