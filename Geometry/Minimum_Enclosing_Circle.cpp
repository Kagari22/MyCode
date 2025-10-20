#include <bits/stdc++.h>

//https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/5/CGL_5_B
// 求包围给定 n 个点的最小圆 (求解圆心和半径)
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

struct Circle {
    P o;       // 圆心
    LD r;      // 半径
    Circle(const P &o_ = {0, 0}, LD r_ = 0) : o(o_), r(r_) {}
};

// 判断点 q 是否在圆 C 内（允许误差 eps）
bool in_circle(const Circle &C, const P &q) {
    return square((q - C.o)) <= (C.r + 1e-12L) * (C.r + 1e-12L);
}

// 由两点构造圆
Circle circle_from_2(const P &A, const P &B) {
    P o = (A + B) / 2.0L;
    LD r = length(A - o);
    return {o, r};
}

// 由三点构造外接圆（假设不共线）
Circle circle_from_3(const P &A, const P &B, const P &C) {
    // 参考外接圆公式：交于垂直平分线
    LD a2 = square(B - C);
    LD b2 = square(C - A);
    LD c2 = square(A - B);
    LD alpha = a2 * (b2 + c2 - a2);
    LD beta  = b2 * (c2 + a2 - b2);
    LD gamma = c2 * (a2 + b2 - c2);
    P o = (alpha * A + beta * B + gamma * C) / (alpha + beta + gamma);
    return {o, length(o - A)};
}

// Welzl 递归
Circle welzl(int i, vector<P> &pts, vector<P> &R) {
    if (i == 0 || R.size() == 3) {
        // 基例：0, 1, 2, 3 个支撑点
        if (R.empty()) {
            return Circle({0, 0}, 0);
        }      
        if (R.size() == 1) {
            return Circle(R[0], 0);
        }
        if (R.size() == 2) {
            return circle_from_2(R[0], R[1]);
        }
        return circle_from_3(R[0], R[1], R[2]);
    }
    // 先求不含第 i−1 点的最小圆
    Circle D = welzl(i - 1, pts, R);
    // 若它已包含第 i−1 个点，则 D 即为前 i 点的最小圆
    if (in_circle(D, pts[i - 1])) {
        return D;
    }
    // 否则，第 i−1 点必在边界上，加入 R
    R.push_back(pts[i - 1]);
    Circle D2 = welzl(i - 1, pts, R);
    R.pop_back();
    return D2;
}

void solve() {
    int n;
    cin >> n;
    vector<P> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(points.begin(), points.end(), rng);

    // 递归求最小包围圆
    vector<P> R;
    Circle mec = welzl(n, points, R);

    cout << fixed << setprecision(6) << mec.o.x << " " << mec.o.y << " " << mec.r << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}