#include <bits/stdc++.h>

// https://codeforces.com/problemset/problem/438/D
/*
1 l r 表示求 al 到 ar 的和
2 l r x 表示对区间 [l, r] 内每个数取模，模数为 x 
3 k x 表示将 ak 修改为 x
*/
// from: cpp.json
#define int long long
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 100001;
int arr[MAXN];
int sum[MAXN << 2];
int Max[MAXN << 2];

void up(int i){
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    Max[i] = max(Max[i << 1], Max[i << 1 | 1]);
}

void build(int l, int r, int i){
    if(l == r){
        sum[i] = Max[i] = arr[l];
    }else{
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i){
    if(jobl <= l && r <= jobr){
        return sum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if(jobl <= mid){
        ans += query(jobl, jobr, l, mid, i << 1);
    }
    if(jobr > mid){
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

void mod(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobv > Max[i]) {
        return;
    }
    if (l == r) {
        sum[i] %= jobv;
        Max[i] %= jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            mod(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            mod(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

void update(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        sum[i] = Max[i] = jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            update(jobi, jobv, l, mid, i << 1);
        } else {
            update(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }
    build(1, n, 1);
    for(int i = 1; i <= m; i++){
        int op;
        cin >> op;
        if(op == 1){
            int jobl, jobr;
            cin >> jobl >> jobr;
            cout << query(jobl, jobr, 1, n, 1) << "\n";
        }else if(op == 2){
            int jobl, jobr, jobv;
            cin >> jobl >> jobr >> jobv;
            mod(jobl, jobr, jobv, 1, n, 1);
        }else{
            int jobi, jobv;
            cin >> jobi >> jobv;
            update(jobi, jobv, 1, n, 1);
        }
    }

    return 0;
}