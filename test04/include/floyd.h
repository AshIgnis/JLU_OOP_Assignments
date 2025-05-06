#include<iostream>
#include<queue>
#include<vector>
#include<string>
using namespace std;

#define MAX 999
#define MVNum 20

typedef int VertexType;
typedef int ArcType;

struct Edge {
    int dest;   // 目标顶点
    int weight; // 权重
};

class Graph
{
public:
	void Create();
	int LocateVex(VertexType u);//查找Graph中的顶点u，并返回其对应在顶点表中的下标，未找到则返回-1
	int firstadj(int v);
	int nextadj(int v, int w);
	void Floyd();//Floyd算法
	void print_path();//打印路径
	// void Show();//调试用，打印邻接矩阵
    void BuildAdjList();
    void SortAdjacentEdges();
    void QueryPath(int start, int end);
private:
	VertexType vexs[MVNum];//顶点表
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	ArcType path[MVNum][MVNum];//保存路径
	int vexnum, arcnum;//图当前的顶点数和边数
    vector<vector<Edge>> adjList;
};