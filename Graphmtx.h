#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

extern const int maxWeight;
const int maxSize = 100;

//邻接矩阵存储的图的类定义（无向图）
template <class T, class E>
class Graphmtx : public Graph<T,E>					//图的邻接矩阵类定义
{
public:
	Graphmtx(int sz = maxSize);						//构造函数
	~Graphmtx()										//析构函数
	{
		delete []VertexList;
		delete []Edge;
	}

	T getValue(int i)								//取顶点i的值, i不合理返回0
	{
		return i >= 0 && i < Graph<T, E>::numVertices ? VertexList[i] : 0;
	}

	E getWeight(int v1, int v2) 					//取边(v1,v2)上的权值，若边不合理，则返回0
	{
		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}

	int getFirstNeighbor(int v);					//取顶点v的第一个邻接顶点
													//返回该邻接顶点的编号，若不存在则返回-1

	int getNextNeighbor(int v, int w);				//取v的邻接顶点w的下一邻接顶点
													//返回下一个邻接定点的编号，若不存在或参数不合理则返回-1

	bool insertVertex(const T &vertex);				//插入顶点vertex
													//接受一个参数，表示插入顶点的值，返回true表示插入成功

	bool insertEdge(int v1, int v2, E cost);		//插入边(v1, v2),权值为cost
													//返回true表示插入成功

	bool removeVertex(int v);						//删去顶点v和所有与它相关联的边
													//返回true表示删除成功

	bool removeEdge(int v1, int v2);				//在图中删去边(v1,v2)
													//返回true表示删除成功

	int name2index(T name);							//由名称得到序号，如果没有返回-1

	int getVertexPos(const T &vertex)				//给出顶点vertex在图中的位置，若不存在则返回-1
	{
		for (int i = 0; i < Graph<T,E>::numVertices; i++)
		{
			if (VertexList[i] == vertex)
			{
				return i;
			}
		}
		return -1;
	}
	void readFile();
	friend ostream& operator << (ostream& out, Graphmtx<T, E>& G)
	{
		int i, j, n, m;
		T e1, e2;
		E weight;
		n = G.NumberOfVertices();		//顶点数与边数
		m = G.NumberOfEdges();
		out << "Number of Vertices: " << n << endl;
		out << "Number of Edges: " << m << endl;
		out << "The edges in the graph are:\n";
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				weight = G.getWeight(i, j);
				if (weight > 0 && weight < maxWeight) {
					e1 = G.getValue(i);	//由下标取得顶点值
					e2 = G.getValue(j);
					out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
				}
			}
		}
		return out;
	}


private:
	T *VertexList; 								   //顶点表
	E **Edge;									   //邻接矩阵
	bool** visited;
};

//由名称得到序号，如果没有返回-1
template <class T, class E>
int Graphmtx<T, E>::name2index(T name)
{
	for (int i = 0; i < Graph<T, E>::NumberOfVertices(); i++)
	{
		if (VertexList[i] == name)
		{
			return i;
		}
	}
	return -1;
}



template <class T, class E>
void Graphmtx<T, E>::readFile()
{
	ifstream infile;
	infile.open("map.txt");
	if (!infile.is_open())
	{ 
		printf("无法打开");
		return;
	}
	string temp;
	int weight;
	for (int i = 0; i < 20; i++)
	{
		infile >> temp;
		insertVertex(temp);
	}
	for (int i = 0; i < 20; i++)
	{
		infile >> temp;
		for (int j = 0; j < 20; j++)
		{
			infile >> weight;
			insertEdge(i, j, weight);
		}
	}
}

//构造函数
template <class T, class E>
Graphmtx<T,E>::Graphmtx(int sz):Graph<T,E>(sz)
{
	int i, j;
	int maxVertices = Graph<T, E>::maxVertices;
	VertexList = new T[maxVertices];			//创建顶点表数组
	Edge =  new int *[maxVertices];		//创建邻接矩阵数组
	visited = new bool *[maxVertices];
	for (i = 0; i < maxVertices; i++)
	{
		Edge[i] = new int[maxVertices];
		visited[i] = 0;
	}
	for (i = 0; i < maxVertices; i++)			//邻接矩阵初始化
	{
		for (j = 0; j < maxVertices; j++)
		{
			Edge[i][j] = maxWeight;
		}
		Edge[i][i] = 0;
	}
	readFile();
}

//给出顶点位置为v的第一个邻接顶点的位置, 如果找不到, 则函数返回-1。
template <class T, class E>
int Graphmtx<T,E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < Graph<T, E>::numVertices; col++)
		{
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
			{
				return col;
			}
		}
	}
	return -1;
}

//给出顶点v的某邻接顶点w的下一个邻接顶点
template <class T, class E>
int Graphmtx<T,E>::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w+1; col < Graph<T, E>::numVertices; col++)
		{
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
			{
				return col;
			}
		}
	}
	return -1;
}

//插入顶点vertex：
//若顶点表满, 则不插入，返回false；若成功插入，则返回true。
template <class T, class E>
bool Graphmtx<T,E>::insertVertex(const T &vertex)
{
	if (Graph<T, E>::numVertices == Graph<T, E>::maxVertices)
	{
		return false;
	}
	VertexList[Graph<T, E>::numVertices++] = vertex;
	return true;
}

//插入边(v1, v2), 权值为cost
template <class T, class E>
bool Graphmtx<T,E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1 < Graph<T, E>::numVertices && v2 > -1 &&
		v2 < Graph<T, E>::numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost; // 若为有向图，则去掉另一条边
		Graph<T, E>::numEdges++;
		return true;
	}
	else
	{
		return false;
	}
}

//删去顶点v和所有与它相关联的边
template <class T, class E>
bool Graphmtx<T,E>::removeVertex(int v)
{
	int numVertices=Graph<T, E>::numVertices;
	int numEdges = Graph<T, E>::numEdges;
	if (v < 0 && v >= numVertices)				//v不在图中,不删除
	{
		return false;
	}
	if (numVertices == 1)						//只剩一个顶点,不删除
	{
		return false;
	}
	int i, j;
	VertexList[v] = VertexList[numVertices-1];	//顶点表中删除该结点
	for (i = 0; i < numVertices; i++)			//减去与v相关联边数
	{
		if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)
		{
			numEdges--;
		}
	}
	for (i = 0; i < numVertices; i++)			//用最后一列填补第v列
	{
		Edge[i][v] = Edge[i][numVertices-1];
	}
	numVertices--;								//顶点数减一
	for (j = 0; j < numVertices; j++)			//用最后一行填补第v行
	{
		Edge[v][j] = Edge[numVertices][j];
	}
	return true;
}

//在图中删去边(v1,v2)
template <class T, class E>
bool Graphmtx<T,E>::removeEdge(int v1, int v2)
{
	int numVertices = Graph<T, E>::numVertices;
	int numEdges = Graph<T, E>::numEdges;
	if (v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && 
		Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return true;
	}
	else
	{
		return false;
	}
}

