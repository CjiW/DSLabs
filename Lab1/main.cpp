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
typedef int ElemType; //����Ԫ�����Ͷ���


typedef struct Node {
    int key;
    int value;
    struct Node *next;
} HashNode;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //˳���˳��ṹ���Ķ���
    ElemType *elem;
    int length;
    int listSize;
} SqList;
typedef struct {  //���Ա�ļ������Ͷ���
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
} LISTS;
LISTS Lists;      //���Ա��ϵĶ���Lists
int usingList = 0;

/*
 * Function:        InitList
 * Description:     ��ʼ��˳���
 * Calls:           malloc
 * Input:
 *  - SqList &L     ˳��������
 * Return:
 *  - status        OK|INFEASIBLE|OVERFLOW
 * Output:          None
 */
status InitList(SqList &L);

/*
 * Function:        DestroyList
 * Description:     ����˳���
 * Calls:           free
 * Input:
 *  - SqList &L     ˳��������
 * Return:
 *  - status        OK|INFEASIBLE
 * Output:          None
 */
status DestroyList(SqList &L);

/*
 * Function:        ClearList
 * Description:     ���˳���
 * Calls:           None
 * Input:
 *  - SqList &L     ˳��������
 * Return:
 *  - status        OK|INFEASIBLE
 * Output:          None
 */
status ClearList(SqList &L);

/*
 * Function:        ListEmpty
 * Description:     ˳����п�
 * Calls:           None
 * Input:
 *  - SqList L      ˳���
 * Return:
 *  - status        TRUE|FALSE|INFEASIBLE
 * Output:          None
 */
status ListEmpty(SqList L);

/*
 * Function:        ListLength
 * Description:     ��ȡ˳�����
 * Calls:           None
 * Input:
 *  - SqList L      ˳���
 * Return:
 *  - int           ����|INFEASIBLE
 * Output:          None
 */
int ListLength(SqList L);

/*
 * Function:        GetElem
 * Description:     ��ȡ˳����ض�λ��Ԫ��
 * Calls:           None
 * Input:
 *  - SqList L      ˳���
 *  - int i         ָ��λ��
 *  - ElemType &e   ����Ԫ�ص�����
 * Return:
 *  - status        OK|ERROR|INFEASIBLE
 * Output:          None
 */
status GetElem(SqList L, int i, ElemType &e);

/*
 * Function:        LocateElem
 * Description:     ��ȡ˳�����Ԫ��λ��
 * Calls:           None
 * Input:
 *  - SqList L      ˳���
 *  - ElemType e    ָ��Ԫ��
 * Return:
 *  - int           λ��|ERROR|INFEASIBLE
 * Output:          None
 */
int LocateElem(SqList L, ElemType e); //�򻯹�
/*
 * Function:         PriorElem
 * Description:      ��ȡ˳���Ԫ�ص�ǰ��
 * Calls:            None
 * Input:
 *  - SqList L       ˳���
 *  - ElemType cur   ��ǰԪ��
 *  - ElemType&pre_e ǰ��Ԫ�ص�����
 * Return:
 *  - status         OK|ERROR|INFEASIBLE
 * Output:           None
 */
status PriorElem(SqList L, ElemType cur, ElemType &pre_e);

/*
 * Function:          NextElem
 * Description:       ��ȡ˳���Ԫ�صĺ��
 * Calls:             None
 * Input:
 *  - SqList L        ˳���
 *  - ElemType cur    ��ǰԪ��
 *  - ElemType&next_e ���Ԫ�ص�����
 * Return:
 *  - status          OK|ERROR|INFEASIBLE
 * Output:            None
 */
status NextElem(SqList L, ElemType cur, ElemType &next_e);

/*
 * Function:        ListInsert
 * Description:     ����Ԫ�ص�ָ��λ��
 * Calls:           realloc
 * Input:
 *  - SqList &L     ˳�������
 *  - int i         ����λ��
 *  - ElemType e    ����Ԫ��
 * Return:
 *  - status        OK|ERROR|INFEASIBLE|OVERFLOW
 * Output:          None
 */
status ListInsert(SqList &L, int i, ElemType e);

/*
 * Function:        ListDelete
 * Description:     ɾ���ض�λ��Ԫ��
 * Calls:           None
 * Input:
 *  - SqList &L     ˳�������
 *  - int i         ָ��λ��
 *  - ElemType &e   ɾ��Ԫ�ص�����
 * Return:
 *  - status        OK|ERROR|INFEASIBLE
 * Output:          None
 */
status ListDelete(SqList &L, int i, ElemType &e);

/*
 * Function:        ListTraverse
 * Description:     ��������ӡ˳���
 * Calls:           printf
 * Input:
 *  - SqList L      ˳���
 * Return:
 *  - status        OK|INFEASIBLE
 * Output:          ˳���Ԫ�أ��Կո�ָ�
 */
status ListTraverse(SqList L);

/*
 * Function:          SaveList
 * Description:       �洢˳���
 * Calls:             fopen, fwrite, fclose
 * Input:
 *  - SqList L        ˳���
 *  - char FileName[] �ļ�·��
 * Return:
 *  - status          OK|ERROR|INFEASIBLE
 * Output:            None
 */
status SaveList(SqList L, char FileName[]);

