#include <bits/stdc++.h>

// 树上点差分 (tarjan)
// https://www.luogu.com.cn/problem/P3258
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;
using namespace std::chrono;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<pair<int, int>> queries[n + 1];

    for (int i = 1; i < n; i++) {
        queries[a[i]].emplace_back(a[i + 1], i);
        queries[a[i + 1]].emplace_back(a[i], i);
    }

    vector<bool> visited(n + 1);
    vector<int> ans(n + 1), nums(n + 1), unionfind(n + 1), father(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        unionfind[i] = i;
    }

    auto find = [&](auto&& find, int i) -> int {
        if (i != unionfind[i]) {
            unionfind[i] = find(find, unionfind[i]);
        }
        return unionfind[i];
    };

    function<void(int, int)> tarjan = [&](int u, int fa) {
        visited[u] = true;

        for (auto v : g[u]) {
            if (v != fa) {
                tarjan(v, u);  
                father[v] = u;
            }
        }

        for (auto q : queries[u]) {
            int v = q.first;
            int idx = q.second;
            if (visited[v]) {
                ans[idx] = find(find, v);
            }
        }

        unionfind[u] = fa;
        father[u] = fa;
    };

    tarjan(1, 0);

    for (int i = 1; i < n; i++) {
        int u = a[i];
        int v = a[i + 1];
        int lca = ans[i];
        int fa = father[lca];
        nums[u]++, nums[v]++;
        nums[lca]--, nums[fa]--;
    }

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        for (auto v : g[u]) {
            if (v != fa) {
                dfs(dfs, v, u);
            }
        }

        for (auto v : g[u]) {
            if (v != fa) {
                nums[u] += nums[v];
            }
        }
    };

    dfs(dfs, 1, 0);

    for (int i = 2; i <= n; i++) {
        nums[a[i]]--;
    }

    for (int i = 1; i <= n; i++) {
        cout << nums[i] << '\n';
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