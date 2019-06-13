#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector < vector < pair < int, int > > > Graph;    // first - edge weight, second - adjacent vertex
vector < long long > MinDistance;
set < pair < long long, int > > Queue; // first - MinDistance[Vertex], second - Vertex

void BuildGraph() {
	int n, m;
	cin >> n >> m;

	Graph.resize(n);
	MinDistance.resize(n, LLONG_MAX);
	MinDistance[0] = 0;

	for (int i = 0; i < m; i++) {
		int v1, v2, w;
		cin >> v1 >> v2 >> w;
		v1--; v2--;
		Graph[v1].push_back(make_pair(w, v2));
		Graph[v2].push_back(make_pair(w, v1));
	}
}

void Dijkstra() {
	Queue.insert(make_pair(MinDistance[0], 0));

	while (!Queue.empty()) {
		int v = Queue.begin()->second;
		Queue.erase(Queue.begin());

		for (auto j : Graph[v]) {
			if (MinDistance[j.second] > j.first + MinDistance[v]) {
				Queue.erase(make_pair(MinDistance[j.second], j.second));
				MinDistance[j.second] = j.first + MinDistance[v];
				Queue.insert(make_pair(MinDistance[j.second], j.second));
			}
		}
	}

	for (auto i : MinDistance) {
		cout << i << ' ';
	}
}

int main() {
	BuildGraph();
	Dijkstra();
	return 0;
}