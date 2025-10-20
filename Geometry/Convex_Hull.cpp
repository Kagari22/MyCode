#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_A
// 求出给定点集 P 的凸包
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

template<class T>
struct Point {
    T x;  // x 坐标
    T y;  // y 坐标

    // 构造函数，默认为 (0, 0)
    Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}

    // 模板化类型转换构造函数，可将 Point<T> 转换为 Point<U>
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }

    // 重载 += 运算符：向量加法
    Point &operator+=(const Point &p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    
    // 重载 -= 运算符：向量减法
    Point &operator-=(const Point &p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    
    // 重载 *= 运算符：数乘
    Point &operator*=(const T &v) & {
        x *= v;
        y *= v;
        return *this;
    }
    
    // 重载 /= 运算符：数除
    Point &operator/=(const T &v) & {
        x /= v;
        y /= v;
        return *this;
    }
    
    // 取负号：返回 (-x, -y)
    Point operator-() const {
        return Point(-x, -y);
    }
    
    // 友元函数，实现 a + b
    friend Point operator+(Point a, const Point &b) {
        return a += b;
    }
    
    // 友元函数，实现 a - b
    friend Point operator-(Point a, const Point &b) {
        return a -= b;
    }
    
    // 友元函数，实现 a * scalar
    friend Point operator*(Point a, const T &b) {
        return a *= b;
    }
    
    // 友元函数，实现 a / scalar
    friend Point operator/(Point a, const T &b) {
        return a /= b;
    }
    
    // 友元函数，实现 scalar * b
    friend Point operator*(const T &a, Point b) {
        return b *= a;
    }
    
    // 相等判断：仅当 x 和 y 都相同时返回 true
    friend bool operator==(const Point &a, const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
    
    // 输入流重载，从输入流读取 x 和 y
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    
    // 输出流重载，以 "(x, y)" 的格式输出
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

/*
    定义一条线段（或直线）的模板结构体：
    由两个 Point<T> 类型的端点 a、b 定义
*/
template<class T>
struct Line {
    Point<T> a;  // 端点 A
    Point<T> b;  // 端点 B
    // 构造函数，默认是两个 (0,0) 的点
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

/*
    计算点 p 到直线 l（通过 l.a 和 l.b 定义）的垂线距离
    distancePL = |cross(l.a-l.b, l.a-p)| / |l|
*/
template<class T>
double distancePL(const Point<T> &p, const Line<T> &l) {
    return std::abs(cross(l.a - l.b, l.a - p)) / length(l);
}

/*
    计算点 p 到线段 l 的最短距离
    如果垂足在线段内部，返回垂线距离；否则返回到最近端点的距离
*/
template<class T>
double distancePS(const Point<T> &p, const Line<T> &l) {
    // 如果 p 在 l.a 的“后方”，距离为 p 到 l.a
    if (dot(p - l.a, l.b - l.a) < 0) {
        return distance(p, l.a);
    }
    // 如果 p 在 l.b 的“后方”，距离为 p 到 l.b
    if (dot(p - l.b, l.a - l.b) < 0) {
        return distance(p, l.b);
    }
    // 否则垂足在线段内部，使用垂线距离
    return distancePL(p, l);
}

/*
    将点 (x, y) 绕原点逆时针旋转 90 度，得到 (-y, x)
*/
template<class T>
Point<T> rotate(const Point<T> &a) {
    return Point(-a.y, a.x);
}

/*
    对向量 a 做象限分类：
    - 如果 a.y > 0，返回 1
    - 如果 a.y == 0 且 a.x > 0，返回 1
    - 否则返回 -1
    用于 half-plane 排序时，将向量分到“上半平面”或“下半平面”
*/
template<class T>
int sgn(const Point<T> &a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

/*
    判断点 p 是否在直线（有向） l 的左侧
    cross(l.b - l.a, p - l.a) > 0 则 p 在 l 左侧
*/
template<class T>
bool pointOnLineLeft(const Point<T> &p, const Line<T> &l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

/*
    计算两条直线（或延长线） l1 和 l2 的交点
    参数：
        l1: 直线1，通过 l1.a, l1.b
        l2: 直线2，通过 l2.a, l2.b
    返回值：
        交点坐标 = l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.b - l1.a))
    需要保证两直线不平行，否则除以 0
*/
template<class T>
Point<T> lineIntersection(const Line<T>& L1, const Line<T>& L2) {
    // d1 = L1.b - L1.a, d2 = L2.b - L2.a
    Point<T> d1 = L1.b - L1.a;
    Point<T> d2 = L2.b - L2.a;
    // 分母：d1 × d2
    T den = cross(d1, d2);
    // 分子：(L2.a - L1.a) × d2
    T num = cross(L2.a - L1.a, d2);
    // 题目保证 den != 0，所以直接用
    T t = num / den;
    return L1.a + d1 * t;
}

/*
    判断点 p 是否在线段 l 上（闭区间）
    条件：
      1) p 与 l.a, l.b 共线：cross(p - l.a, l.b - l.a) == 0
      2) p.x 在 [min(l.a.x, l.b.x), max(l.a.x, l.b.x)] 范围内
      3) p.y 在 [min(l.a.y, l.b.y), max(l.a.y, l.b.y)] 范围内
*/
template<class T>
bool pointOnSegment(const Point<T> &p, const Line<T> &l) {
    return cross(p - l.a, l.b - l.a) == 0
        && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
        && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

/*
    判断点 a 是否在简单多边形 p 内部或边界上
    使用射线法(or 奇偶性算法)：
      1) 若 a 在任意一个边的线段上，则视为在多边形内，直接返回 true
      2) 否则，对从 a 向 +X 方向发射一条水平射线，统计与多边形边的交点个数
         - 若交点数为奇数，则在内部；为偶数，则在外部
    注意：为了避免射线与顶点共线带来的歧义，使用如下两种情况分别异或计数
*/
template<class T>
bool pointInPolygon(const Point<T> &a, const std::vector<Point<T>> &p) {
    int n = p.size();
    // 先检查是否在任意边线上
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    // 射线交点计数
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        // 如果边 (u->v) 从左下方穿过射线
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;  // 交点数 +1 (异或翻转)
        }
        // 如果边 (u->v) 从右下方穿过射线
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;  // 交点数 +1 (异或翻转)
        }
    }
    return t == 1;
}

/*
    计算两条线段 l1, l2 的相交情况
    返回值：tuple{type, p1, p2}
      type = 0: 不相交
      type = 1: 普通相交（在内部相交），交点为 p1==p2
      type = 2: 重叠（共线且有重叠区间），重叠区间端点为 p1, p2
      type = 3: 在端点相交（恰好在某个端点相交），交点为 p1==p2
    具体步骤：
      1) 先用包围盒快速排除：如果两个包围盒不重叠，返回 0
      2) 计算两条线段方向向量叉积，若为 0，则可能共线或平行
         - 如果不共线，返回 0
         - 如果共线，则按区间重叠来判断是 2 还是 3
      3) 非共线时，计算四个叉积 (cp1, cp2, cp3, cp4)，判断是否跨立
         - 若不跨立，返回 0
         - 若跨立，计算交点 p = lineIntersection(...)
           - 若四个叉积都不为 0，返回 type=1
           - 否则必然是类型 3，在端点相交
*/
template<class T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(const Line<T> &l1, const Line<T> &l2) {
    // 包围盒检查：如果 l1 最大 x 坐标 < l2 最小 x，则不可能相交
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    // 如果 l1 最小 x > l2 最大 x，排除
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    // 如果 l1 最大 y < l2 最小 y，排除
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    // 如果 l1 最小 y > l2 最大 y，排除
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    // 计算方向向量叉积
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        // 如果在同一直线上（共线）
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            // 平行但不共线
            return {0, Point<T>(), Point<T>()};
        } else {
            // 共线：找出重叠的区间端点
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            // 重叠区间的左下端点
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            // 重叠区间的右上端点
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            // 如果 p1 不在线段 l1 上，则将 y 坐标交换，使得真正的重叠端点为 p2
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            // 如果 p1 == p2，则只有一个公共端点，返回 type=3
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                // 否则返回重叠区间 (p1, p2)，type = 2
                return {2, p1, p2};
            }
        }
    }
    // 非共线：计算四个叉积，判断跨立
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);

    // 如果不跨立，则不相交
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) ||
        (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }
    // 计算交点
    Point<T> p = lineIntersection(l1, l2);
    // 如果四个叉积都不为 0，则是普通相交
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) {
        return {1, p, p};
    } else {
        // 否则是端点相交
        return {3, p, p};
    }
}

