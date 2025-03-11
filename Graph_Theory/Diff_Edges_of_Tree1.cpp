#include <bits/stdc++.h>

// 树上差分之边差分 (优化版)
// https://www.luogu.com.cn/problem/P2680
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 3e5 + 1; 
const int MAXM = 3e5 + 1; 

int n, m;

int headEdge[MAXN], edgeNext[MAXN * 2], edgeTo[MAXN * 2], edgeWeight[MAXN * 2];
int headQuery[MAXN], queryNext[MAXN * 2], queryTo[MAXN * 2], queryIndex[MAXN * 2];

int tcnt = 1, qcnt = 1;
int maxCost = 0, atLeast = 0, beyond = 0;
bool visited[MAXN];
int dist[MAXN], father[MAXN], lca[MAXN], cost[MAXN], nums[MAXN];
int qu[MAXM], qv[MAXM];

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void tarjan(int u, int fa, int val) {
    visited[u] = true;
    dist[u] = dist[fa] + val;

    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != fa) {
            tarjan(v, u, edgeWeight[e]);
        }
    }

    for (int e = headQuery[u]; e != 0; e = queryNext[e]) {
        int v = queryTo[e];
        if (visited[v]) {
            int idx = queryIndex[e];
            lca[idx] = find(v);
            cost[idx] = dist[u] + dist[v] - 2 * dist[lca[idx]];
            maxCost = max(maxCost, cost[idx]);
        }
    }

    father[u] = fa; 
}

void addEdge(int u, int v, int w){
    edgeNext[tcnt] = headEdge[u];
    edgeTo[tcnt] = v;
    edgeWeight[tcnt] = w;
    headEdge[u] = tcnt++;
}

void addQuery(int u, int v, int i) {
    queryNext[qcnt] = headQuery[u];
    queryTo[qcnt] = v;
    queryIndex[qcnt] = i;
    headQuery[u] = qcnt++;
}

bool dfs(int u, int fa, int val) {
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != fa) {
            if (dfs(v, u, edgeWeight[e])) {
                return true;
            }
        }
    }

    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != fa) {
            nums[u] += nums[v];
        }
    }

    return nums[u] == beyond && val >= atLeast;
}

bool check(int limit) {
    atLeast = maxCost - limit;
    beyond = 0;
    
    fill(nums, nums + MAXN, 0);
    
    for (int i = 1; i <= m; i++) {
        if (cost[i] > limit) {
            nums[qu[i]]++;
            nums[qv[i]]++;
            nums[lca[i]] -= 2;
            beyond++;
        }
    }

    return beyond == 0 || dfs(1, 0, 0);
}

void solve() {
    cin >> n >> m;

    fill(headEdge, headEdge + n + 1, 0);
    fill(headQuery, headQuery + n + 1, 0);
    fill(visited, visited + n + 1, false);
    fill(father, father + n + 1, 0);
    fill(dist, dist + n + 1, 0);

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        addQuery(a, b, i);
        addQuery(b, a, i);
        qu[i] = a;
        qv[i] = b;
    }

    tarjan(1, 0, 0);

    int l = 0, r = maxCost;

    int ans = 0;

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

    while(t--) {
        solve();
    }

    return 0;
}