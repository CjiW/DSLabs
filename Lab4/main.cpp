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
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
typedef struct {
    KeyType key;
    char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号
    int len;
    struct ArcNode *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode {                //头结点及其数组类型定义
    VertexType data;           //顶点信息
    ArcNode *firstarc;           //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {  //邻接表的类型定义
    AdjList vertices;          //头结点数组
    int vexnum, arcnum;         //顶点数、弧数
    GraphKind kind;        //图的类型
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
bool vis[MAX_VERTEX_NUM];
void (*visitFunc)(VertexType);
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][3]);

status DestroyGraph(ALGraph &G);

int LocateVex(ALGraph G, KeyType u);

status PutVex(ALGraph &G, KeyType u, VertexType value);

int FirstAdjVex(ALGraph G, KeyType u);

int NextAdjVex(ALGraph G, KeyType v, KeyType w);

status DeleteVex(ALGraph &G, KeyType v);

status InsertArc(ALGraph &G,KeyType v,KeyType w,int len);

status DeleteArc(ALGraph &G,KeyType v,KeyType w);

status DFSTraverse(ALGraph &G,void (*visit)(VertexType));

void output(VertexType v);

status BFSTraverse(ALGraph &G,void (*visit)(VertexType));

status SaveGraph(ALGraph G, char FileName[]);

status LoadGraph(ALGraph &G, char FileName[]);

//（1）距离小于k的顶点集合：函数名称是VerticesSetLessThanK(G,v,k)，初始条件是图G存在；操作结果是返回与顶点v距离小于k的顶点集合；
status VerticesSetLessThanK(ALGraph G,KeyType v,int k);
//（2）顶点间最短路径和长度：函数名称是ShortestPathLength(G,v,w); 初始条件是图G存在；操作结果是返回顶点v与顶点w的最短路径的长度；
int ShortestPathLength(ALGraph G,KeyType v,KeyType w);
//（3）图的连通分量：函数名称是ConnectedComponentsNums(G)，初始条件是图G存在；操作结果是返回图G的所有连通分量的个数；
int ConnectedComponentsNums(ALGraph G);

void (*Emp)(VertexType){};

int min(int a,int b){

}

