#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_A
// 给定两圆, 输出相交情况
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

void solve() {
    int c1x, c1y, c1r, c2x, c2y, c2r;
    cin >> c1x >> c1y >> c1r >> c2x >> c2y >> c2r;

    int dx = c1x - c2x;
    int dy = c1y - c2y;

    int d = dx * dx + dy * dy;
    int sum = c1r + c2r;
    int diff = llabs(c1r - c2r);

    if (d > sum * sum) {
        cout << 4 << '\n';
    } else if (d == sum * sum) {
        cout << 3 << '\n';
    } else if (d < diff * diff) {
        cout << 0 << '\n';
    } else if (d == diff * diff) {
        cout << 1 << '\n';
    } else {
        cout << 2 << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}