#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_B
// 输出一个三角形内切圆的圆心坐标和半径
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

    LD a = dist(x2, y2, x3, y3);
    LD b = dist(x3, y3, x1, y1);
    LD c = dist(x1, y1, x2, y2);

    LD p = a + b + c;

    LD cx = (a * x1 + b * x2 + c * x3) / p;
    LD cy = (a * y1 + b * y2 + c * y3) / p;

    LD area = fabsl((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) * 0.5L;

    LD s = p * 0.5L;
    LD r = area / s;

    cout << fixed << setprecision(20) << cx << ' ' << cy << ' ' << r << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}