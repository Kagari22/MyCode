#include <bits/stdc++.h>

// 树的直径 (非负的边权)
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<pair<int, int>>> g(n + 5);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    int start, end;
    int diameter;

    // dist[i] : 从规定的头节点出发，走到i的距离
    // last[i] : 从规定的头节点出发，i节点的上一个节点
    vector<int> dist(n + 1), last(n + 1);

    auto dfs = [&](auto&& dfs, int u, int fa, int val) -> void {
        last[u] = fa;
        dist[u] = dist[fa] + val;
        for (auto [v, w] : g[u]) {
            if (v != fa) {
                dfs(dfs, v, u, w);
            }
        }
    };

    dfs(dfs, 1, 0, 0);

    start = 1;

    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }

    dfs(dfs, start, 0, 0);

    end = 1;

    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[end]) {
            end = i;
        }
    }

    diameter = dist[end];

    cout << diameter << '\n';
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