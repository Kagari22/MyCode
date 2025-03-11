#include <bits/stdc++.h>

// 求最长路
// https://www.luogu.com.cn/problem/P1807
#define INF 1e18
#define int long long
using namespace std;

const int MAXN = 50005;

int n, m;
vector<vector<pair<int, int>>> adj(MAXN); 
vector<int> dist(MAXN, INF);             
vector<bool> enter(MAXN, false);        
vector<int> cnt(MAXN, 0);       

void addEdge(int u, int v, int w) {
    adj[u].emplace_back(v, -w); 
}

bool spfa(int start) {
    queue<int> q;
    // priority_queue<int, vector<int>, greater<int>> q;
    dist[start] = 0;
    q.push(start);
    enter[start] = true;
    cnt[start] = 1;

    while (!q.empty()) {
        int u = q.front();
        // int u = q.top();
        q.pop();
        enter[u] = false;

        for (auto &[v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) { 
                dist[v] = dist[u] + w;
                if (!enter[v]) {
                    q.push(v);
                    enter[v] = true;
                    if (++cnt[v] >= n) {
                        return false; 
                    }
                }
            }
        }
    }
    return true; 
}

void solve() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w); 
    }

    if (!spfa(1)) {
        cout << -1 << '\n';
        return;
    }

    int ans = dist[n] == INF ? -1 : -dist[n]; 

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