/*
    计算两条线段 l1 和 l2 之间的最短距离
    如果相交则距离为 0；否则取各自端点到对方线段的最短距离中的最小值
*/
template<class T>
double distanceSS(const Line<T> &l1, const Line<T> &l2) {
    if (std::get<0>(segmentIntersection(l1, l2)) != 0) {
        // 有任何形式的相交
        return 0.0;
    }
    // 不相交时，计算 4 种端点-线段距离，取最小值
    return std::min({
        distancePS(l1.a, l2),
        distancePS(l1.b, l2),
        distancePS(l2.a, l1),
        distancePS(l2.b, l1)
    });
}

/*
    判断线段 l 是否完全在简单多边形 p 内部（含边界）
    逻辑：
      1) 先判断 l 的两端点是否在多边形内部或边界上，若有一个不在，则返回 false
      2) 对多边形的每条边做相交检测：
         - 如果类型为 1（严格相交），则 l 与该边在内部相交，返回 false
         - 如果类型为 2（重叠），需要进一步判断重叠部分是否在合法范围内：
           如果重叠的顶点 v 既不等于 l.a 且不等于 l.b，并且与该顶点相关的内角为凸角，则返回 false
         - 如果类型为 3（端点相交），需判断交点是否在合法位置，否则返回 false
      3) 如果遍历完所有边仍未返回 false，则说明线段在多边形内
*/
template<class T>
bool segmentInPolygon(const Line<T> &l, const std::vector<Point<T>> &p) {
    int n = p.size();
    // 1) 两个端点必须都在多边形内部或边界上
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }

    // 2) 遍历多边形的每一条边
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        // 计算 l 与多边形边 (u->v) 的相交情况
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));

        if (t == 1) {
            // 严格相交（在边的内部相交），线段不在多边形内
            return false;
        }
        if (t == 0) {
            // 不相交，检验下一条边
            continue;
        }
        if (t == 2) {
            // 重叠：重叠的区间端点是 p1, p2
            // 如果重叠的顶点 v 既不等于 l.a 且不等于 l.b
            // 并且在该顶点处的内角是凸角 (cross(v-u, w-v) > 0)，则线段越界
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            // t == 3：端点相交
            // 如果交点 p1 既不等于 u 也不等于 v，则说明交在边的内部
            if (p1 != u && p1 != v) {
                // 如果 l 的端点在该边的“左侧”，说明 l 部分在外部
                if (pointOnLineLeft(l.a, Line(v, u)) || pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                // 交点在顶点 v 处，需要判断与 v 相邻的两条边 (u-v) 和 (v-w) 的位置关系
                if (l.a == v) {
                    // 交点在 l.a
                    if (pointOnLineLeft(u, l)) {
                        // u 在 l 的左侧
                        if (pointOnLineLeft(w, l) && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        // u 在 l 的右侧或共线
                        if (pointOnLineLeft(w, l) || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    // 交点在 l.b
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        // u 相对于（l.b->l.a）的左侧
                        if (pointOnLineLeft(w, Line(l.b, l.a)) && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        // u 相对于（l.b->l.a）的右侧或共线
                        if (pointOnLineLeft(w, Line(l.b, l.a)) || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    // 交点在 v，但既不等于 l.a 也不等于 l.b：
                    // 此时 l 穿过 v，判断 u 和 w 两边是否进入多边形外部
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a)) || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l) || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    // 如果所有边都检查完毕，没有发现越界情况，则线段在多边形内
    return true;
}

/*
    half-plane intersection（半平面交，求凸多边形的顶点序列）
    输入：一组有向直线（通常是边界线，每条线的左侧是合法区域）
    输出：凸多边形的顶点顺序（逆时针或顺时针，依实现而定）
    算法思路（常见的双端队列实现）：
      1) 按极角排序：先比较方向向量落在哪个半平面，再比较叉积确定顺序
      2) 枚举排序后每条直线，用一个双端队列维护当前半平面交的边集合
      3) 每加一条线时，从队首和队尾弹出不满足“左侧”条件的交点
      4) 最后队列剩余的边会形成一个稳态的凸多边形
*/
template<class T>
std::vector<Point<T>> hp(std::vector<Line<T>> lines) {
    // 1) 先按照极角排序
    std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        // 计算方向向量 d1, d2
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        // 如果一个在上半平面，另一个在下半平面，上半平面排前
        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }
        // 否则按 d1 vs d2 的叉积大者排前 (逆时针排序)
        return cross(d1, d2) > 0;
    });

    deque<Line<T>> ls;    // 存储当前半平面交的边
    deque<Point<T>> ps;   // 存储对应的交点

    for (auto l : lines) {
        if (ls.empty()) {
            // 队列为空时直接加入
            ls.push_back(l);
            continue;
        }
        // 从尾部弹出：如果最后一个交点不在新半平面的左侧，则移除
        while (!ps.empty() && !pointOnLineLeft(ps.back(), l)) {
            ps.pop_back();
            ls.pop_back();
        }
        // 从头部弹出：如果最前一个交点不在新半平面的左侧，则移除
        while (!ps.empty() && !pointOnLineLeft(ps.front(), l)) {
            ps.pop_front();
            ls.pop_front();
        }
        // 如果新直线和平行队尾直线同向，则只保留一条
        if (!ls.empty() && cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            // 同向：保留方向更“内”的那条
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                // 如果队尾直线的 a 不在当前新半平面左侧，则替换
                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);  // 确保队列中只有这一条线
                    ls[0] = l;
                }
                continue;
            }
            // 反向：说明无解
            return {};
        }
        // 计算新线与队尾直线的交点，加入交点队列
        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }
    // 最后收尾：去除不满足条件的交点
    while (!ps.empty() && !pointOnLineLeft(ps.back(), ls[0])) {
        ps.pop_back();
        ls.pop_back();
    }
    // 如果有效直线少于等于 2，则无解或退化
    if (ls.size() <= 2) {
        return {};
    }
    // 加入首尾两条直线的交点，完成多边形闭合
    ps.push_back(lineIntersection(ls[0], ls.back()));

    // 返回最终的交点序列，即凸多边形的顶点列表
    return vector<Point<T>>(ps.begin(), ps.end());
}

