#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P3740
// from: cpp.json
#define int long long
#define i32 __int32_t
#define i64 long long
#define i128 __int128_t
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 1001;
int pl[MAXN];
int pr[MAXN];
int nums[MAXN << 2];
int poster[MAXN << 4];
bool visited[MAXN];

int collect(int m) {
    sort(nums + 1, nums + m + 1);
    int size = 1;
    for (int i = 2; i <= m; i++) {
        if (nums[size] != nums[i]) {
            nums[++size] = nums[i];
        }
    }
    int cnt = size;
    for (int i = 2; i <= size; i++) {
        if (nums[i - 1] + 1 < nums[i]) {
            nums[++cnt] = nums[i - 1] + 1;
        }
    }
    sort(nums + 1, nums + cnt + 1);
    return cnt;
}

int rankk(int l, int r, int v) {
    int m;
    int ans = 0;
    while (l <= r) {
        m = (l + r) >> 1;
        if (nums[m] >= v) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

void down(int i) {
    if (poster[i] != 0) {
        poster[i << 1] = poster[i];
        poster[i << 1 | 1] = poster[i];
        poster[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    poster[i] = 0;
}

void update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        poster[i] = jobv;
    } else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (l == r) {
        if (poster[i] != 0 && !visited[poster[i]]) {
            visited[poster[i]] = true;
            return 1;
        } else {
            return 0;
        }
    } else {
        down(i);
        int mid = (l + r) >> 1;
        int ans = 0;
        if (jobl <= mid) {
            ans += query(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}

void solve(){
    int n, m;
    cin >> n >> m;
    int size = 0;
    nums[++size] = n;
    for (int i = 1; i <= m; i++) {
        cin >> pl[i] >> pr[i];
        nums[++size] = pl[i];
        nums[++size] = pr[i];
    }
    size = collect(size);
    build(1, size, 1);
    for (int i = 1; i <= m; i++) {
        int jobl = rankk(1, size, pl[i]);
        int jobr = rankk(1, size, pr[i]);
        update(jobl, jobr, i, 1, size, 1);
    }
    cout << query(1, rankk(1, size, n), 1, size, 1);
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