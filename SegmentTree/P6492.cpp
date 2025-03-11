#include <bits/stdc++.h>

// (R)LRLRL... 最长交替子串
// https://www.luogu.com.cn/problem/P6492
// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

const int MAXN = 200001;
int arr[MAXN];
// 交替最长子串长度
int len[MAXN << 2]; 
// 交替最长前缀长度
int pre[MAXN << 2];
// 交替最长后缀长度
int suf[MAXN << 2];

void up(int l, int r, int i) {
    len[i] = max(len[i << 1], len[i << 1 | 1]);
    pre[i] = pre[i << 1];
    suf[i] = suf[i << 1 | 1];

    int mid = (l + r) >> 1;
    // 左侧个数
    int ln = mid - l + 1;
    // 右侧个数
    int rn = r - mid;

    if (arr[mid] != arr[mid + 1]) {
        len[i] = max(len[i], suf[i << 1] + pre[i << 1 | 1]);
        if (len[i << 1] == ln) {
            pre[i] = ln + pre[i << 1 | 1];
        }
        if (len[i << 1 | 1] == rn) {
            suf[i] = rn + suf[i << 1];
        }
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        len[i] = 1;
        pre[i] = 1;
        suf[i] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(l, r, i);
    }
}

void rev(int jobi, int l, int r, int i) {
    if (l == r) {
        arr[jobi] ^= 1;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            rev(jobi, l, mid, i << 1);
        } else {
            rev(jobi, mid + 1, r, i << 1 | 1);
        }
        up(l, r, i);
    }
}

void solve(){
    int n, q;
    cin >> n >> q;

    build(1, n, 1);
    
    for (int i = 1; i <= q; i++) {
        int idx;
        cin >> idx;
        rev(idx, 1, n, 1);
        cout << len[1] << '\n';
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