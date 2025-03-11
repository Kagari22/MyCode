#include <bits/stdc++.h>

// 并查集模板
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

struct DSU {
    vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    DSU dsu(n);

    // a[a[i]] == i 存在自循环 即有环
    // vector<int> e(n);
    // e[dsu.find(i)] = 1; 标记父节点为 0 即表示无环其为链式结构 1 则代表有环 
    // dsu.find(i) == i 
    /*
    for (int i = 0; i < n; i++) {
        if (a[a[i]] == i) { 成环且节点数小于等于 2 -> 为链式结构 大于 2 为环，要加到 min 里
            e[dsu.find(i)] = 1; 标记父节点 代表此集合为链式结构 
            chain = true; 有链式结构 最终 mn 要 +1
        }
    }
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i) {  代表该节点是此集合的父节点 即该集合的代表 即有一个联通块
            if (!e[i]) { 包含有大于 2 个节点的环
                min++; 
            }
            max++; 
        }
    }
    */
    // 注意 merge 的是下标 而不是其值
    

    return 0;
}