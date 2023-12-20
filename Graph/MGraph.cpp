#include <stdio.h>
#include <string.h>
#include <iostream>
#include<queue>
using namespace std;

#define INFINITY INT_MAX	// 无穷大
#define MAX_VERTEX_NUM	20  // 最大结点个数
#define MAX_NAME 5			// 结点最长字符串

// 图的种类(有向图 无向图 有向网 无向网)
enum GraphKind {DG, UDG, DN, UDN};

// 图的邻接矩阵存储结构
// ArcCell
typedef struct ArcCell {
	int adj;	// 图 1 代表连通(有边), 0 代表不连通(无边)
	// 网 INFINITY 代表不连通(无边), 其余数字代表权值
	char* info; // 存储信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
// AdjMatrix 是一个类型, 是一个二维数组, 数组元素类型为 ArcCell
// AdjMatrix = ArcCell[MAX_VERTEX_NUM][MAX_VERTEX_NUM]

typedef struct {
	char vexs[MAX_VERTEX_NUM][MAX_NAME]; // 结点数组
	AdjMatrix arcs;						 // 邻接矩阵
	int vexnum, arcnum;					 // 结点数 和 边数
	GraphKind kind;						 // 图的种类
} MGraph;

// 查找指定结点在结点数组中的位置, 返回下标
int LocateVex(MGraph G, char* u) {
	for (int i = 0; i < G.vexnum; i++) {
		if (strcmp(G.vexs[i], u) == 0)
			return i;	// 查找成功, 返回下标
	}
	return -1;	// 查找失败, 返回 -1
}

// 创建无向图
void CreateUDG(MGraph& G) {
	printf("请输入该无向图的结点个数和边的条数: ");
	scanf("%d%d", &G.vexnum, &G.arcnum);

	printf("请输入该无向图的结点信息, 结点之间空格分隔开: ");
	for (int i = 0; i < G.vexnum; i++) {
		scanf("%s", G.vexs[i]);
	}

	// 初始化邻接矩阵
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}

	printf("请输入该无向图边的情况, 弧尾 弧头: \n");
	char va[MAX_NAME], vb[MAX_NAME];
	for (int k = 0; k < G.arcnum; k++) {
		scanf("%s%s", va, vb);
		int i = LocateVex(G, va);
		int j = LocateVex(G, vb);
		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;
	}
	G.kind = UDG;
}

// 创建有向图
void CreateDG(MGraph& G) {
	printf("请输入该有向图的结点个数和边的条数: ");
	scanf("%d%d", &G.vexnum, &G.arcnum);

	printf("请输入该有向图的结点信息, 结点之间空格分隔开: ");
	for (int i = 0; i < G.vexnum; i++) {
		scanf("%s", G.vexs[i]);
	}

	// 初始化邻接矩阵
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}

	printf("请输入该有向图边的情况, 弧尾 弧头: \n");
	char va[MAX_NAME], vb[MAX_NAME];
	for (int k = 0; k < G.arcnum; k++) {
		scanf("%s%s", va, vb);
		int i = LocateVex(G, va);
		int j = LocateVex(G, vb);
		G.arcs[i][j].adj = 1;
	}
	G.kind = DG;
}

// 创建无向网
void CreateUDN(MGraph& G) {
	printf("请输入该无向网的结点个数和边的条数: ");
	scanf("%d%d", &G.vexnum, &G.arcnum);

	printf("请输入该无向网的结点信息, 结点之间空格分隔开: ");
	for (int i = 0; i < G.vexnum; i++) {
		scanf("%s", G.vexs[i]);
	}

	// 初始化邻接矩阵
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}

	printf("请输入该无向网边的情况, 弧尾 弧头 权值: \n");
	char va[MAX_NAME], vb[MAX_NAME];
	int weight;
	for (int k = 0; k < G.arcnum; k++) {
		scanf("%s%s%d", va, vb, &weight);
		int i = LocateVex(G, va);
		int j = LocateVex(G, vb);
		G.arcs[i][j].adj = G.arcs[j][i].adj = weight;
	}
	G.kind = UDN;
}

// 创建有向网
void CreateDN(MGraph& G) {
	printf("请输入该有向网的结点个数和边的条数: ");
	scanf("%d%d", &G.vexnum, &G.arcnum);

	printf("请输入该有向网的结点信息, 结点之间空格分隔开: ");
	for (int i = 0; i < G.vexnum; i++) {
		scanf("%s", G.vexs[i]);
	}

	// 初始化邻接矩阵
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}

	printf("请输入该有向网边的情况, 弧尾 弧头 权值: \n");
	char va[MAX_NAME], vb[MAX_NAME];
	int weight;
	for (int k = 0; k < G.arcnum; k++) {
		scanf("%s%s%d", va, vb, &weight);
		int i = LocateVex(G, va);
		int j = LocateVex(G, vb);
		G.arcs[i][j].adj = weight;
	}
	G.kind = DN;
}

