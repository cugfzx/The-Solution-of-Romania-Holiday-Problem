#pragma once
#include "Graphmtx.h"

template <class T, class E>
class searchAlgorithm
{
public:
	searchAlgorithm(Graphmtx<T, E>& Graph, T begin, T target);
	~searchAlgorithm();
	void BFS();   //广度优先
	void DFS_Recursive();   //递归深度优先
	void DFS();				//非递归深度优先
	void Greedy();//贪婪算法
	void Astar(); //A*算法
	int getNumOfNodes() { return numOfNodes; }
	int getFullDist() { return fullDist; }
	void printWay();
	static E* dist_to_end;//存储各节点到终点距离的数组
	E* dist_to_begin;     //存储各节点到起点距离的数组
	static E* priority;   //存储优先级
private:
	Graphmtx<T, E>* G;
	int* wayFrom;        //存储倒序路径
	vector<int> way;	 //存储正序路径
	bool* visited;       //存储是否访问过
	int NumberOfVertices;//顶点数
	bool found;    //是否找到，找到就停止递归，用于深度优先搜索
	int entrance;  //入口序号
	int exit;      //出口序号
	int numOfNodes;//生成的节点数
	int fullDist;  //路径总长度
	void link(int w, int u) { wayFrom[w] = u; }//连接两个节点
	void visit(int v) { visited[v] = 1; }      //标记访问，加入close表
	void visit(int w, int u);                  //标记w的前驱是u，并标记访问
	void getWay();     //打印路径
	void init();         //清空wayFrom和visit数组
	void dijkstra(int v);//迪杰斯特拉算法
	void calcuPriority(int u, int v);//计算优先值
	void dfs(int per, int start);    //深度优先搜索递归函数
};

//声明静态变量
template <class T, class E>
E* searchAlgorithm<T, E>:: dist_to_end;

//声明静态变量
template <class T, class E>
E* searchAlgorithm<T, E>::priority;

//构造函数
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

	init();//初始化
	entrance = G->name2index(begin);
	exit = G->name2index(target);
	dijkstra(exit);
}

//析构函数
template <class T, class E>
searchAlgorithm<T, E>::~searchAlgorithm()
{
	delete []wayFrom;
	delete []visited;
	delete []dist_to_end;
	delete []dist_to_begin;
	delete []priority;
}

//初始化路径数组
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



//设置w的前驱是u
template <class T, class E>
void searchAlgorithm<T, E>::visit(int w, int u)//从u到w
{
	wayFrom[w] = u;
	visited[w] = 1;
}

//打印路径
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

//广度优先搜索
template <class T, class E>
void searchAlgorithm<T, E>::BFS()
{
	int u, w,i = 0;
	queue<int> q;
	init();

	visit(entrance);//访问节点
	++numOfNodes;
	if (entrance == exit)return;

	q.push(entrance);//入队列
	while (!q.empty())//队列非空
	{
		u = q.front();//取队列首节点
		q.pop();//删除队列首节点

		for (w = G->getFirstNeighbor(u); w != -1; w = G->getNextNeighbor(u, w))    
		{//遍历所有邻接结点
			if (!visited[w])//如果该子节点未被访问
			{
				++numOfNodes;//生成结点数+1
				link(w, u);//连接
				visit(w);//标记访问

				if (w == exit)//找到结果
				{
					getWay();
					return;
				}
				q.push(w);//节点压入队列
			}
		}
	}
}

//非递归深度优先搜索
template <class T, class E>
void searchAlgorithm<T, E>::DFS()
{
	init();//初始化路线表和访问表
	stack<int> st;
	int u, w;
	st.push(entrance);//起点入栈
	visit(entrance);
	++numOfNodes;//生成结点数+1

	while (!st.empty())
	{
		u = st.top();
		st.pop();
		for (w = G->getFirstNeighbor(u); w >= 0; w = G->getNextNeighbor(u, w))
		{//遍历邻接结点
			if (!visited[w])
			{
				++numOfNodes;//生成结点数+1
				link(w, u);//连接
				visit(w);//标记访问
				if (w == exit)//找到结果
				{
					getWay();
					return;
				}
				st.push(w);//节点入栈
			}
		}
	}
}

//递归深度优先搜索
template <class T, class E>
void searchAlgorithm<T, E>::DFS_Recursive()
{
	init();//初始化路线表和访问表

	++numOfNodes;//生成结点数+1
	dfs( entrance, entrance);//递归调用

	getWay();

}

template <class T, class E>
void searchAlgorithm<T, E>::dfs(int per,int start)
{
	
	link(start,per);
	visit(start);
	if (start == exit)
	{
		found = 1;//如果找到就标记找到了
		return;//全部return回去
	}
	//如果不是终点就遍历该顶点的所有邻接顶点
	for (int w = G->getFirstNeighbor(start); w >= 0; w = G->getNextNeighbor(start, w))
	{//如果未被访问，递归调用深度优先搜索函数
		if (!visited[w]) 
		{
			++numOfNodes;//生成结点数+1
			dfs(start,w);//递归调用
			if (found) return;//如果已经找到了，就从现在开始一路return回去
		}
	}
}

