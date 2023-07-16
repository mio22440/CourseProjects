#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INFINITY 65535
#define MAX_LEN 20


//结构体定义
typedef struct vertex {
	int id;
	int inDegree;
	int outDegree;
}Vertex;

typedef struct edge {
	bool isExist;
	int dist;
}Edge;

typedef struct graph {
	int vertexNum;
	int edgeNum;
	Edge** AdjMatrix;
	Vertex* vertexs;
}Graph;

//函数声明

Graph* createGraph(int vertexNum);//建图
int destroyGraph(Graph* G);//销毁图
int addEdge(Graph* G, int u, int v, int dist);//增加从u到v，长度为dist的边

int Dijkstra(Graph* G, int v, int end);//找从v出发到end的最短路径
int out_path(Graph* G, int dist[], int path[], int S[], int v, int end);//输出最短路径（目前只能嵌套在Dijkstra函数中
//int DFS_find(Graph* G, int u);//用深度优先遍历寻找结点v

int outputAdj(Graph* G);//打印邻接矩阵


//函数实现
Graph* createGraph(int vertexNum) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	memset(g, 0, sizeof(Graph));
	g->vertexNum = vertexNum;
	g->edgeNum = 0;

	//分配二维数组
	g->AdjMatrix = (Edge**)malloc(vertexNum * sizeof(Edge*));
	int i;
	for (i = 0; i < vertexNum; i++) {//分配空间
		g->AdjMatrix[i] = (Edge*)malloc(vertexNum * sizeof(Edge));
		memset(g->AdjMatrix[i], 0, vertexNum * sizeof(Edge));
	}
	int j;
	for (i = 0; i < vertexNum; i++) {
		for (j = 0; j < vertexNum; j++) {
			g->AdjMatrix[i][j].isExist = false;
		}//for
	}//for

	g->vertexs = (Vertex*)malloc(vertexNum * sizeof(Vertex));//分配一维数组并初始化
	memset(g->vertexs, 0, vertexNum * sizeof(Vertex));
	for (i = 0; i < vertexNum; i++) {
		g->vertexs[i].id = i;
		g->vertexs[i].inDegree = 0;
		g->vertexs[i].outDegree = 0;
	}

	return g;
}

int destroyGraph(Graph* G) {
	if (!G) {
		printf("空图\n");
		return 0;
	}
	int i;
	for (i = 0; i < G->vertexNum; i++) {
		free(G->AdjMatrix[i]);
	}
	free(G->AdjMatrix);

	free(G->vertexs);
	free(G);

	return 1;
}

int addEdge(Graph* G, int u, int v, int dist) {
	if (G->AdjMatrix[u][v].isExist) {
		printf("该边已存在\n");
		return 0;
	}
	G->AdjMatrix[u][v].isExist = true;
	G->AdjMatrix[u][v].dist = dist;
	G->vertexs[u].outDegree++;
	G->vertexs[v].inDegree++;

	return 1;
}

int Dijkstra(Graph* G, int v, int end) {
	//错误处理
	if (!G || (v > G->vertexNum)) {
		printf("该图为空或首结点超出范围\n\n");
		return 0;
	}
	//初始化
	int dist[MAX_LEN], path[MAX_LEN];//u到某顶点的最短距离， u到某顶点最短路径的前一个结点
	int S[MAX_LEN];//为1时顶点在已确定最短路径的顶点集合S中， 为0时表示在其余未确定的顶点集合U中
	int MINdis = INFINITY, i = 0, j = 0, u = 0;//当前最短暂存， 计数， 计数， 顶点暂存
	for (i = 0; i < G->vertexNum; i++) {
		dist[i] = G->AdjMatrix[v][i].dist;//距离用初始距离，注意是以v为始点的
		S[i] = 0;//S集合置空
		if (G->AdjMatrix[v][i].dist < INFINITY)
			path[i] = v;
		else
			path[i] = -1;//表示没有边

	}
	S[v] = 1;
	path[v] = v;

	//循环
	for (i = 0; i < G->vertexNum; i++) {//循环直到所有顶点的最短路径都求出
		if (v == i)//跳过起始顶点
			i++;
		MINdis = INFINITY;
		for(j = 0; j < G->vertexNum; j++)
			if ((0 == S[j]) && (dist[j] < MINdis)) {
				u = j;
				MINdis = dist[j];
			}
		S[u] = 1;//将u加入到集合S中
		for(j = 0; j < G->vertexNum; j++)
			if(0 == S[j])//该顶点不在集合S中
				if ((G->AdjMatrix[u][j].dist < INFINITY) && ((dist[u] + G->AdjMatrix[u][j].dist) < dist[j])) {
					dist[j] = dist[u] + G->AdjMatrix[u][j].dist;
					path[j] = u;
				}



	}
	
	out_path(G, dist, path, S, v, end);


	return 1;
}

