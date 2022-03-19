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
		cout << "�������㷨ִ�еĴ���" << endl;
		cin >> n;

		cout << "�����������(�ǵݹ�)" << endl;
		QueryPerformanceCounter(&t1);
		for(i=0;i<n;++i){
			agent.DFS();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "ƽ����ʱ" << time/n << "��   " << "���ɽ����" << agent.getNumOfNodes()
			<< "   ·���ܳ���" << agent.getFullDist() << endl << endl;

		n = i;
		cout << "�����������(�ݹ�)" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i){
			agent.DFS_Recursive();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "ƽ����ʱ" << time/n << "��   " << "���ɽ����" << agent.getNumOfNodes()
			<< "   ·���ܳ���" << agent.getFullDist() << endl << endl;

		cout << "�����������" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i) {
			agent.BFS();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "ƽ����ʱ" << time/n << "��   " << "���ɽ����" << agent.getNumOfNodes()
			<< "   ·���ܳ���" << agent.getFullDist() << endl << endl;


		cout << "̰���㷨����" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i) {
			agent.Greedy();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "ƽ����ʱ" << time/n << "��   " << "���ɽ����" << agent.getNumOfNodes()
			<< "   ·���ܳ���" << agent.getFullDist() << endl << endl;


		cout << "A*�㷨����" << endl;
		QueryPerformanceCounter(&t1);
		for (i = 0; i < n; ++i) {
			agent.Astar();
		}
		QueryPerformanceCounter(&t2);
		agent.printWay();
		time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		cout << "ƽ����ʱ" << time/n << "��   " << "���ɽ����" << agent.getNumOfNodes()
			<< "   ·���ܳ���" << agent.getFullDist() << endl << endl;
	}
	
	return 0;
}

