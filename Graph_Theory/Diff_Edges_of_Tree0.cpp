#include <bits/stdc++.h>

// 树上差分之边差分
// https://www.luogu.com.cn/problem/P2680
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 3e5 + 1;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(MAXN);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    int maxCost = 0, atLeast = 0, beyond = 0;
    vector<bool> visited(MAXN);
    vector<int> dist(MAXN), father(MAXN), lca(MAXN), cost(MAXN), nums(MAXN);
    vector<int> qu(MAXN), qv(MAXN);
    vector<vector<pair<int, int>>> queries(MAXN);

    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        queries[a].emplace_back(b, i);  
        queries[b].emplace_back(a, i);
        qu[i] = a;
        qv[i] = b;
    }

    auto find = [&](auto&& find, int i) -> int {
        if (i != father[i]) {
            father[i] = find(find, father[i]);
        }
        return father[i];
    };

    function<void(int, int, int)> tarjan = [&](int u, int fa, int val) {
        visited[u] = true;
        dist[u] = dist[fa] + val;

        for (auto [v, w] : g[u]) {
            if (v != fa) {
                tarjan(v, u, w);
            }
        }

        for (auto q : queries[u]) {
            int v = q.first;
            int idx = q.second;
            if (visited[v]) {
                lca[idx] = find(find, v);
                cost[idx] = dist[u] + dist[v] - 2 * dist[lca[idx]];
                maxCost = max(maxCost, cost[idx]);
            }
        }

        father[u] = fa; 
    };

    tarjan(1, 0, 0);

    int l = 0, r = maxCost;

    int ans = 0;

    auto dfs = [&](auto&& dfs, int u, int fa, int val) -> bool {
        for (auto [v, w] : g[u]) {
            if (v != fa) {
                if (dfs(dfs, v, u, w)) {
                    return true;
                }
            }
        }

        // 回收差分信息
        for (auto [v, w] : g[u]) {
            if (v != fa) {
                nums[u] += nums[v];
            }
        }

        return nums[u] == beyond && val >= atLeast;
    };

    auto check = [&](int limit) -> bool {
        atLeast = maxCost - limit;
        beyond = 0;
        
        fill(nums.begin(), nums.end(), 0);
        
        for (int i = 1; i <= m; i++) {
            if (cost[i] > limit) {
                nums[qu[i]]++;
                nums[qv[i]]++;
                nums[lca[i]] -= 2;
                beyond++;
            }
        }

        return beyond == 0 || dfs(dfs, 1, 0, 0);
    };

    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
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