#include <bits/stdc++.h>

// 求给定两点的最短路
// from: cpp.json
#define int long long
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 100001;
const int INF = 1e18; 

vector<pair<int, int>> adj[MAXN]; 

// 时间复杂度 O(nlogn)

void dijkstra(int start, vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;

    pq.emplace(0, start);

    while (!pq.empty()) {
        int d = pq.top().first;
        int v = pq.top().second;

        pq.pop();

        if (d > dist[v]) continue;

        for (const auto& [neighbor, weight] : adj[v]) {
            if (dist[v] + weight < dist[neighbor]) {
                dist[neighbor] = dist[v] + weight;
                pq.emplace(dist[neighbor], neighbor);
            }
        }
    }
}

void solve() {
    // 求 a b 两点的最短路
    int n, m, a, b;
    cin >> n >> m >> a >> b; 

    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    vector<int> dist(n + 1, INF); 
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w; 
        adj[u].emplace_back(v, w); 
        adj[v].emplace_back(u, w); 
    }

    dijkstra(a, dist); 

    if (dist[b] == INF) {
        cout << "INF" << '\n'; 
    } else {
        cout << dist[b] << '\n'; 
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
