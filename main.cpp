#include <stdio.h>
#include <string>
#include <windows.h>
#include "Graphmtx.h"
#include "search.h"

using namespace std;

int main()
{
	Graphmtx<string, int> G;
	searchAlgorithm<string, int> agent(G, "Arad", "Bucharest");
	LARGE_INTEGER t1, t2, tc;
	double time;
	QueryPerformanceFrequency(&tc);
	int n,i;

	while (true)
	{
		cout << "请输入算法执行的次数" << endl;
		cin >> n;

		cout << "深度优先搜索(非递归)" << endl;
		QueryPerformanceCounter(&t1);
		for(i=0;i<n;++i){
			agent.DFS();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "平均用时" << time/n << "秒   " << "生成结点数" << agent.getNumOfNodes()
			<< "   路径总长度" << agent.getFullDist() << endl << endl;

		n = i;
		cout << "深度优先搜索(递归)" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i){
			agent.DFS_Recursive();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "平均用时" << time/n << "秒   " << "生成结点数" << agent.getNumOfNodes()
			<< "   路径总长度" << agent.getFullDist() << endl << endl;

		cout << "广度优先搜索" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i) {
			agent.BFS();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "平均用时" << time/n << "秒   " << "生成结点数" << agent.getNumOfNodes()
			<< "   路径总长度" << agent.getFullDist() << endl << endl;


		cout << "贪婪算法搜索" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i) {
			agent.Greedy();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "平均用时" << time/n << "秒   " << "生成结点数" << agent.getNumOfNodes()
			<< "   路径总长度" << agent.getFullDist() << endl << endl;


		cout << "A*算法搜索" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i) {
			agent.Astar();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "平均用时" << time/n << "秒   " << "生成结点数" << agent.getNumOfNodes()
			<< "   路径总长度" << agent.getFullDist() << endl << endl;
	}
	
	return 0;
}

