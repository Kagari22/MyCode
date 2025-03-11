#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P4145
// from: cpp.json
#define int long long
#define ll long long
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
        sum[i] = arr[l];
        Max[i] = arr[l];
    }else{
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void Sqrt(int jobl, int jobr, int l, int r, int i){
    if(l == r){
        int s = sqrt(Max[i]);
        sum[i] = s;
        Max[i] = s;
    }else{
        int mid = (l + r) >> 1;
        if(jobl <= mid && Max[i << 1] > 1){
            Sqrt(jobl, jobr, l, mid, i << 1);
        }
        if(jobr > mid && Max[i << 1 | 1] > 1){
            Sqrt(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
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

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }
    build(1, n, 1);
    int m;
    cin >> m;
    for(int i = 1; i <= m; i++){
        int op, jobl, jobr;
        cin >> op >> jobl >> jobr;
        if(jobl > jobr){
            swap(jobl, jobr);
        }
        if(op == 0){
            Sqrt(jobl, jobr, 1, n, 1);
        }else{
            cout << query(jobl, jobr, 1, n, 1) << "\n";
        }
    }


    return 0;
}