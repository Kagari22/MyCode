#include <bits/stdc++.h>

// 所有直径的公共部分
// https://www.luogu.com.cn/problem/P3304
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);    
        g[v].emplace_back(u, w);
    }

    vector<int> dist(n + 1), last(n + 1);
    vector<bool> diameter_path(n + 1);
    int diameter = 0, common_edges = 0;

    auto dfs = [&](auto&& dfs, int u, int fa, int c) -> void {
        last[u] = fa;
        dist[u] = c;
        for (auto [v, w] : g[u]) {
            if (v != fa) {
                dfs(dfs, v, u, c + w);
            }
        }
    };

    dfs(dfs, 1, 0, 0);

    int start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }

    dfs(dfs, start, 0, 0);

    int end = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[end]) {
            end = i;
        }
    }

    diameter = dist[end];

    for (int i = end; i != 0; i = last[i]) {
        diameter_path[i] = true;
    }

    int l = start, r = end;
    int maxdist = 0;

    auto DFS = [&](auto&& DFS, int u, int fa, int c) -> int {
        int ans = c;
        for (auto [v, w] : g[u]) {
            if (v != fa && !diameter_path[v]) {
                ans = max(ans, DFS(DFS, v, u, c + w));
            }
        }
        return ans;
    };

    for (int i = last[end]; i != start; i = last[i]) {
        maxdist = DFS(DFS, i, 0, 0);
        if (maxdist == diameter - dist[i]) {
            r = i;
        }
        if (maxdist == dist[i] && l == start) {
            l = i;
        }
    }

    if (l == r) {
        common_edges = 0;
    } else {
        common_edges = 1;
        for (int i = last[r]; i != l; i = last[i]) {
            common_edges++;
        }
    }

    cout << diameter << '\n';
    cout << common_edges << '\n';
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