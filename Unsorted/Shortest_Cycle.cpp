#include <bits/stdc++.h>

// 寻找图中最短环
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

int findShortestCycle(int n, vector<vector<int>>& edges) {
    vector<vector<int>> g(n);
    for (auto& e : edges) {
        int u = e[0], v = e[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<bool> visited(n, false);
    int shortest = numeric_limits<int>::max();
    for (int start = 0; start < n; start++) {
        vector<int> dist(n, -1);
        queue<pair<int, int>> q;
        q.push({start, -1});
        dist[start] = 0;
        while (!q.empty()) {
            auto [node, parent] = q.front();
            q.pop();
            for (int neighbor : g[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push({neighbor, node});
                } else if (neighbor != parent) {
                    int cycle_len = dist[node] + dist[neighbor] + 1;
                    shortest = min(shortest, cycle_len);
                }
            }
        }
    }  
    return shortest == numeric_limits<int>::max() ? -1 : shortest;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> edges(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }
    int ans = findShortestCycle(n, edges);
    cout << ans << endl;

    return 0;
}