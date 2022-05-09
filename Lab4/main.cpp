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
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
    int adjvex;              //����λ�ñ��
    struct ArcNode *nextarc;       //��һ������ָ��
} ArcNode;
typedef struct VNode {                //ͷ��㼰���������Ͷ���
    VertexType data;           //������Ϣ
    ArcNode *firstarc;           //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;          //ͷ�������
    int vexnum, arcnum;         //������������
    GraphKind kind;        //ͼ������
} ALGraph;
typedef struct {  //���Ա�ļ������Ͷ���
    struct {
        char name[30];
        ALGraph G;
    } elem[10];
    int length;
} GRAPHS;
GRAPHS Graphs;      //���Ա��ϵĶ���Lists
int usingGraph = 0;
bool vis[MAX_VERTEX_NUM];
void (*visitFunc)(VertexType);
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]);

status DestroyGraph(ALGraph &G);

int LocateVex(ALGraph G, KeyType u);

status PutVex(ALGraph &G, KeyType u, VertexType value);

int FirstAdjVex(ALGraph G, KeyType u);

int NextAdjVex(ALGraph G, KeyType v, KeyType w);

status DeleteVex(ALGraph &G, KeyType v);

status InsertArc(ALGraph &G,KeyType v,KeyType w);

status DeleteArc(ALGraph &G,KeyType v,KeyType w);

status DFSTraverse(ALGraph &G,void (*visit)(VertexType));

void output(VertexType v);

status BFSTraverse(ALGraph &G,void (*visit)(VertexType));

status SaveGraph(ALGraph G, char FileName[]);

status LoadGraph(ALGraph &G, char FileName[]);
int main() {
    ALGraph G;
    KeyType VR[][2] = {5, 6, -1, -1};
    VertexType V[] = {5, "���Ա�", 8, "����", 7, "������", 6, "����ͼ", -1, "nil"};
    CreateCraph(G, V, VR);
    int i;

    for (i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        printf("%d %s", G.vertices[i].data.key, G.vertices[i].data.others);
        while (p) {
            printf(" %d", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
    DFSTraverse(G,output);
    return 0;
}
void output(VertexType v){
    printf("%d %s\n",v.key,v.others);
}
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {
    // V �ظ���
    int val[1000] = {0}, i = 0;
    for (; V[i].key != -1; i++) {
        if (i >= MAX_VERTEX_NUM || val[V[i].key])return ERROR;// ���̫�ࣿ
        val[V[i].key] = 1;
    }
    if (!i)return ERROR;// �գ�
    // copy ����
    for (i = 0; V[i].key != -1; i++) {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = nullptr;
    }
    G.vexnum = i;
    // �ӱߣ�ͷ��
    for (i = 0; VR[i][0] != -1; i++) {
        int v, w;
        for (v = 0; v <= G.vexnum; v++)if (v == G.vexnum || G.vertices[v].data.key == VR[i][0])break;
        if (v == G.vexnum)return ERROR;// �ҵ� v ?
        for (w = 0; w <= G.vexnum; w++)if (w == G.vexnum || G.vertices[w].data.key == VR[i][1])break;
        if (w == G.vexnum)return ERROR;// �ҵ� w ?
        for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) {
            if (p->adjvex == w)return ERROR;// �رߣ�
        }
        auto newArc = (ArcNode *) malloc(sizeof(ArcNode));// ��ȥ
        if (!newArc)return OVERFLOW;
        newArc->adjvex = w;
        newArc->nextarc = G.vertices[v].firstarc;
        G.vertices[v].firstarc = newArc;
        newArc = (ArcNode *) malloc(sizeof(ArcNode));// ����
        if (!newArc)return OVERFLOW;
        newArc->adjvex = v;
        newArc->nextarc = G.vertices[w].firstarc;
        G.vertices[w].firstarc = newArc;
    }
    G.arcnum = i;
    G.kind = UDG;
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
        if (G.vertices[i].data.key == v) {// �ҵ����� v
            auto p = G.vertices[i].firstarc, o = p;
            while (p) { // ɾ�����б�
                o = p->nextarc;
                free(p);
                p = o;
                tmp--;
            }
            for (int j = 0; j < G.vexnum; j++) {// �������б�
                if (j == i)continue;// �ų��Ѿ�ɾ����
                if ((p = G.vertices[j].firstarc)) {// �������б�
                    if (p->adjvex == i) { // ͷ�ڵ��漰ɾ���㣬ɾ��
                        G.vertices[j].firstarc = p->nextarc;
                        free(p);
                        tmp--;
                    }
                    p = G.vertices[j].firstarc;
                    while (p) {
                        if (p->adjvex > i)p->adjvex--;// ����λ��
                        if (p->nextarc)
                            if (p->nextarc->adjvex == i) {//�漰ɾ���㣬ɾ��
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
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int iw=-1;
    // ���� v ����
    for (int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data.key==w)iw=i;
        if(G.vertices[i].data.key==v){
            // ���� w ����
            if(iw==-1){
                for (iw = i+1; iw < G.vexnum; iw++) {
                    if(G.vertices[iw].data.key==w)break;
                    if(iw==G.vexnum)return ERROR;
                }
            }
            ArcNode *p=G.vertices[i].firstarc,*NewArc=(ArcNode*)malloc(sizeof(ArcNode));
            while (p){
                if(p->adjvex==iw)return ERROR;// �бߣ�����ERROR
                p=p->nextarc;
            }
            // ���뵥���
            NewArc->adjvex=iw;
            NewArc->nextarc=G.vertices[i].firstarc;
            G.vertices[i].firstarc=NewArc;
            NewArc=(ArcNode*)malloc(sizeof(ArcNode));
            NewArc->adjvex=i;
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
void DFS(ALGraph G,int v){
    visitFunc(G.vertices[v].data);
    vis[v]=true;
    for (auto p=G.vertices[v].firstarc; p ; p=p->nextarc) {
        if(!vis[p->adjvex])DFS(G,p->adjvex);
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    visitFunc=visit;
    for (int i = 0; i < G.vexnum; i++) vis[i]=false;
    for (int i = 0; i < G.vexnum; i++) {
        if(!vis[i])DFS(G,i);
    }
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
    return OK;
}
status SaveGraph(ALGraph G, char FileName[]){
    FILE *fw= fopen(FileName,"wb");
    fwrite(&G.kind,sizeof G.kind,1,fw);
    fwrite(&G.vexnum,sizeof(int),1,fw);
    fwrite(&G.arcnum,sizeof(int),1,fw);
    for (int i = 0; i < G.vexnum; ++i) {
        fwrite(&G.vertices[i].data, sizeof(VertexType),1,fw);
    }
    for (int i = 0; i < G.vexnum; ++i) {
        auto tmp=G.vertices[i].firstarc;
        while (tmp){
            if(G.vertices[tmp->adjvex].data.key>G.vertices[i].data.key){
                fwrite(&i, sizeof(int),1,fw);
                fwrite(&G.vertices[tmp->adjvex].data.key, sizeof(int),1,fw);
            }
            tmp=tmp->nextarc;
        }
    }
    return OK;
}
status LoadGraph(ALGraph &G, char FileName[]){

}
