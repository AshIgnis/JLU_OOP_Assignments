#include "floyd.h"
#include <iostream>
using namespace std;

int main() {    
    // 创建图实例
    Graph g;
    
    // 创建图
    g.Create();
    
    // 构建邻接表
    g.BuildAdjList();
    
    // 对邻接表进行排序
    g.SortAdjacentEdges();
    
    // 执行Floyd算法计算所有最短路径
    g.Floyd();
    
    // 打印所有最短路径
    g.print_path();
    
    // 提供路径查询功能
    int choice = 1;
    while(choice) {
        int start, end;
        cout << "\n请输入要查询的起点和终点 (顶点编号): ";
        cin >> start >> end;
        
        g.QueryPath(start, end);
        
        cout << "\n是否继续查询? (1:是，0:否): ";
        cin >> choice;
    }
    

    system("pause");

    return 0;
}