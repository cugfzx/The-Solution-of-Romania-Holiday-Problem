#pragma once
#include "Graphmtx.h"

template <class T, class E>
class searchAlgorithm
{
public:
	searchAlgorithm(Graphmtx<T, E>& Graph, T begin, T target);
	~searchAlgorithm();
	void BFS();   //�������
	void DFS_Recursive();   //�ݹ��������
	void DFS();				//�ǵݹ��������
	void Greedy();//̰���㷨
	void Astar(); //A*�㷨
	int getNumOfNodes() { return numOfNodes; }
	int getFullDist() { return fullDist; }
	void printWay();
	static E* dist_to_end;//�洢���ڵ㵽�յ���������
	E* dist_to_begin;     //�洢���ڵ㵽�����������
	static E* priority;   //�洢���ȼ�
private:
	Graphmtx<T, E>* G;
	int* wayFrom;        //�洢����·��
	vector<int> way;	 //�洢����·��
	bool* visited;       //�洢�Ƿ���ʹ�
	int NumberOfVertices;//������
	bool found;    //�Ƿ��ҵ����ҵ���ֹͣ�ݹ飬���������������
	int entrance;  //������
	int exit;      //�������
	int numOfNodes;//���ɵĽڵ���
	int fullDist;  //·���ܳ���
	void link(int w, int u) { wayFrom[w] = u; }//���������ڵ�
	void visit(int v) { visited[v] = 1; }      //��Ƿ��ʣ�����close��
	void visit(int w, int u);                  //���w��ǰ����u������Ƿ���
	void getWay();     //��ӡ·��
	void init();         //���wayFrom��visit����
	void dijkstra(int v);//�Ͻ�˹�����㷨
	void calcuPriority(int u, int v);//��������ֵ
	void dfs(int per, int start);    //������������ݹ麯��
};

//������̬����
template <class T, class E>
E* searchAlgorithm<T, E>:: dist_to_end;

//������̬����
template <class T, class E>
E* searchAlgorithm<T, E>::priority;

//���캯��
template <class T, class E>
searchAlgorithm<T, E>::searchAlgorithm(Graphmtx<T,E>& Graph, T begin, T target)
{
	G=&Graph;
	fullDist = 0;
	NumberOfVertices = G->NumberOfVertices();
	wayFrom = new int [NumberOfVertices];
	visited= new bool[NumberOfVertices];
	dist_to_end = new E [NumberOfVertices];
	dist_to_begin = new E[NumberOfVertices];
	priority = new E [NumberOfVertices];

	init();//��ʼ��
	entrance = G->name2index(begin);
	exit = G->name2index(target);
	dijkstra(exit);
}

//��������
template <class T, class E>
searchAlgorithm<T, E>::~searchAlgorithm()
{
	delete []wayFrom;
	delete []visited;
	delete []dist_to_end;
	delete []dist_to_begin;
	delete []priority;
}

//��ʼ��·������
template <class T,class E>
void searchAlgorithm<T, E>::init()
{
	for (int i = 0; i < NumberOfVertices; i++)
	{
		wayFrom[i] = -1;
		visited[i] = 0;
	}
	found = 0;
	numOfNodes = 0;
	fullDist = 0;
	way.clear();
}



//����w��ǰ����u
template <class T, class E>
void searchAlgorithm<T, E>::visit(int w, int u)//��u��w
{
	wayFrom[w] = u;
	visited[w] = 1;
}

//��ӡ·��
template <class T, class E>
void searchAlgorithm<T, E>::getWay()
{
	int j = exit;
	while (j != entrance)
	{
		way.push_back(j);
		fullDist += G->getWeight(j, wayFrom[j]);
		j = wayFrom[j];
	}
}

template <class T, class E>
void searchAlgorithm<T, E>::printWay()
{
	int i = way.size()-1;
	cout << G->getValue(entrance);
	while (i>=0)
	{
		cout << "-->" << G->getValue(way[i--]);
	}
	cout << endl;
}

