#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 10001;
vector<int> dfn(MAXN);
vector<int> siz(MAXN);
vector<vector<int>> g(MAXN);
vector<int> nums(MAXN);
int dfncnt = 0;

void f(int u) {
    int i = ++dfncnt;
    dfn[u] = i;
    siz[i] = 1;
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            f(v);
            siz[i] += siz[dfn[v]];
        }
    }
} 

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // nums[i] : 第 i 个节点的值
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f(0);
    for (int i = 0; i < n; i++) {
        cout << dfn[i] << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; i++) {
        cout << siz[i] << " ";
    }

    return 0;
}