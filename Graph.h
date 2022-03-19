#pragma once
#include <iostream>
//const int maxWeight = 0x7fffffff;
const int maxWeight = 1000;

// 图的抽象基类定义#有权无向图
// T为顶点的类型；E为边权值的类型，一般应为某一整数类型。
template <typename T, typename E>
class Graph
{
public:
	Graph(int sz){
		maxVertices = sz;
		numVertices = 0;
		numEdges = 0;
	}
	virtual ~Graph(){};
	bool GraphEmpty() const{				//判图空否	
		return (numEdges == 0);
	}	
	bool GraphFull() const{					//判图满否 	
		return (numVertices == maxVertices || 
			numEdges == maxVertices*(maxVertices-1)/2);//无向图，有向图不除以2
	}
	int NumberOfVertices(){				//返回当前顶点数	
		return numVertices;
	}
	int NumberOfEdges(){					//返回当前边数	
		return numEdges;
	}

	
	//friend istream& operator >> (istream& in, Graph<T, E>& G)
	//{
	//	int i, j, k, n, m;
	//	T e1, e2;
	//	E weight;
	//	in >> n >> m;				//输入顶点数与边数
	//	for (i = 0; i < n; i++) {	//依次输入顶点值
	//		in >> e1;
	//		G.insertVertex(e1);
	//	}
	//	i = 0;
	//	while (i < m) {
	//		assert(in >> e1 >> e2 >> weight);	//依次输入边的两顶点值及其权值
	//		j = G.getVertexPos(e1);				//取对应顶点下标
	//		k = G.getVertexPos(e2);
	//		if (j == -1 || k == -1) {			//取对应顶点不存在
	//			cout << "Input error!\n";
	//		}
	//		else {
	//			G.insertEdge(j, k, weight);		//由顶点下标和权值插入边
	//			i++;
	//		}
	//	}
	//	return in;
	//}

	//friend ostream& operator << (ostream& out, Graph<T, E>& G)
	//{
	//	int i, j, n, m;
	//	T e1, e2;
	//	E weight;
	//	n = G.NumberOfVertices();		//顶点数与边数
	//	m = G.NumberOfEdges();
	//	out << "Number of Vertices: " << n << endl;
	//	out << "Number of Edges: " << m << endl;
	//	out << "The edges in the graph are:\n";
	//	for (i = 0; i < n; i++) {
	//		for (j = i + 1; j < n; j++) {
	//			weight = G.getWeight(i, j);
	//			if (weight > 0 && weight < maxWeight) {
	//				e1 = G.getValue(i);	//由下标取得顶点值
	//				e2 = G.getValue(j);
	//				out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
	//			}
	//		}
	//	}
	//	return out;
	//}

	// 图的子类必须实现的一些接口
	virtual T getValue(int i) = 0;							//取位置为i的顶点中的值
	virtual E getWeight(int v1, int v2) = 0;				//返回边(v1,v2)上的权值
	virtual bool insertVertex(const T &vertex) = 0;			//在图中插入一个顶点vertex
	virtual bool removeVertex(int v) = 0;					//在图中删除一个顶点v
	virtual bool insertEdge(int v1, int v2, E weight) = 0;	//插入权值为weight的边(v1,v2)
	virtual bool removeEdge(int v1, int v2) = 0;			//删除边(v1,v2)
	virtual int getFirstNeighbor(int v) = 0;				//取顶点v的第一个邻接顶点
	virtual int getNextNeighbor(int v, int w) = 0;			//取v的邻接顶点w的下一邻接顶点
	virtual int getVertexPos(const T &vertex) = 0;			//给出顶点vertex在图中的位置
protected:
	int maxVertices;			//图中最大顶点数
	int numEdges;				//当前边数
	int numVertices;			//当前顶点数
};