int main() {
    int op = 1, tmp;
    VertexType v,*V;
    KeyType k;
    KeyType A[30][3];
    char filename[128], s[30];
    for (auto &i: Graphs.elem) {
        i.G.vexnum=i.G.arcnum=0;
    }
    Graphs.length = 1;

    strcpy(Graphs.elem[usingGraph].name, "Default");
    while (op) {
        system("cls");
        printf("\n\n");
        // ╔ ═ ╗ ║ ╚ ╝
        printf("    ╔═══════════════════════════════════════════════════════╗\n");
        printf("    ║               %d-%-10s                         ║\n", usingGraph, Graphs.elem[usingGraph].name);
        printf("    ╟───────────────────────────────────────────────────────╢\n");
        printf("    ║     1. CreateGraph         2. DestroyGraph            ║\n");
        printf("    ║     3. LocateVex           4. PutVex                  ║\n");
        printf("    ║     5. FirstAdjVex         6. NextAdjVex              ║\n");
        printf("    ║     7. DeleteVex           8. InsertArc               ║\n");
        printf("    ║     9. DeleteArc           10. DFSTraverse            ║\n");
        printf("    ║     11. BFSTraverse        12. VerticesSetLessThanK   ║\n");
        printf("    ║     13. ShortestPathLength 14. ConnectedComponentsNums║\n");
        printf("    ║     15. SaveGraph          16. LoadGraph              ║\n");
        printf("    ║     17. sortList           18. RemoveList             ║\n");
        printf("    ║     19. ChangeList         20. AddList                ║\n");
        printf("    ║     21. LocateList         0. Exit                    ║\n");
        printf("    ╚═══════════════════════════════════════════════════════╝\n");
        printf("    请选择你的操作[0~20]:");
        scanf_s("%d", &op);
        switch (op) {
            case 1:
                printf("请输入顶点数目:\n");
                scanf("%d",&tmp);
                V=(VertexType*) malloc(sizeof(VertexType)*(tmp+1));
                V[tmp].key=-1;
                for (int i = 0; i < tmp; ++i) {
                    scanf("%d %s",&V[i].key,V[i].others);
                }
                printf("请输入边的数目:\n");
                scanf("%d",&tmp);
                A[tmp][0]=-1;
                for (int i = 0; i < tmp; ++i) {
                    scanf("%d %d %d",A[i],A[i]+1,A[i]+2);
                }
                switch (CreateGraph(Graphs.elem[usingGraph].G,V,A)) {
                    case ERROR:
                        printf("创建失败！\n");
                        DestroyGraph(Graphs.elem[usingGraph].G);
                        break;
                    case OVERFLOW:
                        printf("内存分配失败！\n");
                        DestroyGraph(Graphs.elem[usingGraph].G);
                        break;
                    case INFEASIBLE:
                        printf("无向网已存在！\n");
                        break;
                    case OK:
                        printf("创建成功！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 2:
                switch (DestroyGraph(Graphs.elem[usingGraph].G)) {
                    case OK:
                        printf("销毁成功！\n");
                        break;
                    case INFEASIBLE:
                        printf("无向网不存在！\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 3:
                printf("")
                switch (LocateVex()) {

                }
                getchar();
                getchar();
                break;
            case 4:

                getchar();
                getchar();
                break;
            case 5:

                getchar();
                getchar();
                break;
            case 6:

                getchar();
                getchar();
                break;
            case 7:

                getchar();
                getchar();
                break;
            case 8:

                getchar();
                getchar();
                break;
            case 9:

                getchar();
                getchar();
                break;
            case 10:

                getchar();
                getchar();
                break;
            case 11:

                getchar();
                getchar();
                break;
            case 12:

                getchar();
                getchar();
                break;
            case 13:

                getchar();
                getchar();
                break;
            case 14:

                getchar();
                getchar();
                break;
            case 15:

                getchar();
                getchar();
                break;
            case 16:

                getchar();
                getchar();
                break;
            case 17:

                getchar();
                getchar();
                break;
            case 18:

                getchar();
                getchar();
                break;
            case 19:

                getchar();
                getchar();
                break;
            case 20:

                getchar();
                getchar();
                break;
            case 21:

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
}
void output(VertexType v){
    printf("%d %s\n",v.key,v.others);
}
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][3]) {
    if(G.vexnum)return INFEASIBLE;
    // V 重复？
    int val[1000] = {0}, i = 0;
    for (; V[i].key != -1; i++) {
        if (i >= MAX_VERTEX_NUM || val[V[i].key])return ERROR;// 结点太多？
        val[V[i].key] = 1;
    }
    if (!i)return ERROR;// 空？
    // copy 顶点
    for (i = 0; V[i].key != -1; i++) {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = nullptr;
    }
    G.vexnum = i;
    // 加边，头插
    for (i = 0; VR[i][0] != -1; i++) {
        int v, w;
        for (v = 0; v <= G.vexnum; v++)if (v == G.vexnum || G.vertices[v].data.key == VR[i][0])break;
        if (v == G.vexnum)return ERROR;// 找到 v ?
        for (w = 0; w <= G.vexnum; w++)if (w == G.vexnum || G.vertices[w].data.key == VR[i][1])break;
        if (w == G.vexnum)return ERROR;// 找到 w ?
        for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) {
            if (p->adjvex == w)return ERROR;// 重边？
        }
        auto newArc = (ArcNode *) malloc(sizeof(ArcNode));// 过去
        if (!newArc)return OVERFLOW;
        newArc->adjvex = w;
        newArc->len = VR[i][2];
        newArc->nextarc = G.vertices[v].firstarc;
        G.vertices[v].firstarc = newArc;
        newArc = (ArcNode *) malloc(sizeof(ArcNode));// 回来
        if (!newArc)return OVERFLOW;
        newArc->adjvex = v;
        newArc->len = VR[i][2];
        newArc->nextarc = G.vertices[w].firstarc;
        G.vertices[w].firstarc = newArc;
    }
    G.arcnum = i;
    G.kind = UDN;
    return OK;
}

status DestroyGraph(ALGraph &G) {
    if (!G.vexnum)return INFEASIBLE;
    for (int i = 0; i < G.vexnum; i++) {
        auto p = G.vertices[i].firstarc, q = p;
        while (p) {
            q = p->nextarc;
            free(p);
            p = q;
        }
    }
    G.vexnum = G.arcnum = 0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u) {
    int ind = -1;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) {
            ind = i;
            break;
        }
    }
    return ind;
}

status PutVex(ALGraph &G, KeyType u, VertexType value) {
    int ind = -1;
    for (int i = 0; i < G.vexnum; i++) {
        if (value.key != u && G.vertices[i].data.key == value.key)return ERROR;
        if (G.vertices[i].data.key == u)ind = i;
    }
    if (ind == -1)return ERROR;
    G.vertices[ind].data = value;
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) {
            return G.vertices[i].firstarc->adjvex;
        }
    }
    return -1;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v) {
            auto p = G.vertices[i].firstarc;
            while (p->nextarc) {
                if (G.vertices[p->adjvex].data.key == w)return p->nextarc->adjvex;
                p = p->nextarc;
            }
            break;
        }
    }
    return -1;
}

