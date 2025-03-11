#include <bits/stdc++.h>

// https://codeforces.com/group/BJlsDCvlJO/contest/574197/problem/C
// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

void Dijkstra(int start, vector<int>& dist, vector<vector<pair<int, int>>>& adj) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int d = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        if (d < dist[v]) continue;

        for (const auto& [neighbor, weight] : adj[v]) {
            int newDist = dist[v] + weight;
            if (newDist > dist[neighbor]) {
                dist[neighbor] = newDist;
                pq.emplace(newDist, neighbor);
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
        // g[v].emplace_back(u, w);
    }

    vector<int> dist(n + 1, -INF); 

    Dijkstra(0, dist, g);

    if (dist[n - 1] == -INF) {
        cout << -1 << '\n';
    } else {
        cout << dist[n - 1] << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}