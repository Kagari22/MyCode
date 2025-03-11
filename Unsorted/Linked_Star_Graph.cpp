#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define i32 __int32_t
#define i64 long long
#define i128 __int128_t
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 20001; // 最大节点数
const int MAXM = 40001; // 最大边数

// 边的数组，存储边的终点
int to[MAXM];
// 存储每个节点的第一条边的索引
int head[MAXN];
// 存储边的下一条边的索引
int nextt[MAXM];
// 当前边的数量
int edge_count = 0;

void add_edge(int u, int v) {
    to[edge_count] = v;          // 设置边的终点
    nextt[edge_count] = head[u]; // 设置当前边的下一条边
    head[u] = edge_count++;      // 更新头指针
}

void display(int n) {
    for (int i = 1; i <= n; i++) {
        if (head[i] != -1) {
            cout << "Node " << i << ": ";
            for (int j = head[i]; j != -1; j = nextt[j]) {
                cout << to[j] << " ";
            }
            cout << "\n";
        }
    }
}

void solve() {
    int n, m; // n: 节点数，m: 边数
    cin >> n >> m;

    // 初始化头指针
    fill(head, head + MAXN, -1);

    for (int i = 0; i < m; i++) {
        int u, v; // 边 u -> v
        cin >> u >> v;
        add_edge(u, v);
        // 如果是无向图，可以再加一条边 add_edge(v, u);
    }

    // 显示图的结构
    display(n);
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