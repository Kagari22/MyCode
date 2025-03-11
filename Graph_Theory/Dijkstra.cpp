#include <bits/stdc++.h>

// 单源最短路
// https://www.luogu.com.cn/problem/P4779
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int N = 1e5 + 5;

vector<pair<int, int>> g[N];

void Dijkstra(int start, vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;

    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    vector<int> dist(n + 1, INF);

    Dijkstra(s, dist);

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}