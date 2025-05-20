#include "floyd.h"
#include "heapsort.h"

int Graph::LocateVex(VertexType u)
{//查找Graph中的顶点u，并返回其对应在顶点表中的下标，未找到则返回-1
	int i;
	for (i = 0; i < this->vexnum; i++)
	{
		if (u == this->vexs[i])
			return i;
	}
	return -1;
}

int Graph::firstadj(int v)
{
	for (int i = 0; i < this->vexnum; i++)
	{
		if (this->arcs[v][i] != MAX)
			return i;
	}
	return -1;
}

int Graph::nextadj(int v, int w)
{
	for (int i = w + 1; i < this->vexnum; i++)
	{
		if (this->arcs[v][i] != MAX)
			return i;
	}
	return -1;
}

// void Graph::Show()
// {
// 	for (int i = 0; i < this->vexnum; i++)
// 	{
// 		for (int j = 0; j < this->vexnum; j++)
// 		{
// 			cout << this->arcs[i][j] << " ";
// 		}
// 		cout << endl;
// 	}
// }

void Graph::Create()
{
	cout << "请输入总结点数和总边数:";
	cin >> this->vexnum >> this->arcnum;//输入总顶点数和总边数
	for (int i = 0; i < this->vexnum; i++)
	{
		this->vexs[i] = i + 1;
	}
	//初始化邻接矩阵
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
            if(i == j)
                this->arcs[i][j] = 0;
            else
			    this->arcs[i][j] = this->arcs[j][i] = MAX;
		}
	}
	//构造邻接矩阵
	for (int i = 0; i < this->arcnum; i++)
    {
        int v1, v2, w;
        cout << "请输入第" << i + 1 << "条边的两个顶点及其对应的权值:"; 
        cin >> v1 >> v2 >> w;
        int m = LocateVex(v1);
        int n = LocateVex(v2);
        this->arcs[m][n] = w; 
        this->arcs[n][m] = w; 
    }
	//初始化路径
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->path[i][j] = j;
		}
	}
	return;
}

void Graph::Floyd()
{
	for (int k = 0; k < this->vexnum; k++)
		for (int i = 0; i < this->vexnum; i++)
			for (int j = 0; j < this->vexnum; j++)
				if (this->arcs[i][k] + this->arcs[k][j] < this->arcs[i][j])
				{
					this->arcs[i][j] = this->arcs[i][k] + this->arcs[k][j];
					this->path[i][j] = this->path[i][k];
				}

	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			if (i == j)
				this->arcs[i][j] = 0;
		}
	}
	// this->Show();
}

void Graph::print_path()
{
	cout << "各个顶点对的最短路径：" << endl;
	int row = 0;
	int col = 0;
	int temp = 0;
	for (row = 0; row < this->vexnum; row++)
	{
		for (col = row + 1; col < this->vexnum; col++)
		{
			if (this->arcs[row][col] != MAX)
			{
				cout << "v" << to_string(row + 1) << "---" << "v" << to_string(col + 1) << " weight: " << this->arcs[row][col] << " path: " << " v" << to_string(row + 1);
				temp = path[row][col];
				//循环输出途径的每条路径。
				while (temp != col)
				{
					cout << "-->" << "v" << to_string(temp + 1);
					temp = path[temp][col];
				}
				cout << "-->" << "v" << to_string(col + 1) << endl;
			}
		}
		cout << endl;
	}
}

void Graph::BuildAdjList() {
    // 初始化邻接表

    adjList.resize(vexnum);

    // 根据邻接矩阵构建邻接表
    for(int i = 0; i < vexnum; i++) {
        for(int j = 0; j < vexnum; j++) {
            if(arcs[i][j] != MAX && i != j) {
                Edge e;
                e.dest = j;
                e.weight = arcs[i][j];
                adjList[i].push_back(e);
            }
        }
    }
}

void Graph::SortAdjacentEdges() {
    // 为每个顶点的邻接边按权重排序
    for(int i = 0; i < vexnum; i++) {
        if(!adjList[i].empty()) {
            // 提取权重到一个数组中供堆排序使用
            int size = adjList[i].size();
            int* weights = new int[size + 1]; // 堆排序从索引1开始

            // 复制权重
            for(int j = 0; j < size; j++) {
                weights[j + 1] = adjList[i][j].weight;
            }

            // 使用堆排序
            HeapSort(weights, size);

            // 根据排序后的权重重新组织邻接表
            vector<Edge> sortedEdges;
            for(int j = 1; j <= size; j++) {
                // 查找具有当前权重的边
                for(auto it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                    if(it->weight == weights[j]) {
                        sortedEdges.push_back(*it);
                        adjList[i].erase(it);
                        break;
                    }
                }
            }

            // 更新邻接表
            adjList[i] = sortedEdges;

            delete[] weights;
        }
    }
}

void Graph::QueryPath(int start, int end) {
    // 转换用户输入的顶点编号为内部索引
    start--;
    end--;

    // 验证输入
    if(start < 0 || start >= vexnum || end < 0 || end >= vexnum) {
        cout << "错误：顶点编号无效！有效范围为1至" << vexnum << endl;
        return;
    }

    if(arcs[start][end] == MAX) {
        cout << "从顶点v" << start+1 << "到顶点v" << end+1 << "没有可达路径。" << endl;
        return;
    }

    cout << "\n从顶点v" << start+1 << "到顶点v" << end+1 << "的最短路径:" << endl;
    cout << "距离: " << arcs[start][end] << endl;

    // 构建完整路径
    vector<int> fullPath;
    fullPath.push_back(start);

    int temp = start;
    while(temp != end) {
        temp = path[temp][end];
        fullPath.push_back(temp);
    }

    // 显示路径
    cout << "路径: ";
    for(size_t i = 0; i < fullPath.size(); i++) {
        cout << "v" << fullPath[i]+1;
        if(i < fullPath.size()-1) cout << " → ";
    }
    cout << endl;

    // 显示邻接表路径表示
    cout << "路径上的边:" << endl;
    for(size_t i = 0; i < fullPath.size()-1; i++) {
        int from = fullPath[i];
        int to = fullPath[i+1];
        int weight = arcs[from][to];
        cout << "  v" << from+1 << " → v" << to+1 << " (权重: " << weight << ")" << endl;
    }
}