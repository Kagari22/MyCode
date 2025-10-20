#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C
// 判断两线的位置关系
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

    double cross(const Point& p) const {
        return x * p.y - y * p.x;
    }

    double norm2() const {
        return x * x + y * y;
    }
};

void solve() {
    double x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;

    int q;
    cin >> q;

    Point p0 = (Point) {x0, y0};
    Point p1 = (Point) {x1, y1};

    const double EPS = 1e-10;

    while (q--) {
        double x, y;
        cin >> x >> y;
        Point p2 = (Point) {x, y};
        
        Point a = p1 - p0;
        Point b = p2 - p0;
        double c = a.cross(b);

        if (c > EPS) {
            cout << "COUNTER_CLOCKWISE\n";
        } else if (c < -EPS) {
            cout << "CLOCKWISE\n";
        } else {
            // c≈0，共线，进入点积/距离判断
            if (a.dot(b) < 0) {
                cout << "ONLINE_BACK\n";
            } else if (a.norm2() < b.norm2()) {
                cout << "ONLINE_FRONT\n";
            } else {
                cout << "ON_SEGMENT\n";
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}