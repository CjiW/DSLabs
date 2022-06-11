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
    KeyType key;
    char others[20];
} TElemType; //二叉树结点类型定义
typedef struct BiTNode {    //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
int z = 0;
typedef struct {  //线性表的集合类型定义
    struct {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
} BiTrees;
BiTrees Trees;      //线性表集合的定义Lists
int usingBiTree = 0,flag=OK;
int keys[1000];

status CreateBiTree(BiTree &T, TElemType definition[]);

status ClearBiTree(BiTree &T);

bool BiTreeEmpty(BiTree T);

int BiTreeDepth(BiTree T);

BiTNode *LocateNode(BiTree T, KeyType e);

status Assign(BiTree &T, KeyType e, TElemType value);

BiTNode *GetSibling(BiTree T, KeyType e);

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);

status DeleteNode(BiTree &T, KeyType e);

status PreOrderTraverse(BiTree T, void (*visit)(BiTree));

status InOrderTraverse(BiTree T, void (*visit)(BiTree));

status PostOrderTraverse(BiTree T, void (*visit)(BiTree));

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

status SaveBiTree(BiTree T, char FileName[]);

status LoadBiTree(BiTree &T, char FileName[]);

status AddBiTree(BiTrees &TS,const char *TreeName);

status DestroyBiTree(BiTrees &TS,const char *TreeName);

int LocateBiTree(BiTrees TS,const char *TreeName);

int MaxPathSum(BiTree T);

BiTNode *LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2);

status InvertTree(BiTree &T);

void visit(BiTree T);

status save(BiTree T, FILE *fw);

int max(int a, int b);

