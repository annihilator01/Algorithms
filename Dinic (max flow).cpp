#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
	int from, to, capacity, flow;
	Edge(int from_, int to_, int capacity_, int flow_) : from(from_), to(to_), capacity(capacity_), flow(flow_){

	}
};

vector < vector < int > > Graph;
vector < int > EdgePtr;
vector < int > Distance;
vector < Edge > Edges;
int S, T;

void BuildGraph() {
	int n, m;
	cin >> n >> m;

	S = 0; 
	T = n - 1;
	Graph.resize(n);

	for (int i = 0; i < m; i++) {
		int from, to, c;
		cin >> from >> to >> c;
		from--; to--;
		
		Graph[from].push_back(Edges.size());
		Edges.push_back(Edge(from, to, c, 0));

		Graph[to].push_back(Edges.size());
		Edges.push_back(Edge(to, from, 0, 0));
	}
}

bool BFS() {
	queue < int > Queue;
	Distance.assign(Graph.size(), -1);

	Queue.push(S);
	Distance[S] = 0;

	while (!Queue.empty()) {
		int v = Queue.front();
		Queue.pop();

		for (int EdgeNum : Graph[v]) {
			int to = Edges[EdgeNum].to;
			int flow = Edges[EdgeNum].flow;
			int capacity = Edges[EdgeNum].capacity;

			if (Distance[to] == -1 && flow < capacity) {
				Queue.push(to);
				Distance[to] = Distance[v] + 1;
			}
		}
	}
	return Distance[T] != -1;
}

int DFS(int v, int CurrentFlow) {
	if (!CurrentFlow) {
		return 0;
	}
	if (v == T) {
		return CurrentFlow;
	}

	for (; EdgePtr[v] < Graph[v].size(); EdgePtr[v]++) {
		int EdgeNum = Graph[v][EdgePtr[v]];
		int to = Edges[EdgeNum].to;
		int flow = Edges[EdgeNum].flow;
		int capacity = Edges[EdgeNum].capacity;

		if (Distance[v] + 1 != Distance[to]) {
			continue;
		}

		int BottleNeck = DFS(to, min(CurrentFlow, capacity - flow));
		if (BottleNeck) {
			Edges[EdgeNum].flow += BottleNeck;
			Edges[EdgeNum ^ 1].flow -= BottleNeck;
			return BottleNeck;
		}
	}

	return 0;
}

int Dinic() {
	int MaxFlow = 0;
	while (BFS()) {
		EdgePtr.assign(Graph.size(), 0);
		while (int BottleNeck = DFS(S, INT_MAX)) {
			MaxFlow += BottleNeck;
		}
	}
	return MaxFlow;
}

int main() {
	ios_base::sync_with_stdio(false);

	freopen("maxflow.in", "r", stdin);
	freopen("maxflow.out", "w", stdout);

	BuildGraph();
	cout << Dinic();

	return 0;
}
