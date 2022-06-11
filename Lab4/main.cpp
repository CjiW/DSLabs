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
#define EMPTY -4
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
    int len;
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
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][3]);

status DestroyGraph(ALGraph &G);

int LocateVex(ALGraph G, KeyType u);

status PutVex(ALGraph &G, KeyType u, VertexType value);

int FirstAdjVex(ALGraph G, KeyType u);

int NextAdjVex(ALGraph G, KeyType v, KeyType w);

status InsertVex(ALGraph &G, VertexType v);

status DeleteVex(ALGraph &G, KeyType v);

status InsertArc(ALGraph &G,KeyType v,KeyType w,int len);

status DeleteArc(ALGraph &G,KeyType v,KeyType w);

status DFSTraverse(ALGraph &G,void (*visit)(VertexType));

void output(VertexType v);

status BFSTraverse(ALGraph &G,void (*visit)(VertexType));

status SaveGraph(ALGraph G, char FileName[]);

status LoadGraph(ALGraph &G, char FileName[]);

//��1������С��k�Ķ��㼯�ϣ�����������VerticesSetLessThanK(G,v,k)����ʼ������ͼG���ڣ���������Ƿ����붥��v����С��k�Ķ��㼯�ϣ�
void LTK_DFS(ALGraph G,int dis,int V_idx,int k);

status VerticesSetLessThanK(ALGraph G,KeyType v,int k);
//��2����������·���ͳ��ȣ�����������ShortestPathLength(G,v,w); ��ʼ������ͼG���ڣ���������Ƿ��ض���v�붥��w�����·���ĳ��ȣ�
int ShortestPathLength(ALGraph G,KeyType v,KeyType w);
//��3��ͼ����ͨ����������������ConnectedComponentsNums(G)����ʼ������ͼG���ڣ���������Ƿ���ͼG��������ͨ�����ĸ�����
void CC_DFS(ALGraph G,int v);

int ConnectedComponentsNums(ALGraph G);

int LocateGraph(GRAPHS graphs, const char GraphName[]);

status AddGraph(GRAPHS &graphs,const char GraphName[]);

status RemoveGraph(GRAPHS &graphs, char ListName[]);

int min(int a,int b){
    if(a<0)a=INT_MAX;
    if(b<0)b=INT_MAX;
    return a<b?a:b;
}

