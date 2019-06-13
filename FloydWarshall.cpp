#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

vector < vector < long long > > MinDistance;

void BuildGraph() {
	int n;
	cin >> n;

	MinDistance.resize(n, vector < long long >(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int w;
			cin >> w;

			if (w == -1) MinDistance[i][j] = INT_MAX;
			else  MinDistance[i][j] = w;

		}
	}
}

void FloydWarshall() {
	for (int k = 0; k < MinDistance.size(); k++) {
		for (int i = 0; i < MinDistance.size(); i++) {
			for (int j = 0; j < MinDistance.size(); j++) {
				if (MinDistance[i][k] < INT_MAX && MinDistance[k][j] < INT_MAX) {
					MinDistance[i][j] = min(MinDistance[i][j], MinDistance[i][k] + MinDistance[k][j]);
				}
			}
		}
	}

	for (auto i : MinDistance) {
		for (auto j : i) {
			cout << j << ' ';
		}
		cout << '\n';
	}
}

int main() {
	BuildGraph();
	FloydWarshall();
	return 0;
}