int main() {
    int op = 1, tmp;
    KeyType k,k1;
    TElemType e, d[1000];
    BiTNode *node;
    memset(keys,0,sizeof keys);
    char filename[100], s[30];
    for (auto &i: Trees.elem) {
        i.T = nullptr;
    }
    Trees.length = 1;
    strcpy(Trees.elem[usingBiTree].name, "Default");
    while (op) {
        system("cls");
        printf("\n\n");
        printf("    ╔══════════════════════════════════════════════════════╗\n");
        printf("    ║                     %d-%-10s                     ║\n", usingBiTree, Trees.elem[usingBiTree].name);
        printf("    ╟──────────────────────────────────────────────────────╢\n");
        printf("    ║      1.  CreateBiTree         2.  ClearBiTree        ║\n");
        printf("    ║      3.  BiTreeEmpty          4.  BiTreeDepth        ║\n");
        printf("    ║      5.  LocateNode           6.  Assign             ║\n");
        printf("    ║      7.  GetSibling           8.  InsertNode         ║\n");
        printf("    ║      9.  DeleteNode           10. PreOrderTraverse   ║\n");
        printf("    ║      11. InOrderTraverse      12. PostOrderTraverse  ║\n");
        printf("    ║      13. LevelOrderTraverse   14. MaxPathSum         ║\n");
        printf("    ║      15. LowestCommonAncestor 16. InvertTree         ║\n");
        printf("    ║      17. SaveBiTree           18. LoadBiTree         ║\n");
        printf("    ║      19. AddBiTree            20. DestroyBiTree      ║\n");
        printf("    ║      21. ChangeBiTree         22. LocateBiTree       ║\n");
        printf("    ║                        0. Exit                       ║\n");
        printf("    ╚══════════════════════════════════════════════════════╝\n");
        printf("    请选择你的操作:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                tmp = 0;
                printf("请输入带空枝的先序序列【key others】:\n");
                while (scanf("%d %s", &d[tmp].key, d[tmp].others), d[tmp].key != -1)tmp++;
                switch (CreateBiTree(Trees.elem[usingBiTree].T, d)) {
                    case OK:
                        printf("二叉树创建成功！\n");
                        break;
                    case ERROR:
                        printf("存在重复关键字！\n");
                        break;
                    case INFEASIBLE:
                        printf("二叉树已存在！\n");
                        break;
                    case OVERFLOW:
                        printf("内存分配失败！\n");
                        break;
                }
                memset(keys,0,sizeof keys);z=0;
                getchar();
                getchar();
                break;
            case 2:
                switch (ClearBiTree(Trees.elem[usingBiTree].T)) {
                    case OK:
                        printf("二叉树清空成功！\n");
                        break;
                    case INFEASIBLE:
                        printf("二叉树为空！\n");
                }
                getchar();
                getchar();
                break;
            case 3:
                if (BiTreeEmpty(Trees.elem[usingBiTree].T)){
                    printf("二叉树为空。\n");
                } else{
                    printf("二叉树不空。\n");
                }
                getchar();
                getchar();
                break;
            case 4:
                printf("二叉树的深度为%d。\n", BiTreeDepth(Trees.elem[usingBiTree].T));
                getchar();
                getchar();
                break;
            case 5:
                printf("请输入目标结点关键字:\n");
                scanf("%d",&k);
                node=LocateNode(Trees.elem[usingBiTree].T,k);
                if(!node){
                    printf("未找到结点！\n");
                } else{
                    printf("结点为【%d %s】。\n",node->data.key,node->data.others);
                }
                getchar();
                getchar();
                break;
            case 6:
                printf("请输入要赋值结点的关键字:\n");
                scanf("%d",&k);
                printf("请输入【key others】:\n");
                scanf("%d %s",&e.key,e.others);
                switch (Assign(Trees.elem[usingBiTree].T, k, e)) {
                    case INFEASIBLE:
                        printf("未找到目标节点！\n");
                        break;
                    case ERROR:
                        printf("存在重复关键字！\n");
                        break;
                    case OK:
                        printf("赋值成功！\n变更为【%d-%s】\n",e.key,e.others);
                        break;
                }
                getchar();
                getchar();
                break;
            case 7:
                //GetSibling()
                printf("请输入key:\n");
                scanf("%d",&k);
                node=GetSibling(Trees.elem[usingBiTree].T, k);
                if(!node){
                    printf("未找到其兄弟结点！\n");
                } else{
                    printf("兄弟结点为【%d %s】\n",node->data.key,node->data.others);
                }
                getchar();
                getchar();
                break;
            case 8:
                //InsertNode()
                printf("请输入目标结点关键字:\n");
                scanf("%d", &k);
                printf("请输入插入选项【-1|0|1】:\n");
                scanf("%d", &tmp);
                printf("请输入插入结点【key others】:\n");
                scanf("%d %s", &e.key, &e.others);
                switch (InsertNode(Trees.elem[usingBiTree].T, k, tmp, e)) {
                    case INFEASIBLE:
                        printf("存在重复关键字！\n");
                        break;
                    case ERROR:
                        printf("未找到目标结点！\n");
                        break;
                    case OK:
                        printf("插入【%d %s】成功！\n",e.key,e.others);
                        break;
                }
                getchar();
                getchar();
                break;
            case 9:
                printf("请输入要删除结点的关键字:\n");
                scanf("%d",&k);
                switch (DeleteNode(Trees.elem[usingBiTree].T, k)) {
                    case OK:
                        printf("结点删除成功！\n");
                        break;
                    case ERROR:
                        printf("未找到目标结点！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 10:
                //PreOrderTraverse()
                switch (PreOrderTraverse(Trees.elem[usingBiTree].T,visit)) {
                    case ERROR:
                        printf("二叉树为空！\n");
                        break;
                    case OK:
                        printf("\n遍历成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 11:
                //InOrderTraverse()
                switch (InOrderTraverse(Trees.elem[usingBiTree].T,visit)) {
                    case ERROR:
                        printf("二叉树为空！\n");
                        break;
                    case OK:
                        printf("\n遍历成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 12:
                //PostOrderTraverse()
                switch (PostOrderTraverse(Trees.elem[usingBiTree].T,visit)) {
                    case ERROR:
                        printf("二叉树为空！\n");
                        break;
                    case OK:
                        printf("\n遍历成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 13:
                //LevelOrderTraverse()
                switch (LevelOrderTraverse(Trees.elem[usingBiTree].T, visit)) {
                    case OVERFLOW:
                        printf("\n遍历失败！\n");
                        break;
                    case INFEASIBLE:
                        printf("二叉树为空！\n");
                        break;
                    case OK:
                        printf("\n遍历成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 14:
                //MaxPathSum
                if (!(tmp=MaxPathSum(Trees.elem[usingBiTree].T))) {
                    printf("二叉树为空！\n");
                } else{
                    printf("最大路径和为%d。\n",tmp);
                }
                getchar();
                getchar();
                break;
            case 15:
                //LowestCommonAncestor
                printf("请输入两结点的关键字:\n");
                scanf("%d%d",&k,&k1);
                node=LowestCommonAncestor(Trees.elem[usingBiTree].T,k,k1);
                if(node!=nullptr){
                    printf("最近公共祖先为【%d %s】\n",node->data.key,node->data.others);
                }else{
                    printf("两结点不都存在！\n");
                }
                getchar();
                getchar();
                break;
            case 16:
                //InvertTree
                switch (InvertTree(Trees.elem[usingBiTree].T)) {
                    case ERROR:
                        printf("二叉树为空！\n");
                        break;
                    case OK:
                        printf("二叉树翻转成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 17:
                //SaveBiTree
                printf("请输入文件路径:\n");
                scanf("%s",filename);
                switch (SaveBiTree(Trees.elem[usingBiTree].T, filename)) {
                    case ERROR:
                        printf("二叉树保存失败！\n");
                        break;
                    case OK:
                        printf("二叉树保存成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 18:
                //LoadBiTree
                printf("请输入文件路径:\n");
                scanf("%s",filename);
                switch (LoadBiTree(Trees.elem[usingBiTree].T, filename)) {
                    case ERROR:
                        printf("二叉树加载失败！\n");
                        break;
                    case INFEASIBLE:
                        printf("二叉树已存在！\n");
                        break;
                    case OVERFLOW:
                        printf("内存分配失败！\n");
                        break;
                    case OK:
                        printf("二叉树加载成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 19:
                //AddBiTree
                printf("请输入要创建的二叉树名:\n");
                scanf("%s", s);
                switch (AddBiTree(Trees, s)) {
                    case OK:
                        printf("创建成功！\n");
                        break;
                    case OVERFLOW:
                        printf("当前二叉树过多！\n");
                        break;
                    case ERROR:
                        printf("二叉树已存在！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 20:
                //DestroyBiTree
                printf("请输入要销毁的树名:\n");
                scanf("%s", s);
                if (DestroyBiTree(Trees, s) == ERROR)printf("删除失败！\n");
                else printf("删除成功！\n");
                getchar();
                getchar();
                break;
            case 21:
                //ChangeBiTree
                printf("请输入要使用的二叉树名:\n");
                scanf("%s", s);
                tmp = LocateBiTree(Trees, s);
                if (tmp) {
                    usingBiTree = tmp - 1;
                    printf("变更成功！\n当前二叉树:%d-%s\n", usingBiTree, Trees.elem[usingBiTree].name);
                } else {
                    printf("二叉树不存在！\n");
                }
                getchar();
                getchar();
                break;
            case 22:
                //LocateBiTree
                printf("请输入二叉树名:\n");
                scanf("%s", s);
                tmp = LocateBiTree(Trees, s);
                if (!tmp) {
                    printf("%s二叉树不存在！\n", s);
                } else {
                    printf("%s是第%d个二叉树。\n", s, tmp - 1);
                }
                getchar();
                getchar();
                break;
            case 0:
                break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    getchar();
    getchar();
    return 0;
}

void visit(BiTree T) {
    printf("【%d-%s】", T->data.key,T->data.others);
}

status CreateBiTree(BiTree &T, TElemType definition[]) {
    if (T)return INFEASIBLE;
    if (definition[z].key == -1)
        return OK;
    if (definition[z].key > 0) {
        if(keys[definition[z].key])return ERROR;
        keys[definition[z].key]=1;
    }
    z++;
    if (definition[z - 1].key == 0)T = nullptr;
    else {
        if (!(T = (BiTNode *) malloc(sizeof(BiTNode)))){
            return OVERFLOW;
        }
        T->data = definition[z - 1];
        T->lchild = T->rchild = nullptr;
        flag=CreateBiTree(T->lchild, definition);
        if (flag == ERROR||flag==OVERFLOW){
            free(T);
            T=nullptr;
            return flag;
        }
        flag=CreateBiTree(T->rchild, definition);
        if (flag == ERROR||flag==OVERFLOW){
            ClearBiTree(T);
            T=nullptr;
            return flag;
        }
    }
    return OK;
}

status ClearBiTree(BiTree &T) {
    if (!T)return INFEASIBLE;
    if (T->lchild)ClearBiTree(T->lchild);
    if (T->rchild)ClearBiTree(T->rchild);
    free(T);
    T = nullptr;
    return OK;
}
bool BiTreeEmpty(BiTree T){
    return T==nullptr;
}
int BiTreeDepth(BiTree T) {
    if (!T)return 0;
    return max(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild)) + 1;
}

BiTNode *LocateNode(BiTree T, KeyType e) {
    BiTNode *tmp;
    if (!T || T->data.key == e)return T;
    if ((tmp = LocateNode(T->lchild, e)))return tmp;
    if ((tmp = LocateNode(T->rchild, e)))return tmp;
    return nullptr;
}

status Assign(BiTree &T, KeyType e, TElemType value) {
    BiTNode *tmp1 = LocateNode(T, e), *tmp2 = nullptr;
    if (!tmp1)return INFEASIBLE;
    if (value.key != e)tmp2 = LocateNode(T, value.key);
    if(tmp2)return ERROR;
    tmp1->data = value;
    return OK;
}

BiTNode *GetSibling(BiTree T, KeyType e) {
    if((!T)||(!T->lchild) && (!T->rchild))return nullptr;
    BiTNode *tmp;
    if (T->lchild && T->lchild->data.key == e)return T->rchild;
    if (T->rchild && T->rchild->data.key == e)return T->lchild;
    if ((tmp = GetSibling(T->lchild, e)))return tmp;
    if ((tmp = GetSibling(T->rchild, e)))return tmp;
    return nullptr;
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c){
    if (!T)return ERROR;
    if (LocateNode(T, c.key))return INFEASIBLE;
    auto *tmp = (BiTNode *) malloc(sizeof(BiTNode));
    tmp->data = c;
    if (T->data.key == e || LR == -1) {
        switch (LR) {
            case -1:
                tmp->rchild = T;
                tmp->lchild = nullptr;
                T = tmp;
                break;
            case 0:
                tmp->lchild = T->lchild;
                tmp->rchild = nullptr;
                T->lchild = tmp;
                break;
            case 1:
                tmp->rchild = T->rchild;
                tmp->lchild = nullptr;
                T->rchild = tmp;
                break;
        }
        return OK;
    } else {
        int st = 0;
        if (T->lchild) {
            if(InsertNode(T->lchild, e, LR, c)==OK)st++;
        }
        if (T->rchild) {
            if(InsertNode(T->rchild, e, LR, c)==OK)st++;
        }
        return st==0?ERROR:OK;
    }
}

status DeleteNode(BiTree &T, KeyType e) {
    if (!T)return ERROR;
    BiTNode *tmp, *p;
    if (T->data.key == e) {
        tmp = T;
        if (T->lchild) { // 左子树不为空
            p = T->lchild;
            while (p->rchild)p = p->rchild;
            p->rchild = T->rchild;
            T = T->lchild;
        } else if (T->rchild) { //左子树为空，右子树不空
            T = T->rchild;
        } else { //左右子树皆空
            T = nullptr;
        }
        free(tmp);
        return OK;
    } else {
        int st = 0;
        if (T->lchild) {
            if(DeleteNode(T->lchild, e)==OK)st++ ;
        }
        if (T->rchild) {
            if(DeleteNode(T->rchild, e)==OK)st++;
        }
        return st==0?ERROR:OK;
    }
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree)){
    if (!T)return ERROR;
    visit(T);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
    return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree)){
    if(!T)return ERROR;
    BiTNode *tmp[100];
    int top = -1;
    auto p = T;
    while (p || top + 1) {
        if (p) {
            tmp[++top] = p;
            p = p->lchild;
        } else {
            p = tmp[top--];
            visit(p);
            p = p->rchild;
        }
    }
    return OK;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree)){
    if (!T)return ERROR;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (!T)return INFEASIBLE;
    // 队空 - h==t; 队满 - h-t==1
    BiTNode *tmp[10000];
    int h = 0, t = 0;
    tmp[t++] = T;
    while (h != t) { // 队不空
        int x = t;
        for (int i = h; i < x; i++) {
            if (tmp[h]->lchild) {
                if (h - t == 1)return OVERFLOW;
                tmp[t++] = tmp[h]->lchild;
            }
            if (tmp[h]->rchild) {
                if (h - t == 1)return OVERFLOW;
                tmp[t++] = tmp[h]->rchild;
            }
            visit(tmp[h++]); //出队
        }
    }

    return OK;
}

status save(BiTree T, FILE *fw) {
    TElemType empty = {0, "null"};
    if (T) {
        if(!fwrite(&T->data, sizeof(TElemType), 1, fw))return ERROR;
        if(save(T->lchild, fw)==ERROR)return ERROR;
        if(save(T->rchild, fw)==ERROR)return ERROR;
        return OK;
    } else {
        if(!fwrite(&empty, sizeof(TElemType), 1, fw))return ERROR;
        return OK;
    }
}

status SaveBiTree(BiTree T, char FileName[]) {
    FILE *fw = fopen(FileName, "wb");
    if (!fw)return ERROR;
    if(save(T, fw)==ERROR)return ERROR;
    fclose(fw);
    return OK;
}

status LoadBiTree(BiTree &T, char FileName[]){
    FILE *fr = fopen(FileName, "rb");
    if (!fr)return ERROR;
    TElemType D[10000];
    int i = 0;
    for (; fread(D + i, sizeof(TElemType), 1, fr); i++);
    fclose(fr);
    D[i] = {-1, "null"};
    z = 0;
    return CreateBiTree(T, D);
}

status AddBiTree(BiTrees &TS, const char *TreeName) {
    if (TS.length >= 10)return OVERFLOW;
    if (LocateBiTree(TS, TreeName)) return ERROR;
    int i = 0;
    while ((TS.elem[TS.length].name[i] = TreeName[i]))i++;
    TS.elem[TS.length].T = nullptr;
    TS.length++;
    return OK;
}

status DestroyBiTree(BiTrees &TS, const char *TreeName) {
    int i = LocateBiTree(TS, TreeName);
    if (!i)
        return INFEASIBLE;
    if (i == usingBiTree + 1)
        return ERROR;
    i--;
    if (usingBiTree >= i)usingBiTree--;
    ClearBiTree(TS.elem[i].T);
    for (; i < TS.length; i++) {
        int j = 0;
        while ((TS.elem[i].name[j] = TS.elem[i + 1].name[j]))j++;
        TS.elem[i].T = TS.elem[i + 1].T;
    }
    TS.length--;
    return OK;

}

int LocateBiTree(BiTrees TS, const char *TreeName) {
    for (int i = 0; i < TS.length; i++) {
        if (strcmp(TS.elem[i].name, TreeName) != 0)continue;
        return i + 1;
    }
    return 0;
}

int MaxPathSum(BiTree T){
    if (!T)return 0;
    return T->data.key+ max(MaxPathSum(T->lchild),MaxPathSum(T->rchild));
}

bool DFS(BiTree T,KeyType e1,KeyType e2,BiTNode *&N){
    if (!T)return false;
    bool f1= DFS(T->lchild,e1,e2,N),f2=DFS(T->rchild,e1,e2,N);
    if((f1&&f2)||((f1||f2)&&(T->data.key==e1||T->data.key==e2))){
        N=T;
    }
    if(f1||f2||(T->data.key==e1||T->data.key==e2)){
        return true;
    }
    return false;
}

BiTNode *LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2){
    BiTNode *N=nullptr;
    DFS(T,e1,e2,N);
    return N;

}

status InvertTree(BiTree &T){
    if(!T)return ERROR;
    BiTree TT=T->rchild;
    T->rchild=T->lchild;
    T->lchild=TT;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
    return OK;
}


int max(int a, int b) {
    return a > b ? a : b;
}