/*
 * Function:          LoadList
 * Description:       ����˳���
 * Calls:             fopen, fread, fclose, ListInsert
 * Input:
 *  - SqList &L       ˳�������
 *  - char FileName[] �ļ�·��
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
        // �X �T �[ �U �^ �a
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
        printf("    �U     15. MaxSubArray       16. SubArrayNum      �U\n");
        printf("    �U     17. sortList          18. RemoveList       �U\n");
        printf("    �U     19. ChangeList        20. AddList          �U\n");
        printf("    �U     21. LocateList        0. Exit              �U\n");
        printf("    �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        printf("    ��ѡ����Ĳ���[0~20]:");
        scanf_s("%d", &op);
        switch (op) {
            case 1:
                switch (InitList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("���Ա����ɹ���\n");
                        break;
                    case OVERFLOW:
                        printf("���Ա���ʧ�ܣ�\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա��Ѵ��ڣ�\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 2:
                // printf("\n----DestroyList���ܴ�ʵ�֣�\n");
                switch (DestroyList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("���Ա����ٳɹ���\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 3:
                // printf("\n----ClearList���ܴ�ʵ�֣�\n");
                switch (ClearList(Lists.elem[usingList].L)) {
                    case OK:
                        printf("���Ա���ճɹ���\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 4:
                // printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
                switch (ListEmpty(Lists.elem[usingList].L)) {
                    case TRUE:
                        printf("���Ա�Ϊ�ա�\n");
                        break;
                    case FALSE:
                        printf("���Ա�Ϊ�ա�\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 5:
                // printf("\n----ListLength���ܴ�ʵ�֣�\n");
                if ((tmp = ListLength(Lists.elem[usingList].L)) == INFEASIBLE)
                    printf("���Ա�δ��ʼ����\n");
                else
                    printf("���Ա���Ϊ %d��", tmp);
                getchar();
                getchar();
                break;
            case 6:
                // printf("\n----GetElem���ܴ�ʵ�֣�\n");
                printf("������Ԫ��λ��:\n");
                scanf_s("%d", &tmp);
                switch (GetElem(Lists.elem[usingList].L, tmp, e)) {
                    case OK:
                        printf("��%d��Ԫ��Ϊ%d��\n", tmp, e);
                        break;
                    case ERROR:
                        printf("λ��%d�Ƿ���\n", tmp);
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 7:
                // printf("\n----LocateElem���ܴ�ʵ�֣�\n");
                printf("������Ԫ��ֵ:\n");
                scanf_s("%d", &e);
                switch (tmp = LocateElem(Lists.elem[usingList].L, e)) {
                    case ERROR:
                        printf("Ԫ��%d�����ڣ�\n", e);
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                    default:
                        printf("Ԫ��%dλ��Ϊ%d��\n", e, tmp);
                        break;
                }
                getchar();
                getchar();
                break;
            case 8:
                // printf("\n----PriorElem���ܴ�ʵ�֣�\n");
                printf("�����뵱ǰԪ��ֵ:\n");
                scanf_s("%d", &e);
                switch (PriorElem(Lists.elem[usingList].L, e, e)) {
                    case OK:
                        printf("ǰ��Ԫ��Ϊ%d��\n", e);
                        break;
                    case ERROR:
                        printf("Ԫ��%d��ǰ��Ԫ�ز����ڣ�\n", e);
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 9:
                // printf("\n----NextElem���ܴ�ʵ�֣�\n");
                printf("�����뵱ǰԪ��ֵ:\n");
                scanf_s("%d", &e);
                switch (NextElem(Lists.elem[usingList].L, e, e)) {
                    case OK:
                        printf("���Ԫ��Ϊ%d��\n", e);
                        break;
                    case ERROR:
                        printf("Ԫ��%d�ĺ��Ԫ�ز����ڣ�\n", e);
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 10:
                // printf("\n----ListInsert���ܴ�ʵ�֣�\n");
                printf("������λ��ֵ:\n");
                scanf_s("%d", &tmp);
                printf("������Ԫ��ֵ:\n");
                scanf_s("%d", &e);
                switch (ListInsert(Lists.elem[usingList].L, tmp, e)) {
                    case OK:
                        printf("Ԫ��%d����ɹ���\n", e);
                        break;
                    case ERROR:
                        printf("λ��%d�Ƿ���\n", tmp);
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                    case OVERFLOW:
                        printf("�ڴ����ʧ�ܣ�\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 11:
                // printf("\n----ListDelete���ܴ�ʵ�֣�\n");
                printf("������λ��ֵ:\n");
                scanf_s("%d", &tmp);
                switch (ListDelete(Lists.elem[usingList].L, tmp, e)) {
                    case OK:
                        printf("��%d��Ԫ��%dɾ���ɹ���\n", tmp, e);
                        break;
                    case ERROR:
                        printf("λ��%d�Ƿ���\n", tmp);
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 12:

                if (ListTraverse(Lists.elem[usingList].L) == INFEASIBLE) {
                    printf("���Ա�δ��ʼ����\n");
                }
                getchar();
                getchar();
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
                getchar();
                getchar();
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
                getchar();
                getchar();
                break;
            case 15:
                tmp = MaxSubArray(Lists.elem[usingList].L);
                printf("����������Ϊ%d��\n", tmp);
                getchar();
                getchar();
                break;
            case 16:
                printf("�������������:\n");
                scanf_s("%d", &e);
                tmp = SubArrayNum(Lists.elem[usingList].L, e);
                printf("��Ϊ%d����������Ϊ%d��\n", e, tmp);
                getchar();
                getchar();
                break;
            case 17:
                if (sortList(Lists.elem[usingList].L) == OK) {
                    printf("����ɹ���\n");
                } else {
                    printf("����ʧ�ܣ�\n");
                }
                getchar();
                getchar();
                break;
            case 18:
                printf("������Ҫɾ���ı���:\n");
                scanf_s("%s", s);
                if (RemoveList(Lists, s) == ERROR)printf("ɾ��ʧ�ܣ�\n");
                else printf("ɾ���ɹ���\n");
                getchar();
                getchar();
                break;
            case 19:
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
            case 20:
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
            case 21:
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
            default:;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
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
            printf("���Ա��ǿձ�\n");
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