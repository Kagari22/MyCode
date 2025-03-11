#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define i32 __int32_t
#define i64 long long
#define i128 __int128_t
const int MOD = 1e9 + 7;
using namespace std;

constexpr int MAXN = 200001;
int indegree[MAXN];
int ans[MAXN];
int n, m;

bool TopuSort(vector<vector<int>>& g) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    int visited = 0;
    while (!q.empty()) {
        int u = q.front();
        ans[visited++] = u;
        q.pop();
        for (auto& v : g[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    return visited == n; 
}

void solve() {
    cin >> n >> m;
    vector<vector<int>> g(n + 1); 
    fill(indegree, indegree + n + 1, 0);  

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indegree[v]++;
    }

    if (!TopuSort(g)) {
        cout << "-1\n";
    } else {
        for (int i = 0; i < n - 1; i++) {
            cout << ans[i] << " ";
        }
        cout << ans[n - 1];
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