using LD = long double;    
using P = Point<LD>;       

constexpr LD eps = 0; 

// 凸包 (Convex Hull) 求法：Andrew 算法（Monotone Chain）
// 输入：points - 任意点集
// 输出：按逆时针顺序返回凸包顶点列表，如果所有点共线则返回所有点

vector<P> convexHull(vector<P> points) {
    int n = points.size();
    // 小于等于 1 个点，直接返回
    if (n <= 1) {
        return points;
    }
    // 1) 按 x 再 y 升序排序，为构造上下链做准备
    sort(points.begin(), points.end(), [](auto &a, auto &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    // 去重
    points.erase(unique(points.begin(), points.end()), points.end());
    n = points.size();

    // 2) 检测退化——所有点共线
    bool alline = true;
    for (int i = 2; i < n; i++) {
        // 如果第 i 个点不在 points[0]-points[1] 直线上，则不是共线
        if (cross(points[1] - points[0], points[i] - points[0]) != 0) {
            alline = false;
            break;
        }
    }
    // 共线时直接返回排序后的所有点
    if (alline) {
        return {points.front(), points.back()};
    }

    vector<P> lower, upper;
    // 3) 构造下凸包
    // 从左到右扫描所有点
    for (auto &p : points) {
        // 判断最后两条边与新点是否产生右转（违背凸包的逆时针顺序）
        while (lower.size() >= 2) {
            int m = lower.size();
            P a = lower[m - 2];
            P b = lower[m - 1];
            if (cross(b - a, p - b) < 0) {
                // 右转：移除中间点 b
                lower.pop_back();
            } else {
                break;
            }
        }
        lower.push_back(p);
    }
    // 4) 构造上凸包
    // 从右到左扫描所有点
    for (int i = n - 1; i >= 0; i--) {
        auto &p = points[i];
        while (upper.size() >= 2) {
            int m = upper.size();
            P a = upper[m - 2];
            P b = upper[m - 1];
            if (cross(b - a, p - b) < 0) {
                upper.pop_back();
            } else {
                break;
            }
        }
        upper.push_back(p);
    }
    // 5) 合并下凸包和上凸包
    // 去掉尾部重复点，再拼接两段
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

void solve() {
    int n;
    cin >> n;

    vector<P> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    auto hull = convexHull(points);
    int m = hull.size();
    int si = 0;
    for (int i = 1; i < m; i++) {
        if (hull[i].y < hull[si].y || (hull[i].y == hull[si].y && hull[i].x < hull[si].x)) {
            si = i;
        }
    }

    cout << m << "\n";
    for (int k = 0; k < m; k++) {
        const P &p = hull[(si + k) % m];
        cout << p.x << " " << p.y << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }

    return 0;
}