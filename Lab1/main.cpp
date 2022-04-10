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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //˳���˳��ṹ���Ķ���
    ElemType *elem;
    int length;
    int listSize;
} SqList;

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
        // �X �T �[ �U �^ �a
        printf("    �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        printf("    �U  Menu for Linear Table On Sequence Structure   �U\n");
        printf("    �c�������������������������������������������������������������������������������������������������f\n");
        printf("    �U     1. InitList           2. DestroyList       �U\n");
        printf("    �U     3. ClearList          4. ListEmpty         �U\n");
        printf("    �U     5. ListLength         6. GetElem           �U\n");
        printf("    �U     7. LocateElem         8. PriorElem         �U\n");
        printf("    �U     9. NextElem           10. ListInsert       �U\n");
        printf("    �U     11. ListDelete        12. ListTraverse     �U\n");
        printf("    �U     13. SaveList          14. LoadList         �U\n");
        printf("    �U                  0. Exit                       �U\n");
        printf("    �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        printf("    ��ѡ����Ĳ���[0~12]:");
        scanf_s("%d", &op);
        switch (op) {
            case 1:
                switch (InitList(L)) {
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
                switch (DestroyList(L)) {
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
                switch (ClearList(L)) {
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
                switch (ListEmpty(L)) {
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
                if ((tmp = ListLength(L)) == INFEASIBLE)
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
                switch (GetElem(L, tmp, e)) {
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
                switch (tmp = LocateElem(L, e)) {
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
                switch (PriorElem(L, e, e)) {
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
                switch (NextElem(L, e, e)) {
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
                switch (ListInsert(L, tmp, e)) {
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
                switch (ListDelete(L, tmp, e)) {
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

                if (ListTraverse(L) == INFEASIBLE) {
                    printf("���Ա�δ��ʼ����\n");
                }
                getchar();
                getchar();
                break;
            case 13:
                printf("�������ļ�·��:\n");
                scanf("%s", filename);
                switch (SaveList(L, filename)) {
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
                switch (LoadList(L, filename)) {
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