int out_path(Graph* G, int dist[], int path[], int S[], int v, int end) {
	//错误处理
	if (!G || !dist || !path || !S || (v > G->vertexNum) || (end > G->vertexNum)) {
		printf("有指针参数为空或有变量超出限定值\n\n");
		return 0;
	}

	//初始化
	int i, j, k;//计数， 计数， 临时顶点
	int apath[MAX_LEN] = {0};//一条逆向最短路径
	int d;

	//循环
	/*******************************************************************************
	for(i = 0; i < G->vertexNum; i++)//这是输出到所有顶点的最短路径
		if ((1 == S[i]) && (i != v)) {
			printf("从顶点%d到顶点%d的最短路径长度为%d\t路径为:", v, i, dist[i]);
			d = 0;//最短路径上的顶点个数
			apath[d] = i;
			k = path[i];//i的前驱
			if (-1 == k)
				printf("无路径\n");
			else {
				while (k != v) {//依次往回找
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d] = v;//加上数组最后一个顶点（最短路径的起始顶点
				printf("%d", apath[d]);
				for (j = d - 1; j >= 0; j--)
					printf("->%d", apath[j]);
				printf("\n");
			}

		}

		***************************************************************************************/
	if ((1 == S[end]) && (end != v)) {
		printf("从顶点%d到顶点%d的最短路径长度为%d\t路径为:", v, end, dist[end]);
		d = 0;//最短路径上的顶点个数
		apath[d] = end;
		k = path[end];//i的前驱
		if (-1 == k)
			printf("无路径\n");
		else {
			while (k != v) {//依次往回找
				d++;
				apath[d] = k;
				k = path[k];
			}
			d++;
			apath[d] = v;//加上数组最后一个顶点（最短路径的起始顶点
			printf("%d", apath[d]);
			for (j = d - 1; j >= 0; j--)
				printf("->%d", apath[j]);
			printf("\n");
		}
	}


	


	return 1;
}

/********************************************************************************
int DFS_find(Graph* G, int u) {
	if (!G || (u > G->vertexNum)) {
		printf("该图不存在\n\n");
		return 0;
	}
	else {
		printf("开始深度遍历搜索(ノ￣▽￣)~~\n\n");
	}

	bool *visited = (bool*)malloc(G->vertexNum * sizeof(int));
	memset(visited, false, G->vertexNum * sizeof(int));

	visited[u] = true;


	int v;
	for (v = 0; v < G->vertexNum; v++) {
		
	};
	

	

	return 0;//返回0表示未搜索到相应结点
}

******************************************************************/


int outputAdj(Graph* G) {
	if (!G) {
		printf("该图为空\n");
		return 0;
	}

	int i, j;
	for (i = 0; i < G->vertexNum; i++) {
		for (j = 0; j < G->vertexNum; j++) {
			//if (G->AdjMatrix[i][j].isExist)
				printf("%-5d ", G->AdjMatrix[i][j].dist);
			//else
			//	printf("%-5d ", INFINITY);
		}
		printf("\n");
	}

	return 1;
}


int main(void)
{
	freopen("input.txt", "r", stdin);//输入重定向，使用txt文件代替手动输入
	int vertexNum = 0, edgeNum = 0, start = 0, end = 0;

	//printf("输入有向图的结点数目、边的数目、起点id和终点id，用空格分隔：\n");
	scanf("%d %d %d %d", &vertexNum, &edgeNum, &start, &end);
	Graph* G = createGraph(vertexNum);
	G->edgeNum = edgeNum;

	int i;
	int u = 0, v = 0, dist = 0;
	for (i = 0; i < edgeNum; i++) {
		//printf("输入第%d条边的起始端点u和终止端点v的id和该边的长度dist,并用空格隔开\n");
		scanf("%d %d %d", &u, &v, &dist);
		addEdge(G, u, v, dist);
		G->AdjMatrix[u][u].isExist = true;
		G->AdjMatrix[u][u].dist = 0;
		G->AdjMatrix[v][v].isExist = true;
		G->AdjMatrix[v][v].dist = 0;
	}
	int j;
	for (i = 0; i < G->vertexNum; i++) {
		for (j = 0; j < G->vertexNum; j++) {
			if (false == G->AdjMatrix[i][j].isExist)
				G->AdjMatrix[i][j].dist = INFINITY;
		}
	}
	

	fclose(stdin);

	printf("邻接矩阵为：\n");
	outputAdj(G);
	printf("\n\n");

	Dijkstra(G, start, end);


	destroyGraph(G);
	return 0;

}
