#pragma once
#include <iostream>
//const int maxWeight = 0x7fffffff;
const int maxWeight = 1000;

// ͼ�ĳ�����ඨ��#��Ȩ����ͼ
// TΪ��������ͣ�EΪ��Ȩֵ�����ͣ�һ��ӦΪĳһ�������͡�
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
	bool GraphEmpty() const{				//��ͼ�շ�	
		return (numEdges == 0);
	}	
	bool GraphFull() const{					//��ͼ���� 	
		return (numVertices == maxVertices || 
			numEdges == maxVertices*(maxVertices-1)/2);//����ͼ������ͼ������2
	}
	int NumberOfVertices(){				//���ص�ǰ������	
		return numVertices;
	}
	int NumberOfEdges(){					//���ص�ǰ����	
		return numEdges;
	}

	
	//friend istream& operator >> (istream& in, Graph<T, E>& G)
	//{
	//	int i, j, k, n, m;
	//	T e1, e2;
	//	E weight;
	//	in >> n >> m;				//���붥���������
	//	for (i = 0; i < n; i++) {	//�������붥��ֵ
	//		in >> e1;
	//		G.insertVertex(e1);
	//	}
	//	i = 0;
	//	while (i < m) {
	//		assert(in >> e1 >> e2 >> weight);	//��������ߵ�������ֵ����Ȩֵ
	//		j = G.getVertexPos(e1);				//ȡ��Ӧ�����±�
	//		k = G.getVertexPos(e2);
	//		if (j == -1 || k == -1) {			//ȡ��Ӧ���㲻����
	//			cout << "Input error!\n";
	//		}
	//		else {
	//			G.insertEdge(j, k, weight);		//�ɶ����±��Ȩֵ�����
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
	//	n = G.NumberOfVertices();		//�����������
	//	m = G.NumberOfEdges();
	//	out << "Number of Vertices: " << n << endl;
	//	out << "Number of Edges: " << m << endl;
	//	out << "The edges in the graph are:\n";
	//	for (i = 0; i < n; i++) {
	//		for (j = i + 1; j < n; j++) {
	//			weight = G.getWeight(i, j);
	//			if (weight > 0 && weight < maxWeight) {
	//				e1 = G.getValue(i);	//���±�ȡ�ö���ֵ
	//				e2 = G.getValue(j);
	//				out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
	//			}
	//		}
	//	}
	//	return out;
	//}

	// ͼ���������ʵ�ֵ�һЩ�ӿ�
	virtual T getValue(int i) = 0;							//ȡλ��Ϊi�Ķ����е�ֵ
	virtual E getWeight(int v1, int v2) = 0;				//���ر�(v1,v2)�ϵ�Ȩֵ
	virtual bool insertVertex(const T &vertex) = 0;			//��ͼ�в���һ������vertex
	virtual bool removeVertex(int v) = 0;					//��ͼ��ɾ��һ������v
	virtual bool insertEdge(int v1, int v2, E weight) = 0;	//����ȨֵΪweight�ı�(v1,v2)
	virtual bool removeEdge(int v1, int v2) = 0;			//ɾ����(v1,v2)
	virtual int getFirstNeighbor(int v) = 0;				//ȡ����v�ĵ�һ���ڽӶ���
	virtual int getNextNeighbor(int v, int w) = 0;			//ȡv���ڽӶ���w����һ�ڽӶ���
	virtual int getVertexPos(const T &vertex) = 0;			//��������vertex��ͼ�е�λ��
protected:
	int maxVertices;			//ͼ����󶥵���
	int numEdges;				//��ǰ����
	int numVertices;			//��ǰ������
};

