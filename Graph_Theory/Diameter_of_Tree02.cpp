#include <bits/stdc++.h>

// 树的直径 (边权可负) 
// 树型DP 写法
// https://www.luogu.com.cn/problem/U81904
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    // dist[u] : 从u开始必须往下走，能走出的最大距离，可以不选任何边
    // ans[u] : 路径必须包含点u的情况下，最大路径和
    vector<int> dist(n + 1), ans(n + 1);

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        for (auto [v, _] : g[u]) {
            if (v != fa) {
                dfs(dfs, v, u);
            }
        }

        for (auto [v, w] : g[u]) {
            if (v != fa) {
                ans[u] = max(ans[u], dist[u] + dist[v] + w);
                dist[u] = max(dist[u], dist[v] + w);
            }
        }
    };

    dfs(dfs, 1, 0);

    int diameter = -INF;

    for (int i = 1; i <= n; i++) {
        diameter = max(diameter, ans[i]);
    }

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