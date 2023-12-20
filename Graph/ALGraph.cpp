#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

#define MAX_VERTEX_NUM 20	// 顶点数量最大值
#define MAX_NAME 5			// 顶点字符串最大长度

// 图的邻接表存储结构
// 边结点
typedef struct ArcNode {
	int adjvex;		// 在邻接表当中的下标
	struct ArcNode* nextarc;	// 指向下一个边结点的指针
	int info;		// 储存该边结点相关信息的指针
}ArcNode;

// 顶点
typedef struct VNode {
	char data[MAX_NAME];	// 顶点字符串
	ArcNode* fistarc;	// 指向第一个边结点的指针
}VNode, AdjList[MAX_VERTEX_NUM];
// AdjList 是一个自定义类型, 为一个数组
// 相当于 AdjList = VNode[MAX_VERTEX_NUM]

// 图
typedef struct ALGraph {
	AdjList vertices;	// 邻接表
	int vexnum, arcnum; // 顶点个数 边的条数
	int kind;			// 图的种类 0 有向图, 1 无向图, 2 有向网, 3 无向网
}ALGraph;

// 查找顶点
int LocateVex(ALGraph G, char* u) {
	for(int i = 0; i < G.vexnum; i++) {
		if(strcmp(G.vertices[i].data,u) == 0)
			return i;	// 查找成功, 返回下标
	}
	return 0;	// 查找失败, 返回 0
}

// 创建图
void CreatGraph(ALGraph& G) {
	printf("请输入图的种类, 0 有向图, 1 无向图, 2 有向网, 3 无向网: ");
	scanf("%d",&G.kind);
	
	printf("请输入图或网的顶点个数 边的条数: ");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	printf("请输入图或网的顶点: ");
	for(int i = 0; i < G.vexnum; i++) {
		scanf("%s",G.vertices[i].data);
		G.vertices[i].fistarc = NULL;
	}
	
	if(G.kind == 0 || G.kind == 1) {
		printf("请输入图的边, 弧尾 弧头:\n");
	} else {
		printf("请输入网的边, 弧尾 弧头 权值:\n");
	}
	char va[MAX_NAME], vb[MAX_NAME];
	int weight = 1;
	ArcNode* p;
	for(int k = 0; k < G.arcnum; k++) {
		scanf("%s%s",va,vb);
		if(G.kind >= 2) {
			scanf("%d",&weight);
		}
		int i = LocateVex(G,va);
		int j = LocateVex(G,vb);
		p = (ArcNode*) malloc (sizeof(ArcNode));
		p->info = weight;
		p->adjvex = j;
		p->nextarc = G.vertices[i].fistarc;
		G.vertices[i].fistarc = p;
		if(G.kind == 0 || G.kind == 2) {
			p = (ArcNode*) malloc (sizeof(ArcNode));
			p->info = weight;
			p->adjvex = i;
			p->nextarc = G.vertices[j].fistarc;
			G.vertices[j].fistarc = p;
		}
	}
}

// 访问结点并打印结点
void Visit(char* u) {
	printf("%s ",u);
}

// 深度优先搜索
int visited[MAX_VERTEX_NUM];	// 访问数组, 1 代表已经访问, 0 代表未访问
void DFS(ALGraph G, int v) {
	Visit(G.vertices[v].data);
	visited[v] = 1;
	ArcNode* p = G.vertices[v].fistarc;
	int w;
	while(p) {
		w = p->adjvex;
		if(!visited[w])
			DFS(G,w);
		p = p->nextarc;
	}
}

void DFSTraverse(ALGraph G) {
	for(int i = 0; i < G.vexnum; i++)
		visited[i] = 0;
	for(int v = 0; v < G.vexnum; v++) {
		if(!visited[v])
			DFS(G,v);
	} 
}

// 广度优先搜索算法
void BFS(ALGraph G, int v) {
	visited[v] = 1;
}

void BFSTraverse(ALGraph G) {
	int v;
	for(v = 0; v < G.vexnum; v++)
		visited[v] = 0;
	for(v = 0; v < G.vexnum; v++)
		if(!visited[v])
			BFS(G,v);
}

// 测试
/*
1
8 8
A B C D E F G H
A B
A C
B D
B E
C F
C G
D H
E H
*/

int main() {
	ALGraph G;
	CreatGraph(G);
	DFSTraverse(G);
}
