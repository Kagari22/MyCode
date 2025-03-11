#include <bits/stdc++.h>

// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 500001;
const int LIMIT = 20;

int power;
vector<int> deep(MAXN);
int stjump[MAXN][LIMIT];

int Log2(int n) {
    int ans = 0;
    while ((1LL << ans) <= (n >> 1LL)) {
        ans++;
    }
    return ans;
}

void build(int n) {
    power = Log2(n);
}

void dfs(vector<vector<int>>& g, int u, int father) {
    deep[u] = deep[father] + 1;
    stjump[u][0] = father;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (auto v : g[u]) {
        if (v != father) {
            dfs(g, v, u);
        }
    }
}

int LCA(int a, int b) {
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
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;

    build(n);

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs(g, s, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
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