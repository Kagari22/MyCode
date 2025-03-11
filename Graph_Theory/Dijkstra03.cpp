#include <bits/stdc++.h>

// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

const int MAXN = 1001;
vector<pair<int, int>> adj[MAXN];   // 正向图的邻接表
vector<pair<int, int>> rev_adj[MAXN]; // 反向图的邻接表
int n, m;

vector<int> dijkstra(int start, const vector<pair<int, int>> graph[]) {
    vector<int> dist(n, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

void solve() {
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--; 
        adj[u].emplace_back(v, w);       
        rev_adj[v].emplace_back(u, w);   
    }

    int source = 0; 

    vector<int> dist_from_source = dijkstra(source, adj);
    
    vector<int> dist_to_source = dijkstra(source, rev_adj);

    int ans = 0;

    for (int i = 1; i < n; i++) { 
        if (dist_from_source[i] == INF || dist_to_source[i] == INF) {
            cout << "-1\n"; 
            return;
        }
        ans += dist_from_source[i] + dist_to_source[i]; 
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }

    return 0;
}