// 创建图或网
void CreatGraph(MGraph& G) {
	// 有向图 无向图 有向网 无向网
	printf("请输入图的种类, 0 有向图, 1 无向图, 2 有向网, 3 无向网: ");
	int kind;
	scanf("%d", &kind);
	switch (kind) {
		case 0:
			CreateDG(G);
			break;
		case 1:
			CreateUDG(G);
			break;
		case 2:
			CreateDN(G);
			break;
		case 3:
			CreateUDN(G);
			break;
	}
}

// 访问结点数组, 打印结点字符串
void Visit(char* u) {
	printf("%s ", u);
}

// 打印邻接矩阵
void Display(MGraph G) {
	printf("该图的结点信息: ");
	for (int i = 0; i < G.vexnum; i++) {
		Visit(G.vexs[i]);
	}
	printf("\n");
	printf("该图的邻接矩阵: \n");
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			printf("%10d	", G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

// 深度优先搜索
int visited[MAX_VERTEX_NUM]; // 访问数组, 1 代表已经访问
							 // 0 代表未访问	
void DFS(MGraph G, int v) {
	Visit(G.vexs[v]);
	visited[v] = 1;
	int j = 0;
	if(G.kind == UDN || G.kind == DN) {
		j = INFINITY;
	}
	for(int w = 0; w < G.vexnum; w++) {
		if(!visited[w] && G.arcs[v][w].adj != j) {
			DFS(G,w);
		}
	}
}

void DFSTraverse(MGraph G) {
	for(int i = 0; i < G.vexnum; i++)
		visited[i] = 0;		// 初始化为 0
	
	for(int v = 0; v < G.vexnum; v++) {
		if(!visited[v]) {
			DFS(G,v);
		}
	}
	printf("\n");
}

void BFS(MGraph G, int v) {
	queue<int> Q;
	Q.push(v);
	Visit(G.vexs[v]);
	visited[v] = 1;		// 进队列置为 1
	int w;
	int j = 0;
	if(G.kind == 2 || G.kind == 3) {
		j = INFINITY;
	}
	while(!Q.empty()) {
		w = Q.front();
		Q.pop();
		for(int i = 0; i < G.vexnum; i++) {
			if(!visited[i] && G.arcs[w][i].adj != j) {
				Q.push(i);
				Visit(G.vexs[i]);
				visited[i] = 1;		// 进队列置为 1
			}
		}
	}
}

void BFSTraverse(MGraph G){ 
	int v;
	for(v = 0; v < G.vexnum; v++)  
		visited[v] = 0;    
	for(v = 0; v < G.vexnum; v++)
		if(!visited[v])  
			BFS(G, v); 
	printf("\n");
}

// Prim 算法求最小生成树
typedef struct Edge {
	int adjvex;
	int lowcost;
}Edge;

void Prim(MGraph G, int start) {
	Edge shortEdge[MAX_VERTEX_NUM];
	for(int i = 0; i < G.vexnum; i++) { // 初始化辅助数组
		shortEdge[i].lowcost = G.arcs[start][i].adj;
		shortEdge[i].adjvex	= start;
		visited[i] = 0;
	}
	visited[start] = 1;
	int k, min;
	for(int i = 0; i < G.vexnum-1; i++) {
		min = INFINITY;
		for(int j = 0; j < G.vexnum; j++) {
			if(!visited[j] && shortEdge[j].lowcost < min) {
				min = shortEdge[j].lowcost;
				k = j;
			}
		}
		visited[k] = 1;
		printf("%s -> %s\n",G.vexs[shortEdge[k].adjvex],G.vexs[k]);
		
		// 更新最小边
		for(int j = 0; j < G.vexnum; j++) {
			if(!visited[j] && shortEdge[j].lowcost > G.arcs[k][j].adj) {
				shortEdge[j].lowcost = G.arcs[k][j].adj;
				shortEdge[j].adjvex = k;
			}
		}
	}
}
// 测试无向图
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

// 测试无向网
/*
3
7 9
0 1 2 3 4 5 6
0 1 28
0 5 10
1 2 16
1 6 14
2 3 12
3 6 18
3 4 22
4 5 25
4 6 24
*/
int main() {
	MGraph G;
	CreatGraph(G);
	Display(G);
	DFSTraverse(G);
	BFSTraverse(G);
	Prim(G,0);
	return 0;
}
