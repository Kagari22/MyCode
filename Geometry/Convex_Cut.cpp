#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_C
// 给定一个凸多边形, 输出其被直线 p1p2 切割的左侧多边形面积
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

struct Point {
    double x, y;
};

// 计算 (B-A)×(C-A)
double cross(const Point &A, const Point &B, const Point &C) {
    return (B.x - A.x) * (C.y - A.y)
         - (B.y - A.y) * (C.x - A.x);
}

// 计算线段 AB 与直线 P1P2 的交点
Point intersect(const Point &A, const Point &B,
                const Point &P1, const Point &P2) {
    double c1 = cross(P1, P2, A);
    double c2 = cross(P1, P2, B);
    double t = c1 / (c1 - c2);
    return { A.x + t * (B.x - A.x),
             A.y + t * (B.y - A.y) };
}

// 对多边形 poly（逆时针）按直线 P1→P2 裁剪，返回左侧多边形
vector<Point> clipPolygon(const vector<Point> &poly, const Point &P1, const Point &P2) {
    vector<Point> out;
    int m = poly.size();
    for (int i = 0; i < m; i++) {
        Point A = poly[i];
        Point B = poly[(i+1)%m];
        double cA = cross(P1, P2, A);
        double cB = cross(P1, P2, B);
        if (cA >= 0 && cB >= 0) {
            out.push_back(B);
        } else if (cA >= 0 && cB < 0) {
            Point I = intersect(A, B, P1, P2);
            out.push_back(I);
        } else if (cA < 0 && cB >= 0) {
            Point I = intersect(A, B, P1, P2);
            out.push_back(I);
            out.push_back(B);
        }
    }
    return out;
}

// 计算多边形面积（有向）
double polygonArea(const vector<Point> &poly) {
    int k = poly.size();
    double s = 0;
    for (int i = 0; i < k; i++) {
        int j = (i + 1) % k;
        s += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabs(s) * 0.5;
}

void solve() {
    int n;
    cin >> n;

    vector<Point> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i].x >> g[i].y;
    }

    int q;
    cin >> q;

    while (q--) {
        Point p1, p2;
        cin >> p1.x >> p1.y >> p2.x >> p2.y;
        auto clipped = clipPolygon(g, p1, p2);
        auto area = clipped.empty() ? 0.0 : polygonArea(clipped);
        cout << fixed << setprecision(10) << area << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}