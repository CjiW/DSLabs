#include <iostream>
#include <malloc.h>
#include <cstring>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //������������Ͷ���
typedef struct BiTNode{    //����������Ķ���  
    TElemType data;
    struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
int z=0;
typedef struct {  //���Ա�ļ������Ͷ���
    struct {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
} BiTrees;
BiTrees Trees;      //���Ա��ϵĶ���Lists
int usingBiTree = 0;
status CreateBiTree(BiTree &T,TElemType definition[]);
status ClearBiTree(BiTree &T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T,  char FileName[]);
void visit(BiTree T);
status save(BiTree T,FILE *fw);
int max(int a,int b);
int main() {
    int op=1,tmp;
    TElemType e,d[1000];
    char filename[100],s[30];
    for (auto &i: Trees.elem) {
        i.T = nullptr;
    }
    Trees.length = 1;
    strcpy(Trees.elem[usingBiTree].name, "Default");
    while(op) {
        system("cls");
        printf("\n\n");
        printf("    �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        printf("    �U                     %d-%-10s                     �U\n", usingBiTree, Trees.elem[usingBiTree].name);
        printf("    �c�������������������������������������������������������������������������������������������������������������f\n");
        printf("    �U       1.  CreateBiTree      2.  DestroyBiTree        �U\n");
        printf("    �U       3.  ClearBiTree       4.  BiTreeEmpty          �U\n");
        printf("    �U       5.  BiTreeDepth       6.  LocateNode           �U\n");
        printf("    �U       7.  Assign            8.  GetSibling           �U\n");
        printf("    �U       9.  InsertNode        10. DeleteNode           �U\n");
        printf("    �U       11. PreOrderTraverse  12. InOrderTraverse      �U\n");
        printf("    �U       13. PostOrderTraverse 14. LevelOrderTraverse   �U\n");
        printf("    �U       15. MaxPathSum        16. LowestCommonAncestor �U\n");
        printf("    �U       17. InvertTree        18. SaveBiTree           �U\n");
        printf("    �U       19. LoadBiTree        20. AddTree              �U\n");
        printf("    �U       21. RemoveTree        22. ChangeTree           �U\n");
        printf("    �U       23. LocateTree        0.  Exit                 �U\n");
        printf("    �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        printf("    ��ѡ����Ĳ���[0~20]:");
        scanf_s("%d", &op);
        switch (op) {
            case 1:
                tmp=0;
                printf("���������֦����������:\n");
                while (scanf("%d %s",&d[tmp].key,d[tmp].others),d[tmp].key!=-1)tmp++;
                switch (CreateBiTree(Trees.elem[usingBiTree].T,d)) {
                    case OK:
                        printf("�����������ɹ���\n");break;
                    case ERROR:
                        printf("�����ظ��ؼ��֣�\n");break;
                    case INFEASIBLE:
                        printf("�������Ѵ��ڣ�\n");break;
                }
                getchar();getchar();
                break;
            case 14:
                switch (LevelOrderTraverse(Trees.elem[usingBiTree].T, visit)) {
                    case OVERFLOW:
                        printf("\n����ʧ�ܣ�\n");break;
                    case INFEASIBLE:
                        printf("��Ϊ�գ�\n");break;
                    case OK:
                        printf("\n�����ɹ���\n");break;
                }
                getchar();getchar();
                break;
            case 0:
                break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    getchar();
    getchar();
    return 0;
}
void visit(BiTree T){
    printf("%d ",T->data.key);
}
status CreateBiTree(BiTree &T,TElemType definition[]){
    if (T)return INFEASIBLE;
    if(definition[z].key==-1)
        return OK;
    if(definition[z].key>0){
        int i=0;
        while (definition[z+(++i)].key!=-1){
            if(definition[z+i].key==definition[z].key)return ERROR;
        }
    }
    z++;
    if(definition[z-1].key==0)T=nullptr;
    else{
        if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))return OVERFLOW;
        T->data=definition[z-1];
        T->lchild=T->rchild=nullptr;
        if(CreateBiTree(T->lchild,definition)==ERROR)return ERROR;
        if(CreateBiTree(T->rchild,definition)==ERROR)return ERROR;
    }
    return OK;
}

status ClearBiTree(BiTree &T){
    if (!T)return INFEASIBLE;
    if(T->lchild)ClearBiTree(T->lchild);
    if(T->rchild)ClearBiTree(T->rchild);
    free(T);
    T= nullptr;
    return OK;
}
int BiTreeDepth(BiTree T){
    if (!T)return 0;
    return max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild))+1;
}
BiTNode* LocateNode(BiTree T,KeyType e){
    BiTNode *tmp;
    if(!T||T->data.key==e)return T;
    if((tmp=LocateNode(T->lchild,e)))return tmp;
    if((tmp=LocateNode(T->rchild,e)))return tmp;
    return nullptr;
}
status Assign(BiTree &T,KeyType e,TElemType value){
    BiTNode *tmp1= LocateNode(T,e),*tmp2=nullptr;
    if(value.key!=e)tmp2=LocateNode(T,value.key);
    if(!tmp1||tmp2)return ERROR;
    tmp1->data=value;
    return OK;
}
BiTNode* GetSibling(BiTree T,KeyType e){
    BiTNode *tmp;
    if((!T->lchild)&&(!T->rchild))return nullptr;
    if(T->lchild&&T->lchild->data.key==e)return T->rchild;
    if(T->rchild&&T->rchild->data.key==e)return T->lchild;
    if((tmp=GetSibling(T->lchild,e)))return tmp;
    if((tmp=GetSibling(T->rchild,e)))return tmp;
    return nullptr;
}
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
// e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��LRΪ0��1��c�Ǵ������㣻
// ����LRΪ0����1��������c��T�У���Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬���e��ԭ������������������Ϊ���c��������������OK��
// �������ʧ�ܣ�����ERROR��
// �ر�أ���LRΪ-1ʱ����Ϊ�������룬ԭ�������Ϊc����������
{
    if(LocateNode(T,c.key))return ERROR;
    auto *tmp=(BiTNode*) malloc(sizeof(BiTNode));
    tmp->data=c;
    int status=ERROR;
    if(T->data.key==e||LR==-1){
        switch (LR) {
            case -1:
                tmp->rchild=T;
                tmp->lchild= nullptr;
                T=tmp;
                break;
            case 0:
                tmp->lchild=T->lchild;
                tmp->rchild= nullptr;
                T->lchild=tmp;
                break;
            case 1:
                tmp->rchild=T->rchild;
                tmp->lchild= nullptr;
                T->rchild=tmp;
                break;
        }
        status=OK;
    } else{
        if(T->lchild){
            status|=InsertNode(T->lchild,e,LR,c);
        }
        if(T->rchild){
            status|=InsertNode(T->rchild,e,LR,c);
        }
    }
    return status;
}
status DeleteNode(BiTree &T,KeyType e){
    BiTNode *tmp,*p;
    int status=ERROR;
    if(T->data.key==e){
        tmp=T;
        if (T->lchild){ // ��������Ϊ��
            p=T->lchild;
            while (p->rchild)p=p->rchild;
            p->rchild=T->rchild;
            T=T->lchild;
        }
        else if (T->rchild){ //������Ϊ��
            T=T->rchild;
        } else{
            T= nullptr;
        }
        free(tmp);
        status=OK;
    } else{
        if(T->lchild){
            status|=DeleteNode(T->lchild,e);
        }
        if(T->rchild){
            status|=DeleteNode(T->rchild,e);
        }
    }
    return status;
}
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    if(!T)return OK;
    visit(T);
    PreOrderTraverse(T->lchild,visit);
    PreOrderTraverse(T->rchild,visit);
    return OK;
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    BiTNode *tmp[100];int top=-1;
    auto p=T;
    while (p||top+1){
        if(p){
            tmp[++top]=p;
            p=p->lchild;
        } else{
            p=tmp[top--];
            visit(p);
            p=p->rchild;
        }
    }
    return OK;
}
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    if(!T)return OK;
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    visit(T);
    return OK;
}
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree)){
    if (!T)return INFEASIBLE;
    // �ӿ� - h==t; ���� - h-t==1
    BiTNode *tmp[10000];int h=0,t=0;
    tmp[t++]=T;
    while (h!=t){ // �Ӳ���
        int x=t;
        for (int i = h; i < x; i++) {
            if(tmp[h]->lchild){
                if (h-t==1)return OVERFLOW;
                tmp[t++]=tmp[h]->lchild;
            }
            if(tmp[h]->rchild){
                if (h-t==1)return OVERFLOW;
                tmp[t++]=tmp[h]->rchild;
            }
            visit(tmp[h++]); //����
        }
    }

    return OK;
}

status save(BiTree T,FILE *fw){
    TElemType empty={0, "null"};
    if(T){
        fwrite(&T->data, sizeof(TElemType),1,fw);
        save(T->lchild,fw);
        save(T->rchild,fw);
        return OK;
    }
    else {
        fwrite(&empty, sizeof(TElemType), 1, fw);
        return OK;
    }
}
status SaveBiTree(BiTree T, char FileName[]){
    FILE*fw= fopen(FileName,"wb");
    if(!fw)return ERROR;
    save(T,fw);
    fclose(fw);
    return OK;
}
status LoadBiTree(BiTree &T,  char FileName[])
//�����ļ�FileName�Ľ�����ݣ�����������
{
    FILE *fr= fopen(FileName,"rb");
    if(!fr)return ERROR;
    TElemType D[10000];
    int i = 0;
    for (; fread(D+i, sizeof(TElemType),1,fr); i++);
    fclose(fr);
    D[i]={-1,"null"};
    z=0;
    CreateBiTree(T,D);
    return OK;
}
int max(int a,int b){
    return a>b?a:b;
}