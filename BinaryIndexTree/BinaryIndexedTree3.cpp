#include <bits/stdc++.h>

//树状数组模版3，范围增加 + 范围查询
//https://www.luogu.com.cn/problem/P3372
using namespace std;

#define MAXN 100001

vector<long> info1(MAXN, 0);
vector<long> info2(MAXN, 0);

int n, m;

int lowbit(int i) {
    return i & -i;
}

void add(vector<long>& tree, int i, long v) {
    while (i <= MAXN) {
        tree[i] += v;
        i += lowbit(i);
    }
}

long sum(vector<long>& tree, int i) {
    long ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

void add(int l, int r, long v) {
    add(info1, l, v);
    add(info1, r + 1, -v);
    add(info2, l, (l - 1) * v);
    add(info2, r + 1, -r * v);
}

long long range(int l, int r) {
    return sum(info1, r) * r - sum(info2, r) - sum(info1, l - 1) * (l - 1) + sum(info2, l - 1);
}

int main() {
    cin >> n >> m;
    long cur;
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        cur = temp;
        add(i, i, cur);
    }
    long v;
    for (int i = 1, op, l, r; i <= m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> v;
            // 将区间 [l, r] 内每个数加上 k 
            add(l, r, v);
        }
        else {
            cin >> l >> r;
            // 输出 [l, r] 内每个数的和
            cout << range(l, r) << endl;
        }
    }

    return 0;
}