//�����������
template <class T, class E>
void searchAlgorithm<T, E>::BFS()
{
	int u, w,i = 0;
	queue<int> q;
	init();

	visit(entrance);//���ʽڵ�
	++numOfNodes;
	if (entrance == exit)return;

	q.push(entrance);//�����
	while (!q.empty())//���зǿ�
	{
		u = q.front();//ȡ�����׽ڵ�
		q.pop();//ɾ�������׽ڵ�

		for (w = G->getFirstNeighbor(u); w != -1; w = G->getNextNeighbor(u, w))    
		{//���������ڽӽ��
			if (!visited[w])//������ӽڵ�δ������
			{
				++numOfNodes;//���ɽ����+1
				link(w, u);//����
				visit(w);//��Ƿ���

				if (w == exit)//�ҵ����
				{
					getWay();
					return;
				}
				q.push(w);//�ڵ�ѹ�����
			}
		}
	}
}

//�ǵݹ������������
template <class T, class E>
void searchAlgorithm<T, E>::DFS()
{
	init();//��ʼ��·�߱�ͷ��ʱ�
	stack<int> st;
	int u, w;
	st.push(entrance);//�����ջ
	visit(entrance);
	++numOfNodes;//���ɽ����+1

	while (!st.empty())
	{
		u = st.top();
		st.pop();
		for (w = G->getFirstNeighbor(u); w >= 0; w = G->getNextNeighbor(u, w))
		{//�����ڽӽ��
			if (!visited[w])
			{
				++numOfNodes;//���ɽ����+1
				link(w, u);//����
				visit(w);//��Ƿ���
				if (w == exit)//�ҵ����
				{
					getWay();
					return;
				}
				st.push(w);//�ڵ���ջ
			}
		}
	}
}

//�ݹ������������
template <class T, class E>
void searchAlgorithm<T, E>::DFS_Recursive()
{
	init();//��ʼ��·�߱�ͷ��ʱ�

	++numOfNodes;//���ɽ����+1
	dfs( entrance, entrance);//�ݹ����

	getWay();

}

template <class T, class E>
void searchAlgorithm<T, E>::dfs(int per,int start)
{
	
	link(start,per);
	visit(start);
	if (start == exit)
	{
		found = 1;//����ҵ��ͱ���ҵ���
		return;//ȫ��return��ȥ
	}
	//��������յ�ͱ����ö���������ڽӶ���
	for (int w = G->getFirstNeighbor(start); w >= 0; w = G->getNextNeighbor(start, w))
	{//���δ�����ʣ��ݹ�������������������
		if (!visited[w]) 
		{
			++numOfNodes;//���ɽ����+1
			dfs(start,w);//�ݹ����
			if (found) return;//����Ѿ��ҵ��ˣ��ʹ����ڿ�ʼһ·return��ȥ
		}
	}
}

//�Զ������ȶ���less�ȽϺ���������̰���㷨
template <class T, class E>
struct cmp
{
	bool operator()(int& a, int& b) const
	{
		//��Ϊ���ȳ����ж�Ϊ!cmp�����Է�����ʵ����Сֵ����
		return searchAlgorithm<T, E>::dist_to_end[a] > searchAlgorithm<T, E>::dist_to_end[b];
	}
};

//�Զ������ȶ���less�ȽϺ���������A*�㷨
template <class T, class E>
struct cmp2
{
	bool operator()(int& a, int& b) const
	{
		//��Ϊ���ȳ����ж�Ϊ!cmp�����Է�����ʵ����Сֵ����
		return searchAlgorithm<T, E>::priority[a] > 
			searchAlgorithm<T, E>::priority[b];
	}
};