status InsertVex(ALGraph &G, VertexType v) {
    if (G.vexnum == MAX_VERTEX_NUM)return ERROR;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v.key)return ERROR;
    }
    G.vertices[G.vexnum++].data = v;
    return OK;
}

status DeleteVex(ALGraph &G, KeyType v){
    int tmp = 2 * G.arcnum;
    if (G.vexnum == 1)return ERROR;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v) {// 找到顶点 v
            auto p = G.vertices[i].firstarc, o = p;
            while (p) { // 删除所有边
                o = p->nextarc;
                free(p);
                p = o;
                tmp--;
            }
            for (int j = 0; j < G.vexnum; j++) {// 遍历所有边
                if (j == i)continue;// 排除已经删除的
                if ((p = G.vertices[j].firstarc)) {// 遍历所有边
                    if (p->adjvex == i) { // 头节点涉及删除点，删除
                        G.vertices[j].firstarc = p->nextarc;
                        free(p);
                        tmp--;
                    }
                    p = G.vertices[j].firstarc;
                    while (p) {
                        if (p->adjvex > i)p->adjvex--;// 调整位序
                        if (p->nextarc)
                            if (p->nextarc->adjvex == i) {//涉及删除点，删除
                                auto q = p->nextarc;
                                p->nextarc = p->nextarc->nextarc;
                                p = p->nextarc;
                                free(q);
                                tmp--;
                                continue;
                            }
                        p = p->nextarc;
                    }
                }
                if (j < i)continue;
                G.vertices[j - 1] = G.vertices[j];
            }
            G.vexnum--;
            G.arcnum = tmp / 2;
            return OK;
        }
    }
    return ERROR;
}
status InsertArc(ALGraph &G,KeyType v,KeyType w,int len)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    int iw=-1;
    // 查找 v 顶点
    for (int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data.key==w)iw=i;
        if(G.vertices[i].data.key==v){
            // 查找 w 顶点
            if(iw==-1){
                for (iw = i+1; iw < G.vexnum; iw++) {
                    if(G.vertices[iw].data.key==w)break;
                    if(iw==G.vexnum)return ERROR;
                }
            }
            ArcNode *p=G.vertices[i].firstarc,*NewArc;
            while (p){
                if(p->adjvex==iw)return ERROR;// 有边，返回ERROR
                p=p->nextarc;
            }
            // 插入单向边
            NewArc=(ArcNode*)malloc(sizeof(ArcNode));
            NewArc->adjvex=iw;
            NewArc->len=len;
            NewArc->nextarc=G.vertices[i].firstarc;
            G.vertices[i].firstarc=NewArc;
            NewArc=(ArcNode*)malloc(sizeof(ArcNode));
            NewArc->adjvex=i;
            NewArc->len=len;
            NewArc->nextarc=G.vertices[iw].firstarc;
            G.vertices[iw].firstarc=NewArc;
            G.arcnum++;
            return OK;
        }
    }
    return ERROR;
}
status DeleteArc(ALGraph &G,KeyType v,KeyType w){
    int iw=-1;
    for (int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data.key==w)iw=i;
        if(G.vertices[i].data.key==v){
            if(iw==-1){
                for (iw = i+1; iw < G.vexnum; iw++) {
                    if(G.vertices[iw].data.key==w)break;
                    if(iw==G.vexnum-1)return ERROR;
                }
            }
            ArcNode *p=G.vertices[i].firstarc,*q;
            if(p->adjvex==iw){
                G.vertices[i].firstarc=p->nextarc;
                free(p);
                p=G.vertices[iw].firstarc;
                if(p->adjvex==i){
                    G.vertices[iw].firstarc=p->nextarc;
                    free(p);
                    G.arcnum--;
                    return OK;
                }
                while (p->nextarc){
                    q=p->nextarc;
                    if(q->adjvex==i){
                        p->nextarc=q->nextarc;
                        free(q);
                        G.arcnum--;
                        return OK;
                    }
                    p=p->nextarc;
                }
            }
            while (p->nextarc){
                q=p->nextarc;
                if(q->adjvex==iw){
                    p->nextarc=q->nextarc;
                    free(q);
                    p=G.vertices[iw].firstarc;
                    if(p->adjvex==i){
                        G.vertices[iw].firstarc=p->nextarc;
                        free(p);
                        G.arcnum--;
                        return OK;
                    }
                    while (p->nextarc){
                        q=p->nextarc;
                        if(q->adjvex==i){
                            p->nextarc=q->nextarc;
                            free(q);
                            G.arcnum--;
                            return OK;
                        }
                        p=p->nextarc;
                    }
                }
                p=p->nextarc;
            }
        }
    }
    return ERROR;
}
void DFS(ALGraph G,int v,void (*visit)(VertexType)){
    visit(G.vertices[v].data);
    vis[v]=true;
    for (auto p=G.vertices[v].firstarc; p ; p=p->nextarc) {
        if(!vis[p->adjvex])DFS(G,p->adjvex,visit);
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    for (int i = 0; i < G.vexnum; i++) vis[i]=false;
    for (int i = 0; i < G.vexnum; i++) {
        if(!vis[i])DFS(G,i,visit);
    }
    memset(vis,0, sizeof(vis));
    return OK;
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType)){
    int queue[MAX_VERTEX_NUM+1],h=0,t=0;
    for (int i = 0; i < G.vexnum; i++) vis[i]=false;
    for (int i = 0; i < G.vexnum; i++) {
        if(!vis[i]){
            queue[t++]=i;
            vis[i]=true;
            visit(G.vertices[i].data);
            while (h!=t){
                h++;
                for (auto p=G.vertices[h-1].firstarc; p ; p=p->nextarc) {
                    if(!vis[p->adjvex]){
                        visit(G.vertices[queue[t++]=p->adjvex].data);
                        vis[p->adjvex]=true;
                    }
                }
            }
        }
    }
    memset(vis,0, sizeof(vis));
    return OK;
}
status SaveGraph(ALGraph G, char FileName[]){
    FILE *fw= fopen(FileName,"wb");int nil=-1;
    fwrite(&G.kind,sizeof G.kind,1,fw);
    fwrite(&G.vexnum,sizeof(int),1,fw);
    for (int i = 0; i < G.vexnum; ++i) {
        fwrite(&G.vertices[i].data, sizeof(VertexType),1,fw);
        ArcNode *tmp=G.vertices[i].firstarc;
        while (tmp){
            fwrite(&(tmp->adjvex), sizeof(int),1,fw);
            fwrite(&(tmp->len), sizeof(int),1,fw);
            tmp=tmp->nextarc;
        }
        fwrite(&nil, sizeof(int),2,fw);
    }
    fclose(fw);
    return OK;
}
status LoadGraph(ALGraph &G, char FileName[]){
    FILE *fr= fopen(FileName,"rb");
    G.vexnum=G.arcnum=0;
    fread(&G.kind,sizeof(GraphKind),1,fr);
    fread(&G.vexnum,sizeof(int),1,fr);
    for (int i = 0; i < G.vexnum; ++i) {
        fread(&(G.vertices[i].data), sizeof(VertexType),1,fr);
        G.vertices[i].firstarc= nullptr;
        auto NArc=(ArcNode*)malloc(sizeof(ArcNode));
        fread(&(NArc->adjvex), sizeof(int), 1, fr);
        fread(&(NArc->len), sizeof(int), 1, fr);
        NArc->nextarc= nullptr;
        if(NArc->adjvex == -1)continue;
        G.vertices[i].firstarc=NArc;
        auto head=NArc;
        while (true){
            NArc=(ArcNode*)malloc(sizeof(ArcNode));
            fread(&(NArc->adjvex), sizeof(int), 1, fr);
            fread(&(NArc->len), sizeof(int), 1, fr);
            if(NArc->adjvex == -1)break;
            head->nextarc=NArc;
            NArc->nextarc= nullptr;
            head=head->nextarc;
            G.arcnum++;
        }
    }
    fclose(fr);
    return OK;
}
//（1）距离小于k的顶点集合：函数名称是VerticesSetLessThanK(G,v,k)，初始条件是图G存在；操作结果是返回与顶点v距离小于k的顶点集合；
status VerticesSetLessThanK(ALGraph G,KeyType v,int k){
    int n=0;
    for (int i = 0; i < G.vexnum; ++i) {
        if(G.vertices[i].data.key==v){
            auto tmp=G.vertices[i].firstarc;
            while (tmp){
                if(tmp->len<k){
                    n++;
                    printf("【%d %s】",G.vertices[tmp->adjvex].data.key,G.vertices[tmp->adjvex].data.others);
                }
                tmp=tmp->nextarc;
            }
            if(n)return OK;
            return INFEASIBLE;
        }
    }
    return ERROR;
}
//（2）顶点间最短路径和长度：函数名称是ShortestPathLength(G,v,w); 初始条件是图G存在；操作结果是返回顶点v与顶点w的最短路径的长度；
int ShortestPathLength(ALGraph G,KeyType v,KeyType w){
    int dist[G.vexnum],start=-1,end=-1;
    for (int i = 0; i < G.vexnum; ++i) {
        dist[i]=INT_MAX;
        if(G.vertices[i].data.key==v)start=i;
        if(G.vertices[i].data.key==w)end=i;

    }
    if(start==-1||end==-1)return ERROR;
    dist[start]=0;
    for (int i = 1; i < G.vexnum; i++) {
        ArcNode *tmp=G.vertices[i].firstarc;
        while (tmp){
            dist[tmp->adjvex]=min(tmp->len+dist[i],dist[tmp->adjvex]);
            tmp=tmp->nextarc;
        }
    }
    return dist[end];
}
//（3）图的连通分量：函数名称是ConnectedComponentsNums(G)，初始条件是图G存在；操作结果是返回图G的所有连通分量的个数；

int ConnectedComponentsNums(ALGraph G){
    int ans=0;
    for (int i = 0; i < G.vexnum; ++i) {
        if(!vis[i]){
            DFS(G,i,Emp);
            ans++;
        }
    }
    return ans;
}