int main() {
    int op = 1, tmp;
    VertexType v,V[30];
    KeyType j,k;
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
        // �X �T �[ �U �^ �a
        printf("    �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        printf("    �U                  %d-%-10s                         �U\n", usingGraph, Graphs.elem[usingGraph].name);
        printf("    �c���������������������������������������������������������������������������������������������������������������f\n");
        printf("    �U   1. CreateGraph             2. DestroyGraph          �U\n");
        printf("    �U   3. LocateVex               4. PutVex                �U\n");
        printf("    �U   5. FirstAdjVex             6. NextAdjVex            �U\n");
        printf("    �U   7. InsertVex               8. DeleteVex             �U\n");
        printf("    �U   9. InsertArc               10.DeleteArc             �U\n");
        printf("    �U   11.DFSTraverse             12.BFSTraverse           �U\n");
        printf("    �U   13.VerticesSetLessThanK    14.ShortestPathLength    �U\n");
        printf("    �U   15.ConnectedComponentsNums 16.LoadGraph             �U\n");
        printf("    �U   17.SaveGraph               18.AddGraph              �U\n");
        printf("    �U   19.RemoveGraph             20.ChangeGraph           �U\n");
        printf("    �U   21.LocateGraph             0. Exit                  �U\n");
        printf("    �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        printf("    ��ѡ����Ĳ���:");
        scanf_s("%d", &op);
        switch (op) {
            case 1:
                printf("�����붥������(key others):\n");
                tmp=-1;
                do{
                    tmp++;
                    scanf("%d %s",&V[tmp].key,V[tmp].others);
                } while (V[tmp].key!=-1);
                printf("�����������(v_key w_key len):\n");
                tmp=-1;
                do {
                    tmp++;
                    scanf("%d %d %d",A[tmp],A[tmp]+1,A[tmp]+2);
                } while (A[tmp][0]!=-1);
                switch (CreateGraph(Graphs.elem[usingGraph].G,V,A)) {
                    case ERROR:
                        printf("����ʧ�ܣ�\n");
                        DestroyGraph(Graphs.elem[usingGraph].G);
                        break;
                    case OVERFLOW:
                        printf("�ڴ����ʧ�ܣ�\n");
                        DestroyGraph(Graphs.elem[usingGraph].G);
                        break;
                    case INFEASIBLE:
                        printf("�������Ѵ��ڣ�\n");
                        break;
                    case OK:
                        printf("�����ɹ���\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 2:
                switch (DestroyGraph(Graphs.elem[usingGraph].G)) {
                    case OK:
                        printf("���ٳɹ���\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 3:
                printf("������Ŀ�궥��Ĺؼ���:\n");
                scanf("%d",&k);
                switch (tmp=LocateVex(Graphs.elem[usingGraph].G,k)) {
                    case -1:
                        printf("Ŀ�궥�㲻���ڣ�\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                    default:
                        v = Graphs.elem[usingGraph].G.vertices[tmp].data;
                        printf("�ҵ���%d�����㡾%d %s��\n",tmp,v.key,v.others);
                        break;
                }
                getchar();
                getchar();
                break;
            case 4:
                printf("������Ҫ�޸Ķ���Ĺؼ���:\n");
                scanf("%d",&k);
                printf("������Ŀ�꡾k v��ֵ:\n");
                scanf("%d %s",&v.key,v.others);
                switch(PutVex(Graphs.elem[usingGraph].G,k,v)){
                    case OK:
                        printf("�޸ĳɹ�����ǰֵ��%d %s����\n",v.key,v.others);
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                    case ERROR:
                        printf("Ŀ�궥�㲻���ڣ�\n");
                        break;
                    case INFEASIBLE:
                        printf("�ؼ����ظ���\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 5:
                printf("�����붥��Ĺؼ���:\n");
                scanf("%d",&k);
                switch (tmp=FirstAdjVex(Graphs.elem[usingGraph].G, k)) {
                    case -1:
                        printf("�ö��㲻���ڣ�\n");
                        break;
                    case -2:
                        printf("�ö������ڽӶ��㣡\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                    default:
                        v = Graphs.elem[usingGraph].G.vertices[tmp].data;
                        printf("�ö�����׸��ڽӶ���Ϊ��%d %s��\n",v.key,v.others);
                        break;
                }
                getchar();
                getchar();
                break;
            case 6:
                printf("�����붥��ؼ���:\n");
                scanf("%d",&k);
                printf("�������ڽӶ���ؼ���:\n");
                scanf("%d",&j);
                switch(tmp=NextAdjVex(Graphs.elem[usingGraph].G,k,j)){
                    case -1:
                        printf("Ŀ�궥�㲻���ڣ�\n");
                        break;
                    case -2:
                        printf("Ŀ�궥�㲻���ڸ��ڽӶ��㣡\n");
                        break;
                    case -3:
                        printf("���ٽ綥���޺������㣡\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                    default:
                        v = Graphs.elem[usingGraph].G.vertices[tmp].data;
                        printf("�����ٽ綥��Ϊ��%d %s��\n",v.key,v.others);
                        break;
                }
                getchar();
                getchar();
                break;
            case 7:
                printf("������Ҫ����Ķ���:\n");
                scanf("%d %s",&v.key,v.others);
                switch (InsertVex(Graphs.elem[usingGraph].G,v)) {
                    case ERROR:
                        printf("�ؼ����Ѵ��ڣ�\n");
                        break;
                    case OVERFLOW:
                        printf("���������࣡\n");
                        break;
                    case OK:
                        printf("���㡾%d %s������ɹ���\n",v.key,v.others);
                        break;
                }
                getchar();
                getchar();
                break;
            case 8:
                printf("������Ҫɾ���Ķ���ؼ���:\n");
                scanf("%d",&k);
                switch (DeleteVex(Graphs.elem[usingGraph].G, k)) {
                    case INFEASIBLE:
                        printf("���������٣�\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                    case ERROR:
                        printf("δ�ҵ�Ŀ�궥�㣡\n");
                        break;
                    case OK:
                        printf("����ɾ���ɹ���\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 9:
                printf("������Ҫ���ӵı�(v_Key w_Key len):\n");
                scanf("%d %d %d",&j,&k,&tmp);
                switch (InsertArc(Graphs.elem[usingGraph].G, j, k, tmp)) {
                    case ERROR:
                        printf("�˵㲻���ڣ�\n");
                        break;
                    case OVERFLOW:
                        printf("�ڴ����ʧ�ܣ�\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                    case INFEASIBLE:
                        if(j==k)printf("�������Ի�·��\n");
                        else printf("%d,%d�����бߣ�\n",j,k);
                        break;
                    case OK:
                        printf("�߲���ɹ���\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 10:
                printf("������Ҫɾ���ߵĶ˵�ؼ���:\n");
                scanf("%d %d",&j,&k);
                switch (DeleteArc(Graphs.elem[usingGraph].G, j, k)) {
                    case ERROR:
                        printf("δ�ҵ��ñߣ�\n");
                        break;
                    case OK:
                        printf("ɾ���ɹ���\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 11:
                if(DFSTraverse(Graphs.elem[usingGraph].G,output)==OK){
                    printf("������ȱ����ɹ���\n");
                } else{
                    printf("������δ������\n");
                }

                getchar();
                getchar();
                break;
            case 12:
                if(BFSTraverse(Graphs.elem[usingGraph].G,output)==OK)
                    printf("������ȱ����ɹ���\n");
                else
                    printf("������δ������\n");
                getchar();
                getchar();
                break;
            case 13:
                printf("���������ؼ���:\n");
                scanf("%d",&k);
                printf("������Kֵ:\n");
                scanf("%d",&tmp);
                switch (VerticesSetLessThanK(Graphs.elem[usingGraph].G, k, tmp)) {
                    case OK:
                        printf("\n���ҳɹ���\n");
                        break;
                    case ERROR:
                        printf("��㲻���ڣ�\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 14:
                printf("��������㡢�յ�ؼ���:\n");
                scanf("%d %d",&j,&k);
                switch((tmp=ShortestPathLength(Graphs.elem[usingGraph].G,j,k))) {
                    case INT_MAX:
                        printf("�����㲻��ͨ��\n");
                        break;
                    case ERROR:
                        printf("�����յ㲻���ڣ�\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                    default:
                        printf("���·������Ϊ%d��\n",tmp);
                }
                getchar();
                getchar();
                break;
            case 15:
                if((tmp=ConnectedComponentsNums(Graphs.elem[usingGraph].G))==EMPTY)
                    printf("������δ������\n");
                else
                    printf("��ͨ������Ϊ%d��\n", tmp);
                getchar();
                getchar();
                break;
            case 16:
                printf("�������ļ�·��:\n");
                scanf("%s",filename);
                switch (LoadGraph(Graphs.elem[usingGraph].G,filename)) {
                    case OK:
                        printf("���سɹ���\n");
                        break;
                    case INFEASIBLE:
                        printf("��ǰͼδ���٣�\n");
                        break;
                    case OVERFLOW:
                        printf("�ڴ����ʧ�ܣ�\n");
                        break;
                    case ERROR:
                        printf("�ļ���ʧ�ܣ�\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 17:
                printf("�������ļ�·��:\n");
                scanf("%s",filename);
                switch (SaveGraph(Graphs.elem[usingGraph].G,filename)) {
                    case OK:
                        printf("����ɹ���\n");
                        break;
                    case ERROR:
                        printf("�ļ���ʧ�ܣ�\n");
                        break;
                    case EMPTY:
                        printf("������δ������\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 18:
                printf("������������������:\n");
                scanf("%s",s);
                switch (AddGraph(Graphs,s)) {
                    case ERROR:
                        printf("�����Ѵ��ڣ�\n");
                        break;
                    case OVERFLOW:
                        printf("���������࣡\n");
                        break;
                    case OK:
                        printf("��������ӳɹ���\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 19:
                printf("������Ҫɾ����������������:\n");
                scanf_s("%s", s);
                switch (RemoveGraph(Graphs, s) ) {
                    case ERROR:
                        printf("�����������ڣ�\n");
                        break;
                    case INFEASIBLE:
                        printf("����ɾ����ǰ��������\n");
                        break;
                    case OK:
                        printf("ɾ���ɹ���\n");
                        break;
                }
                getchar();
                getchar();
                break;
            case 20:
                printf("������Ҫʹ�õ�������������:\n");
                scanf_s("%s", s);
                tmp = LocateGraph(Graphs, s);
                if (tmp) {
                    usingGraph = tmp - 1;
                    printf("�л��������ɹ���\n��ǰ������:%d-%s\n", usingGraph, Graphs.elem[usingGraph].name);
                } else {
                    printf("�����������ڣ�\n");
                }
                getchar();
                getchar();
                break;
            case 21:
                printf("������������������:\n");
                scanf_s("%s", s);
                tmp = LocateGraph(Graphs, s);
                if (!tmp) {
                    printf("%s�����������ڣ�\n", s);
                } else {
                    printf("%s�ǵ�%d����������\n", s, tmp - 1);
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
}
void output(VertexType v){
    printf("%d %s\n",v.key,v.others);
}
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][3]) {
    if(G.vexnum)return INFEASIBLE;
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
        newArc->len = VR[i][2];
        newArc->nextarc = G.vertices[v].firstarc;
        G.vertices[v].firstarc = newArc;
        newArc = (ArcNode *) malloc(sizeof(ArcNode));// ����
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
    if (!G.vexnum)return EMPTY;
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
    if (!G.vexnum)return EMPTY;
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
    if (!G.vexnum)return EMPTY;
    int ind = -1;
    for (int i = 0; i < G.vexnum; i++) {
        if (value.key != u && G.vertices[i].data.key == value.key)return INFEASIBLE;
        if (G.vertices[i].data.key == u)ind = i;
    }
    if (ind == -1)return ERROR;
    G.vertices[ind].data = value;
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u) {
    if (!G.vexnum)return EMPTY;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) {
            if(G.vertices[i].firstarc== nullptr){
                return -2;
            }
            return G.vertices[i].firstarc->adjvex;
        }
    }
    return -1;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w) {
    if (!G.vexnum)return EMPTY;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v) {
            auto p = G.vertices[i].firstarc;
            while (p) {
                if (G.vertices[p->adjvex].data.key == w){
                    if(p->nextarc==nullptr)return -3;
                    return p->nextarc->adjvex;
                    }
                p = p->nextarc;
            }
            return -2;
        }
    }
    return -1;
}

status InsertVex(ALGraph &G, VertexType v) {
    if (G.vexnum == MAX_VERTEX_NUM)return OVERFLOW;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v.key)return ERROR;
    }
    G.vertices[G.vexnum++].data = v;
    return OK;
}

status DeleteVex(ALGraph &G, KeyType v){
    if (!G.vexnum)return EMPTY;
    int tmp = 2 * G.arcnum;
    if (G.vexnum == 1)return INFEASIBLE;
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
status InsertArc(ALGraph &G,KeyType v,KeyType w,int len){
    if (!G.vexnum)return EMPTY;
    if(v==w)return INFEASIBLE;
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
            ArcNode *p=G.vertices[i].firstarc,*NewArc;
            while (p){
                if(p->adjvex==iw)return INFEASIBLE;// �бߣ�����ERROR
                p=p->nextarc;
            }
            // ���뵥���
            if((NewArc=(ArcNode*)malloc(sizeof(ArcNode)))==nullptr)return OVERFLOW;
            NewArc->adjvex=iw;
            NewArc->len=len;
            NewArc->nextarc=G.vertices[i].firstarc;
            G.vertices[i].firstarc=NewArc;
            if((NewArc=(ArcNode*)malloc(sizeof(ArcNode)))==nullptr)return OVERFLOW;
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
    if (!G.vexnum)return EMPTY;
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
status DFSTraverse(ALGraph &G,void (*visit)(VertexType)){
    if (!G.vexnum)return EMPTY;
    for (int i = 0; i < G.vexnum; i++) vis[i]=false;
    for (int i = 0; i < G.vexnum; i++) {
        if(!vis[i])DFS(G,i,visit);
    }
    memset(vis,0, sizeof(vis));
    return OK;
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType)){
    if (!G.vexnum)return EMPTY;
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
    if (!G.vexnum)return EMPTY;
    FILE *fw= fopen(FileName,"wb");int nil=-1;
    if(fw==nullptr)return ERROR;
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
    if(G.vexnum)return INFEASIBLE;
    FILE *fr= fopen(FileName,"rb");
    if(fr==nullptr)return ERROR;
    G.vexnum=G.arcnum=0;
    fread(&G.kind,sizeof(GraphKind),1,fr);
    fread(&G.vexnum,sizeof(int),1,fr);
    for (int i = 0; i < G.vexnum; ++i) {
        fread(&(G.vertices[i].data), sizeof(VertexType),1,fr);
        G.vertices[i].firstarc= nullptr;
        auto NArc=(ArcNode*)malloc(sizeof(ArcNode));
        if(NArc==nullptr)return OVERFLOW;
        fread(&(NArc->adjvex), sizeof(int), 1, fr);
        fread(&(NArc->len), sizeof(int), 1, fr);
        NArc->nextarc= nullptr;
        if(NArc->adjvex == -1){
            free(NArc);
            continue;
        }
        G.vertices[i].firstarc=NArc;
        auto head=NArc;
        while (true){
            NArc=(ArcNode*)malloc(sizeof(ArcNode));
            if(NArc==nullptr)return OVERFLOW;
            fread(&(NArc->adjvex), sizeof(int), 1, fr);
            fread(&(NArc->len), sizeof(int), 1, fr);
            if(NArc->adjvex == -1)break;
            head->nextarc=NArc;
            NArc->nextarc= nullptr;
            head=head->nextarc;
            G.arcnum++;
        }
    }
    G.arcnum/=2;
    fclose(fr);
    return OK;
}
//��1������С��k�Ķ��㼯�ϣ�����������VerticesSetLessThanK(G,v,k)����ʼ������ͼG���ڣ���������Ƿ����붥��v����С��k�Ķ��㼯�ϣ�
void LTK_DFS(ALGraph G,int dis,int V_idx,int k){
    if(dis>k||vis[V_idx])return;
    vis[V_idx]=true;
    if(dis)printf("��%d %s��",G.vertices[V_idx].data.key,G.vertices[V_idx].data.others);
    auto p=G.vertices[V_idx].firstarc;
    while (p){
        LTK_DFS(G,dis+p->len,p->adjvex,k);
        p=p->nextarc;
    }
}
status VerticesSetLessThanK(ALGraph G,KeyType v,int k){
    if (!G.vexnum)return EMPTY;
    for (int i = 0; i < G.vexnum; ++i) {
        if(G.vertices[i].data.key==v){
            LTK_DFS(G,0,i,k);
            memset(vis,0, sizeof vis);
            return OK;
        }
    }
    return ERROR;
}
//��2����������·���ͳ��ȣ�����������ShortestPathLength(G,v,w); ��ʼ������ͼG���ڣ���������Ƿ��ض���v�붥��w�����·���ĳ��ȣ�
int ShortestPathLength(ALGraph G,KeyType v,KeyType w){
    if (!G.vexnum)return EMPTY;
    int dist[G.vexnum],start=-1,end=-1;
    for (int i = 0; i < G.vexnum; ++i) {
        dist[i]=INT_MAX;
        if(G.vertices[i].data.key==v)start=i;
        if(G.vertices[i].data.key==w)end=i;

    }
    if(start==-1||end==-1)return ERROR;
    dist[start]=0;
    for(int j=0;j<G.vexnum;j++) {
        for (int i = 0; i < G.vexnum; i++) {
            ArcNode *tmp = G.vertices[i].firstarc;
            while (tmp) {
                dist[tmp->adjvex] = min(tmp->len+dist[i], dist[tmp->adjvex]);
                tmp = tmp->nextarc;
            }
        }
    }
    return dist[end];
}
//��3��ͼ����ͨ����������������ConnectedComponentsNums(G)����ʼ������ͼG���ڣ���������Ƿ���ͼG��������ͨ�����ĸ�����
void CC_DFS(ALGraph G,int v){
    vis[v]=true;
    for (auto p=G.vertices[v].firstarc; p ; p=p->nextarc) {
        if(!vis[p->adjvex])CC_DFS(G,p->adjvex);
    }
}
int ConnectedComponentsNums(ALGraph G){
    if (!G.vexnum)return EMPTY;
    int ans=0;
    for (int i = 0; i < G.vexnum; ++i) {
        if(!vis[i]){
            CC_DFS(G,i);
            ans++;
        }
    }
    memset(vis,0, sizeof vis);
    return ans;
}

int LocateGraph(GRAPHS graphs, const char GraphName[]) {
    for (int i = 0; i < graphs.length; i++) {
        if (strcmp(graphs.elem[i].name, GraphName) != 0)continue;
        return i + 1;
    }
    return 0;
}
status AddGraph(GRAPHS &graphs,const char GraphName[]){
    if(graphs.length>=10)return OVERFLOW;
    if(LocateGraph(graphs,GraphName))return ERROR;
    int i=0;
    while ((((graphs.elem)[graphs.length]).name[i] = GraphName[i]))i++;
    ((graphs.elem)[graphs.length]).G.vexnum = 0;
    graphs.length++;
    return OK;
}
status RemoveGraph(GRAPHS &graphs, char ListName[]) {
    int i = LocateGraph(graphs, ListName);
    if (!i) {
        return ERROR;
    }
    if (i == usingGraph + 1) {
        return INFEASIBLE;
    }
    i--;
    if (usingGraph >= i)usingGraph--;
    DestroyGraph(graphs.elem[i].G);
    for (; i < graphs.length; i++) {
        graphs.elem[i] = graphs.elem[i + 1];
    }
    graphs.elem[i].G.vexnum=0;
    graphs.length--;
    return OK;

}