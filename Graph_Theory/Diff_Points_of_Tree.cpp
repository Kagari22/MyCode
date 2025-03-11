#include <bits/stdc++.h>

// 树上点差分模版
// https://www.luogu.com.cn/problem/P3128
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

int Log2(int n) {
    int ans = 0;
    while ((1LL << ans) <= (n >> 1LL)) {
        ans++;
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> g(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> nums(n + 1), deep(n + 1);
    vector<array<int, 16>> stjump(n + 1);

    int power = Log2(n);

    auto dfs1 = [&](auto&& dfs1, int u, int fa) -> void {
        deep[u] = deep[fa] + 1;
        stjump[u][0] = fa;
        for (int p = 1; p <= power; p++) {
            stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        }
        for (auto v : g[u]) {
            if (v != fa) {
                dfs1(dfs1, v, u);
            }
        }
    };

    auto LCA = [&](int a, int b) -> int {
        if (deep[a] < deep[b]) {
            swap(a, b);
        }
        for (int p = power; p >= 0; p--) {
            if (deep[stjump[a][p]] >= deep[b]) {
                a = stjump[a][p];
            }
        }
        if (a == b) {
            return a;
        }
        for (int p = power; p >= 0; p--) {
            if (stjump[a][p] != stjump[b][p]) {
                a = stjump[a][p];
                b = stjump[b][p];
            }
        }
        return stjump[a][0];
    };

    auto dfs2 = [&](auto&& dfs2, int u, int fa) -> void {
        for (auto v : g[u]) {
            if (v != fa) {
                dfs2(dfs2, v, u);
            }
        }
        for (auto v : g[u]) {
            if (v != fa) {
                nums[u] += nums[v];
            }
        }
    };

    dfs1(dfs1, 1, 0);

    for (int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        int fa = stjump[lca][0];
        nums[u]++, nums[v]++;
        nums[lca]--, nums[fa]--;
    }

    dfs2(dfs2, 1, 0);

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        ans = max(ans, nums[i]);
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