#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_E
// 求两圆交点
// from: cpp.json
#define INF 8e18
#define int long long
#define LD long double
using namespace std;

void solve() {
    LD x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    LD dx = x2 - x1;
    LD dy = y2 - y1;

    LD d = sqrtl(dx * dx + dy * dy);
    LD exx = dx / d;
    LD exy = dy / d;

    LD a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    LD x0 = x1 + a * exx;
    LD y0 = y1 + a * exy;

    LD h2 = r1 * r1 - a * a;
    h2 = max<LD>(h2, 0L);

    LD h = sqrtl(h2);
    LD eyx = -exy;
    LD eyy = exx;

    pair<LD, LD> p1 = {x0 + h * eyx, y0 + h * eyy};
    pair<LD, LD> p2 = {x0 - h * eyx, y0 - h * eyy};

    if (fabsl(h) < 1e-15L) {
        p2 = p1;
    }

    if (p2 < p1) {
        swap(p1, p2);
    }

    cout << fixed << setprecision(20) << p1.first << ' ' << p1.second << ' ' << p2.first << ' ' << p2.second << '\n';
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