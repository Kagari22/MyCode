#include <bits/stdc++.h>

// 树的直径
// https://www.luogu.com.cn/problem/P2195
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> father(n + 1);

    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }

    auto find = [&](auto&& find, int i) -> int {
        if (i != father[i]) {
            father[i] = find(find, father[i]);
        }
        return father[i];
    };

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);    
        g[v].emplace_back(u);
        u = find(find, u);
        v = find(find, v);
        father[u] = v;
    }

    // diameter[i] : 如果i是集合的头节点，diameter[i]表示整个集合的直径长度
	//               如果i不再是集合的头节点，diameter[i]的值没有用
    // dist[u] : 从u开始必须往下走，能走出的最大距离，可以不选任何边
    vector<int> diameter(n + 1), dist(n + 1);

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        for (auto v : g[u]) {
            if (v != fa) {
                dfs(dfs, v, u);
            }
        }
        for (auto v : g[u]) {
            if (v != fa) {
                diameter[u] = max(diameter[u], max(diameter[v], dist[u] + dist[v] + 1));
                dist[u] = max(dist[u], dist[v] + 1);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (i == father[i]) {
            dfs(dfs, i, 0);
        }
    }

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            x = find(find, x);
            cout << diameter[x] << '\n';
        } else {
            int x, y;
            cin >> x >> y;
            x = find(find, x);
            y = find(find, y);
            if (x != y) {
                father[x] = y;
                diameter[y] = max((diameter[x] + 1) / 2 + (diameter[y] + 1) / 2 + 1, max(diameter[x], diameter[y]));
            }
        }
    }
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