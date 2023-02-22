#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<vector<int> > graph;
vector<int> tagged, maxMatchings;
int DFS(int vertex);
int AP(int n, int m);

int main(){
	int n, m, k, a, b, res = 0;
	cin >> n >> m >> k;
	graph.resize(n + 1);
	for(int i = 0; i < k; i++){
		cin >> a >> b;
		graph[a].push_back(b);
	}
	AP(n, m);
	for(int i = 1; i <= m; i++)
		if(maxMatchings[i] != -1) res++;
	cout << res << endl;
	for(int i = 1; i <= m; i++)
		if(maxMatchings[i] != -1) cout << maxMatchings[i] << " " << i << endl;
	return 0;
}

int DFS(int vertex){
	if(tagged[vertex] != 0) return 0;
	tagged[vertex] = 1;
	for(size_t i = 0; i < graph[vertex].size(); i++){
		int target = graph[vertex][i];
		if(maxMatchings[target] == -1 || DFS(maxMatchings[target]) != 0){
			maxMatchings[target] = vertex;
			return 1;
		}
	}
	return 0;
}

int AP(int n, int m){
	maxMatchings.assign(m + 1, -1);
	for(int i = 1; i <= n; i++){
		tagged.assign(n + 1, 0);
		DFS(i);
	}
	return 0;
}
