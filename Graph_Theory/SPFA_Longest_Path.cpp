#include <bits/stdc++.h>

// 求最长路
// https://codeforces.com/group/BJlsDCvlJO/contest/574197/problem/C
#define INF 1e18
#define int long long
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 5); 
    vector<int> dist(n + 5, INF);             
    vector<bool> enter(n + 5);        
    vector<int> cnt(n + 5);  

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].emplace_back(v, -w); 
    }

    auto spfa = [&](int start) -> bool {
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
    };
 
    if (!spfa(0)) {
        cout << -1 << '\n';
        return;
    }

    int ans = dist[n - 1] == INF ? -1 : -dist[n - 1]; 

    cout << ans << '\n';
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