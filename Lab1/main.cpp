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
// 功能：顺序表不存在：初始化表，返回OK；
//      顺序表已存在，返回INFEASIBLE。
// 参数：顺序表的引用 SqList &L
// 返回：【OK|OVERFLOW|INFEASIBLE】
status InitList(SqList &L);
// 功能：顺序表存在：销毁表，释放空间，返回 OK；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表的引用 SqList &L
// 返回：【OK|INFEASIBLE】
status DestroyList(SqList &L);
// 功能：顺序表存在：清空表，返回 OK；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表的引用 SqList &L
// 返回：【OK|INFEASIBLE】
status ClearList(SqList &L);
// 功能：顺序表存在：判断线性表是否为空，返回【TRUE|FALSE】；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L
// 返回：【TRUE|FALSE|INFEASIBLE】
status ListEmpty(SqList L);
// 功能：顺序表存在：返回表长；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L
// 返回：【表长|INFEASIBLE】
int ListLength(SqList L);
// 功能：顺序表存在：查找指定位置的元素，返回OK；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L，位序 int i，元素引用 ElemType &e
// 返回：【OK|ERROR|INFEASIBLE】
status GetElem(SqList L, int i, ElemType &e);
// 功能：顺序表存在：查找指定元素，找到返回位序，未找到则返回ERROR；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L，指定元素 ElemType e
// 返回：【位序|ERROR|INFEASIBLE】
int LocateElem(SqList L, ElemType e);
// 功能：顺序表存在：查找指定元素的前驱，找到返回OK，未找到则返回ERROR。
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L，当前元素 ElemType cur，前驱元素的引用 ElemType &pre_e
// 返回：【OK|ERROR|INFEASIBLE】
status PriorElem(SqList L, ElemType cur, ElemType &pre_e);
// 功能：顺序表存在：查找指定元素的后继，找到返回OK，未找到则返回ERROR；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L，当前元素 ElemType cur，后继元素的引用 ElemType &next_e
// 返回：【OK|ERROR|INFEASIBLE】
status NextElem(SqList L, ElemType cur, ElemType &next_e);
// 功能：顺序表存在：在指定位序前插入指定元素，成功返回OK，失败返回ERROR；内存分配失败，返回OVERFLOW。
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表引用 SqList &L，位序 int i，元素 ElemType e
// 返回：【OK|OVERFLOW|ERROR|INFEASIBLE】
status ListInsert(SqList &L, int i, ElemType e);
// 功能：顺序表存在：删除指定位置的元素，并将其值通过引用传回，成功返回OK，失败返回ERROR；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表引用 SqList &L，位序 int i，元素引用 ElemType &e
// 返回：【OK|ERROR|INFEASIBLE】
status ListDelete(SqList &L, int i, ElemType &e);
// 功能：顺序表存在：遍历顺序表并输出元素值，返回OK；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L
// 返回：【OK|INFEASIBLE】
status ListTraverse(SqList L);
// 功能：顺序表存在：保存表数据到指定文件，成功返回OK，失败返回ERROR；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L，文件路径 char FileName[]
// 返回：【OK|ERROR|INFEASIBLE】
status SaveList(SqList L, char FileName[]);
// 功能：顺序表不存在：从指定文件加载表数据，成功返回OK，失败返回ERROR|OVERFLOW；
//      顺序表已存在，返回 INFEASIBLE。
// 参数：顺序表的引用 SqList &L，文件路径 char FileName[]
// 返回：【OK|OVERFLOW|ERROR|INFEASIBLE】
status LoadList(SqList &L, char FileName[]);
// 功能：顺序表存在：返回最大子数组和；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L
// 返回：【子数组和|INFEASIBLE】
int MaxSubArray(SqList L);
// 功能：顺序表存在：返回和为k的子数组的数目；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L 整数 int k
// 返回：【和为k的子数组数目|INFEASIBLE】
int SubArrayNum(SqList L, ElemType k);
// 功能：顺序表存在：将顺序表按升序排序，返回OK；
//      顺序表不存在，返回 INFEASIBLE。
// 参数：顺序表 SqList L
// 返回：【OK|ERROR|INFEASIBLE】
status sortList(SqList L);
// 辅助函数
ElemType min(ElemType a, ElemType b);
// 辅助函数
int hash(int key, int numsSize);
// 辅助函数
int containKey(HashNode *hashtable, int key, int numsSize);
// 辅助函数
int getKey(HashNode *hashtable, int key, int numsSize);
// 辅助函数
void push(HashNode *hashtable, int key, int numsSize);

