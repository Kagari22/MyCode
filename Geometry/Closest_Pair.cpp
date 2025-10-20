#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/5/CGL_5_A
// 给定 n 个点, 求出最近的两点距离
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

template<class T>
struct Point {
    T x; 
    T y; 

    Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}

    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }

    Point &operator+=(const Point &p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    
    Point &operator-=(const Point &p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    
    Point &operator*=(const T &v) & {
        x *= v;
        y *= v;
        return *this;
    }
    
    Point &operator/=(const T &v) & {
        x /= v;
        y /= v;
        return *this;
    }
    
    Point operator-() const {
        return Point(-x, -y);
    }
    
    friend Point operator+(Point a, const Point &b) {
        return a += b;
    }
    
    friend Point operator-(Point a, const Point &b) {
        return a -= b;
    }
    
    friend Point operator*(Point a, const T &b) {
        return a *= b;
    }
    
    friend Point operator/(Point a, const T &b) {
        return a /= b;
    }
    
    friend Point operator*(const T &a, Point b) {
        return b *= a;
    }
    
    friend bool operator==(const Point &a, const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
    
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
struct Line {
    Point<T> a;  
    Point<T> b;  
    Line(const Point<T> &a_ = Point<T>(), const Point<T> &b_ = Point<T>()) : a(a_), b(b_) {}
};

/*
    计算向量 a 和 b 的点积（内积）
    dot(a, b) = a.x*b.x + a.y*b.y
*/
template<class T>
T dot(const Point<T> &a, const Point<T> &b) {
    return a.x * b.x + a.y * b.y;
}

/*
    计算向量 a 和 b 的叉积（2D 向量的“伪叉积”）
    cross(a, b) = a.x*b.y - a.y*b.x
    正值表示 b 在 a 的逆时针方向，负值表示顺时针方向
*/
template<class T>
T cross(const Point<T> &a, const Point<T> &b) {
    return a.x * b.y - a.y * b.x;
}

/*
    计算点 p 的平方模：|p|^2 = dot(p, p)
*/
template<class T>
T square(const Point<T> &p) {
    return dot(p, p);
}

/*
    计算点 p 的长度（欧几里得范数），返回 double
*/
template<class T>
double length(const Point<T> &p) {
    return std::sqrt(square(p));
}

/*
    计算线段 l 的长度
    通过端点之差的长度来计算
*/
template<class T>
double length(const Line<T> &l) {
    return length(l.a - l.b);
}

/*
    将向量 p 归一化：返回单位向量 p/|p|
    注意：调用者需保证 p != (0,0)
*/
template<class T>
Point<T> normalize(const Point<T> &p) {
    return p / length(p);
}

/*
    判断两条直线（线段） l1, l2 是否平行
    平行当且仅当方向向量叉积为 0
*/
template<class T>
bool parallel(const Line<T> &l1, const Line<T> &l2) {
    return cross(l1.b - l1.a, l2.b - l2.a) == 0;
}

/*
    计算两点 a, b 之间的距离，等价于 |a - b|
*/
template<class T>
double distance(const Point<T> &a, const Point<T> &b) {
    return length(a - b);
}

using LD = long double;    
using P = Point<LD>;       

constexpr LD eps = 0;  

void solve() {
    int n;
    cin >> n;

    vector<P> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    sort(points.begin(), points.end(), [&](const P &a, const P &b) {
        return a.x < b.x;
    });

    vector<P> tmp;

    auto compute = [&](auto &&self, int l, int r) -> LD {
        if (r - l + 1 <= 3) {
            LD d = INF;
            for (int i = l; i <= r; i++) {
                for (int j = i + 1; j <= r; j++) {
                    d = min<LD>(d, (LD) distance(points[i], points[j]));
                }
            }
            sort(points.begin() + l, points.begin() + r + 1, [&](const P &a, const P &b) {
                return a.y < b.y;
            });
            return d;
        }

        int m = (l + r) >> 1;
        LD midx = points[m].x;
        LD d = min(self(self, l, m), self(self, m + 1, r));

        merge(points.begin() + l, points.begin() + m + 1, points.begin() + m + 1, points.begin() + r + 1, 
            back_inserter(tmp), [&](const P &a, const P &b) { return a.y < b.y; });

        copy(tmp.begin(), tmp.end(), points.begin() + l);
        tmp.clear();

        vector<P> b;
        for (int i = l; i <= r; i++) {
            if (fabs(points[i].x - midx) < d) {
                b.push_back(points[i]);
            }
        }

        for (int i = 0; i < b.size(); i++) {
            for (int j = i + 1; j < b.size() && j <= i + 7; j++) {
                d = min<LD>(d, distance(b[i], b[j]));
            }
        }

        return d;
    };

    LD ans = compute(compute, 0, n - 1);

    cout << fixed << setprecision(6) << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}