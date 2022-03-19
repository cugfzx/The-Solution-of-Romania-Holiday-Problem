#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

extern const int maxWeight;
const int maxSize = 100;

//�ڽӾ���洢��ͼ���ඨ�壨����ͼ��
template <class T, class E>
class Graphmtx : public Graph<T,E>					//ͼ���ڽӾ����ඨ��
{
public:
	Graphmtx(int sz = maxSize);						//���캯��
	~Graphmtx()										//��������
	{
		delete []VertexList;
		delete []Edge;
	}

	T getValue(int i)								//ȡ����i��ֵ, i��������0
	{
		return i >= 0 && i < Graph<T, E>::numVertices ? VertexList[i] : 0;
	}

	E getWeight(int v1, int v2) 					//ȡ��(v1,v2)�ϵ�Ȩֵ�����߲������򷵻�0
	{
		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}

	int getFirstNeighbor(int v);					//ȡ����v�ĵ�һ���ڽӶ���
													//���ظ��ڽӶ���ı�ţ����������򷵻�-1

	int getNextNeighbor(int v, int w);				//ȡv���ڽӶ���w����һ�ڽӶ���
													//������һ���ڽӶ���ı�ţ��������ڻ�����������򷵻�-1

	bool insertVertex(const T &vertex);				//���붥��vertex
													//����һ����������ʾ���붥���ֵ������true��ʾ����ɹ�

	bool insertEdge(int v1, int v2, E cost);		//�����(v1, v2),ȨֵΪcost
													//����true��ʾ����ɹ�

	bool removeVertex(int v);						//ɾȥ����v����������������ı�
													//����true��ʾɾ���ɹ�

	bool removeEdge(int v1, int v2);				//��ͼ��ɾȥ��(v1,v2)
													//����true��ʾɾ���ɹ�

	int name2index(T name);							//�����Ƶõ���ţ����û�з���-1

	int getVertexPos(const T &vertex)				//��������vertex��ͼ�е�λ�ã����������򷵻�-1
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
		n = G.NumberOfVertices();		//�����������
		m = G.NumberOfEdges();
		out << "Number of Vertices: " << n << endl;
		out << "Number of Edges: " << m << endl;
		out << "The edges in the graph are:\n";
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				weight = G.getWeight(i, j);
				if (weight > 0 && weight < maxWeight) {
					e1 = G.getValue(i);	//���±�ȡ�ö���ֵ
					e2 = G.getValue(j);
					out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
				}
			}
		}
		return out;
	}


private:
	T *VertexList; 								   //�����
	E **Edge;									   //�ڽӾ���
	bool** visited;
};

//�����Ƶõ���ţ����û�з���-1
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
		printf("�޷���");
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

//���캯��
template <class T, class E>
Graphmtx<T,E>::Graphmtx(int sz):Graph<T,E>(sz)
{
	int i, j;
	int maxVertices = Graph<T, E>::maxVertices;
	VertexList = new T[maxVertices];			//�������������
	Edge =  new int *[maxVertices];		//�����ڽӾ�������
	visited = new bool *[maxVertices];
	for (i = 0; i < maxVertices; i++)
	{
		Edge[i] = new int[maxVertices];
		visited[i] = 0;
	}
	for (i = 0; i < maxVertices; i++)			//�ڽӾ����ʼ��
	{
		for (j = 0; j < maxVertices; j++)
		{
			Edge[i][j] = maxWeight;
		}
		Edge[i][i] = 0;
	}
	readFile();
}

//��������λ��Ϊv�ĵ�һ���ڽӶ����λ��, ����Ҳ���, ��������-1��
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

//��������v��ĳ�ڽӶ���w����һ���ڽӶ���
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

//���붥��vertex��
//���������, �򲻲��룬����false�����ɹ����룬�򷵻�true��
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

//�����(v1, v2), ȨֵΪcost
template <class T, class E>
bool Graphmtx<T,E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1 < Graph<T, E>::numVertices && v2 > -1 &&
		v2 < Graph<T, E>::numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost; // ��Ϊ����ͼ����ȥ����һ����
		Graph<T, E>::numEdges++;
		return true;
	}
	else
	{
		return false;
	}
}

//ɾȥ����v����������������ı�
template <class T, class E>
bool Graphmtx<T,E>::removeVertex(int v)
{
	int numVertices=Graph<T, E>::numVertices;
	int numEdges = Graph<T, E>::numEdges;
	if (v < 0 && v >= numVertices)				//v����ͼ��,��ɾ��
	{
		return false;
	}
	if (numVertices == 1)						//ֻʣһ������,��ɾ��
	{
		return false;
	}
	int i, j;
	VertexList[v] = VertexList[numVertices-1];	//�������ɾ���ý��
	for (i = 0; i < numVertices; i++)			//��ȥ��v���������
	{
		if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)
		{
			numEdges--;
		}
	}
	for (i = 0; i < numVertices; i++)			//�����һ�����v��
	{
		Edge[i][v] = Edge[i][numVertices-1];
	}
	numVertices--;								//��������һ
	for (j = 0; j < numVertices; j++)			//�����һ�����v��
	{
		Edge[v][j] = Edge[numVertices][j];
	}
	return true;
}

//��ͼ��ɾȥ��(v1,v2)
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