//自定义优先队列less比较函数，用于贪婪算法
template <class T, class E>
struct cmp
{
	bool operator()(int& a, int& b) const
	{
		//因为优先出列判定为!cmp，所以反向定义实现最小值优先
		return searchAlgorithm<T, E>::dist_to_end[a] > searchAlgorithm<T, E>::dist_to_end[b];
	}
};

//自定义优先队列less比较函数，用于A*算法
template <class T, class E>
struct cmp2
{
	bool operator()(int& a, int& b) const
	{
		//因为优先出列判定为!cmp，所以反向定义实现最小值优先
		return searchAlgorithm<T, E>::priority[a] > 
			searchAlgorithm<T, E>::priority[b];
	}
};


//贪婪算法
template <class T, class E>
void searchAlgorithm<T, E>::Greedy()
{
	int u, w;
	priority_queue<int, vector<int>, cmp<T,E>> pq;//优先级队列
	init();

	visit(entrance);//访问节点
	++numOfNodes;//生成结点数+1
	if (entrance == exit)return;

	pq.push(entrance);//入队列
	while (!pq.empty())//队列非空
	{
		u = pq.top();//取队列首节点
		pq.pop();//删除队列首节点

		for (w = G->getFirstNeighbor(u); w >= 0; w = G->getNextNeighbor(u, w))    
		{//遍历邻接结点
			if (!visited[w])//如果子节点未被访问，则访问子节点
			{
				++numOfNodes;//生成结点数+1
				link(w, u);
				visit(w);
				//cout << "从" << G->getValue(u) << "访问" << G->getValue(w) << endl;
				if (u == exit)//找到结果
				{
					getWay();
					return;
				}
				pq.push(w);//节点压入队列
			}
		}
	}
}

//计算优先级f(x)=h(x)+g(x)
template <class T, class E>
void searchAlgorithm<T, E>::calcuPriority(int u, int w)
{//u是起点，v是终点
	E*& a = searchAlgorithm<T, E>::dist_to_end;
	E*& b = searchAlgorithm<T, E>::dist_to_begin;
	b[w] = b[u] + G->getWeight(w, u);
	priority[w] = b[w] + a[w];
}

//A*算法
template <typename T, typename E>
void searchAlgorithm<T, E>::Astar()
{
	int u,w;
	priority_queue<int, vector<int>, cmp2<T, E>> pq;//优先级队列open_set
	init();
	if (entrance == exit)return;

	pq.push(entrance);//入队列
	++numOfNodes;//生成结点数+1
	dist_to_begin[entrance] = 0;

	while (!pq.empty())
	{
		u = pq.top();//取队头结点
		pq.pop();//将结点u从open_set中删除
		visit(u);//标记访问过

		for (w = G->getFirstNeighbor(u); w >= 0; w = G->getNextNeighbor(u, w)) 
		{//遍历结点u所有的邻接顶点
			if (!visited[w])
			{
				++numOfNodes;//生成结点数+1
				link(w, u);//设置节点w的前一个结点为u
				if (u == exit)//如果节点u为终点
				{
					getWay();
					return;
				}
				calcuPriority(u, w);//计算优先级
				pq.push(w);//入优先级队列
			}
		}
	}
}


//迪杰斯特拉算法，计算节点距离终点路径会用到,非本次作业的重点
template <typename T, typename E>
void searchAlgorithm<T, E>::dijkstra(int v)
{
	int n = G->NumberOfVertices();
	bool* S = new bool[n]; 	   //最短路径顶点集
	int i, j, k;  E w, min;

	for (i = 0; i < n; i++) {
		dist_to_end[i] = G->getWeight(v, i);
		S[i] = false;
		/*if (i != v && dist[i] < maxWeight) path[i] = v;
		else path[i] = -1;*/
	}


	S[v] = true;  dist_to_end[v] = 0;     	//顶点v计入S

	for (i = 0; i < n - 1; i++) {       //确定由结点v出发的n-1条路	
		min = maxWeight;
		int u = v; 					//选不在S中具有最短路径的顶点u
		for (j = 0; j < n; j++) {
			if (!S[j] && dist_to_end[j] < min) {
				u = j;
				min = dist_to_end[j];
			}
		}


		S[u] = true;	               	//将顶点u加入集合S


		for (k = 0; k < n; k++) {       	//修改		
			w = G->getWeight(u, k);
			if (!S[k] && w < maxWeight && dist_to_end[u] + w < dist_to_end[k]) { //顶点k未加入S   			            
				dist_to_end[k] = dist_to_end[u] + w;	//更改为较小的
				//path[k] = u;     		//修改到k的最短路径
			}
		}
	}
}