// 功能：向顺序表序列尾部添加一个顺序表并返回OK；
//      若顺序表已存在，返回ERROR；
//      若顺序表列表已满，返回OVERFLOW。
// 参数：顺序表序列引用 LISTS &Lists，表名 char ListName[]
// 返回：【OK|ERROR|OVERFLOW】
status AddList(LISTS &lists, const char ListName[]);
// 功能：改变usingList的值，从而改变当前表，返回OK，
//      若表不存在，返回ERROR。
// 参数：顺序表序列 LISTS Lists，表名 char ListName[]
// 返回：【OK|ERROR】
status ChangeList(LISTS lists, const char ListName[]);
// 功能：从顺序表序列中删除指定表名的顺序表，返回OK；
//      若顺序表不存在，返回ERROR；
//      若该顺序表正在使用，返回INFEASIBLE。
// 参数：顺序表序列引用 LISTS \&Lists，表名 char ListName[]
// 返回：【OK|ERROR|INFEASIBLE】
status RemoveList(LISTS &lists, char ListName[]);
// 功能：查找指定表名的顺序表，查找成功，返回位序（i>=1）；
//      查找失败，返回0
// 参数：顺序表序列 LISTS Lists，表名 char ListName[]
// 返回：【0|位序】
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
        printf("    请选择你的操作:");
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
                if(tmp==INFEASIBLE)printf("线性表未初始化！");
                else printf("最大子数组和为%d。\n", tmp);
                getchar();
                getchar();
                break;
            case 16:
                printf("请输入子数组和:\n");
                scanf_s("%d", &e);
                switch(tmp = SubArrayNum(Lists.elem[usingList].L, e)){
                    case INFEASIBLE:
                        printf("线性表未初始化！\n", e, tmp);
                        break;
                    case ERROR:
                        printf("线性表为空表！\n", e, tmp);
                        break;
                    default:
                        printf("和为%d的子数组数为%d。\n", e, tmp);
                        break;
                }

                getchar();
                getchar();
                break;
            case 17:
                switch (sortList(Lists.elem[usingList].L)) {
                    case ERROR:
                        printf("排序失败！\n");
                        break;
                    case INFEASIBLE:
                        printf("线性表未初始化！\n");
                        break;
                    case OK:
                        printf("排序成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 18:
                printf("请输入要删除的表名:\n");
                scanf_s("%s", s);
                switch(RemoveList(Lists, s)){
                    case ERROR:
                        printf("顺序表不存在！\n");
                        break;
                    case INFEASIBLE:
                        printf("不能删除当前表！\n");
                        break;
                    case OK:
                        printf("删除成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 19:
                printf("请输入要使用的表名:\n");
                scanf_s("%s", s);
                if (ChangeList(Lists,s)==OK) {
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
        if(s!=OK)DestroyList(L);
        return s;
    } else {
        DestroyList(L);
        return ERROR;
    }
}

int MaxSubArray(SqList L) {
    if (!L.elem)return INFEASIBLE;
    int now=0,max=0;
    for (int i = 0; i < L.length; i++) {
        now+=L.elem[i];
        if(now<0)now=0;
        if(now>max)max=now;
    }
    return max;
}

status sortList(SqList L) {
    if(!L.elem)return INFEASIBLE;
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
    if(!L.elem)return INFEASIBLE;
    if(!L.length)return ERROR;
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

status ChangeList(LISTS lists, const char ListName[]){
    int tmp=LocateList(lists, ListName);
    if(tmp){
        usingList=tmp-1;
        return OK;
    }
    return ERROR;
}

status RemoveList(LISTS &lists, char ListName[]) {
    int i = LocateList(lists, ListName);
    if (!i) return ERROR;
    if (i == usingList + 1) return INFEASIBLE;
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