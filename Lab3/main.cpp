#include <iostream>
#include <malloc.h>

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
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{    //二叉链表结点的定义  
    TElemType data;
    struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
int z=0;
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
int max(int a,int b);
int main() {
    TElemType D[]={1 ,"a", 2 ,"b", 0, "null",0,"null",3,"c",4,"d",
                   0,"null", 0,"null",5,"e",0,"null",0,"null",-1,"null"};
    BiTree T=nullptr;
    CreateBiTree(T,D);
    return 0;
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
BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    BiTNode *tmp;
    if((!T->lchild)&&(!T->rchild))return nullptr;
    if(T->lchild&&T->lchild->data.key==e)return T->rchild;
    if(T->rchild&&T->rchild->data.key==e)return T->lchild;
    if((tmp=GetSibling(T->lchild,e)))return tmp;
    if((tmp=GetSibling(T->rchild,e)))return tmp;
    return nullptr;
}
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{

}
status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{

}
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    if(!T)return OK;
    visit(T);
    PreOrderTraverse(T->lchild,visit);
    PreOrderTraverse(T->rchild,visit);
    return OK;
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
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
//后序遍历二叉树T
{
    if(!T)return OK;
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    visit(T);
    return OK;
}
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    BiTNode *tmp[100];int b=0,t=0;
    auto p=T;

    return OK;
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{

}
status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{

}
int max(int a,int b){
    return a>b?a:b;
}