#include <cstdio>
#include <malloc.h>
#include <cstring>

using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号
    struct ArcNode  *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode{                //头结点及其数组类型定义
    VertexType data;           //顶点信息
    ArcNode *firstarc;           //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;          //头结点数组
    int vexnum,arcnum;         //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;
typedef struct {  //线性表的集合类型定义
    struct {
        char name[30];
        ALGraph G;
    } elem[10];
    int length;
} GRAPHS;
GRAPHS Graphs;      //线性表集合的定义Lists
int usingGraph = 0;
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
int main() {
    ALGraph G;
    KeyType VR[][2]={-1,-1};
    VertexType V[]={1, "G1", 2, "G2", 3, "G3", 4, "G4", 5, "G5", 6,"G6",
                    7, "G7", 8, "G8", 9,"G9", 10, "G10", 11, "G11", 12, "G12",
                    13, "G13", 14, "G14", 15, "G15", 16, "G16", 17, "G17", 18, "G18",
                    19, "G19", 20, "G20",  21, "G21",-1,"nil"};
    CreateCraph(G,V,VR);
    return 0;
}
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]){
    // V 重复？
    int val[1000]={0},i = 0;
    for (; V[i].key != -1; i++) {
        if(i>=MAX_VERTEX_NUM||val[V[i].key])return ERROR;// 结点太多？
        val[V[i].key]=1;
    }
    if(!i)return ERROR;// 空？
    // copy 顶点
    for (i = 0; V[i].key!=-1; i++) {
        G.vertices[i].data=V[i];
        G.vertices[i].firstarc=nullptr;
    }
    G.vexnum = i;
    // 加边，头插
    for (i = 0; VR[i][0]!=-1; i++) {
        int v,w;
        for (v = 0; v <= G.vexnum; v++)if(v==G.vexnum||G.vertices[v].data.key==VR[i][0])break;
        if(v==G.vexnum)return ERROR;// 找到 v ?
        for (w = 0; w <= G.vexnum; w++)if(w==G.vexnum||G.vertices[w].data.key==VR[i][1])break;
        if(w==G.vexnum)return ERROR;// 找到 w ?
        for (ArcNode *p = G.vertices[v].firstarc; p ; p=p->nextarc) {
            if(p->adjvex==w)return ERROR;// 重边？
        }
        auto newArc=(ArcNode*)malloc(sizeof(ArcNode));// 过去
        if(!newArc)return OVERFLOW;
        newArc->adjvex=w;
        newArc->nextarc=G.vertices[v].firstarc;
        G.vertices[v].firstarc=newArc;
        newArc=(ArcNode*)malloc(sizeof(ArcNode));// 回来
        if(!newArc)return OVERFLOW;
        newArc->adjvex=v;
        newArc->nextarc=G.vertices[w].firstarc;
        G.vertices[w].firstarc=newArc;
    }
    G.arcnum = i;
    G.kind=UDG;
    return OK;
}
status DestroyGraph(ALGraph &G){
    if(!G.vexnum)return INFEASIBLE;
    for (int i = 0; i < G.vexnum; i++) {
        auto p=G.vertices[i].firstarc,q=p;
        while (p){
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    G.vexnum=G.arcnum=0;
    return OK;
}
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{

}
