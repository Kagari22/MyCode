#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_D
// 求直线和圆的交点
// from: cpp.json
#define INF 8e18
#define int long long
#define LD long double
using namespace std;

void solve() {
    int cx, cy, r;
    cin >> cx >> cy >> r;

    int q;
    cin >> q;
    cout << fixed << setprecision(20);

    while (q--) {
        LD x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        LD dx = x2 - x1, dy = y2 - y1;
        LD A = dx * dx + dy * dy;
        LD B = 2 * (dx * (x1 - cx) + dy * (y1 - cy));
        LD C0 = (x1 - cx) * (x1 - cx) + (y1 - cy) * (y1 - cy) - r * r;

        LD disc = B * B - 4 * A * C0;
        LD sqrtD = sqrtl(max((LD) 0, disc));

        LD t1 = (-B - sqrtD) / (2 * A);
        LD t2 = (-B + sqrtD) / (2 * A);

        pair<LD, LD> P1 = {x1 + dx * t1, y1 + dy * t1};
        pair<LD, LD> P2 = {x1 + dx * t2, y1 + dy * t2};

        if (fabsl(disc) < 1e-15L) {
            P2 = P1;
        }

        if (P2 < P1) {
            swap(P1, P2);
        }

        cout << P1.first << ' ' << P1.second << ' ' << P2.first << ' ' << P2.second << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}