//̰���㷨
template <class T, class E>
void searchAlgorithm<T, E>::Greedy()
{
	int u, w;
	priority_queue<int, vector<int>, cmp<T,E>> pq;//���ȼ�����
	init();

	visit(entrance);//���ʽڵ�
	++numOfNodes;//���ɽ����+1
	if (entrance == exit)return;

	pq.push(entrance);//�����
	while (!pq.empty())//���зǿ�
	{
		u = pq.top();//ȡ�����׽ڵ�
		pq.pop();//ɾ�������׽ڵ�

		for (w = G->getFirstNeighbor(u); w >= 0; w = G->getNextNeighbor(u, w))    
		{//�����ڽӽ��
			if (!visited[w])//����ӽڵ�δ�����ʣ�������ӽڵ�
			{
				++numOfNodes;//���ɽ����+1
				link(w, u);
				visit(w);
				//cout << "��" << G->getValue(u) << "����" << G->getValue(w) << endl;
				if (u == exit)//�ҵ����
				{
					getWay();
					return;
				}
				pq.push(w);//�ڵ�ѹ�����
			}
		}
	}
}

//�������ȼ�f(x)=h(x)+g(x)
template <class T, class E>
void searchAlgorithm<T, E>::calcuPriority(int u, int w)
{//u����㣬v���յ�
	E*& a = searchAlgorithm<T, E>::dist_to_end;
	E*& b = searchAlgorithm<T, E>::dist_to_begin;
	b[w] = b[u] + G->getWeight(w, u);
	priority[w] = b[w] + a[w];
}

//A*�㷨
template <typename T, typename E>
void searchAlgorithm<T, E>::Astar()
{
	int u,w;
	priority_queue<int, vector<int>, cmp2<T, E>> pq;//���ȼ�����open_set
	init();
	if (entrance == exit)return;

	pq.push(entrance);//�����
	++numOfNodes;//���ɽ����+1
	dist_to_begin[entrance] = 0;

	while (!pq.empty())
	{
		u = pq.top();//ȡ��ͷ���
		pq.pop();//�����u��open_set��ɾ��
		visit(u);//��Ƿ��ʹ�

		for (w = G->getFirstNeighbor(u); w >= 0; w = G->getNextNeighbor(u, w)) 
		{//�������u���е��ڽӶ���
			if (!visited[w])
			{
				++numOfNodes;//���ɽ����+1
				link(w, u);//���ýڵ�w��ǰһ�����Ϊu
				if (u == exit)//����ڵ�uΪ�յ�
				{
					getWay();
					return;
				}
				calcuPriority(u, w);//�������ȼ�
				pq.push(w);//�����ȼ�����
			}
		}
	}
}


//�Ͻ�˹�����㷨������ڵ�����յ�·�����õ�,�Ǳ�����ҵ���ص�
template <typename T, typename E>
void searchAlgorithm<T, E>::dijkstra(int v)
{
	int n = G->NumberOfVertices();
	bool* S = new bool[n]; 	   //���·�����㼯
	int i, j, k;  E w, min;

	for (i = 0; i < n; i++) {
		dist_to_end[i] = G->getWeight(v, i);
		S[i] = false;
		/*if (i != v && dist[i] < maxWeight) path[i] = v;
		else path[i] = -1;*/
	}


	S[v] = true;  dist_to_end[v] = 0;     	//����v����S

	for (i = 0; i < n - 1; i++) {       //ȷ���ɽ��v������n-1��·	
		min = maxWeight;
		int u = v; 					//ѡ����S�о������·���Ķ���u
		for (j = 0; j < n; j++) {
			if (!S[j] && dist_to_end[j] < min) {
				u = j;
				min = dist_to_end[j];
			}
		}


		S[u] = true;	               	//������u���뼯��S


		for (k = 0; k < n; k++) {       	//�޸�		
			w = G->getWeight(u, k);
			if (!S[k] && w < maxWeight && dist_to_end[u] + w < dist_to_end[k]) { //����kδ����S   			            
				dist_to_end[k] = dist_to_end[u] + w;	//����Ϊ��С��
				//path[k] = u;     		//�޸ĵ�k�����·��
			}
		}
	}
}