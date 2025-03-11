#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P3379
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 500001;

vector<int> g[MAXN];
vector<pair<int, int>> queries[MAXN];
vector<bool> visited(MAXN);
vector<int> father(MAXN);
vector<int> ans(MAXN);

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void tarjan(int u, int fa) {
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
            ans[idx] = find(v);
        }
    }
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 1; i <= n; i++) {
        father[i] = i;
        visited[i] = false;
    }

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        queries[a].push_back({b, i});
        queries[b].push_back({a, i});
    }

    tarjan(s, -1);

    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
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