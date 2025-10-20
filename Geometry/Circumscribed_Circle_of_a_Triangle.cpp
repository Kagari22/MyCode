#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_C
// 求给定三角形的外接圆的坐标和半径
// from: cpp.json
#define INF 8e18
#define int long long
#define LD long double
using namespace std;

void solve() {
    LD x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    auto dist = [&](LD X1, LD Y1, LD X2, LD Y2) -> LD {
        LD dx = X1 - X2;
        LD dy = Y1 - Y2;
        return sqrtl(dx * dx + dy * dy);
    };

    LD d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    LD x1sq = x1 * x1 + y1 * y1;
    LD x2sq = x2 * x2 + y2 * y2;
    LD x3sq = x3 * x3 + y3 * y3;

    LD cx = (x1sq * (y2 - y3) + x2sq * (y3 - y1) + x3sq * (y1 - y2)) / d;
    LD cy = (x1sq * (x3 - x2) + x2sq * (x1 - x3) + x3sq * (x2 - x1)) / d;

    LD r = dist(cx, cy, x1, y1);

    cout << fixed << setprecision(20) << cx << ' ' << cy << ' ' << r << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}