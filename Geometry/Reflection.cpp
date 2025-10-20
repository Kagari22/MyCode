#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_B
// 求一个点关于一条直线的对称点
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y): x(x), y(y) {}

    Point operator - (const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    Point operator + (const Point &b) const {
        return Point(x + b.x, y + b.y);
    }

    Point operator * (double t) const {
        return Point(x * t, y * t);
    }

    double dot(const Point &p) const {
        return x * p.x + y * p.y;
    }
};

void solve() {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    int q;
    cin >> q;

    Point p1 = (Point) {x1, y1};
    Point p2 = (Point) {x2, y2};

    auto calc = [&](Point p) -> Point {
        Point v = p2 - p1;
        Point u = p - p1;
        double t = u.dot(v) / v.dot(v);
        Point x = p1 + v * t;
        Point px = x - p;
        return x + px;   
    };

    while (q--) {
        double x, y;
        cin >> x >> y;
        Point p = (Point) {x, y};
        auto ans = calc(p);
        cout << fixed << setprecision(10) << ans.x << ' ' << ans.y << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}